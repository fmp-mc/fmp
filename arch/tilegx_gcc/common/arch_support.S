/**
 * TILEGx Architecture Support Package for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2015 by Yixiao Li (liyixiao@ertl.jp)
 *
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 *
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 *
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 *
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *      conditions must be satisfied:
 *
 *    (a) The above copyright notice, this use conditions, and the
 *        disclaimer shown below must be shown without modification in
 *        the document provided with the redistributed software, such as
 *        the user manual.
 *
 *    (b) How the software is to be redistributed must be reported to the
 *        TOPPERS Project according to the procedure described
 *        separately.
 *
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

#define TOPPERS_MACRO_ONLY
#include "arch_asm_inc.S"
#include "tilegx.h"
#include "arch_config.h"

/**
 * void dispatch(void)
 * dispatch from task context
 */
    ATEXT
    .align 8 //TODO: ARM arch: AALIGN(2)
    AGLOBAL(dispatch)
ALABEL(dispatch)
    push_callee_regs
    push lr          /* save non scratch registers */
#if defined(USE_GCC_BUILTIN_CAS)
    mfspr lr, SPR_CMPEXCH_VALUE
    push  lr
#endif
    my_pcb tp
    add_offset r0, tp, PCB_p_runtsk
    ld r0, r0                       /* r0 = my_pcb->p_runtsk */
    add_offset r1, r0, TCB_sp       /* r1 = &(my_pcb->p_runtsk->sp) */
    st r1, sp                       /* my_pcb->p_runtsk->sp = sp */
    add_offset r1, r0, TCB_pc       /* r1 = &(my_pcb->p_runtsk->sp) */
    load_symbol r0, dispatch_r      /* r0 = Return address (dispatch_r) */
    st r1, r0                       /* my_pcb->p_runtsk->pc = dispatch_r */
    j dispatcher

/**
 * Input:
 * r0: address of TCB (called from dispatcher_0)
 */
    AGLOBAL(dispatch_r)
ALABEL(dispatch_r)
#if defined(USE_GCC_BUILTIN_CAS)
    pop   lr
    mtspr SPR_CMPEXCH_VALUE, lr
#endif
    pop lr
    pop_callee_regs /* restore non scratch registers */
    /* TODO: call dispatch_call_texrtn !TASK EXCEPTION NOT SUPPORT! */
ALABEL(dispatch_r_1)
    jr lr

/**
 * void start_dispatch(void)
 *
 * Preconditions:
 * 1. CPU is locked
 *
 * Postconditions:
 * 1. my_pcb->excpt_nest_count == 0
 * 2. goto dispatcher_0
 */
    AGLOBAL(start_dispatch)
ALABEL(start_dispatch)
    my_pcb tp
    add_offset r0, tp, PCB_excpt_nest_count
    st r0, zero
    j dispatcher_0

/**
 * void dispatcher(void) & exit_and_dispatch()
 * Output:
 * r0: address of TCB
 */
     AGLOBAL(exit_and_dispatch)
ALABEL(exit_and_dispatch)
    AGLOBAL(dispatcher)
ALABEL(dispatcher)
#if defined(LOG_DSP_ENTER)
    my_pcb tp
    add_offset r0, tp, PCB_p_runtsk   /* r0 = &(my_pcb->p_runtsk) */
    ld r0, r0
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal log_dsp_enter /* call log_dsp_enter(my_pcb.p_runtsk); */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE
#endif /* LOG_DSP_ENTER */
#if defined(DEBUG_CPU_USAGE)
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal debug_dsp_enter /* call debug_dsp_enter(); */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE
#endif
ALABEL(dispatcher_0)
    my_pcb tp                         /* tp = my_pcb */
    add_offset r0, tp, PCB_p_schedtsk /* r0 = my_pcb->p_schedtsk */
    ld r0, r0
    add_offset r1, tp, PCB_p_runtsk   /* r1 = &(my_pcb->p_runtsk) */
#if defined(SUPPORT_GET_P_RUNTSK_SPR)
	mtspr SPR_SAVE_P_RUNTSK, r0
#endif
    st r1, r0                         /* my_pcb->p_runtsk = my_pcb->p_schedtsk */
    beqz r0, dispatcher_1             /* if (r0 == NULL) goto dispatcher_1 */
    add_offset r1, r0, TCB_sp         /* r1 = &(my_pcb->p_schedtsk->sp) */
    ld sp, r1                         /* sp = my_pcb->p_runtsk->sp */
