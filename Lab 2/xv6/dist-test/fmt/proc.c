2100 #include "types.h"
2101 #include "defs.h"
2102 #include "param.h"
2103 #include "memlayout.h"
2104 #include "mmu.h"
2105 #include "x86.h"
2106 #include "proc.h"
2107 #include "spinlock.h"
2108 
2109 struct {
2110   struct spinlock lock;
2111   struct proc proc[NPROC];
2112 } ptable;
2113 
2114 static struct proc *initproc;
2115 
2116 int nextpid = 1;
2117 extern void forkret(void);
2118 extern void trapret(void);
2119 
2120 static void wakeup1(void *chan);
2121 
2122 void
2123 pinit(void)
2124 {
2125   initlock(&ptable.lock, "ptable");
2126 }
2127 
2128 // Look in the process table for an UNUSED proc.
2129 // If found, change state to EMBRYO and initialize
2130 // state required to run in the kernel.
2131 // Otherwise return 0.
2132 static struct proc*
2133 allocproc(void)
2134 {
2135   struct proc *p;
2136   char *sp;
2137 
2138   acquire(&ptable.lock);
2139 
2140   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
2141     if(p->state == UNUSED)
2142       goto found;
2143 
2144   release(&ptable.lock);
2145   return 0;
2146 
2147 found:
2148   p->state = EMBRYO;
2149   p->pid = nextpid++;
2150   release(&ptable.lock);
2151 
2152   // Allocate kernel stack.
2153   if((p->kstack = kalloc()) == 0){
2154     p->state = UNUSED;
2155     return 0;
2156   }
2157   sp = p->kstack + KSTACKSIZE;
2158 
2159   // Leave room for trap frame.
2160   sp -= sizeof *p->tf;
2161   p->tf = (struct trapframe*)sp;
2162 
2163   // Set up new context to start executing at forkret,
2164   // which returns to trapret.
2165   sp -= 4;
2166   *(uint*)sp = (uint)trapret;
2167 
2168   sp -= sizeof *p->context;
2169   p->context = (struct context*)sp;
2170   memset(p->context, 0, sizeof *p->context);
2171   p->context->eip = (uint)forkret;
2172 
2173   return p;
2174 }
2175 
2176 // Set up first user process.
2177 void
2178 userinit(void)
2179 {
2180   struct proc *p;
2181   extern char _binary_initcode_start[], _binary_initcode_size[];
2182 
2183   p = allocproc();
2184 
2185   initproc = p;
2186   if((p->pgdir = setupkvm()) == 0)
2187     panic("userinit: out of memory?");
2188   inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
2189   p->sz = PGSIZE;
2190   memset(p->tf, 0, sizeof(*p->tf));
2191   p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
2192   p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
2193   p->tf->es = p->tf->ds;
2194   p->tf->ss = p->tf->ds;
2195   p->tf->eflags = FL_IF;
2196   p->tf->esp = PGSIZE;
2197   p->tf->eip = 0;  // beginning of initcode.S
2198 
2199 
2200   safestrcpy(p->name, "initcode", sizeof(p->name));
2201   p->cwd = namei("/");
2202 
2203   // this assignment to p->state lets other cores
2204   // run this process. the acquire forces the above
2205   // writes to be visible, and the lock is also needed
2206   // because the assignment might not be atomic.
2207   acquire(&ptable.lock);
2208 
2209   p->state = RUNNABLE;
2210 
2211   release(&ptable.lock);
2212 }
2213 
2214 // Grow current process's memory by n bytes.
2215 // Return 0 on success, -1 on failure.
2216 int
2217 growproc(int n)
2218 {
2219   uint sz;
2220 
2221   sz = proc->sz;
2222   if(n > 0){
2223     if((sz = allocuvm(proc->pgdir, sz, sz + n)) == 0)
2224       return -1;
2225   } else if(n < 0){
2226     if((sz = deallocuvm(proc->pgdir, sz, sz + n)) == 0)
2227       return -1;
2228   }
2229   proc->sz = sz;
2230   switchuvm(proc);
2231   return 0;
2232 }
2233 
2234 // Create a new process copying p as the parent.
2235 // Sets up stack to return as if from system call.
2236 // Caller must set state of returned proc to RUNNABLE.
2237 int
2238 fork(void)
2239 {
2240   int i, pid;
2241   struct proc *np;
2242 
2243   // Allocate process.
2244   if((np = allocproc()) == 0){
2245     return -1;
2246   }
2247 
2248 
2249 
2250   // Copy process state from p.
2251   if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
2252     kfree(np->kstack);
2253     np->kstack = 0;
2254     np->state = UNUSED;
2255     return -1;
2256   }
2257   np->sz = proc->sz;
2258   np->parent = proc;
2259   *np->tf = *proc->tf;
2260 
2261   // Clear %eax so that fork returns 0 in the child.
2262   np->tf->eax = 0;
2263 
2264   for(i = 0; i < NOFILE; i++)
2265     if(proc->ofile[i])
2266       np->ofile[i] = filedup(proc->ofile[i]);
2267   np->cwd = idup(proc->cwd);
2268 
2269   safestrcpy(np->name, proc->name, sizeof(proc->name));
2270 
2271   pid = np->pid;
2272 
2273   acquire(&ptable.lock);
2274 
2275   np->state = RUNNABLE;
2276 
2277   release(&ptable.lock);
2278 
2279   return pid;
2280 }
2281 
2282 // Exit the current process.  Does not return.
2283 // An exited process remains in the zombie state
2284 // until its parent calls wait() to find out it exited.
2285 void
2286 exit(void)
2287 {
2288   struct proc *p;
2289   int fd;
2290 
2291   if(proc == initproc)
2292     panic("init exiting");
2293 
2294   // Close all open files.
2295   for(fd = 0; fd < NOFILE; fd++){
2296     if(proc->ofile[fd]){
2297       fileclose(proc->ofile[fd]);
2298       proc->ofile[fd] = 0;
2299     }
2300   }
2301 
2302   begin_op();
2303   iput(proc->cwd);
2304   end_op();
2305   proc->cwd = 0;
2306 
2307   acquire(&ptable.lock);
2308 
2309   // Parent might be sleeping in wait().
2310   wakeup1(proc->parent);
2311 
2312   // Pass abandoned children to init.
2313   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
2314     if(p->parent == proc){
2315       p->parent = initproc;
2316       if(p->state == ZOMBIE)
2317         wakeup1(initproc);
2318     }
2319   }
2320 
2321   // Jump into the scheduler, never to return.
2322   proc->state = ZOMBIE;
2323   sched();
2324   panic("zombie exit");
2325 }
2326 
2327 // Wait for a child process to exit and return its pid.
2328 // Return -1 if this process has no children.
2329 int
2330 wait(void)
2331 {
2332   struct proc *p;
2333   int havekids, pid;
2334 
2335   acquire(&ptable.lock);
2336   for(;;){
2337     // Scan through table looking for exited children.
2338     havekids = 0;
2339     for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
2340       if(p->parent != proc)
2341         continue;
2342       havekids = 1;
2343       if(p->state == ZOMBIE){
2344         // Found one.
2345         pid = p->pid;
2346         kfree(p->kstack);
2347         p->kstack = 0;
2348         freevm(p->pgdir);
2349         p->pid = 0;
2350         p->parent = 0;
2351         p->name[0] = 0;
2352         p->killed = 0;
2353         p->state = UNUSED;
2354         release(&ptable.lock);
2355         return pid;
2356       }
2357     }
2358 
2359     // No point waiting if we don't have any children.
2360     if(!havekids || proc->killed){
2361       release(&ptable.lock);
2362       return -1;
2363     }
2364 
2365     // Wait for children to exit.  (See wakeup1 call in proc_exit.)
2366     sleep(proc, &ptable.lock);  //DOC: wait-sleep
2367   }
2368 }
2369 
2370 // Per-CPU process scheduler.
2371 // Each CPU calls scheduler() after setting itself up.
2372 // Scheduler never returns.  It loops, doing:
2373 //  - choose a process to run
2374 //  - swtch to start running that process
2375 //  - eventually that process transfers control
2376 //      via swtch back to the scheduler.
2377 void
2378 scheduler(void)
2379 {
2380   struct proc *p;
2381 
2382   for(;;){
2383     // Enable interrupts on this processor.
2384     sti();
2385 
2386     // Loop over process table looking for process to run.
2387     acquire(&ptable.lock);
2388     for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
2389       if(p->state != RUNNABLE)
2390         continue;
2391 
2392       // Switch to chosen process.  It is the process's job
2393       // to release ptable.lock and then reacquire it
2394       // before jumping back to us.
2395       proc = p;
2396       switchuvm(p);
2397       p->state = RUNNING;
2398       swtch(&cpu->scheduler, p->context);
2399       switchkvm();
2400       // Process is done running for now.
2401       // It should have changed its p->state before coming back.
2402       proc = 0;
2403     }
2404     release(&ptable.lock);
2405 
2406   }
2407 }
2408 
2409 // Enter scheduler.  Must hold only ptable.lock
2410 // and have changed proc->state. Saves and restores
2411 // intena because intena is a property of this
2412 // kernel thread, not this CPU. It should
2413 // be proc->intena and proc->ncli, but that would
2414 // break in the few places where a lock is held but
2415 // there's no process.
2416 void
2417 sched(void)
2418 {
2419   int intena;
2420 
2421   if(!holding(&ptable.lock))
2422     panic("sched ptable.lock");
2423   if(cpu->ncli != 1)
2424     panic("sched locks");
2425   if(proc->state == RUNNING)
2426     panic("sched running");
2427   if(readeflags()&FL_IF)
2428     panic("sched interruptible");
2429   intena = cpu->intena;
2430   swtch(&proc->context, cpu->scheduler);
2431   cpu->intena = intena;
2432 }
2433 
2434 // Give up the CPU for one scheduling round.
2435 void
2436 yield(void)
2437 {
2438   acquire(&ptable.lock);  //DOC: yieldlock
2439   proc->state = RUNNABLE;
2440   sched();
2441   release(&ptable.lock);
2442 }
2443 
2444 
2445 
2446 
2447 
2448 
2449 
2450 // A fork child's very first scheduling by scheduler()
2451 // will swtch here.  "Return" to user space.
2452 void
2453 forkret(void)
2454 {
2455   static int first = 1;
2456   // Still holding ptable.lock from scheduler.
2457   release(&ptable.lock);
2458 
2459   if (first) {
2460     // Some initialization functions must be run in the context
2461     // of a regular process (e.g., they call sleep), and thus cannot
2462     // be run from main().
2463     first = 0;
2464     iinit(ROOTDEV);
2465     initlog(ROOTDEV);
2466   }
2467 
2468   // Return to "caller", actually trapret (see allocproc).
2469 }
2470 
2471 // Atomically release lock and sleep on chan.
2472 // Reacquires lock when awakened.
2473 void
2474 sleep(void *chan, struct spinlock *lk)
2475 {
2476   if(proc == 0)
2477     panic("sleep");
2478 
2479   if(lk == 0)
2480     panic("sleep without lk");
2481 
2482   // Must acquire ptable.lock in order to
2483   // change p->state and then call sched.
2484   // Once we hold ptable.lock, we can be
2485   // guaranteed that we won't miss any wakeup
2486   // (wakeup runs with ptable.lock locked),
2487   // so it's okay to release lk.
2488   if(lk != &ptable.lock){  //DOC: sleeplock0
2489     acquire(&ptable.lock);  //DOC: sleeplock1
2490     release(lk);
2491   }
2492 
2493   // Go to sleep.
2494   proc->chan = chan;
2495   proc->state = SLEEPING;
2496   sched();
2497 
2498   // Tidy up.
2499   proc->chan = 0;
2500   // Reacquire original lock.
2501   if(lk != &ptable.lock){  //DOC: sleeplock2
2502     release(&ptable.lock);
2503     acquire(lk);
2504   }
2505 }
2506 
2507 // Wake up all processes sleeping on chan.
2508 // The ptable lock must be held.
2509 static void
2510 wakeup1(void *chan)
2511 {
2512   struct proc *p;
2513 
2514   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
2515     if(p->state == SLEEPING && p->chan == chan)
2516       p->state = RUNNABLE;
2517 }
2518 
2519 // Wake up all processes sleeping on chan.
2520 void
2521 wakeup(void *chan)
2522 {
2523   acquire(&ptable.lock);
2524   wakeup1(chan);
2525   release(&ptable.lock);
2526 }
2527 
2528 // Kill the process with the given pid.
2529 // Process won't exit until it returns
2530 // to user space (see trap in trap.c).
2531 int
2532 kill(int pid)
2533 {
2534   struct proc *p;
2535 
2536   acquire(&ptable.lock);
2537   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
2538     if(p->pid == pid){
2539       p->killed = 1;
2540       // Wake process from sleep if necessary.
2541       if(p->state == SLEEPING)
2542         p->state = RUNNABLE;
2543       release(&ptable.lock);
2544       return 0;
2545     }
2546   }
2547   release(&ptable.lock);
2548   return -1;
2549 }
2550 // Print a process listing to console.  For debugging.
2551 // Runs when user types ^P on console.
2552 // No lock to avoid wedging a stuck machine further.
2553 void
2554 procdump(void)
2555 {
2556   static char *states[] = {
2557   [UNUSED]    "unused",
2558   [EMBRYO]    "embryo",
2559   [SLEEPING]  "sleep ",
2560   [RUNNABLE]  "runble",
2561   [RUNNING]   "run   ",
2562   [ZOMBIE]    "zombie"
2563   };
2564   int i;
2565   struct proc *p;
2566   char *state;
2567   uint pc[10];
2568 
2569   for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
2570     if(p->state == UNUSED)
2571       continue;
2572     if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
2573       state = states[p->state];
2574     else
2575       state = "???";
2576     cprintf("%d %s %s", p->pid, state, p->name);
2577     if(p->state == SLEEPING){
2578       getcallerpcs((uint*)p->context->ebp+2, pc);
2579       for(i=0; i<10 && pc[i] != 0; i++)
2580         cprintf(" %p", pc[i]);
2581     }
2582     cprintf("\n");
2583   }
2584 }
2585 
2586 
2587 
2588 
2589 
2590 
2591 
2592 
2593 
2594 
2595 
2596 
2597 
2598 
2599 
