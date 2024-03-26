3900 // Buffer cache.
3901 //
3902 // The buffer cache is a linked list of buf structures holding
3903 // cached copies of disk block contents.  Caching disk blocks
3904 // in memory reduces the number of disk reads and also provides
3905 // a synchronization point for disk blocks used by multiple processes.
3906 //
3907 // Interface:
3908 // * To get a buffer for a particular disk block, call bread.
3909 // * After changing buffer data, call bwrite to write it to disk.
3910 // * When done with the buffer, call brelse.
3911 // * Do not use the buffer after calling brelse.
3912 // * Only one process at a time can use a buffer,
3913 //     so do not keep them longer than necessary.
3914 //
3915 // The implementation uses two state flags internally:
3916 // * B_VALID: the buffer data has been read from the disk.
3917 // * B_DIRTY: the buffer data has been modified
3918 //     and needs to be written to disk.
3919 
3920 #include "types.h"
3921 #include "defs.h"
3922 #include "param.h"
3923 #include "spinlock.h"
3924 #include "sleeplock.h"
3925 #include "fs.h"
3926 #include "buf.h"
3927 
3928 struct {
3929   struct spinlock lock;
3930   struct buf buf[NBUF];
3931 
3932   // Linked list of all buffers, through prev/next.
3933   // head.next is most recently used.
3934   struct buf head;
3935 } bcache;
3936 
3937 void
3938 binit(void)
3939 {
3940   struct buf *b;
3941 
3942   initlock(&bcache.lock, "bcache");
3943 
3944   // Create linked list of buffers
3945   bcache.head.prev = &bcache.head;
3946   bcache.head.next = &bcache.head;
3947   for(b = bcache.buf; b < bcache.buf+NBUF; b++){
3948     b->next = bcache.head.next;
3949     b->prev = &bcache.head;
3950     initsleeplock(&b->lock, "buffer");
3951     bcache.head.next->prev = b;
3952     bcache.head.next = b;
3953   }
3954 }
3955 
3956 // Look through buffer cache for block on device dev.
3957 // If not found, allocate a buffer.
3958 // In either case, return locked buffer.
3959 static struct buf*
3960 bget(uint dev, uint blockno)
3961 {
3962   struct buf *b;
3963 
3964   acquire(&bcache.lock);
3965 
3966   // Is the block already cached?
3967   for(b = bcache.head.next; b != &bcache.head; b = b->next){
3968     if(b->dev == dev && b->blockno == blockno){
3969       b->refcnt++;
3970       release(&bcache.lock);
3971       acquiresleep(&b->lock);
3972       return b;
3973     }
3974   }
3975 
3976   // Not cached; recycle some unused buffer and clean buffer
3977   // "clean" because B_DIRTY and not locked means log.c
3978   // hasn't yet committed the changes to the buffer.
3979   for(b = bcache.head.prev; b != &bcache.head; b = b->prev){
3980     if(b->refcnt == 0 && (b->flags & B_DIRTY) == 0) {
3981       b->dev = dev;
3982       b->blockno = blockno;
3983       b->flags = 0;
3984       b->refcnt = 1;
3985       release(&bcache.lock);
3986       acquiresleep(&b->lock);
3987       return b;
3988     }
3989   }
3990   panic("bget: no buffers");
3991 }
3992 
3993 
3994 
3995 
3996 
3997 
3998 
3999 
4000 // Return a locked buf with the contents of the indicated block.
4001 struct buf*
4002 bread(uint dev, uint blockno)
4003 {
4004   struct buf *b;
4005 
4006   b = bget(dev, blockno);
4007   if(!(b->flags & B_VALID)) {
4008     iderw(b);
4009   }
4010   return b;
4011 }
4012 
4013 // Write b's contents to disk.  Must be locked.
4014 void
4015 bwrite(struct buf *b)
4016 {
4017   if(!holdingsleep(&b->lock))
4018     panic("bwrite");
4019   b->flags |= B_DIRTY;
4020   iderw(b);
4021 }
4022 
4023 // Release a locked buffer.
4024 // Move to the head of the MRU list.
4025 void
4026 brelse(struct buf *b)
4027 {
4028   if(!holdingsleep(&b->lock))
4029     panic("brelse");
4030 
4031   releasesleep(&b->lock);
4032 
4033   acquire(&bcache.lock);
4034   b->refcnt--;
4035   if (b->refcnt == 0) {
4036     // no one is waiting for it.
4037     b->next->prev = b->prev;
4038     b->prev->next = b->next;
4039     b->next = bcache.head.next;
4040     b->prev = &bcache.head;
4041     bcache.head.next->prev = b;
4042     bcache.head.next = b;
4043   }
4044 
4045   release(&bcache.lock);
4046 }
4047 // Blank page.
4048 
4049 