#if defined(LOG_DSP_LEAVE)
    push r0
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal log_dsp_leave /* call log_dsp_leave(my_pcb.p_runtsk); */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE
    pop r0
#endif /* LOG_DSP_LEAVE */
#if defined(DEBUG_CPU_USAGE)
    push r0
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE // Allocate caller state save area
    jal debug_dsp_leave /* call debug_dsp_enter(); */
    addi sp, sp, C_ABI_SAVE_AREA_SIZE
    pop r0
#endif
    add_offset r1, r0, TCB_pc         /* r1 = &(my_pcb->p_schedtsk->pc) */
    ld r1, r1
    jr r1                             /* pc = my_pcb->p_runtsk->pc (start_r/dispatch_r), with r0 = my_pcb->p_runtsk */

    /* when my_pcb->p_runtsk == NULL */
ALABEL(dispatcher_1)
    /* switch to interrupt context & prepare for unlocking CPU */
    my_pcb tp
    add_offset r0, tp, PCB_istkpt
    ld sp, r0                                /* sp = my_pcb->istkpt */
#define USE_CALLER_ONLY
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    add_offset r1, tp, PCB_reqflg           /* r1 = &(my_pcb->reqflg) */
    add_offset r2, tp, PCB_excpt_nest_count /* r2 = &(my_pcb->excpt_nest_count) */
#else
    add_offset r30, tp, PCB_reqflg           /* r30 = &(my_pcb->reqflg) */
    add_offset r31, tp, PCB_excpt_nest_count /* r31 = &(my_pcb->excpt_nest_count) */
#endif
ALABEL(dispatcher_2)
    /**
     * Callee-saved register:
     * r30 = &(my_pcb->reqflg),
     * r31 = &(my_pcb->excpt_nest_count)
     */
    movei r0, 1
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    st r2, r0
#else
    st r31, r0             /* excpt_nest_count = 1 */
#endif

#ifdef TOPPERS_CUSTOM_IDLE
    toppers_asm_custom_idle
#else
    //local_irq enable r32   /* Enable interrupts */
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    cpu_unlock r3
#else
    cpu_unlock r32
#endif
    nop
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    cpu_lock r3
#else
    cpu_lock r32
#endif
    //local_irq disable r32  /* Lock CPU (disable interrupts) */
#endif /* TOPPERS_CUSTOM_IDLE */
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    ld r0, r1             /* r0 = my_pcb->reqflg */
#else
    ld r0, r30             /* r0 = my_pcb->reqflg */
#endif
    beqz  r0, dispatcher_2 /* if (!r0) goto dispatcher_2 */
    //movei r0, 0
#if defined(USE_CALLER_ONLY) /* Should use caller? */
    st    r1, zero          /* my_pcb->reqflg = FALSE */
    st    r2, zero          /* my_pcb->excpt_nest_count = 0 */
#else
    st    r30, zero          /* my_pcb->reqflg = FALSE */
    st    r31, zero          /* my_pcb->excpt_nest_count = 0 */
#endif
    j     dispatcher_0

/**
 * Start a task. This routine will ONLY be called from dispatcher.
 * Input:
 * r0: address of TCB
 */
    ATEXT
    AGLOBAL(start_r)
ALABEL(start_r)
    //local_irq enable r1            /* Unlock CPU (enable interrupts) */ // TODO: this seems buggy
    cpu_unlock r1
    //mtspr 0x2306, zero
    //            j debug_loop // TODO: for debug, remove this line -- ertl-liyixiao
    load_symbol lr, ext_tsk        /* Return address (exit task) */
    add_offset r2, r0, TCB_p_tinib
    ld r2, r2                      /* r2 = p_runtsk->p_tinib */
    add_offset r0, r2, TINIB_exinf
    ld r0, r0                      /* r0 = exinf */
    add_offset r1, r2, TINIB_task
    ld r1, r1                      /* r1 = task */

    addi sp, sp, -C_ABI_SAVE_AREA_SIZE /* allocate caller state save area */
    jr r1


    ATEXT
    AGLOBAL(call_backtracer)
ALABEL(call_backtracer)
    st sp, lr
    move r0, sp
    addi sp, sp, -C_ABI_SAVE_AREA_SIZE /* allocate caller state save area */
    j dump_stack_frame
    addi sp, sp, C_ABI_SAVE_AREA_SIZE  /* deallocate caller state save area */
    jrp lr   /* keep backtracer happy */
