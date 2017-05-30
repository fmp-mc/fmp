#define TOPPERS_MACRO_ONLY

#include <kernel.h>
#include "tilegx.h"

#define SYSTEM_SAVE_BME_0 SPR_SYSTEM_SAVE_2_1
#define INTERRUPT_MASK_BME INTERRUPT_MASK_2
#define INTERRUPT_MASK_SET_BME INTERRUPT_MASK_SET_2
#define EX_CONTEXT_BME_0 EX_CONTEXT_2_0
#define EX_CONTEXT_BME_1 EX_CONTEXT_2_1
#define INT_MASK(intno) (1 << (intno))
#define BS_INT_HANDLER_OFF (0) /* magic number, tp == int_handler */

#include "asm_inc.h"
#include "arch_asm_inc.S"

//#include "linux-3.12/arch/tile/kernel/intvec_64.S"

/** Interrupts the BME handles, and which should be masked when calling
 *  the C routine to service an interrupt */
// FIXME: need better documentation about when/how users should add
// to these tables
#define BME_INTS_MASKED_DURING_INTHANDLER ( \
0)

// FIXME: the register/save restore stuff needs to be factored out into a
// macro so we can use it in two places.

    .altmacro   // Necessary for \xx& macro substitution feature

    //
    // Put the handle-while-in-supervisor interrupt mask, plus the
    // specified vector, into the two specified registers.  (If the
    // vector is less than zero, ignore it and just store the mask.)
    //
    .macro int_mask vec, reg
    .iflt   \vec
     moveli \reg, hw2_last(BME_INTS_MASKED_DURING_INTHANDLER)
     shl16insli \reg, \reg, hw1(BME_INTS_MASKED_DURING_INTHANDLER)
     shl16insli \reg, \reg, hw0(BME_INTS_MASKED_DURING_INTHANDLER)
    .else
     moveli \reg, hw3(BME_INTS_MASKED_DURING_INTHANDLER | INT_MASK(\vec))
     shl16insli \reg, \reg, hw2(BME_INTS_MASKED_DURING_INTHANDLER | \
                                    INT_MASK(\vec))
     shl16insli \reg, \reg, hw1(BME_INTS_MASKED_DURING_INTHANDLER | \
                                    INT_MASK(\vec))
     shl16insli \reg, \reg, hw0(BME_INTS_MASKED_DURING_INTHANDLER | \
                                    INT_MASK(\vec))
    .endif
    .endm


    //
    // Define a label for the start of the array of pointers to interrupt
    // names; we'll fill this in via the vec_start macro.
    //
    .pushsection .rodata.int_names, "a"
    .global int_names
    .align 8
int_names:
    .org    0
    .popsection

    //
    // Start an interrupt vector.
    // vecnum is where we'll put this code.
    // vecname is the name of the vector to use.
    //
    .macro vec_start vecnum, vecname

    .pushsection .rodata, "a"
    #if 0
intname_\vecname:
    .asciz "\vecname"
    .popsection

    .pushsection .rodata.int_names, "a"
    .org    (\vecnum << 3)
    .quad   intname_\vecname
#endif
    .popsection

    .org    (\vecnum << 8)

    .endm

    //
    // Interrupt handler for faults where we save the full register set.
    //
    // vecnum is where we'll put this code.
    // vecname is the name of the vector to use.
    // c_routine is the C routine we'll call.
    //
    .macro  int_hand_full vecnum, vecname, c_routine

    vec_start \vecnum, \vecname

intvec_\vecname:
    // Temporarily save a register so we have somewhere to work.
jal debug_loop // No int_hand_full is acceptable! -- ertl-liyixiao
    mtspr   SYSTEM_SAVE_BME_0, r0

