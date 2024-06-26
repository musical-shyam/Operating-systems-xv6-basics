0700 // This file contains definitions for the
0701 // x86 memory management unit (MMU).
0702 
0703 // Eflags register
0704 #define FL_CF           0x00000001      // Carry Flag
0705 #define FL_PF           0x00000004      // Parity Flag
0706 #define FL_AF           0x00000010      // Auxiliary carry Flag
0707 #define FL_ZF           0x00000040      // Zero Flag
0708 #define FL_SF           0x00000080      // Sign Flag
0709 #define FL_TF           0x00000100      // Trap Flag
0710 #define FL_IF           0x00000200      // Interrupt Enable
0711 #define FL_DF           0x00000400      // Direction Flag
0712 #define FL_OF           0x00000800      // Overflow Flag
0713 #define FL_IOPL_MASK    0x00003000      // I/O Privilege Level bitmask
0714 #define FL_IOPL_0       0x00000000      //   IOPL == 0
0715 #define FL_IOPL_1       0x00001000      //   IOPL == 1
0716 #define FL_IOPL_2       0x00002000      //   IOPL == 2
0717 #define FL_IOPL_3       0x00003000      //   IOPL == 3
0718 #define FL_NT           0x00004000      // Nested Task
0719 #define FL_RF           0x00010000      // Resume Flag
0720 #define FL_VM           0x00020000      // Virtual 8086 mode
0721 #define FL_AC           0x00040000      // Alignment Check
0722 #define FL_VIF          0x00080000      // Virtual Interrupt Flag
0723 #define FL_VIP          0x00100000      // Virtual Interrupt Pending
0724 #define FL_ID           0x00200000      // ID flag
0725 
0726 // Control Register flags
0727 #define CR0_PE          0x00000001      // Protection Enable
0728 #define CR0_MP          0x00000002      // Monitor coProcessor
0729 #define CR0_EM          0x00000004      // Emulation
0730 #define CR0_TS          0x00000008      // Task Switched
0731 #define CR0_ET          0x00000010      // Extension Type
0732 #define CR0_NE          0x00000020      // Numeric Errror
0733 #define CR0_WP          0x00010000      // Write Protect
0734 #define CR0_AM          0x00040000      // Alignment Mask
0735 #define CR0_NW          0x20000000      // Not Writethrough
0736 #define CR0_CD          0x40000000      // Cache Disable
0737 #define CR0_PG          0x80000000      // Paging
0738 
0739 #define CR4_PSE         0x00000010      // Page size extension
0740 
0741 // various segment selectors.
0742 #define SEG_KCODE 1  // kernel code
0743 #define SEG_KDATA 2  // kernel data+stack
0744 #define SEG_KCPU  3  // kernel per-cpu data
0745 #define SEG_UCODE 4  // user code
0746 #define SEG_UDATA 5  // user data+stack
0747 #define SEG_TSS   6  // this process's task state
0748 
0749 
0750 // cpu->gdt[NSEGS] holds the above segments.
0751 #define NSEGS     7
0752 
0753 #ifndef __ASSEMBLER__
0754 // Segment Descriptor
0755 struct segdesc {
0756   uint lim_15_0 : 16;  // Low bits of segment limit
0757   uint base_15_0 : 16; // Low bits of segment base address
0758   uint base_23_16 : 8; // Middle bits of segment base address
0759   uint type : 4;       // Segment type (see STS_ constants)
0760   uint s : 1;          // 0 = system, 1 = application
0761   uint dpl : 2;        // Descriptor Privilege Level
0762   uint p : 1;          // Present
0763   uint lim_19_16 : 4;  // High bits of segment limit
0764   uint avl : 1;        // Unused (available for software use)
0765   uint rsv1 : 1;       // Reserved
0766   uint db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
0767   uint g : 1;          // Granularity: limit scaled by 4K when set
0768   uint base_31_24 : 8; // High bits of segment base address
0769 };
0770 
0771 // Normal segment
0772 #define SEG(type, base, lim, dpl) (struct segdesc)    \
0773 { ((lim) >> 12) & 0xffff, (uint)(base) & 0xffff,      \
0774   ((uint)(base) >> 16) & 0xff, type, 1, dpl, 1,       \
0775   (uint)(lim) >> 28, 0, 0, 1, 1, (uint)(base) >> 24 }
0776 #define SEG16(type, base, lim, dpl) (struct segdesc)  \
0777 { (lim) & 0xffff, (uint)(base) & 0xffff,              \
0778   ((uint)(base) >> 16) & 0xff, type, 1, dpl, 1,       \
0779   (uint)(lim) >> 16, 0, 0, 1, 0, (uint)(base) >> 24 }
0780 #endif
0781 
0782 #define DPL_USER    0x3     // User DPL
0783 
0784 // Application segment type bits
0785 #define STA_X       0x8     // Executable segment
0786 #define STA_E       0x4     // Expand down (non-executable segments)
0787 #define STA_C       0x4     // Conforming code segment (executable only)
0788 #define STA_W       0x2     // Writeable (non-executable segments)
0789 #define STA_R       0x2     // Readable (executable segments)
0790 #define STA_A       0x1     // Accessed
0791 
0792 // System segment type bits
0793 #define STS_T16A    0x1     // Available 16-bit TSS
0794 #define STS_LDT     0x2     // Local Descriptor Table
0795 #define STS_T16B    0x3     // Busy 16-bit TSS
0796 #define STS_CG16    0x4     // 16-bit Call Gate
0797 #define STS_TG      0x5     // Task Gate / Coum Transmitions
0798 #define STS_IG16    0x6     // 16-bit Interrupt Gate
0799 #define STS_TG16    0x7     // 16-bit Trap Gate
0800 #define STS_T32A    0x9     // Available 32-bit TSS
0801 #define STS_T32B    0xB     // Busy 32-bit TSS
0802 #define STS_CG32    0xC     // 32-bit Call Gate
0803 #define STS_IG32    0xE     // 32-bit Interrupt Gate
0804 #define STS_TG32    0xF     // 32-bit Trap Gate
0805 
0806 // A virtual address 'la' has a three-part structure as follows:
0807 //
0808 // +--------10------+-------10-------+---------12----------+
0809 // | Page Directory |   Page Table   | Offset within Page  |
0810 // |      Index     |      Index     |                     |
0811 // +----------------+----------------+---------------------+
0812 //  \--- PDX(va) --/ \--- PTX(va) --/
0813 
0814 // page directory index
0815 #define PDX(va)         (((uint)(va) >> PDXSHIFT) & 0x3FF)
0816 
0817 // page table index
0818 #define PTX(va)         (((uint)(va) >> PTXSHIFT) & 0x3FF)
0819 
0820 // construct virtual address from indexes and offset
0821 #define PGADDR(d, t, o) ((uint)((d) << PDXSHIFT | (t) << PTXSHIFT | (o)))
0822 
0823 // Page directory and page table constants.
0824 #define NPDENTRIES      1024    // # directory entries per page directory
0825 #define NPTENTRIES      1024    // # PTEs per page table
0826 #define PGSIZE          4096    // bytes mapped by a page
0827 
0828 #define PGSHIFT         12      // log2(PGSIZE)
0829 #define PTXSHIFT        12      // offset of PTX in a linear address
0830 #define PDXSHIFT        22      // offset of PDX in a linear address
0831 
0832 #define PGROUNDUP(sz)  (((sz)+PGSIZE-1) & ~(PGSIZE-1))
0833 #define PGROUNDDOWN(a) (((a)) & ~(PGSIZE-1))
0834 
0835 // Page table/directory entry flags.
0836 #define PTE_P           0x001   // Present
0837 #define PTE_W           0x002   // Writeable
0838 #define PTE_U           0x004   // User
0839 #define PTE_PWT         0x008   // Write-Through
0840 #define PTE_PCD         0x010   // Cache-Disable
0841 #define PTE_A           0x020   // Accessed
0842 #define PTE_D           0x040   // Dirty
0843 #define PTE_PS          0x080   // Page Size
0844 #define PTE_MBZ         0x180   // Bits must be zero
0845 
0846 // Address in page table or page directory entry
0847 #define PTE_ADDR(pte)   ((uint)(pte) & ~0xFFF)
0848 #define PTE_FLAGS(pte)  ((uint)(pte) &  0xFFF)
0849 
0850 #ifndef __ASSEMBLER__
0851 typedef uint pte_t;
0852 
0853 // Task state segment format
0854 struct taskstate {
0855   uint link;         // Old ts selector
0856   uint esp0;         // Stack pointers and segment selectors
0857   ushort ss0;        //   after an increase in privilege level
0858   ushort padding1;
0859   uint *esp1;
0860   ushort ss1;
0861   ushort padding2;
0862   uint *esp2;
0863   ushort ss2;
0864   ushort padding3;
0865   void *cr3;         // Page directory base
0866   uint *eip;         // Saved state from last task switch
0867   uint eflags;
0868   uint eax;          // More saved state (registers)
0869   uint ecx;
0870   uint edx;
0871   uint ebx;
0872   uint *esp;
0873   uint *ebp;
0874   uint esi;
0875   uint edi;
0876   ushort es;         // Even more saved state (segment selectors)
0877   ushort padding4;
0878   ushort cs;
0879   ushort padding5;
0880   ushort ss;
0881   ushort padding6;
0882   ushort ds;
0883   ushort padding7;
0884   ushort fs;
0885   ushort padding8;
0886   ushort gs;
0887   ushort padding9;
0888   ushort ldt;
0889   ushort padding10;
0890   ushort t;          // Trap on task switch
0891   ushort iomb;       // I/O map base address
0892 };
0893 
0894 
0895 
0896 
0897 
0898 
0899 
0900 // Gate descriptors for interrupts and traps
0901 struct gatedesc {
0902   uint off_15_0 : 16;   // low 16 bits of offset in segment
0903   uint cs : 16;         // code segment selector
0904   uint args : 5;        // # args, 0 for interrupt/trap gates
0905   uint rsv1 : 3;        // reserved(should be zero I guess)
0906   uint type : 4;        // type(STS_{TG,IG32,TG32})
0907   uint s : 1;           // must be 0 (system)
0908   uint dpl : 2;         // descriptor(meaning new) privilege level
0909   uint p : 1;           // Present
0910   uint off_31_16 : 16;  // high bits of offset in segment
0911 };
0912 
0913 // Set up a normal interrupt/trap gate descriptor.
0914 // - istrap: 1 for a trap (= exception) gate, 0 for an interrupt gate.
0915 //   interrupt gate clears FL_IF, trap gate leaves FL_IF alone
0916 // - sel: Code segment selector for interrupt/trap handler
0917 // - off: Offset in code segment for interrupt/trap handler
0918 // - dpl: Descriptor Privilege Level -
0919 //        the privilege level required for software to invoke
0920 //        this interrupt/trap gate explicitly using an int instruction.
0921 #define SETGATE(gate, istrap, sel, off, d)                \
0922 {                                                         \
0923   (gate).off_15_0 = (uint)(off) & 0xffff;                \
0924   (gate).cs = (sel);                                      \
0925   (gate).args = 0;                                        \
0926   (gate).rsv1 = 0;                                        \
0927   (gate).type = (istrap) ? STS_TG32 : STS_IG32;           \
0928   (gate).s = 0;                                           \
0929   (gate).dpl = (d);                                       \
0930   (gate).p = 1;                                           \
0931   (gate).off_31_16 = (uint)(off) >> 16;                  \
0932 }
0933 
0934 #endif
0935 
0936 
0937 
0938 
0939 
0940 
0941 
0942 
0943 
0944 
0945 
0946 
0947 
0948 
0949 
