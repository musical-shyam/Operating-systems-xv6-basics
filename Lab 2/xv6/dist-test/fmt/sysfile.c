5350 //
5351 // File-system system calls.
5352 // Mostly argument checking, since we don't trust
5353 // user code, and calls into file.c and fs.c.
5354 //
5355 
5356 #include "types.h"
5357 #include "defs.h"
5358 #include "param.h"
5359 #include "stat.h"
5360 #include "mmu.h"
5361 #include "proc.h"
5362 #include "fs.h"
5363 #include "spinlock.h"
5364 #include "sleeplock.h"
5365 #include "file.h"
5366 #include "fcntl.h"
5367 
5368 // Fetch the nth word-sized system call argument as a file descriptor
5369 // and return both the descriptor and the corresponding struct file.
5370 static int
5371 argfd(int n, int *pfd, struct file **pf)
5372 {
5373   int fd;
5374   struct file *f;
5375 
5376   if(argint(n, &fd) < 0)
5377     return -1;
5378   if(fd < 0 || fd >= NOFILE || (f=proc->ofile[fd]) == 0)
5379     return -1;
5380   if(pfd)
5381     *pfd = fd;
5382   if(pf)
5383     *pf = f;
5384   return 0;
5385 }
5386 
5387 
5388 
5389 
5390 
5391 
5392 
5393 
5394 
5395 
5396 
5397 
5398 
5399 
5400 // Allocate a file descriptor for the given file.
5401 // Takes over file reference from caller on success.
5402 static int
5403 fdalloc(struct file *f)
5404 {
5405   int fd;
5406 
5407   for(fd = 0; fd < NOFILE; fd++){
5408     if(proc->ofile[fd] == 0){
5409       proc->ofile[fd] = f;
5410       return fd;
5411     }
5412   }
5413   return -1;
5414 }
5415 
5416 int
5417 sys_dup(void)
5418 {
5419   struct file *f;
5420   int fd;
5421 
5422   if(argfd(0, 0, &f) < 0)
5423     return -1;
5424   if((fd=fdalloc(f)) < 0)
5425     return -1;
5426   filedup(f);
5427   return fd;
5428 }
5429 
5430 int
5431 sys_read(void)
5432 {
5433   struct file *f;
5434   int n;
5435   char *p;
5436 
5437   if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
5438     return -1;
5439   return fileread(f, p, n);
5440 }
5441 
5442 
5443 
5444 
5445 
5446 
5447 
5448 
5449 
5450 int
5451 sys_write(void)
5452 {
5453   struct file *f;
5454   int n;
5455   char *p;
5456 
5457   if(argfd(0, 0, &f) < 0 || argint(2, &n) < 0 || argptr(1, &p, n) < 0)
5458     return -1;
5459   return filewrite(f, p, n);
5460 }
5461 
5462 int
5463 sys_close(void)
5464 {
5465   int fd;
5466   struct file *f;
5467 
5468   if(argfd(0, &fd, &f) < 0)
5469     return -1;
5470   proc->ofile[fd] = 0;
5471   fileclose(f);
5472   return 0;
5473 }
5474 
5475 int
5476 sys_fstat(void)
5477 {
5478   struct file *f;
5479   struct stat *st;
5480 
5481   if(argfd(0, 0, &f) < 0 || argptr(1, (void*)&st, sizeof(*st)) < 0)
5482     return -1;
5483   return filestat(f, st);
5484 }
5485 
5486 
5487 
5488 
5489 
5490 
5491 
5492 
5493 
5494 
5495 
5496 
5497 
5498 
5499 
5500 // Create the path new as a link to the same inode as old.
5501 int
5502 sys_link(void)
5503 {
5504   char name[DIRSIZ], *new, *old;
5505   struct inode *dp, *ip;
5506 
5507   if(argstr(0, &old) < 0 || argstr(1, &new) < 0)
5508     return -1;
5509 
5510   begin_op();
5511   if((ip = namei(old)) == 0){
5512     end_op();
5513     return -1;
5514   }
5515 
5516   ilock(ip);
5517   if(ip->type == T_DIR){
5518     iunlockput(ip);
5519     end_op();
5520     return -1;
5521   }
5522 
5523   ip->nlink++;
5524   iupdate(ip);
5525   iunlock(ip);
5526 
5527   if((dp = nameiparent(new, name)) == 0)
5528     goto bad;
5529   ilock(dp);
5530   if(dp->dev != ip->dev || dirlink(dp, name, ip->inum) < 0){
5531     iunlockput(dp);
5532     goto bad;
5533   }
5534   iunlockput(dp);
5535   iput(ip);
5536 
5537   end_op();
5538 
5539   return 0;
5540 
5541 bad:
5542   ilock(ip);
5543   ip->nlink--;
5544   iupdate(ip);
5545   iunlockput(ip);
5546   end_op();
5547   return -1;
5548 }
5549 
5550 // Is the directory dp empty except for "." and ".." ?
5551 static int
5552 isdirempty(struct inode *dp)
5553 {
5554   int off;
5555   struct dirent de;
5556 
5557   for(off=2*sizeof(de); off<dp->size; off+=sizeof(de)){
5558     if(readi(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
5559       panic("isdirempty: readi");
5560     if(de.inum != 0)
5561       return 0;
5562   }
5563   return 1;
5564 }
5565 
5566 int
5567 sys_unlink(void)
5568 {
5569   struct inode *ip, *dp;
5570   struct dirent de;
5571   char name[DIRSIZ], *path;
5572   uint off;
5573 
5574   if(argstr(0, &path) < 0)
5575     return -1;
5576 
5577   begin_op();
5578   if((dp = nameiparent(path, name)) == 0){
5579     end_op();
5580     return -1;
5581   }
5582 
5583   ilock(dp);
5584 
5585   // Cannot unlink "." or "..".
5586   if(namecmp(name, ".") == 0 || namecmp(name, "..") == 0)
5587     goto bad;
5588 
5589   if((ip = dirlookup(dp, name, &off)) == 0)
5590     goto bad;
5591   ilock(ip);
5592 
5593   if(ip->nlink < 1)
5594     panic("unlink: nlink < 1");
5595   if(ip->type == T_DIR && !isdirempty(ip)){
5596     iunlockput(ip);
5597     goto bad;
5598   }
5599 
5600   memset(&de, 0, sizeof(de));
5601   if(writei(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
5602     panic("unlink: writei");
5603   if(ip->type == T_DIR){
5604     dp->nlink--;
5605     iupdate(dp);
5606   }
5607   iunlockput(dp);
5608 
5609   ip->nlink--;
5610   iupdate(ip);
5611   iunlockput(ip);
5612 
5613   end_op();
5614 
5615   return 0;
5616 
5617 bad:
5618   iunlockput(dp);
5619   end_op();
5620   return -1;
5621 }
5622 
5623 static struct inode*
5624 create(char *path, short type, short major, short minor)
5625 {
5626   uint off;
5627   struct inode *ip, *dp;
5628   char name[DIRSIZ];
5629 
5630   if((dp = nameiparent(path, name)) == 0)
5631     return 0;
5632   ilock(dp);
5633 
5634   if((ip = dirlookup(dp, name, &off)) != 0){
5635     iunlockput(dp);
5636     ilock(ip);
5637     if(type == T_FILE && ip->type == T_FILE)
5638       return ip;
5639     iunlockput(ip);
5640     return 0;
5641   }
5642 
5643   if((ip = ialloc(dp->dev, type)) == 0)
5644     panic("create: ialloc");
5645 
5646 
5647 
5648 
5649 
5650   ilock(ip);
5651   ip->major = major;
5652   ip->minor = minor;
5653   ip->nlink = 1;
5654   iupdate(ip);
5655 
5656   if(type == T_DIR){  // Create . and .. entries.
5657     dp->nlink++;  // for ".."
5658     iupdate(dp);
5659     // No ip->nlink++ for ".": avoid cyclic ref count.
5660     if(dirlink(ip, ".", ip->inum) < 0 || dirlink(ip, "..", dp->inum) < 0)
5661       panic("create dots");
5662   }
5663 
5664   if(dirlink(dp, name, ip->inum) < 0)
5665     panic("create: dirlink");
5666 
5667   iunlockput(dp);
5668 
5669   return ip;
5670 }
5671 
5672 int
5673 sys_open(void)
5674 {
5675   char *path;
5676   int fd, omode;
5677   struct file *f;
5678   struct inode *ip;
5679 
5680   if(argstr(0, &path) < 0 || argint(1, &omode) < 0)
5681     return -1;
5682 
5683   begin_op();
5684 
5685   if(omode & O_CREATE){
5686     ip = create(path, T_FILE, 0, 0);
5687     if(ip == 0){
5688       end_op();
5689       return -1;
5690     }
5691   } else {
5692     if((ip = namei(path)) == 0){
5693       end_op();
5694       return -1;
5695     }
5696     ilock(ip);
5697     if(ip->type == T_DIR && omode != O_RDONLY){
5698       iunlockput(ip);
5699       end_op();
5700       return -1;
5701     }
5702   }
5703 
5704   if((f = filealloc()) == 0 || (fd = fdalloc(f)) < 0){
5705     if(f)
5706       fileclose(f);
5707     iunlockput(ip);
5708     end_op();
5709     return -1;
5710   }
5711   iunlock(ip);
5712   end_op();
5713 
5714   f->type = FD_INODE;
5715   f->ip = ip;
5716   f->off = 0;
5717   f->readable = !(omode & O_WRONLY);
5718   f->writable = (omode & O_WRONLY) || (omode & O_RDWR);
5719   return fd;
5720 }
5721 
5722 int
5723 sys_mkdir(void)
5724 {
5725   char *path;
5726   struct inode *ip;
5727 
5728   begin_op();
5729   if(argstr(0, &path) < 0 || (ip = create(path, T_DIR, 0, 0)) == 0){
5730     end_op();
5731     return -1;
5732   }
5733   iunlockput(ip);
5734   end_op();
5735   return 0;
5736 }
5737 
5738 
5739 
5740 
5741 
5742 
5743 
5744 
5745 
5746 
5747 
5748 
5749 
5750 int
5751 sys_mknod(void)
5752 {
5753   struct inode *ip;
5754   char *path;
5755   int major, minor;
5756 
5757   begin_op();
5758   if((argstr(0, &path)) < 0 ||
5759      argint(1, &major) < 0 ||
5760      argint(2, &minor) < 0 ||
5761      (ip = create(path, T_DEV, major, minor)) == 0){
5762     end_op();
5763     return -1;
5764   }
5765   iunlockput(ip);
5766   end_op();
5767   return 0;
5768 }
5769 
5770 int
5771 sys_chdir(void)
5772 {
5773   char *path;
5774   struct inode *ip;
5775 
5776   begin_op();
5777   if(argstr(0, &path) < 0 || (ip = namei(path)) == 0){
5778     end_op();
5779     return -1;
5780   }
5781   ilock(ip);
5782   if(ip->type != T_DIR){
5783     iunlockput(ip);
5784     end_op();
5785     return -1;
5786   }
5787   iunlock(ip);
5788   iput(proc->cwd);
5789   end_op();
5790   proc->cwd = ip;
5791   return 0;
5792 }
5793 
5794 
5795 
5796 
5797 
5798 
5799 
5800 int
5801 sys_exec(void)
5802 {
5803   char *path, *argv[MAXARG];
5804   int i;
5805   uint uargv, uarg;
5806 
5807   if(argstr(0, &path) < 0 || argint(1, (int*)&uargv) < 0){
5808     return -1;
5809   }
5810   memset(argv, 0, sizeof(argv));
5811   for(i=0;; i++){
5812     if(i >= NELEM(argv))
5813       return -1;
5814     if(fetchint(uargv+4*i, (int*)&uarg) < 0)
5815       return -1;
5816     if(uarg == 0){
5817       argv[i] = 0;
5818       break;
5819     }
5820     if(fetchstr(uarg, &argv[i]) < 0)
5821       return -1;
5822   }
5823   return exec(path, argv);
5824 }
5825 
5826 int
5827 sys_pipe(void)
5828 {
5829   int *fd;
5830   struct file *rf, *wf;
5831   int fd0, fd1;
5832 
5833   if(argptr(0, (void*)&fd, 2*sizeof(fd[0])) < 0)
5834     return -1;
5835   if(pipealloc(&rf, &wf) < 0)
5836     return -1;
5837   fd0 = -1;
5838   if((fd0 = fdalloc(rf)) < 0 || (fd1 = fdalloc(wf)) < 0){
5839     if(fd0 >= 0)
5840       proc->ofile[fd0] = 0;
5841     fileclose(rf);
5842     fileclose(wf);
5843     return -1;
5844   }
5845   fd[0] = fd0;
5846   fd[1] = fd1;
5847   return 0;
5848 }
5849 
