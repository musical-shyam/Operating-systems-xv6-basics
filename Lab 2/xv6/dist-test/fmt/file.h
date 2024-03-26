3650 struct file {
3651   enum { FD_NONE, FD_PIPE, FD_INODE } type;
3652   int ref; // reference count
3653   char readable;
3654   char writable;
3655   struct pipe *pipe;
3656   struct inode *ip;
3657   uint off;
3658 };
3659 
3660 
3661 // in-memory copy of an inode
3662 struct inode {
3663   uint dev;           // Device number
3664   uint inum;          // Inode number
3665   int ref;            // Reference count
3666   struct sleeplock lock;
3667   int flags;          // I_VALID
3668 
3669   short type;         // copy of disk inode
3670   short major;
3671   short minor;
3672   short nlink;
3673   uint size;
3674   uint addrs[NDIRECT+1];
3675 };
3676 #define I_VALID 0x2
3677 
3678 // table mapping major device number to
3679 // device functions
3680 struct devsw {
3681   int (*read)(struct inode*, char*, int);
3682   int (*write)(struct inode*, char*, int);
3683 };
3684 
3685 extern struct devsw devsw[];
3686 
3687 #define CONSOLE 1
3688 
3689 // Blank page.
3690 
3691 
3692 
3693 
3694 
3695 
3696 
3697 
3698 
3699 
