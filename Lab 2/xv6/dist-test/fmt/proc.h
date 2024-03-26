2000 // Per-CPU state
2001 struct cpu {
2002   uchar apicid;                // Local APIC ID
2003   struct context *scheduler;   // swtch() here to enter scheduler
2004   struct taskstate ts;         // Used by x86 to find stack for interrupt
2005   struct segdesc gdt[NSEGS];   // x86 global descriptor table
2006   volatile uint started;       // Has the CPU started?
2007   int ncli;                    // Depth of pushcli nesting.
2008   int intena;                  // Were interrupts enabled before pushcli?
2009 
2010   // Cpu-local storage variables; see below
2011   struct cpu *cpu;
2012   struct proc *proc;           // The currently-running process.
2013 };
2014 
2015 extern struct cpu cpus[NCPU];
2016 extern int ncpu;
2017 
2018 // Per-CPU variables, holding pointers to the
2019 // current cpu and to the current process.
2020 // The asm suffix tells gcc to use "%gs:0" to refer to cpu
2021 // and "%gs:4" to refer to proc.  seginit sets up the
2022 // %gs segment register so that %gs refers to the memory
2023 // holding those two variables in the local cpu's struct cpu.
2024 // This is similar to how thread-local variables are implemented
2025 // in thread libraries such as Linux pthreads.
2026 extern struct cpu *cpu asm("%gs:0");       // &cpus[cpunum()]
2027 extern struct proc *proc asm("%gs:4");     // cpus[cpunum()].proc
2028 
2029 // Saved registers for kernel context switches.
2030 // Don't need to save all the segment registers (%cs, etc),
2031 // because they are constant across kernel contexts.
2032 // Don't need to save %eax, %ecx, %edx, because the
2033 // x86 convention is that the caller has saved them.
2034 // Contexts are stored at the bottom of the stack they
2035 // describe; the stack pointer is the address of the context.
2036 // The layout of the context matches the layout of the stack in swtch.S
2037 // at the "Switch stacks" comment. Switch doesn't save eip explicitly,
2038 // but it is on the stack and allocproc() manipulates it.
2039 struct context {
2040   uint edi;
2041   uint esi;
2042   uint ebx;
2043   uint ebp;
2044   uint eip;
2045 };
2046 
2047 
2048 
2049 
2050 enum procstate { UNUSED, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
2051 
2052 // Per-process state
2053 struct proc {
2054   uint sz;                     // Size of process memory (bytes)
2055   pde_t* pgdir;                // Page table
2056   char *kstack;                // Bottom of kernel stack for this process
2057   enum procstate state;        // Process state
2058   int pid;                     // Process ID
2059   struct proc *parent;         // Parent process
2060   struct trapframe *tf;        // Trap frame for current syscall
2061   struct context *context;     // swtch() here to run process
2062   void *chan;                  // If non-zero, sleeping on chan
2063   int killed;                  // If non-zero, have been killed
2064   struct file *ofile[NOFILE];  // Open files
2065   struct inode *cwd;           // Current directory
2066   char name[16];               // Process name (debugging)
2067 };
2068 
2069 // Process memory is laid out contiguously, low addresses first:
2070 //   text
2071 //   original data and bss
2072 //   fixed-size stack
2073 //   expandable heap
2074 
2075 
2076 
2077 
2078 
2079 
2080 
2081 
2082 
2083 
2084 
2085 
2086 
2087 
2088 
2089 
2090 
2091 
2092 
2093 
2094 
2095 
2096 
2097 
2098 
2099 
