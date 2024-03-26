6600 // The local APIC manages internal (non-I/O) interrupts.
6601 // See Chapter 8 & Appendix C of Intel processor manual volume 3.
6602 
6603 #include "param.h"
6604 #include "types.h"
6605 #include "defs.h"
6606 #include "date.h"
6607 #include "memlayout.h"
6608 #include "traps.h"
6609 #include "mmu.h"
6610 #include "x86.h"
6611 #include "proc.h"  // ncpu
6612 
6613 // Local APIC registers, divided by 4 for use as uint[] indices.
6614 #define ID      (0x0020/4)   // ID
6615 #define VER     (0x0030/4)   // Version
6616 #define TPR     (0x0080/4)   // Task Priority
6617 #define EOI     (0x00B0/4)   // EOI
6618 #define SVR     (0x00F0/4)   // Spurious Interrupt Vector
6619   #define ENABLE     0x00000100   // Unit Enable
6620 #define ESR     (0x0280/4)   // Error Status
6621 #define ICRLO   (0x0300/4)   // Interrupt Command
6622   #define INIT       0x00000500   // INIT/RESET
6623   #define STARTUP    0x00000600   // Startup IPI
6624   #define DELIVS     0x00001000   // Delivery status
6625   #define ASSERT     0x00004000   // Assert interrupt (vs deassert)
6626   #define DEASSERT   0x00000000
6627   #define LEVEL      0x00008000   // Level triggered
6628   #define BCAST      0x00080000   // Send to all APICs, including self.
6629   #define BUSY       0x00001000
6630   #define FIXED      0x00000000
6631 #define ICRHI   (0x0310/4)   // Interrupt Command [63:32]
6632 #define TIMER   (0x0320/4)   // Local Vector Table 0 (TIMER)
6633   #define X1         0x0000000B   // divide counts by 1
6634   #define PERIODIC   0x00020000   // Periodic
6635 #define PCINT   (0x0340/4)   // Performance Counter LVT
6636 #define LINT0   (0x0350/4)   // Local Vector Table 1 (LINT0)
6637 #define LINT1   (0x0360/4)   // Local Vector Table 2 (LINT1)
6638 #define ERROR   (0x0370/4)   // Local Vector Table 3 (ERROR)
6639   #define MASKED     0x00010000   // Interrupt masked
6640 #define TICR    (0x0380/4)   // Timer Initial Count
6641 #define TCCR    (0x0390/4)   // Timer Current Count
6642 #define TDCR    (0x03E0/4)   // Timer Divide Configuration
6643 
6644 volatile uint *lapic;  // Initialized in mp.c
6645 
6646 
6647 
6648 
6649 
6650 static void
6651 lapicw(int index, int value)
6652 {
6653   lapic[index] = value;
6654   lapic[ID];  // wait for write to finish, by reading
6655 }
6656 
6657 void
6658 lapicinit(void)
6659 {
6660   if(!lapic)
6661     return;
6662 
6663   // Enable local APIC; set spurious interrupt vector.
6664   lapicw(SVR, ENABLE | (T_IRQ0 + IRQ_SPURIOUS));
6665 
6666   // The timer repeatedly counts down at bus frequency
6667   // from lapic[TICR] and then issues an interrupt.
6668   // If xv6 cared more about precise timekeeping,
6669   // TICR would be calibrated using an external time source.
6670   lapicw(TDCR, X1);
6671   lapicw(TIMER, PERIODIC | (T_IRQ0 + IRQ_TIMER));
6672   lapicw(TICR, 10000000);
6673 
6674   // Disable logical interrupt lines.
6675   lapicw(LINT0, MASKED);
6676   lapicw(LINT1, MASKED);
6677 
6678   // Disable performance counter overflow interrupts
6679   // on machines that provide that interrupt entry.
6680   if(((lapic[VER]>>16) & 0xFF) >= 4)
6681     lapicw(PCINT, MASKED);
6682 
6683   // Map error interrupt to IRQ_ERROR.
6684   lapicw(ERROR, T_IRQ0 + IRQ_ERROR);
6685 
6686   // Clear error status register (requires back-to-back writes).
6687   lapicw(ESR, 0);
6688   lapicw(ESR, 0);
6689 
6690   // Ack any outstanding interrupts.
6691   lapicw(EOI, 0);
6692 
6693   // Send an Init Level De-Assert to synchronise arbitration ID's.
6694   lapicw(ICRHI, 0);
6695   lapicw(ICRLO, BCAST | INIT | LEVEL);
6696   while(lapic[ICRLO] & DELIVS)
6697     ;
6698 
6699 
6700   // Enable interrupts on the APIC (but not on the processor).
6701   lapicw(TPR, 0);
6702 }
6703 
6704 int
6705 cpunum(void)
6706 {
6707   int apicid, i;
6708 
6709   // Cannot call cpu when interrupts are enabled:
6710   // result not guaranteed to last long enough to be used!
6711   // Would prefer to panic but even printing is chancy here:
6712   // almost everything, including cprintf and panic, calls cpu,
6713   // often indirectly through acquire and release.
6714   if(readeflags()&FL_IF){
6715     static int n;
6716     if(n++ == 0)
6717       cprintf("cpu called from %x with interrupts enabled\n",
6718         __builtin_return_address(0));
6719   }
6720 
6721   if (!lapic)
6722     return 0;
6723 
6724   apicid = lapic[ID] >> 24;
6725   for (i = 0; i < ncpu; ++i) {
6726     if (cpus[i].apicid == apicid)
6727       return i;
6728   }
6729   panic("unknown apicid\n");
6730 }
6731 
6732 // Acknowledge interrupt.
6733 void
6734 lapiceoi(void)
6735 {
6736   if(lapic)
6737     lapicw(EOI, 0);
6738 }
6739 
6740 // Spin for a given number of microseconds.
6741 // On real hardware would want to tune this dynamically.
6742 void
6743 microdelay(int us)
6744 {
6745 }
6746 
6747 
6748 
6749 
6750 #define CMOS_PORT    0x70
6751 #define CMOS_RETURN  0x71
6752 
6753 // Start additional processor running entry code at addr.
6754 // See Appendix B of MultiProcessor Specification.
6755 void
6756 lapicstartap(uchar apicid, uint addr)
6757 {
6758   int i;
6759   ushort *wrv;
6760 
6761   // "The BSP must initialize CMOS shutdown code to 0AH
6762   // and the warm reset vector (DWORD based at 40:67) to point at
6763   // the AP startup code prior to the [universal startup algorithm]."
6764   outb(CMOS_PORT, 0xF);  // offset 0xF is shutdown code
6765   outb(CMOS_PORT+1, 0x0A);
6766   wrv = (ushort*)P2V((0x40<<4 | 0x67));  // Warm reset vector
6767   wrv[0] = 0;
6768   wrv[1] = addr >> 4;
6769 
6770   // "Universal startup algorithm."
6771   // Send INIT (level-triggered) interrupt to reset other CPU.
6772   lapicw(ICRHI, apicid<<24);
6773   lapicw(ICRLO, INIT | LEVEL | ASSERT);
6774   microdelay(200);
6775   lapicw(ICRLO, INIT | LEVEL);
6776   microdelay(100);    // should be 10ms, but too slow in Bochs!
6777 
6778   // Send startup IPI (twice!) to enter code.
6779   // Regular hardware is supposed to only accept a STARTUP
6780   // when it is in the halted state due to an INIT.  So the second
6781   // should be ignored, but it is part of the official Intel algorithm.
6782   // Bochs complains about the second one.  Too bad for Bochs.
6783   for(i = 0; i < 2; i++){
6784     lapicw(ICRHI, apicid<<24);
6785     lapicw(ICRLO, STARTUP | (addr>>12));
6786     microdelay(200);
6787   }
6788 }
6789 
6790 
6791 
6792 
6793 
6794 
6795 
6796 
6797 
6798 
6799 
6800 #define CMOS_STATA   0x0a
6801 #define CMOS_STATB   0x0b
6802 #define CMOS_UIP    (1 << 7)        // RTC update in progress
6803 
6804 #define SECS    0x00
6805 #define MINS    0x02
6806 #define HOURS   0x04
6807 #define DAY     0x07
6808 #define MONTH   0x08
6809 #define YEAR    0x09
6810 
6811 static uint cmos_read(uint reg)
6812 {
6813   outb(CMOS_PORT,  reg);
6814   microdelay(200);
6815 
6816   return inb(CMOS_RETURN);
6817 }
6818 
6819 static void fill_rtcdate(struct rtcdate *r)
6820 {
6821   r->second = cmos_read(SECS);
6822   r->minute = cmos_read(MINS);
6823   r->hour   = cmos_read(HOURS);
6824   r->day    = cmos_read(DAY);
6825   r->month  = cmos_read(MONTH);
6826   r->year   = cmos_read(YEAR);
6827 }
6828 
6829 // qemu seems to use 24-hour GWT and the values are BCD encoded
6830 void cmostime(struct rtcdate *r)
6831 {
6832   struct rtcdate t1, t2;
6833   int sb, bcd;
6834 
6835   sb = cmos_read(CMOS_STATB);
6836 
6837   bcd = (sb & (1 << 2)) == 0;
6838 
6839   // make sure CMOS doesn't modify time while we read it
6840   for(;;) {
6841     fill_rtcdate(&t1);
6842     if(cmos_read(CMOS_STATA) & CMOS_UIP)
6843         continue;
6844     fill_rtcdate(&t2);
6845     if(memcmp(&t1, &t2, sizeof(t1)) == 0)
6846       break;
6847   }
6848 
6849 
6850   // convert
6851   if(bcd) {
6852 #define    CONV(x)     (t1.x = ((t1.x >> 4) * 10) + (t1.x & 0xf))
6853     CONV(second);
6854     CONV(minute);
6855     CONV(hour  );
6856     CONV(day   );
6857     CONV(month );
6858     CONV(year  );
6859 #undef     CONV
6860   }
6861 
6862   *r = t1;
6863   r->year += 2000;
6864 }
6865 
6866 
6867 
6868 
6869 
6870 
6871 
6872 
6873 
6874 
6875 
6876 
6877 
6878 
6879 
6880 
6881 
6882 
6883 
6884 
6885 
6886 
6887 
6888 
6889 
6890 
6891 
6892 
6893 
6894 
6895 
6896 
6897 
6898 
6899 
