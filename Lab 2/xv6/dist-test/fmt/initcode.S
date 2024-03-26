7750 # Initial process execs /init.
7751 # This code runs in user space.
7752 
7753 #include "syscall.h"
7754 #include "traps.h"
7755 
7756 
7757 # exec(init, argv)
7758 .globl start
7759 start:
7760   pushl $argv
7761   pushl $init
7762   pushl $0  // where caller pc would be
7763   movl $SYS_exec, %eax
7764   int $T_SYSCALL
7765 
7766 # for(;;) exit();
7767 exit:
7768   movl $SYS_exit, %eax
7769   int $T_SYSCALL
7770   jmp exit
7771 
7772 # char init[] = "/init\0";
7773 init:
7774   .string "/init\0"
7775 
7776 # char *argv[] = { init, 0 };
7777 .p2align 2
7778 argv:
7779   .long init
7780   .long 0
7781 
7782 
7783 
7784 
7785 
7786 
7787 
7788 
7789 
7790 
7791 
7792 
7793 
7794 
7795 
7796 
7797 
7798 
7799 
