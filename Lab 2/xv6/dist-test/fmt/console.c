7300 // Console input and output.
7301 // Input is from the keyboard or serial port.
7302 // Output is written to the screen and serial port.
7303 
7304 #include "types.h"
7305 #include "defs.h"
7306 #include "param.h"
7307 #include "traps.h"
7308 #include "spinlock.h"
7309 #include "sleeplock.h"
7310 #include "fs.h"
7311 #include "file.h"
7312 #include "memlayout.h"
7313 #include "mmu.h"
7314 #include "proc.h"
7315 #include "x86.h"
7316 
7317 static void consputc(int);
7318 
7319 static int panicked = 0;
7320 
7321 static struct {
7322   struct spinlock lock;
7323   int locking;
7324 } cons;
7325 
7326 static void
7327 printint(int xx, int base, int sign)
7328 {
7329   static char digits[] = "0123456789abcdef";
7330   char buf[16];
7331   int i;
7332   uint x;
7333 
7334   if(sign && (sign = xx < 0))
7335     x = -xx;
7336   else
7337     x = xx;
7338 
7339   i = 0;
7340   do{
7341     buf[i++] = digits[x % base];
7342   }while((x /= base) != 0);
7343 
7344   if(sign)
7345     buf[i++] = '-';
7346 
7347   while(--i >= 0)
7348     consputc(buf[i]);
7349 }
7350 // Print to the console. only understands %d, %x, %p, %s.
7351 void
7352 cprintf(char *fmt, ...)
7353 {
7354   int i, c, locking;
7355   uint *argp;
7356   char *s;
7357 
7358   locking = cons.locking;
7359   if(locking)
7360     acquire(&cons.lock);
7361 
7362   if (fmt == 0)
7363     panic("null fmt");
7364 
7365   argp = (uint*)(void*)(&fmt + 1);
7366   for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
7367     if(c != '%'){
7368       consputc(c);
7369       continue;
7370     }
7371     c = fmt[++i] & 0xff;
7372     if(c == 0)
7373       break;
7374     switch(c){
7375     case 'd':
7376       printint(*argp++, 10, 1);
7377       break;
7378     case 'x':
7379     case 'p':
7380       printint(*argp++, 16, 0);
7381       break;
7382     case 's':
7383       if((s = (char*)*argp++) == 0)
7384         s = "(null)";
7385       for(; *s; s++)
7386         consputc(*s);
7387       break;
7388     case '%':
7389       consputc('%');
7390       break;
7391     default:
7392       // Print unknown % sequence to draw attention.
7393       consputc('%');
7394       consputc(c);
7395       break;
7396     }
7397   }
7398 
7399 
7400   if(locking)
7401     release(&cons.lock);
7402 }
7403 
7404 void
7405 panic(char *s)
7406 {
7407   int i;
7408   uint pcs[10];
7409 
7410   cli();
7411   cons.locking = 0;
7412   cprintf("cpu with apicid %d: panic: ", cpu->apicid);
7413   cprintf(s);
7414   cprintf("\n");
7415   getcallerpcs(&s, pcs);
7416   for(i=0; i<10; i++)
7417     cprintf(" %p", pcs[i]);
7418   panicked = 1; // freeze other CPU
7419   for(;;)
7420     ;
7421 }
7422 
7423 #define BACKSPACE 0x100
7424 #define CRTPORT 0x3d4
7425 static ushort *crt = (ushort*)P2V(0xb8000);  // CGA memory
7426 
7427 static void
7428 cgaputc(int c)
7429 {
7430   int pos;
7431 
7432   // Cursor position: col + 80*row.
7433   outb(CRTPORT, 14);
7434   pos = inb(CRTPORT+1) << 8;
7435   outb(CRTPORT, 15);
7436   pos |= inb(CRTPORT+1);
7437 
7438   if(c == '\n')
7439     pos += 80 - pos%80;
7440   else if(c == BACKSPACE){
7441     if(pos > 0) --pos;
7442   } else
7443     crt[pos++] = (c&0xff) | 0x0700;  // black on white
7444 
7445   if(pos < 0 || pos > 25*80)
7446     panic("pos under/overflow");
7447 
7448 
7449 
7450   if((pos/80) >= 24){  // Scroll up.
7451     memmove(crt, crt+80, sizeof(crt[0])*23*80);
7452     pos -= 80;
7453     memset(crt+pos, 0, sizeof(crt[0])*(24*80 - pos));
7454   }
7455 
7456   outb(CRTPORT, 14);
7457   outb(CRTPORT+1, pos>>8);
7458   outb(CRTPORT, 15);
7459   outb(CRTPORT+1, pos);
7460   crt[pos] = ' ' | 0x0700;
7461 }
7462 
7463 void
7464 consputc(int c)
7465 {
7466   if(panicked){
7467     cli();
7468     for(;;)
7469       ;
7470   }
7471 
7472   if(c == BACKSPACE){
7473     uartputc('\b'); uartputc(' '); uartputc('\b');
7474   } else
7475     uartputc(c);
7476   cgaputc(c);
7477 }
7478 
7479 #define INPUT_BUF 128
7480 struct {
7481   char buf[INPUT_BUF];
7482   uint r;  // Read index
7483   uint w;  // Write index
7484   uint e;  // Edit index
7485 } input;
7486 
7487 #define C(x)  ((x)-'@')  // Control-x
7488 
7489 void
7490 consoleintr(int (*getc)(void))
7491 {
7492   int c, doprocdump = 0;
7493 
7494   acquire(&cons.lock);
7495   while((c = getc()) >= 0){
7496     switch(c){
7497     case C('P'):  // Process listing.
7498       // procdump() locks cons.lock indirectly; invoke later
7499       doprocdump = 1;
7500       break;
7501     case C('U'):  // Kill line.
7502       while(input.e != input.w &&
7503             input.buf[(input.e-1) % INPUT_BUF] != '\n'){
7504         input.e--;
7505         consputc(BACKSPACE);
7506       }
7507       break;
7508     case C('H'): case '\x7f':  // Backspace
7509       if(input.e != input.w){
7510         input.e--;
7511         consputc(BACKSPACE);
7512       }
7513       break;
7514     default:
7515       if(c != 0 && input.e-input.r < INPUT_BUF){
7516         c = (c == '\r') ? '\n' : c;
7517         input.buf[input.e++ % INPUT_BUF] = c;
7518         consputc(c);
7519         if(c == '\n' || c == C('D') || input.e == input.r+INPUT_BUF){
7520           input.w = input.e;
7521           wakeup(&input.r);
7522         }
7523       }
7524       break;
7525     }
7526   }
7527   release(&cons.lock);
7528   if(doprocdump) {
7529     procdump();  // now call procdump() wo. cons.lock held
7530   }
7531 }
7532 
7533 int
7534 consoleread(struct inode *ip, char *dst, int n)
7535 {
7536   uint target;
7537   int c;
7538 
7539   iunlock(ip);
7540   target = n;
7541   acquire(&cons.lock);
7542   while(n > 0){
7543     while(input.r == input.w){
7544       if(proc->killed){
7545         release(&cons.lock);
7546         ilock(ip);
7547         return -1;
7548       }
7549       sleep(&input.r, &cons.lock);
7550     }
7551     c = input.buf[input.r++ % INPUT_BUF];
7552     if(c == C('D')){  // EOF
7553       if(n < target){
7554         // Save ^D for next time, to make sure
7555         // caller gets a 0-byte result.
7556         input.r--;
7557       }
7558       break;
7559     }
7560     *dst++ = c;
7561     --n;
7562     if(c == '\n')
7563       break;
7564   }
7565   release(&cons.lock);
7566   ilock(ip);
7567 
7568   return target - n;
7569 }
7570 
7571 int
7572 consolewrite(struct inode *ip, char *buf, int n)
7573 {
7574   int i;
7575 
7576   iunlock(ip);
7577   acquire(&cons.lock);
7578   for(i = 0; i < n; i++)
7579     consputc(buf[i] & 0xff);
7580   release(&cons.lock);
7581   ilock(ip);
7582 
7583   return n;
7584 }
7585 
7586 void
7587 consoleinit(void)
7588 {
7589   initlock(&cons.lock, "console");
7590 
7591   devsw[CONSOLE].write = consolewrite;
7592   devsw[CONSOLE].read = consoleread;
7593   cons.locking = 1;
7594 
7595   picenable(IRQ_KBD);
7596   ioapicenable(IRQ_KBD, 0);
7597 }
7598 
7599 
