6400 // Multiprocessor support
6401 // Search memory for MP description structures.
6402 // http://developer.intel.com/design/pentium/datashts/24201606.pdf
6403 
6404 #include "types.h"
6405 #include "defs.h"
6406 #include "param.h"
6407 #include "memlayout.h"
6408 #include "mp.h"
6409 #include "x86.h"
6410 #include "mmu.h"
6411 #include "proc.h"
6412 
6413 struct cpu cpus[NCPU];
6414 int ismp;
6415 int ncpu;
6416 uchar ioapicid;
6417 
6418 static uchar
6419 sum(uchar *addr, int len)
6420 {
6421   int i, sum;
6422 
6423   sum = 0;
6424   for(i=0; i<len; i++)
6425     sum += addr[i];
6426   return sum;
6427 }
6428 
6429 // Look for an MP structure in the len bytes at addr.
6430 static struct mp*
6431 mpsearch1(uint a, int len)
6432 {
6433   uchar *e, *p, *addr;
6434 
6435   addr = P2V(a);
6436   e = addr+len;
6437   for(p = addr; p < e; p += sizeof(struct mp))
6438     if(memcmp(p, "_MP_", 4) == 0 && sum(p, sizeof(struct mp)) == 0)
6439       return (struct mp*)p;
6440   return 0;
6441 }
6442 
6443 
6444 
6445 
6446 
6447 
6448 
6449 
6450 // Search for the MP Floating Pointer Structure, which according to the
6451 // spec is in one of the following three locations:
6452 // 1) in the first KB of the EBDA;
6453 // 2) in the last KB of system base memory;
6454 // 3) in the BIOS ROM between 0xE0000 and 0xFFFFF.
6455 static struct mp*
6456 mpsearch(void)
6457 {
6458   uchar *bda;
6459   uint p;
6460   struct mp *mp;
6461 
6462   bda = (uchar *) P2V(0x400);
6463   if((p = ((bda[0x0F]<<8)| bda[0x0E]) << 4)){
6464     if((mp = mpsearch1(p, 1024)))
6465       return mp;
6466   } else {
6467     p = ((bda[0x14]<<8)|bda[0x13])*1024;
6468     if((mp = mpsearch1(p-1024, 1024)))
6469       return mp;
6470   }
6471   return mpsearch1(0xF0000, 0x10000);
6472 }
6473 
6474 // Search for an MP configuration table.  For now,
6475 // don't accept the default configurations (physaddr == 0).
6476 // Check for correct signature, calculate the checksum and,
6477 // if correct, check the version.
6478 // To do: check extended table checksum.
6479 static struct mpconf*
6480 mpconfig(struct mp **pmp)
6481 {
6482   struct mpconf *conf;
6483   struct mp *mp;
6484 
6485   if((mp = mpsearch()) == 0 || mp->physaddr == 0)
6486     return 0;
6487   conf = (struct mpconf*) P2V((uint) mp->physaddr);
6488   if(memcmp(conf, "PCMP", 4) != 0)
6489     return 0;
6490   if(conf->version != 1 && conf->version != 4)
6491     return 0;
6492   if(sum((uchar*)conf, conf->length) != 0)
6493     return 0;
6494   *pmp = mp;
6495   return conf;
6496 }
6497 
6498 
6499 
6500 void
6501 mpinit(void)
6502 {
6503   uchar *p, *e;
6504   struct mp *mp;
6505   struct mpconf *conf;
6506   struct mpproc *proc;
6507   struct mpioapic *ioapic;
6508 
6509   if((conf = mpconfig(&mp)) == 0)
6510     return;
6511   ismp = 1;
6512   lapic = (uint*)conf->lapicaddr;
6513   for(p=(uchar*)(conf+1), e=(uchar*)conf+conf->length; p<e; ){
6514     switch(*p){
6515     case MPPROC:
6516       proc = (struct mpproc*)p;
6517       if(ncpu < NCPU) {
6518         cpus[ncpu].apicid = proc->apicid;  // apicid may differ from ncpu
6519         ncpu++;
6520       }
6521       p += sizeof(struct mpproc);
6522       continue;
6523     case MPIOAPIC:
6524       ioapic = (struct mpioapic*)p;
6525       ioapicid = ioapic->apicno;
6526       p += sizeof(struct mpioapic);
6527       continue;
6528     case MPBUS:
6529     case MPIOINTR:
6530     case MPLINTR:
6531       p += 8;
6532       continue;
6533     default:
6534       ismp = 0;
6535       break;
6536     }
6537   }
6538   if(!ismp){
6539     // Didn't like what we found; fall back to no MP.
6540     ncpu = 1;
6541     lapic = 0;
6542     ioapicid = 0;
6543     return;
6544   }
6545 
6546 
6547 
6548 
6549 
6550   if(mp->imcrp){
6551     // Bochs doesn't support IMCR, so this doesn't run on Bochs.
6552     // But it would on real hardware.
6553     outb(0x22, 0x70);   // Select IMCR
6554     outb(0x23, inb(0x23) | 1);  // Mask external interrupts.
6555   }
6556 }
6557 
6558 
6559 
6560 
6561 
6562 
6563 
6564 
6565 
6566 
6567 
6568 
6569 
6570 
6571 
6572 
6573 
6574 
6575 
6576 
6577 
6578 
6579 
6580 
6581 
6582 
6583 
6584 
6585 
6586 
6587 
6588 
6589 
6590 
6591 
6592 
6593 
6594 
6595 
6596 
6597 
6598 
6599 
