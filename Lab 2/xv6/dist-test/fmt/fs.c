4400 // File system implementation.  Five layers:
4401 //   + Blocks: allocator for raw disk blocks.
4402 //   + Log: crash recovery for multi-step updates.
4403 //   + Files: inode allocator, reading, writing, metadata.
4404 //   + Directories: inode with special contents (list of other inodes!)
4405 //   + Names: paths like /usr/rtm/xv6/fs.c for convenient naming.
4406 //
4407 // This file contains the low-level file system manipulation
4408 // routines.  The (higher-level) system call implementations
4409 // are in sysfile.c.
4410 
4411 #include "types.h"
4412 #include "defs.h"
4413 #include "param.h"
4414 #include "stat.h"
4415 #include "mmu.h"
4416 #include "proc.h"
4417 #include "spinlock.h"
4418 #include "sleeplock.h"
4419 #include "fs.h"
4420 #include "buf.h"
4421 #include "file.h"
4422 
4423 #define min(a, b) ((a) < (b) ? (a) : (b))
4424 static void itrunc(struct inode*);
4425 // there should be one superblock per disk device, but we run with
4426 // only one device
4427 struct superblock sb;
4428 
4429 // Read the super block.
4430 void
4431 readsb(int dev, struct superblock *sb)
4432 {
4433   struct buf *bp;
4434 
4435   bp = bread(dev, 1);
4436   memmove(sb, bp->data, sizeof(*sb));
4437   brelse(bp);
4438 }
4439 
4440 
4441 
4442 
4443 
4444 
4445 
4446 
4447 
4448 
4449 
4450 // Zero a block.
4451 static void
4452 bzero(int dev, int bno)
4453 {
4454   struct buf *bp;
4455 
4456   bp = bread(dev, bno);
4457   memset(bp->data, 0, BSIZE);
4458   log_write(bp);
4459   brelse(bp);
4460 }
4461 
4462 // Blocks.
4463 
4464 // Allocate a zeroed disk block.
4465 static uint
4466 balloc(uint dev)
4467 {
4468   int b, bi, m;
4469   struct buf *bp;
4470 
4471   bp = 0;
4472   for(b = 0; b < sb.size; b += BPB){
4473     bp = bread(dev, BBLOCK(b, sb));
4474     for(bi = 0; bi < BPB && b + bi < sb.size; bi++){
4475       m = 1 << (bi % 8);
4476       if((bp->data[bi/8] & m) == 0){  // Is block free?
4477         bp->data[bi/8] |= m;  // Mark block in use.
4478         log_write(bp);
4479         brelse(bp);
4480         bzero(dev, b + bi);
4481         return b + bi;
4482       }
4483     }
4484     brelse(bp);
4485   }
4486   panic("balloc: out of blocks");
4487 }
4488 
4489 
4490 
4491 
4492 
4493 
4494 
4495 
4496 
4497 
4498 
4499 
4500 // Free a disk block.
4501 static void
4502 bfree(int dev, uint b)
4503 {
4504   struct buf *bp;
4505   int bi, m;
4506 
4507   readsb(dev, &sb);
4508   bp = bread(dev, BBLOCK(b, sb));
4509   bi = b % BPB;
4510   m = 1 << (bi % 8);
4511   if((bp->data[bi/8] & m) == 0)
4512     panic("freeing free block");
4513   bp->data[bi/8] &= ~m;
4514   log_write(bp);
4515   brelse(bp);
4516 }
4517 
4518 // Inodes.
4519 //
4520 // An inode describes a single unnamed file.
4521 // The inode disk structure holds metadata: the file's type,
4522 // its size, the number of links referring to it, and the
4523 // list of blocks holding the file's content.
4524 //
4525 // The inodes are laid out sequentially on disk at
4526 // sb.startinode. Each inode has a number, indicating its
4527 // position on the disk.
4528 //
4529 // The kernel keeps a cache of in-use inodes in memory
4530 // to provide a place for synchronizing access
4531 // to inodes used by multiple processes. The cached
4532 // inodes include book-keeping information that is
4533 // not stored on disk: ip->ref and ip->flags.
4534 //
4535 // An inode and its in-memory represtative go through a
4536 // sequence of states before they can be used by the
4537 // rest of the file system code.
4538 //
4539 // * Allocation: an inode is allocated if its type (on disk)
4540 //   is non-zero. ialloc() allocates, iput() frees if
4541 //   the link count has fallen to zero.
4542 //
4543 // * Referencing in cache: an entry in the inode cache
4544 //   is free if ip->ref is zero. Otherwise ip->ref tracks
4545 //   the number of in-memory pointers to the entry (open
4546 //   files and current directories). iget() to find or
4547 //   create a cache entry and increment its ref, iput()
4548 //   to decrement ref.
4549 //
4550 // * Valid: the information (type, size, &c) in an inode
4551 //   cache entry is only correct when the I_VALID bit
4552 //   is set in ip->flags. ilock() reads the inode from
4553 //   the disk and sets I_VALID, while iput() clears
4554 //   I_VALID if ip->ref has fallen to zero.
4555 //
4556 // * Locked: file system code may only examine and modify
4557 //   the information in an inode and its content if it
4558 //   has first locked the inode.
4559 //
4560 // Thus a typical sequence is:
4561 //   ip = iget(dev, inum)
4562 //   ilock(ip)
4563 //   ... examine and modify ip->xxx ...
4564 //   iunlock(ip)
4565 //   iput(ip)
4566 //
4567 // ilock() is separate from iget() so that system calls can
4568 // get a long-term reference to an inode (as for an open file)
4569 // and only lock it for short periods (e.g., in read()).
4570 // The separation also helps avoid deadlock and races during
4571 // pathname lookup. iget() increments ip->ref so that the inode
4572 // stays cached and pointers to it remain valid.
4573 //
4574 // Many internal file system functions expect the caller to
4575 // have locked the inodes involved; this lets callers create
4576 // multi-step atomic operations.
4577 
4578 struct {
4579   struct spinlock lock;
4580   struct inode inode[NINODE];
4581 } icache;
4582 
4583 void
4584 iinit(int dev)
4585 {
4586   int i = 0;
4587 
4588   initlock(&icache.lock, "icache");
4589   for(i = 0; i < NINODE; i++) {
4590     initsleeplock(&icache.inode[i].lock, "inode");
4591   }
4592 
4593   readsb(dev, &sb);
4594   cprintf("sb: size %d nblocks %d ninodes %d nlog %d logstart %d\
4595  inodestart %d bmap start %d\n", sb.size, sb.nblocks,
4596           sb.ninodes, sb.nlog, sb.logstart, sb.inodestart,
4597           sb.bmapstart);
4598 }
4599 
4600 static struct inode* iget(uint dev, uint inum);
4601 
4602 // Allocate a new inode with the given type on device dev.
4603 // A free inode has a type of zero.
4604 struct inode*
4605 ialloc(uint dev, short type)
4606 {
4607   int inum;
4608   struct buf *bp;
4609   struct dinode *dip;
4610 
4611   for(inum = 1; inum < sb.ninodes; inum++){
4612     bp = bread(dev, IBLOCK(inum, sb));
4613     dip = (struct dinode*)bp->data + inum%IPB;
4614     if(dip->type == 0){  // a free inode
4615       memset(dip, 0, sizeof(*dip));
4616       dip->type = type;
4617       log_write(bp);   // mark it allocated on the disk
4618       brelse(bp);
4619       return iget(dev, inum);
4620     }
4621     brelse(bp);
4622   }
4623   panic("ialloc: no inodes");
4624 }
4625 
4626 // Copy a modified in-memory inode to disk.
4627 void
4628 iupdate(struct inode *ip)
4629 {
4630   struct buf *bp;
4631   struct dinode *dip;
4632 
4633   bp = bread(ip->dev, IBLOCK(ip->inum, sb));
4634   dip = (struct dinode*)bp->data + ip->inum%IPB;
4635   dip->type = ip->type;
4636   dip->major = ip->major;
4637   dip->minor = ip->minor;
4638   dip->nlink = ip->nlink;
4639   dip->size = ip->size;
4640   memmove(dip->addrs, ip->addrs, sizeof(ip->addrs));
4641   log_write(bp);
4642   brelse(bp);
4643 }
4644 
4645 
4646 
4647 
4648 
4649 
4650 // Find the inode with number inum on device dev
4651 // and return the in-memory copy. Does not lock
4652 // the inode and does not read it from disk.
4653 static struct inode*
4654 iget(uint dev, uint inum)
4655 {
4656   struct inode *ip, *empty;
4657 
4658   acquire(&icache.lock);
4659 
4660   // Is the inode already cached?
4661   empty = 0;
4662   for(ip = &icache.inode[0]; ip < &icache.inode[NINODE]; ip++){
4663     if(ip->ref > 0 && ip->dev == dev && ip->inum == inum){
4664       ip->ref++;
4665       release(&icache.lock);
4666       return ip;
4667     }
4668     if(empty == 0 && ip->ref == 0)    // Remember empty slot.
4669       empty = ip;
4670   }
4671 
4672   // Recycle an inode cache entry.
4673   if(empty == 0)
4674     panic("iget: no inodes");
4675 
4676   ip = empty;
4677   ip->dev = dev;
4678   ip->inum = inum;
4679   ip->ref = 1;
4680   ip->flags = 0;
4681   release(&icache.lock);
4682 
4683   return ip;
4684 }
4685 
4686 // Increment reference count for ip.
4687 // Returns ip to enable ip = idup(ip1) idiom.
4688 struct inode*
4689 idup(struct inode *ip)
4690 {
4691   acquire(&icache.lock);
4692   ip->ref++;
4693   release(&icache.lock);
4694   return ip;
4695 }
4696 
4697 
4698 
4699 
4700 // Lock the given inode.
4701 // Reads the inode from disk if necessary.
4702 void
4703 ilock(struct inode *ip)
4704 {
4705   struct buf *bp;
4706   struct dinode *dip;
4707 
4708   if(ip == 0 || ip->ref < 1)
4709     panic("ilock");
4710 
4711   acquiresleep(&ip->lock);
4712 
4713   if(!(ip->flags & I_VALID)){
4714     bp = bread(ip->dev, IBLOCK(ip->inum, sb));
4715     dip = (struct dinode*)bp->data + ip->inum%IPB;
4716     ip->type = dip->type;
4717     ip->major = dip->major;
4718     ip->minor = dip->minor;
4719     ip->nlink = dip->nlink;
4720     ip->size = dip->size;
4721     memmove(ip->addrs, dip->addrs, sizeof(ip->addrs));
4722     brelse(bp);
4723     ip->flags |= I_VALID;
4724     if(ip->type == 0)
4725       panic("ilock: no type");
4726   }
4727 }
4728 
4729 // Unlock the given inode.
4730 void
4731 iunlock(struct inode *ip)
4732 {
4733   if(ip == 0 || !holdingsleep(&ip->lock) || ip->ref < 1)
4734     panic("iunlock");
4735 
4736   releasesleep(&ip->lock);
4737 }
4738 
4739 
4740 
4741 
4742 
4743 
4744 
4745 
4746 
4747 
4748 
4749 
4750 // Drop a reference to an in-memory inode.
4751 // If that was the last reference, the inode cache entry can
4752 // be recycled.
4753 // If that was the last reference and the inode has no links
4754 // to it, free the inode (and its content) on disk.
4755 // All calls to iput() must be inside a transaction in
4756 // case it has to free the inode.
4757 void
4758 iput(struct inode *ip)
4759 {
4760   acquire(&icache.lock);
4761   if(ip->ref == 1 && (ip->flags & I_VALID) && ip->nlink == 0){
4762     // inode has no links and no other references: truncate and free.
4763     release(&icache.lock);
4764     itrunc(ip);
4765     ip->type = 0;
4766     iupdate(ip);
4767     acquire(&icache.lock);
4768     ip->flags = 0;
4769   }
4770   ip->ref--;
4771   release(&icache.lock);
4772 }
4773 
4774 // Common idiom: unlock, then put.
4775 void
4776 iunlockput(struct inode *ip)
4777 {
4778   iunlock(ip);
4779   iput(ip);
4780 }
4781 
4782 // Inode content
4783 //
4784 // The content (data) associated with each inode is stored
4785 // in blocks on the disk. The first NDIRECT block numbers
4786 // are listed in ip->addrs[].  The next NINDIRECT blocks are
4787 // listed in block ip->addrs[NDIRECT].
4788 
4789 // Return the disk block address of the nth block in inode ip.
4790 // If there is no such block, bmap allocates one.
4791 static uint
4792 bmap(struct inode *ip, uint bn)
4793 {
4794   uint addr, *a;
4795   struct buf *bp;
4796 
4797   if(bn < NDIRECT){
4798     if((addr = ip->addrs[bn]) == 0)
4799       ip->addrs[bn] = addr = balloc(ip->dev);
4800     return addr;
4801   }
4802   bn -= NDIRECT;
4803 
4804   if(bn < NINDIRECT){
4805     // Load indirect block, allocating if necessary.
4806     if((addr = ip->addrs[NDIRECT]) == 0)
4807       ip->addrs[NDIRECT] = addr = balloc(ip->dev);
4808     bp = bread(ip->dev, addr);
4809     a = (uint*)bp->data;
4810     if((addr = a[bn]) == 0){
4811       a[bn] = addr = balloc(ip->dev);
4812       log_write(bp);
4813     }
4814     brelse(bp);
4815     return addr;
4816   }
4817 
4818   panic("bmap: out of range");
4819 }
4820 
4821 // Truncate inode (discard contents).
4822 // Only called when the inode has no links
4823 // to it (no directory entries referring to it)
4824 // and has no in-memory reference to it (is
4825 // not an open file or current directory).
4826 static void
4827 itrunc(struct inode *ip)
4828 {
4829   int i, j;
4830   struct buf *bp;
4831   uint *a;
4832 
4833   for(i = 0; i < NDIRECT; i++){
4834     if(ip->addrs[i]){
4835       bfree(ip->dev, ip->addrs[i]);
4836       ip->addrs[i] = 0;
4837     }
4838   }
4839 
4840   if(ip->addrs[NDIRECT]){
4841     bp = bread(ip->dev, ip->addrs[NDIRECT]);
4842     a = (uint*)bp->data;
4843     for(j = 0; j < NINDIRECT; j++){
4844       if(a[j])
4845         bfree(ip->dev, a[j]);
4846     }
4847     brelse(bp);
4848     bfree(ip->dev, ip->addrs[NDIRECT]);
4849     ip->addrs[NDIRECT] = 0;
4850   }
4851 
4852   ip->size = 0;
4853   iupdate(ip);
4854 }
4855 
4856 // Copy stat information from inode.
4857 void
4858 stati(struct inode *ip, struct stat *st)
4859 {
4860   st->dev = ip->dev;
4861   st->ino = ip->inum;
4862   st->type = ip->type;
4863   st->nlink = ip->nlink;
4864   st->size = ip->size;
4865 }
4866 
4867 // Read data from inode.
4868 int
4869 readi(struct inode *ip, char *dst, uint off, uint n)
4870 {
4871   uint tot, m;
4872   struct buf *bp;
4873 
4874   if(ip->type == T_DEV){
4875     if(ip->major < 0 || ip->major >= NDEV || !devsw[ip->major].read)
4876       return -1;
4877     return devsw[ip->major].read(ip, dst, n);
4878   }
4879 
4880   if(off > ip->size || off + n < off)
4881     return -1;
4882   if(off + n > ip->size)
4883     n = ip->size - off;
4884 
4885   for(tot=0; tot<n; tot+=m, off+=m, dst+=m){
4886     bp = bread(ip->dev, bmap(ip, off/BSIZE));
4887     m = min(n - tot, BSIZE - off%BSIZE);
4888     /*
4889     cprintf("data off %d:\n", off);
4890     for (int j = 0; j < min(m, 10); j++) {
4891       cprintf("%x ", bp->data[off%BSIZE+j]);
4892     }
4893     cprintf("\n");
4894     */
4895     memmove(dst, bp->data + off%BSIZE, m);
4896     brelse(bp);
4897   }
4898   return n;
4899 }
4900 // Write data to inode.
4901 int
4902 writei(struct inode *ip, char *src, uint off, uint n)
4903 {
4904   uint tot, m;
4905   struct buf *bp;
4906 
4907   if(ip->type == T_DEV){
4908     if(ip->major < 0 || ip->major >= NDEV || !devsw[ip->major].write)
4909       return -1;
4910     return devsw[ip->major].write(ip, src, n);
4911   }
4912 
4913   if(off > ip->size || off + n < off)
4914     return -1;
4915   if(off + n > MAXFILE*BSIZE)
4916     return -1;
4917 
4918   for(tot=0; tot<n; tot+=m, off+=m, src+=m){
4919     bp = bread(ip->dev, bmap(ip, off/BSIZE));
4920     m = min(n - tot, BSIZE - off%BSIZE);
4921     memmove(bp->data + off%BSIZE, src, m);
4922     log_write(bp);
4923     brelse(bp);
4924   }
4925 
4926   if(n > 0 && off > ip->size){
4927     ip->size = off;
4928     iupdate(ip);
4929   }
4930   return n;
4931 }
4932 
4933 // Directories
4934 
4935 int
4936 namecmp(const char *s, const char *t)
4937 {
4938   return strncmp(s, t, DIRSIZ);
4939 }
4940 
4941 
4942 
4943 
4944 
4945 
4946 
4947 
4948 
4949 
4950 // Look for a directory entry in a directory.
4951 // If found, set *poff to byte offset of entry.
4952 struct inode*
4953 dirlookup(struct inode *dp, char *name, uint *poff)
4954 {
4955   uint off, inum;
4956   struct dirent de;
4957 
4958   if(dp->type != T_DIR)
4959     panic("dirlookup not DIR");
4960 
4961   for(off = 0; off < dp->size; off += sizeof(de)){
4962     if(readi(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
4963       panic("dirlink read");
4964     if(de.inum == 0)
4965       continue;
4966     if(namecmp(name, de.name) == 0){
4967       // entry matches path element
4968       if(poff)
4969         *poff = off;
4970       inum = de.inum;
4971       return iget(dp->dev, inum);
4972     }
4973   }
4974 
4975   return 0;
4976 }
4977 
4978 // Write a new directory entry (name, inum) into the directory dp.
4979 int
4980 dirlink(struct inode *dp, char *name, uint inum)
4981 {
4982   int off;
4983   struct dirent de;
4984   struct inode *ip;
4985 
4986   // Check that name is not present.
4987   if((ip = dirlookup(dp, name, 0)) != 0){
4988     iput(ip);
4989     return -1;
4990   }
4991 
4992   // Look for an empty dirent.
4993   for(off = 0; off < dp->size; off += sizeof(de)){
4994     if(readi(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
4995       panic("dirlink read");
4996     if(de.inum == 0)
4997       break;
4998   }
4999 
5000   strncpy(de.name, name, DIRSIZ);
5001   de.inum = inum;
5002   if(writei(dp, (char*)&de, off, sizeof(de)) != sizeof(de))
5003     panic("dirlink");
5004 
5005   return 0;
5006 }
5007 
5008 // Paths
5009 
5010 // Copy the next path element from path into name.
5011 // Return a pointer to the element following the copied one.
5012 // The returned path has no leading slashes,
5013 // so the caller can check *path=='\0' to see if the name is the last one.
5014 // If no name to remove, return 0.
5015 //
5016 // Examples:
5017 //   skipelem("a/bb/c", name) = "bb/c", setting name = "a"
5018 //   skipelem("///a//bb", name) = "bb", setting name = "a"
5019 //   skipelem("a", name) = "", setting name = "a"
5020 //   skipelem("", name) = skipelem("////", name) = 0
5021 //
5022 static char*
5023 skipelem(char *path, char *name)
5024 {
5025   char *s;
5026   int len;
5027 
5028   while(*path == '/')
5029     path++;
5030   if(*path == 0)
5031     return 0;
5032   s = path;
5033   while(*path != '/' && *path != 0)
5034     path++;
5035   len = path - s;
5036   if(len >= DIRSIZ)
5037     memmove(name, s, DIRSIZ);
5038   else {
5039     memmove(name, s, len);
5040     name[len] = 0;
5041   }
5042   while(*path == '/')
5043     path++;
5044   return path;
5045 }
5046 
5047 
5048 
5049 
5050 // Look up and return the inode for a path name.
5051 // If parent != 0, return the inode for the parent and copy the final
5052 // path element into name, which must have room for DIRSIZ bytes.
5053 // Must be called inside a transaction since it calls iput().
5054 static struct inode*
5055 namex(char *path, int nameiparent, char *name)
5056 {
5057   struct inode *ip, *next;
5058 
5059   if(*path == '/')
5060     ip = iget(ROOTDEV, ROOTINO);
5061   else
5062     ip = idup(proc->cwd);
5063 
5064   while((path = skipelem(path, name)) != 0){
5065     ilock(ip);
5066     if(ip->type != T_DIR){
5067       iunlockput(ip);
5068       return 0;
5069     }
5070     if(nameiparent && *path == '\0'){
5071       // Stop one level early.
5072       iunlock(ip);
5073       return ip;
5074     }
5075     if((next = dirlookup(ip, name, 0)) == 0){
5076       iunlockput(ip);
5077       return 0;
5078     }
5079     iunlockput(ip);
5080     ip = next;
5081   }
5082   if(nameiparent){
5083     iput(ip);
5084     return 0;
5085   }
5086   return ip;
5087 }
5088 
5089 struct inode*
5090 namei(char *path)
5091 {
5092   char name[DIRSIZ];
5093   return namex(path, 0, name);
5094 }
5095 
5096 
5097 
5098 
5099 
5100 struct inode*
5101 nameiparent(char *path, char *name)
5102 {
5103   return namex(path, 1, name);
5104 }
5105 
5106 
5107 
5108 
5109 
5110 
5111 
5112 
5113 
5114 
5115 
5116 
5117 
5118 
5119 
5120 
5121 
5122 
5123 
5124 
5125 
5126 
5127 
5128 
5129 
5130 
5131 
5132 
5133 
5134 
5135 
5136 
5137 
5138 
5139 
5140 
5141 
5142 
5143 
5144 
5145 
5146 
5147 
5148 
5149 
