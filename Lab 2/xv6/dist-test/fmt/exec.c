5850 #include "types.h"
5851 #include "param.h"
5852 #include "memlayout.h"
5853 #include "mmu.h"
5854 #include "proc.h"
5855 #include "defs.h"
5856 #include "x86.h"
5857 #include "elf.h"
5858 
5859 int
5860 exec(char *path, char **argv)
5861 {
5862   char *s, *last;
5863   int i, off;
5864   uint argc, sz, sp, ustack[3+MAXARG+1];
5865   struct elfhdr elf;
5866   struct inode *ip;
5867   struct proghdr ph;
5868   pde_t *pgdir, *oldpgdir;
5869 
5870   begin_op();
5871 
5872   if((ip = namei(path)) == 0){
5873     end_op();
5874     return -1;
5875   }
5876   ilock(ip);
5877   pgdir = 0;
5878 
5879   // Check ELF header
5880   if(readi(ip, (char*)&elf, 0, sizeof(elf)) < sizeof(elf))
5881     goto bad;
5882   if(elf.magic != ELF_MAGIC)
5883     goto bad;
5884 
5885   if((pgdir = setupkvm()) == 0)
5886     goto bad;
5887 
5888   // Load program into memory.
5889   sz = 0;
5890   for(i=0, off=elf.phoff; i<elf.phnum; i++, off+=sizeof(ph)){
5891     if(readi(ip, (char*)&ph, off, sizeof(ph)) != sizeof(ph))
5892       goto bad;
5893     if(ph.type != ELF_PROG_LOAD)
5894       continue;
5895     if(ph.memsz < ph.filesz)
5896       goto bad;
5897     if(ph.vaddr + ph.memsz < ph.vaddr)
5898       goto bad;
5899     if((sz = allocuvm(pgdir, sz, ph.vaddr + ph.memsz)) == 0)
5900       goto bad;
5901     if(ph.vaddr % PGSIZE != 0)
5902       goto bad;
5903     if(loaduvm(pgdir, (char*)ph.vaddr, ip, ph.off, ph.filesz) < 0)
5904       goto bad;
5905   }
5906   iunlockput(ip);
5907   end_op();
5908   ip = 0;
5909 
5910   // Allocate two pages at the next page boundary.
5911   // Make the first inaccessible.  Use the second as the user stack.
5912   sz = PGROUNDUP(sz);
5913   if((sz = allocuvm(pgdir, sz, sz + 2*PGSIZE)) == 0)
5914     goto bad;
5915   clearpteu(pgdir, (char*)(sz - 2*PGSIZE));
5916   sp = sz;
5917 
5918   // Push argument strings, prepare rest of stack in ustack.
5919   for(argc = 0; argv[argc]; argc++) {
5920     if(argc >= MAXARG)
5921       goto bad;
5922     sp = (sp - (strlen(argv[argc]) + 1)) & ~3;
5923     if(copyout(pgdir, sp, argv[argc], strlen(argv[argc]) + 1) < 0)
5924       goto bad;
5925     ustack[3+argc] = sp;
5926   }
5927   ustack[3+argc] = 0;
5928 
5929   ustack[0] = 0xffffffff;  // fake return PC
5930   ustack[1] = argc;
5931   ustack[2] = sp - (argc+1)*4;  // argv pointer
5932 
5933   sp -= (3+argc+1) * 4;
5934   if(copyout(pgdir, sp, ustack, (3+argc+1)*4) < 0)
5935     goto bad;
5936 
5937   // Save program name for debugging.
5938   for(last=s=path; *s; s++)
5939     if(*s == '/')
5940       last = s+1;
5941   safestrcpy(proc->name, last, sizeof(proc->name));
5942 
5943   // Commit to the user image.
5944   oldpgdir = proc->pgdir;
5945   proc->pgdir = pgdir;
5946   proc->sz = sz;
5947   proc->tf->eip = elf.entry;  // main
5948   proc->tf->esp = sp;
5949   switchuvm(proc);
5950   freevm(oldpgdir);
5951   return 0;
5952 
5953  bad:
5954   if(pgdir)
5955     freevm(pgdir);
5956   if(ip){
5957     iunlockput(ip);
5958     end_op();
5959   }
5960   return -1;
5961 }
5962 
5963 
5964 
5965 
5966 
5967 
5968 
5969 
5970 
5971 
5972 
5973 
5974 
5975 
5976 
5977 
5978 
5979 
5980 
5981 
5982 
5983 
5984 
5985 
5986 
5987 
5988 
5989 
5990 
5991 
5992 
5993 
5994 
5995 
5996 
5997 
5998 
5999 