addi    r0, sp, -8 // this line is IMPORTANT -- ertl-liyixiao

    // Push the parameter-passing registers on the stack, so that we can
    // set them to vector-unique values before we jump to the common code.
    // Registers are pushed on the stack in this order:
    //
    // (untouched)        <- initial stack pointer value, highest
    //                       address
    // sp
    // lr
    // r0
    // r1
    // r2
    // .
    // .
    // .
    // r12            <- last register saved by this macro
    // ------------------------------------------------------------------
    // r13            <- first register saved by handle_intr_full;
    //               sp is here when we jump to handle_intr_full
    // .
    // .
    // .
    // r52
    // r53/tp
    // EX_CONTEXT_BME_1
    // EX_CONTEXT_BME_0
    // Interrupt mask
        // Caller state save area word 0
        // Caller state save area word 1 <- final stack pointer value, lowest
    //                                  address

        push_reg sp, r0

    push_reg lr, r0
    {
     mfspr  r0, SYSTEM_SAVE_BME_0    // Original r0
     move   sp, r0
    }
    push_reg r0
    push_reg r1
    push_reg r2
    push_reg r3
    push_reg r4
    push_reg r5
    push_reg r6
    push_reg r7
    push_reg r8
    push_reg r9
    push_reg r10
    push_reg r11
    push_reg r12

    //
    // We pass one parameter to the eventual C routine: the number of
    // the interrupt, in r0.  (handle_intr_full may pass more values
    // in addition to those.)  We also pass two values to
    // handle_intr_full itself:
    //
    // - The address of the C routine to jump to (in r10).
    //
    // - A set of interrupts we want masked while we're in the C routine
    //   and not in an interrupt critical section (low word in r11, high
    //   word in r12).  We always mask the interrupt we're handling;
    //   in addition we mask a set of standard things which we never want
    //   to handle at our PL.
    //

    {
         moveli r0, \vecnum
     moveli r10, hw2_last(\c_routine)
    }
    int_mask \vecnum, r11
    shl16insli r10, r10, hw1(\c_routine)

    // Jump to remainder of interrupt handling code.

    {
     j  handle_intr_full
     shl16insli r10, r10, hw0(\c_routine)
    }

    .size intvec_\vecname,.-intvec_\vecname
    .endm

/**
 * Generate the entry point of a interrupt handler that follows TOPPERS/FMP Kernel porting guide.
 * This macro jumps to common interrupt entry code (fmp_int_entry) with
 * 1) lr stored in stack
 * 2) interrupt number stored in lr register
 */
.macro fmp_int_hand vecnum, vecname
    vec_start \vecnum, \vecname
intvec_\vecname:
    push lr
    .ifeq \vecnum - INTNO_SWINT_1
    /**
     * Increase the return address so the same swint
     * instruction won't execute again.
     */
    mfspr lr, EX_CONTEXT_BME_0
    addi lr, lr, 8     // FIXME need a #define for this
    mtspr EX_CONTEXT_BME_0, lr
    .endif
    moveli lr, \vecnum
    j fmp_int_entry
    .size intvec_\vecname,.-intvec_\vecname
.endm

    //
    // This symbol is referenced by the BME runtime startup code to force
    // the object module containing the vectors to be linked in to the BME
    // application.  If an application wants to define its own vectors
    // statically, it should define this symbol in those vectors so that
    // both sets aren't linked in.
    //
    .section ".intrpt", "ax"
    .global intrpt_start
    .global interrupt_vectors
