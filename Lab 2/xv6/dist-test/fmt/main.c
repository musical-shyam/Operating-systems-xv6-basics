1200 #include "types.h"
1201 #include "defs.h"
1202 #include "param.h"
1203 #include "memlayout.h"
1204 #include "mmu.h"
1205 #include "proc.h"
1206 #include "x86.h"
1207 
1208 static void startothers(void);
1209 static void mpmain(void)  __attribute__((noreturn));
1210 extern pde_t *kpgdir;
1211 extern char end[]; // first address after kernel loaded from ELF file
1212 
1213 // Bootstrap processor starts running C code here.
1214 // Allocate a real stack and switch to it, first
1215 // doing some setup required for memory allocator to work.
1216 int
1217 main(void)
1218 {
1219   kinit1(end, P2V(4*1024*1024)); // phys page allocator
1220   kvmalloc();      // kernel page table
1221   mpinit();        // detect other processors
1222   lapicinit();     // interrupt controller
1223   seginit();       // segment descriptors
1224   cprintf("\ncpu%d: starting xv6\n\n", cpunum());
1225   picinit();       // another interrupt controller
1226   ioapicinit();    // another interrupt controller
1227   consoleinit();   // console hardware
1228   uartinit();      // serial port
1229   pinit();         // process table
1230   tvinit();        // trap vectors
1231   binit();         // buffer cache
1232   fileinit();      // file table
1233   ideinit();       // disk
1234   if(!ismp)
1235     timerinit();   // uniprocessor timer
1236   startothers();   // start other processors
1237   kinit2(P2V(4*1024*1024), P2V(PHYSTOP)); // must come after startothers()
1238   userinit();      // first user process
1239   mpmain();        // finish this processor's setup
1240 }
1241 
1242 
1243 
1244 
1245 
1246 
1247 
1248 
1249 
1250 // Other CPUs jump here from entryother.S.
1251 static void
1252 mpenter(void)
1253 {
1254   switchkvm();
1255   seginit();
1256   lapicinit();
1257   mpmain();
1258 }
1259 
1260 // Common CPU setup code.
1261 static void
1262 mpmain(void)
1263 {
1264   cprintf("cpu%d: starting\n", cpunum());
1265   idtinit();       // load idt register
1266   xchg(&cpu->started, 1); // tell startothers() we're up
1267   scheduler();     // start running processes
1268 }
1269 
1270 pde_t entrypgdir[];  // For entry.S
1271 
1272 // Start the non-boot (AP) processors.
1273 static void
1274 startothers(void)
1275 {
1276   extern uchar _binary_entryother_start[], _binary_entryother_size[];
1277   uchar *code;
1278   struct cpu *c;
1279   char *stack;
1280 
1281   // Write entry code to unused memory at 0x7000.
1282   // The linker has placed the image of entryother.S in
1283   // _binary_entryother_start.
1284   code = P2V(0x7000);
1285   memmove(code, _binary_entryother_start, (uint)_binary_entryother_size);
1286 
1287   for(c = cpus; c < cpus+ncpu; c++){
1288     if(c == cpus+cpunum())  // We've started already.
1289       continue;
1290 
1291     // Tell entryother.S what stack to use, where to enter, and what
1292     // pgdir to use. We cannot use kpgdir yet, because the AP processor
1293     // is running in low  memory, so we use entrypgdir for the APs too.
1294     stack = kalloc();
1295     *(void**)(code-4) = stack + KSTACKSIZE;
1296     *(void**)(code-8) = mpenter;
1297     *(int**)(code-12) = (void *) V2P(entrypgdir);
1298 
1299     lapicstartap(c->apicid, V2P(code));
1300     // wait for cpu to finish mpmain()
1301     while(c->started == 0)
1302       ;
1303   }
1304 }
1305 
1306 // The boot page table used in entry.S and entryother.S.
1307 // Page directories (and page tables) must start on page boundaries,
1308 // hence the __aligned__ attribute.
1309 // PTE_PS in a page directory entry enables 4Mbyte pages.
1310 
1311 __attribute__((__aligned__(PGSIZE)))
1312 pde_t entrypgdir[NPDENTRIES] = {
1313   // Map VA's [0, 4MB) to PA's [0, 4MB)
1314   [0] = (0) | PTE_P | PTE_W | PTE_PS,
1315   // Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
1316   [KERNBASE>>PDXSHIFT] = (0) | PTE_P | PTE_W | PTE_PS,
1317 };
1318 
1319 // Blank page.
1320 
1321 
1322 
1323 
1324 
1325 
1326 
1327 
1328 
1329 
1330 
1331 
1332 
1333 
1334 
1335 
1336 
1337 
1338 
1339 
1340 
1341 
1342 
1343 
1344 
1345 
1346 
1347 
1348 
1349 
