3550 // On-disk file system format.
3551 // Both the kernel and user programs use this header file.
3552 
3553 
3554 #define ROOTINO 1  // root i-number
3555 #define BSIZE 512  // block size
3556 
3557 // Disk layout:
3558 // [ boot block | super block | log | inode blocks |
3559 //                                          free bit map | data blocks]
3560 //
3561 // mkfs computes the super block and builds an initial file system. The
3562 // super block describes the disk layout:
3563 struct superblock {
3564   uint size;         // Size of file system image (blocks)
3565   uint nblocks;      // Number of data blocks
3566   uint ninodes;      // Number of inodes.
3567   uint nlog;         // Number of log blocks
3568   uint logstart;     // Block number of first log block
3569   uint inodestart;   // Block number of first inode block
3570   uint bmapstart;    // Block number of first free map block
3571 };
3572 
3573 #define NDIRECT 12
3574 #define NINDIRECT (BSIZE / sizeof(uint))
3575 #define MAXFILE (NDIRECT + NINDIRECT)
3576 
3577 // On-disk inode structure
3578 struct dinode {
3579   short type;           // File type
3580   short major;          // Major device number (T_DEV only)
3581   short minor;          // Minor device number (T_DEV only)
3582   short nlink;          // Number of links to inode in file system
3583   uint size;            // Size of file (bytes)
3584   uint addrs[NDIRECT+1];   // Data block addresses
3585 };
3586 
3587 
3588 
3589 
3590 
3591 
3592 
3593 
3594 
3595 
3596 
3597 
3598 
3599 
3600 // Inodes per block.
3601 #define IPB           (BSIZE / sizeof(struct dinode))
3602 
3603 // Block containing inode i
3604 #define IBLOCK(i, sb)     ((i) / IPB + sb.inodestart)
3605 
3606 // Bitmap bits per block
3607 #define BPB           (BSIZE*8)
3608 
3609 // Block of free map containing bit for block b
3610 #define BBLOCK(b, sb) (b/BPB + sb.bmapstart)
3611 
3612 // Directory is a file containing a sequence of dirent structures.
3613 #define DIRSIZ 14
3614 
3615 struct dirent {
3616   ushort inum;
3617   char name[DIRSIZ];
3618 };
3619 
3620 
3621 
3622 
3623 
3624 
3625 
3626 
3627 
3628 
3629 
3630 
3631 
3632 
3633 
3634 
3635 
3636 
3637 
3638 
3639 
3640 
3641 
3642 
3643 
3644 
3645 
3646 
3647 
3648 
3649 