intrpt_start:
interrupt_vectors:
    int_hand_full INTNO_MEM_ERROR, MEM_ERROR, bme_bad_intr
    int_hand_full INTNO_SINGLE_STEP_3, SINGLE_STEP_3, bme_bad_intr
    int_hand_full INTNO_SINGLE_STEP_2, SINGLE_STEP_2, bme_bad_intr
    int_hand_full INTNO_SINGLE_STEP_1, SINGLE_STEP_1, bme_bad_intr
    int_hand_full INTNO_SINGLE_STEP_0, SINGLE_STEP_0, bme_bad_intr
    int_hand_full INTNO_IDN_COMPLETE, IDN_COMPLETE, bme_bad_intr
    int_hand_full INTNO_UDN_COMPLETE, UDN_COMPLETE, bme_bad_intr
    fmp_int_hand INTNO_ITLB_MISS, ITLB_MISS // int_hand_full INTNO_ITLB_MISS, ITLB_MISS, bme_bad_intr
    fmp_int_hand INTNO_ILL, ILL //int_hand_full INTNO_ILL, ILL, bme_bad_intr
    int_hand_full INTNO_GPV, GPV, bme_bad_intr
    int_hand_full INTNO_IDN_ACCESS, IDN_ACCESS, bme_bad_intr
    int_hand_full INTNO_UDN_ACCESS, UDN_ACCESS, bme_bad_intr
    int_hand_full INTNO_SWINT_3, SWINT_3, bme_bad_intr
    int_hand_full INTNO_SWINT_2, SWINT_2, bme_bad_intr
    fmp_int_hand INTNO_SWINT_1, SWINT_1 //int_hand_full INTNO_SWINT_1, SWINT_1, bme_bad_intr
    int_hand_full INTNO_SWINT_0, SWINT_0, bme_bad_intr
    fmp_int_hand INTNO_ILL_TRANS, ILL_TRANS //int_hand_full INTNO_ILL_TRANS, ILL_TRANS, bme_bad_intr
    fmp_int_hand INTNO_UNALIGN_DATA, UNALIGN_DATA //int_hand_full INTNO_UNALIGN_DATA, UNALIGN_DATA, bme_bad_intr
    int_hand_full INTNO_DTLB_MISS, DTLB_MISS, bme_bad_intr
    int_hand_full INTNO_DTLB_ACCESS, DTLB_ACCESS, bme_bad_intr
    int_hand_full INTNO_IDN_FIREWALL, IDN_FIREWALL, bme_bad_intr
    int_hand_full INTNO_UDN_FIREWALL, UDN_FIREWALL, bme_bad_intr
    fmp_int_hand  INTNO_TILE_TIMER, TILE_TIMER //int_hand_full INTNO_TILE_TIMER, TILE_TIMER, bme_bad_intr
    int_hand_full INTNO_IDN_TIMER, IDN_TIMER, bme_bad_intr
    int_hand_full INTNO_UDN_TIMER, UDN_TIMER, bme_bad_intr
    int_hand_full INTNO_IDN_AVAIL, IDN_AVAIL, bme_bad_intr
    int_hand_full INTNO_UDN_AVAIL, UDN_AVAIL, bme_bad_intr
    int_hand_full INTNO_IPI_3, IPI_3, bme_bad_intr
    fmp_int_hand  INTNO_IPI_2, IPI_2 //int_hand_full INTNO_IPI_2, IPI_2, bme_bad_intr
    int_hand_full INTNO_IPI_1, IPI_1, bme_bad_intr
    int_hand_full INTNO_IPI_0, IPI_0, bme_bad_intr
    int_hand_full INTNO_PERF_COUNT, PERF_COUNT, bme_bad_intr
    int_hand_full INTNO_AUX_PERF_COUNT, AUX_PERF_COUNT, bme_bad_intr
    int_hand_full INTNO_INTCTRL_3, INTCTRL_3, bme_bad_intr
    int_hand_full INTNO_INTCTRL_2, INTCTRL_2, bme_bad_intr
    int_hand_full INTNO_INTCTRL_1, INTCTRL_1, bme_bad_intr
    int_hand_full INTNO_INTCTRL_0, INTCTRL_0, bme_bad_intr
    int_hand_full INTNO_BOOT_ACCESS, BOOT_ACCESS, bme_bad_intr
    int_hand_full INTNO_WORLD_ACCESS, WORLD_ACCESS, bme_bad_intr
    int_hand_full INTNO_I_ASID, I_ASID, bme_bad_intr
    int_hand_full INTNO_D_ASID, D_ASID, bme_bad_intr
    int_hand_full INTNO_DOUBLE_FAULT, DOUBLE_FAULT, bme_bad_intr



    //
    // Code to handle interrupts which save the full register set.
    // The C function we're eventually going to is in r10, and its args
    // are in r0...r9; the original values for all of those registers,
    // plus some others, are on the stack (see stack layout above in
    // the int_hand_full macro).
    //
handle_intr_full:
    // Save the rest of the registers that we didn't save in the actual
    // vector itself

    push_reg r13
    push_reg r14
    push_reg r15
    push_reg r16
    push_reg r17
    push_reg r18
    push_reg r19
    push_reg r20
    push_reg r21
    push_reg r22
    push_reg r23
    push_reg r24
    push_reg r25
    push_reg r26
    push_reg r27
    push_reg r28
    push_reg r29
    push_reg r30
    push_reg r31
    push_reg r32
    push_reg r33
    push_reg r34
    push_reg r35
    push_reg r36
    push_reg r37
    push_reg r38
    push_reg r39
    push_reg r40
    push_reg r41
    push_reg r42
    push_reg r43
    push_reg r44
    push_reg r45
    push_reg r46
    push_reg r47
    push_reg r48
    push_reg r49
    push_reg r50
    push_reg r51
    push_reg r52
    push_reg tp
    mfspr   r52, EX_CONTEXT_BME_1
    push_reg r52
    mfspr   r52, EX_CONTEXT_BME_0
    push_reg r52

    // Calculate the address of the interrupt routine.  It is stored
    // in a table in the BME state structure, which is pointed to
    // by the tp register (r53).  Store it in r10.

#if 0 // Always use bme_bad_intr
    // Get the address of the interrupt pointer table, which is just an
        // offset from the start of the _bme_state_t.
    my_pcb tp
    add_offset r7, tp, PCB_p_inh_tbl
    ld r7,  r7                        /* r7 = my_pcb->p_inh_tbl */

    // Get the address of the handler for the interrupt we are
    // servicing.  The interrupt number is in r0.

    // Calculate the offset into the table of pointers to interrupt
        // handlers (sizeof(ptr) * interrupt_number).
    shl3add r7, r0, r7

    // Load the address of the interrupt handler into r10 if it
        // is not 0.  If it is 0, use the default which is already in r10.
    ld      r7, r7
    cmovnez r10, r7, r7
