8450 #include "asm.h"
8451 #include "memlayout.h"
8452 #include "mmu.h"
8453 
8454 # Start the first CPU: switch to 32-bit protected mode, jump into C.
8455 # The BIOS loads this code from the first sector of the hard disk into
8456 # memory at physical address 0x7c00 and starts executing in real mode
8457 # with %cs=0 %ip=7c00.
8458 
8459 .code16                       # Assemble for 16-bit mode
8460 .globl start
8461 start:
8462   cli                         # BIOS enabled interrupts; disable
8463 
8464   # Zero data segment registers DS, ES, and SS.
8465   xorw    %ax,%ax             # Set %ax to zero
8466   movw    %ax,%ds             # -> Data Segment
8467   movw    %ax,%es             # -> Extra Segment
8468   movw    %ax,%ss             # -> Stack Segment
8469 
8470   # Physical address line A20 is tied to zero so that the first PCs
8471   # with 2 MB would run software that assumed 1 MB.  Undo that.
8472 seta20.1:
8473   inb     $0x64,%al               # Wait for not busy
8474   testb   $0x2,%al
8475   jnz     seta20.1
8476 
8477   movb    $0xd1,%al               # 0xd1 -> port 0x64
8478   outb    %al,$0x64
8479 
8480 seta20.2:
8481   inb     $0x64,%al               # Wait for not busy
8482   testb   $0x2,%al
8483   jnz     seta20.2
8484 
8485   movb    $0xdf,%al               # 0xdf -> port 0x60
8486   outb    %al,$0x60
8487 
8488   # Switch from real to protected mode.  Use a bootstrap GDT that makes
8489   # virtual addresses map directly to physical addresses so that the
8490   # effective memory map doesn't change during the transition.
8491   lgdt    gdtdesc
8492   movl    %cr0, %eax
8493   orl     $CR0_PE, %eax
8494   movl    %eax, %cr0
8495 
8496   # Complete the transition to 32-bit protected mode by using a long jmp
8497   # to reload %cs and %eip.  The segment descriptors are set up with no
8498   # translation, so that the mapping is still the identity mapping.
8499   ljmp    $(SEG_KCODE<<3), $start32
8500 .code32  # Tell assembler to generate 32-bit code now.
8501 start32:
8502   # Set up the protected-mode data segment registers
8503   movw    $(SEG_KDATA<<3), %ax    # Our data segment selector
8504   movw    %ax, %ds                # -> DS: Data Segment
8505   movw    %ax, %es                # -> ES: Extra Segment
8506   movw    %ax, %ss                # -> SS: Stack Segment
8507   movw    $0, %ax                 # Zero segments not ready for use
8508   movw    %ax, %fs                # -> FS
8509   movw    %ax, %gs                # -> GS
8510 
8511   # Set up the stack pointer and call into C.
8512   movl    $start, %esp
8513   call    bootmain
8514 
8515   # If bootmain returns (it shouldn't), trigger a Bochs
8516   # breakpoint if running under Bochs, then loop.
8517   movw    $0x8a00, %ax            # 0x8a00 -> port 0x8a00
8518   movw    %ax, %dx
8519   outw    %ax, %dx
8520   movw    $0x8ae0, %ax            # 0x8ae0 -> port 0x8a00
8521   outw    %ax, %dx
8522 spin:
8523   jmp     spin
8524 
8525 # Bootstrap GDT
8526 .p2align 2                                # force 4 byte alignment
8527 gdt:
8528   SEG_NULLASM                             # null seg
8529   SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)   # code seg
8530   SEG_ASM(STA_W, 0x0, 0xffffffff)         # data seg
8531 
8532 gdtdesc:
8533   .word   (gdtdesc - gdt - 1)             # sizeof(gdt) - 1
8534   .long   gdt                             # address gdt
8535 
8536 
8537 
8538 
8539 
8540 
8541 
8542 
8543 
8544 
8545 
8546 
8547 
8548 
8549 
