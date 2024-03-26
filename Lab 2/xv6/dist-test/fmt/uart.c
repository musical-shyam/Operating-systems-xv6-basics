7650 // Intel 8250 serial port (UART).
7651 
7652 #include "types.h"
7653 #include "defs.h"
7654 #include "param.h"
7655 #include "traps.h"
7656 #include "spinlock.h"
7657 #include "sleeplock.h"
7658 #include "fs.h"
7659 #include "file.h"
7660 #include "mmu.h"
7661 #include "proc.h"
7662 #include "x86.h"
7663 
7664 #define COM1    0x3f8
7665 
7666 static int uart;    // is there a uart?
7667 
7668 void
7669 uartinit(void)
7670 {
7671   char *p;
7672 
7673   // Turn off the FIFO
7674   outb(COM1+2, 0);
7675 
7676   // 9600 baud, 8 data bits, 1 stop bit, parity off.
7677   outb(COM1+3, 0x80);    // Unlock divisor
7678   outb(COM1+0, 115200/9600);
7679   outb(COM1+1, 0);
7680   outb(COM1+3, 0x03);    // Lock divisor, 8 data bits.
7681   outb(COM1+4, 0);
7682   outb(COM1+1, 0x01);    // Enable receive interrupts.
7683 
7684   // If status is 0xFF, no serial port.
7685   if(inb(COM1+5) == 0xFF)
7686     return;
7687   uart = 1;
7688 
7689   // Acknowledge pre-existing interrupt conditions;
7690   // enable interrupts.
7691   inb(COM1+2);
7692   inb(COM1+0);
7693   picenable(IRQ_COM1);
7694   ioapicenable(IRQ_COM1, 0);
7695 
7696   // Announce that we're here.
7697   for(p="xv6...\n"; *p; p++)
7698     uartputc(*p);
7699 }
7700 void
7701 uartputc(int c)
7702 {
7703   int i;
7704 
7705   if(!uart)
7706     return;
7707   for(i = 0; i < 128 && !(inb(COM1+5) & 0x20); i++)
7708     microdelay(10);
7709   outb(COM1+0, c);
7710 }
7711 
7712 static int
7713 uartgetc(void)
7714 {
7715   if(!uart)
7716     return -1;
7717   if(!(inb(COM1+5) & 0x01))
7718     return -1;
7719   return inb(COM1+0);
7720 }
7721 
7722 void
7723 uartintr(void)
7724 {
7725   consoleintr(uartgetc);
7726 }
7727 
7728 
7729 
7730 
7731 
7732 
7733 
7734 
7735 
7736 
7737 
7738 
7739 
7740 
7741 
7742 
7743 
7744 
7745 
7746 
7747 
7748 
7749 