#endif

    // Save the current interrupt masks

    mfspr   r20, INTERRUPT_MASK_BME
    st  sp, r20  // Interrupt mask word

    // Then mask the requested interrupts

    mtspr   INTERRUPT_MASK_SET_BME, r11

        {
     // Pass the state pointer to the C routine as the second argument, so
     // that it can get at the saved registers.
     move   r1, sp
     addi   sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
        }

    // Everything is saved now; exit from the critical section

    mtspr   INTERRUPT_CRITICAL_SECTION, zero

    // Jump to the C routine

    //jalr    r10

    // Upon return, fall through to...

return_from_intr_full:
    // Enable critical section bit

    movei   r52, 1

        {
     mtspr  INTERRUPT_CRITICAL_SECTION, r52
     addi   sp, sp, C_ABI_SAVE_AREA_SIZE
        }

    // Restore the previous interrupt masks, the EX_CONTEXT values, and
    // the registers.

    pop_reg r52
    mtspr   INTERRUPT_MASK_BME, r52
    pop_reg r52
    mtspr   EX_CONTEXT_BME_0, r52
    pop_reg r52
    mtspr   EX_CONTEXT_BME_1, r52
    pop_reg tp
    pop_reg r52
    pop_reg r51
    pop_reg r50
    pop_reg r49
    pop_reg r48
    pop_reg r47
    pop_reg r46
    pop_reg r45
    pop_reg r44
    pop_reg r43
    pop_reg r42
    pop_reg r41
    pop_reg r40
    pop_reg r39
    pop_reg r38
    pop_reg r37
    pop_reg r36
    pop_reg r35
    pop_reg r34
    pop_reg r33
    pop_reg r32
    pop_reg r31
    pop_reg r30
    pop_reg r29
    pop_reg r28
    pop_reg r27
    pop_reg r26
    pop_reg r25
    pop_reg r24
    pop_reg r23
    pop_reg r22
    pop_reg r21
    pop_reg r20
    pop_reg r19
    pop_reg r18
    pop_reg r17
    pop_reg r16
    pop_reg r15
    pop_reg r14
    pop_reg r13
    pop_reg r12
    pop_reg r11
    pop_reg r10
    pop_reg r9
    pop_reg r8
    pop_reg r7
    pop_reg r6
    pop_reg r5
    pop_reg r4
    pop_reg r3
    pop_reg r2
    pop_reg r1
    pop_reg r0
    pop_reg lr
    ld  sp, sp

    iret

    /** 
     * lr IS interrupt number when this routine is called.
     * r0-r10 MUST not be modified before the handler is called,
     * since they are used in handling system calls (SWINT1).
     */
fmp_int_entry:
    push_caller_regs_except_lr
#if defined(USE_GCC_BUILTIN_CAS)
    mfspr r11, SPR_CMPEXCH_VALUE
    push  r11
#endif
    mfspr r11, EX_CONTEXT_BME_1
    push r11
    mfspr r11, EX_CONTEXT_BME_0
    push r11 /* now all caller-saved registers are in stack */

#if 0
push_caller_regs_except_lr
push lr
    move r0, sp
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal dump_fmp_int_entry_saved_regs_full
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  // Deallocate caller save area
    #if 0
    move r0, sp
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal dump_fmp_int_entry_saved_regs_full
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  // Deallocate caller save area
    move r0, sp
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal dump_fmp_int_entry_saved_regs_full
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  // Deallocate caller save area
    move r0, sp
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal dump_fmp_int_entry_saved_regs_full
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  // Deallocate caller save area
    #endif
pop lr
pop_caller_regs_except_lr
#endif

#if TTYPE_KLOCK != G_KLOCK
    push lr // Save lr which holds interrupt number
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal release_pcb_two_locks
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  // Deallocate caller save area
    pop lr
#endif

    my_pcb tp
    add_offset r11, tp, PCB_excpt_nest_count
    ld r12, r11        /* r12 = my_pcb->excpt_nest_count */
    addi r12, r12, 1
    st r11, r12        /* my_pcb->excpt_nest_count++ */
    addi r12, r12, -1 //TODO: !!!!!!!!!!!!!!!!IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!!!! check this

    move r11, sp      /* r11 = stack pointer at this point */

