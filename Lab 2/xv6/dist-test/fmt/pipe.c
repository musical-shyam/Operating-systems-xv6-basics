6000 #include "types.h"
6001 #include "defs.h"
6002 #include "param.h"
6003 #include "mmu.h"
6004 #include "proc.h"
6005 #include "fs.h"
6006 #include "spinlock.h"
6007 #include "sleeplock.h"
6008 #include "file.h"
6009 
6010 #define PIPESIZE 512
6011 
6012 struct pipe {
6013   struct spinlock lock;
6014   char data[PIPESIZE];
6015   uint nread;     // number of bytes read
6016   uint nwrite;    // number of bytes written
6017   int readopen;   // read fd is still open
6018   int writeopen;  // write fd is still open
6019 };
6020 
6021 int
6022 pipealloc(struct file **f0, struct file **f1)
6023 {
6024   struct pipe *p;
6025 
6026   p = 0;
6027   *f0 = *f1 = 0;
6028   if((*f0 = filealloc()) == 0 || (*f1 = filealloc()) == 0)
6029     goto bad;
6030   if((p = (struct pipe*)kalloc()) == 0)
6031     goto bad;
6032   p->readopen = 1;
6033   p->writeopen = 1;
6034   p->nwrite = 0;
6035   p->nread = 0;
6036   initlock(&p->lock, "pipe");
6037   (*f0)->type = FD_PIPE;
6038   (*f0)->readable = 1;
6039   (*f0)->writable = 0;
6040   (*f0)->pipe = p;
6041   (*f1)->type = FD_PIPE;
6042   (*f1)->readable = 0;
6043   (*f1)->writable = 1;
6044   (*f1)->pipe = p;
6045   return 0;
6046 
6047 
6048 
6049 
6050  bad:
6051   if(p)
6052     kfree((char*)p);
6053   if(*f0)
6054     fileclose(*f0);
6055   if(*f1)
6056     fileclose(*f1);
6057   return -1;
6058 }
6059 
6060 void
6061 pipeclose(struct pipe *p, int writable)
6062 {
6063   acquire(&p->lock);
6064   if(writable){
6065     p->writeopen = 0;
6066     wakeup(&p->nread);
6067   } else {
6068     p->readopen = 0;
6069     wakeup(&p->nwrite);
6070   }
6071   if(p->readopen == 0 && p->writeopen == 0){
6072     release(&p->lock);
6073     kfree((char*)p);
6074   } else
6075     release(&p->lock);
6076 }
6077 
6078 int
6079 pipewrite(struct pipe *p, char *addr, int n)
6080 {
6081   int i;
6082 
6083   acquire(&p->lock);
6084   for(i = 0; i < n; i++){
6085     while(p->nwrite == p->nread + PIPESIZE){  //DOC: pipewrite-full
6086       if(p->readopen == 0 || proc->killed){
6087         release(&p->lock);
6088         return -1;
6089       }
6090       wakeup(&p->nread);
6091       sleep(&p->nwrite, &p->lock);  //DOC: pipewrite-sleep
6092     }
6093     p->data[p->nwrite++ % PIPESIZE] = addr[i];
6094   }
6095   wakeup(&p->nread);  //DOC: pipewrite-wakeup1
6096   release(&p->lock);
6097   return n;
6098 }
6099 
6100 int
6101 piperead(struct pipe *p, char *addr, int n)
6102 {
6103   int i;
6104 
6105   acquire(&p->lock);
6106   while(p->nread == p->nwrite && p->writeopen){  //DOC: pipe-empty
6107     if(proc->killed){
6108       release(&p->lock);
6109       return -1;
6110     }
6111     sleep(&p->nread, &p->lock); //DOC: piperead-sleep
6112   }
6113   for(i = 0; i < n; i++){  //DOC: piperead-copy
6114     if(p->nread == p->nwrite)
6115       break;
6116     addr[i] = p->data[p->nread++ % PIPESIZE];
6117   }
6118   wakeup(&p->nwrite);  //DOC: piperead-wakeup
6119   release(&p->lock);
6120   return i;
6121 }
6122 
6123 
6124 
6125 
6126 
6127 
6128 
6129 
6130 
6131 
6132 
6133 
6134 
6135 
6136 
6137 
6138 
6139 
6140 
6141 
6142 
6143 
6144 
6145 
6146 
6147 
6148 
6149 
