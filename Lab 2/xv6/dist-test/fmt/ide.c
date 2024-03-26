3700 // Simple PIO-based (non-DMA) IDE driver code.
3701 
3702 #include "types.h"
3703 #include "defs.h"
3704 #include "param.h"
3705 #include "memlayout.h"
3706 #include "mmu.h"
3707 #include "proc.h"
3708 #include "x86.h"
3709 #include "traps.h"
3710 #include "spinlock.h"
3711 #include "sleeplock.h"
3712 #include "fs.h"
3713 #include "buf.h"
3714 
3715 #define SECTOR_SIZE   512
3716 #define IDE_BSY       0x80
3717 #define IDE_DRDY      0x40
3718 #define IDE_DF        0x20
3719 #define IDE_ERR       0x01
3720 
3721 #define IDE_CMD_READ  0x20
3722 #define IDE_CMD_WRITE 0x30
3723 #define IDE_CMD_RDMUL 0xc4
3724 #define IDE_CMD_WRMUL 0xc5
3725 
3726 // idequeue points to the buf now being read/written to the disk.
3727 // idequeue->qnext points to the next buf to be processed.
3728 // You must hold idelock while manipulating queue.
3729 
3730 static struct spinlock idelock;
3731 static struct buf *idequeue;
3732 
3733 static int havedisk1;
3734 static void idestart(struct buf*);
3735 
3736 // Wait for IDE disk to become ready.
3737 static int
3738 idewait(int checkerr)
3739 {
3740   int r;
3741 
3742   while(((r = inb(0x1f7)) & (IDE_BSY|IDE_DRDY)) != IDE_DRDY)
3743     ;
3744   if(checkerr && (r & (IDE_DF|IDE_ERR)) != 0)
3745     return -1;
3746   return 0;
3747 }
3748 
3749 
3750 void
3751 ideinit(void)
3752 {
3753   int i;
3754 
3755   initlock(&idelock, "ide");
3756   picenable(IRQ_IDE);
3757   ioapicenable(IRQ_IDE, ncpu - 1);
3758   idewait(0);
3759 
3760   // Check if disk 1 is present
3761   outb(0x1f6, 0xe0 | (1<<4));
3762   for(i=0; i<1000; i++){
3763     if(inb(0x1f7) != 0){
3764       havedisk1 = 1;
3765       break;
3766     }
3767   }
3768 
3769   // Switch back to disk 0.
3770   outb(0x1f6, 0xe0 | (0<<4));
3771 }
3772 
3773 // Start the request for b.  Caller must hold idelock.
3774 static void
3775 idestart(struct buf *b)
3776 {
3777   if(b == 0)
3778     panic("idestart");
3779   if(b->blockno >= FSSIZE)
3780     panic("incorrect blockno");
3781   int sector_per_block =  BSIZE/SECTOR_SIZE;
3782   int sector = b->blockno * sector_per_block;
3783   int read_cmd = (sector_per_block == 1) ? IDE_CMD_READ :  IDE_CMD_RDMUL;
3784   int write_cmd = (sector_per_block == 1) ? IDE_CMD_WRITE : IDE_CMD_WRMUL;
3785 
3786   if (sector_per_block > 7) panic("idestart");
3787 
3788   idewait(0);
3789   outb(0x3f6, 0);  // generate interrupt
3790   outb(0x1f2, sector_per_block);  // number of sectors
3791   outb(0x1f3, sector & 0xff);
3792   outb(0x1f4, (sector >> 8) & 0xff);
3793   outb(0x1f5, (sector >> 16) & 0xff);
3794   outb(0x1f6, 0xe0 | ((b->dev&1)<<4) | ((sector>>24)&0x0f));
3795   if(b->flags & B_DIRTY){
3796     outb(0x1f7, write_cmd);
3797     outsl(0x1f0, b->data, BSIZE/4);
3798   } else {
3799     outb(0x1f7, read_cmd);
3800   }
3801 }
3802 
3803 // Interrupt handler.
3804 void
3805 ideintr(void)
3806 {
3807   struct buf *b;
3808 
3809   // First queued buffer is the active request.
3810   acquire(&idelock);
3811   if((b = idequeue) == 0){
3812     release(&idelock);
3813     // cprintf("spurious IDE interrupt\n");
3814     return;
3815   }
3816   idequeue = b->qnext;
3817 
3818   // Read data if needed.
3819   if(!(b->flags & B_DIRTY) && idewait(1) >= 0)
3820     insl(0x1f0, b->data, BSIZE/4);
3821 
3822   // Wake process waiting for this buf.
3823   b->flags |= B_VALID;
3824   b->flags &= ~B_DIRTY;
3825   wakeup(b);
3826 
3827   // Start disk on next buf in queue.
3828   if(idequeue != 0)
3829     idestart(idequeue);
3830 
3831   release(&idelock);
3832 }
3833 
3834 // Sync buf with disk.
3835 // If B_DIRTY is set, write buf to disk, clear B_DIRTY, set B_VALID.
3836 // Else if B_VALID is not set, read buf from disk, set B_VALID.
3837 void
3838 iderw(struct buf *b)
3839 {
3840   struct buf **pp;
3841 
3842   if(!holdingsleep(&b->lock))
3843     panic("iderw: buf not locked");
3844   if((b->flags & (B_VALID|B_DIRTY)) == B_VALID)
3845     panic("iderw: nothing to do");
3846   if(b->dev != 0 && !havedisk1)
3847     panic("iderw: ide disk 1 not present");
3848 
3849   acquire(&idelock);  //DOC:acquire-lock
3850   // Append b to idequeue.
3851   b->qnext = 0;
3852   for(pp=&idequeue; *pp; pp=&(*pp)->qnext)  //DOC:insert-queue
3853     ;
3854   *pp = b;
3855 
3856   // Start disk if necessary.
3857   if(idequeue == b)
3858     idestart(b);
3859 
3860   // Wait for request to finish.
3861   while((b->flags & (B_VALID|B_DIRTY)) != B_VALID){
3862     sleep(b, &idelock);
3863   }
3864 
3865   release(&idelock);
3866 }
3867 
3868 
3869 
3870 
3871 
3872 
3873 
3874 
3875 
3876 
3877 
3878 
3879 
3880 
3881 
3882 
3883 
3884 
3885 
3886 
3887 
3888 
3889 
3890 
3891 
3892 
3893 
3894 
3895 
3896 
3897 
3898 
3899 