irq_handler:
    /* switch to interrupt context stack if in task context */
    bnez r12, irq_handler_1
    add_offset r12, tp, PCB_istkpt
    ld r12, r12
    move sp, r12

irq_handler_1:
//            j debug_loop
    push lr  /* save interrupt number TODO: CAREFUL! */
    push r11 /* save stack pointer before switching */

    add_offset r11, tp, PCB_p_inh_tbl
    ld r11, r11
    shl3add r11, lr, r11
    ld r11, r11 /* r11 = interrupt handler pointer (p_inh_tbl[lr]) */

    /* TODO: mask all interrupts with priority not higher than current one.  */
    /* For now, we mask all interrupts since ONLY one priority is supported. */
    local_irq disable r12  /* Lock CPU (disable interrupts) */

    mtspr INTERRUPT_CRITICAL_SECTION, zero /* exit from the critical section & enable interrupt */

    //addi sp, sp, -C_ABI_SAVE_AREA_SIZE /* allocate caller state save area */
    push zero
    push zero
    jalr r11                                /* call actual interrupt handler */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE

ret_int:
    movei r3, 1
    mtspr INTERRUPT_CRITICAL_SECTION, r3 /* enter interrupt critical section */

    /* TODO: restore IPM. For now, enable all interrupts */
    local_irq enable r3

    pop r3

    /* TODO: BE CAREFUL! */
    pop lr /* restore interrupt number */
    addi lr, lr, -INTNO_SWINT_1
    bnez lr, skip_swint1_proc
    /* special process for SWINT1, keep its r0, r1 */
    addli r4, r3, 8 * (30 + 2) // TODO: CAREFUL! r0-r29, EX_*
    push r0, r4   /* r0 in stack -> r0 (now) */
    push zero, r4 /* r1 in stack -> 0 */
skip_swint1_proc:

    move sp, r3 /* restore stack pointer before call irq_handler */

    my_pcb r0
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal _kernel_force_unlock_spin /* call force_unlock_spin */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE

ALABEL(ret_int_1)
    my_pcb tp
    add_offset r0, tp, PCB_excpt_nest_count
    ld r1, r0        /* r1 = my_pcb->excpt_nest_count */
    addi r1, r1, -1
    st r0, r1 /* my_pcb->excpt_nest_count-- */
    bnez r1, ret_int_2 /* return to interrupt context, call ret_int_2 directly */

    /* return to task context */
    add_offset r0, tp, PCB_reqflg
    ld r1, r0        /* r1 = reqflg */
    bnez r1, ret_int_3 /* if (reqflg) goto ret_int_3; */

ALABEL(ret_int_2)
    pop r0
    mtspr   EX_CONTEXT_BME_0, r0
    pop r0
    mtspr   EX_CONTEXT_BME_1, r0
#if defined(USE_GCC_BUILTIN_CAS)
    pop   r0
    mtspr SPR_CMPEXCH_VALUE, r0
#endif
    pop_caller_regs_except_lr
    pop lr /* restore caller-saved registers and EX_CONTEXT */
    iret

ALABEL(ret_int_3)
    /* r0 = &reqflg */
    st r0, zero /* reqflg = FALSE */

    /* TODO: LOCK CPU, do nothing since in interrupt critical section. check this. */

    /* TODO: task stack pointer has been restored. check this */

ALABEL(ret_int_4)
    add_offset r1, tp, PCB_p_runtsk
    ld r1, r1                       /* r1 = p_runtsk */
    add_offset r2, tp, PCB_dspflg
    ld r2, r2                       /* r2 = dspflg */
    beqz r2, ret_int_r_1            /* if (!dspflg) goto ret_int_r_1 */

    add_offset r2, tp, PCB_p_schedtsk
    ld r2, r2                       /* r2 = p_schedtsk */
    cmpeq r0, r1, r2                /* r0 = (r1 == r2) */
    bnez r0, ret_int_r_1            /* if (r1==r2) goto ret_int_r_1 */
    push_callee_regs                /* now all registers (both caller & callee) are stored in task stack */
    add_offset r2, r1, TCB_sp
    st r2, sp                       /* TCB.sp = sp */
    add_offset r2, r1, TCB_pc
    load_symbol r3, ret_int_r
    st r2, r3                       /* TCB.pc = ret_int_r */
    j dispatcher                    /* call dispatcher */

    AGLOBAL(ret_int_r)
ALABEL(ret_int_r)   // return from dispatcher
    pop_callee_regs
ALABEL(ret_int_r_1)
    /* TODO: TASK exception not supported, so do nothing here ! */
    j ret_int_2
