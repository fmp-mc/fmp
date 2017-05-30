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

#pragma once

#include "offset.h"

/**
 * Assembler directives
 */
//#define ASECTION(name) .section name,"a"
#define ATEXT          .text
#define AGLOBAL(name)  .global name
//#define AALIGN(x)      .align x
//#define ALONG          .long
#define ALABEL(label)  label:
//#define AOR            |

/**
 * Load a 48-bit symbolic value
 * Result:  re_reg
 */
.macro load_symbol re_reg sym
    moveli \re_reg, hw2_last(\sym)
    shl16insli \re_reg, \re_reg, hw1(\sym)
    shl16insli \re_reg, \re_reg, hw0(\sym)
.endm

/**
 * my_pcb() macro is valid after initialized by this macro.
 * Input: prc_id_reg
 * Scratch: sc_reg1
 */
.macro init_my_pcb prc_id_reg sc_reg1
    load_symbol \sc_reg1, _kernel_p_pcb_table     /* sc_reg1 =  _kernel_p_pcb_table */
    shl3add \sc_reg1, \prc_id_reg, \sc_reg1       /* sc_reg1 += prc_id_reg * 8 */
    ld tp, \sc_reg1                               /* tp = *(intptr_t*)(sc_reg1) */
.endm

/**
 * Get the pointer of my PCB.
 * Result: re_reg
 */
.macro my_pcb re_reg
    .if \re_reg != tp
        move \re_reg, tp
    .endif
.endm

/**
 * Get the pointer of a PCB member.
 * Result: re_reg
 */
.macro add_offset re_reg src_reg offset
    addi \re_reg, \src_reg, \offset
.endm

#include "tilegx.h"
#define MANAGED_INTERRUPTS ((0x1<<INTNO_TILE_TIMER)|(0x1<<INTNO_IPI_2)|(0x1<<INTNO_SWINT_1)|(0x1<<INTNO_ITLB_MISS))

/**
 * Enable or Disable interrupts
 * Scratch: sc_reg
 */
.macro local_irq op sc_reg
    //load_symbol \sc_reg, (0x1 << 22)
    //nor \sc_reg,
    //nor \sc_reg, zero, zero
#if 0
    // TODO: hard coding for TILE_TIMER & IPI_2
    moveli \sc_reg, hw2_last((0x1 << 22)|(0x1 << 29))
    shl16insli \sc_reg, \sc_reg, hw1((0x1 << 22)|(0x1 << 29))
    shl16insli \sc_reg, \sc_reg, hw0((0x1 << 22)|(0x1 << 29))
#endif
    moveli \sc_reg, hw2_last(MANAGED_INTERRUPTS)
    shl16insli \sc_reg, \sc_reg, hw1(MANAGED_INTERRUPTS)
    shl16insli \sc_reg, \sc_reg, hw0(MANAGED_INTERRUPTS)
    .if \op == disable
    mtspr SPR_INTERRUPT_MASK_SET_2, \sc_reg
    .endif
    .if \op == enable
    mtspr SPR_INTERRUPT_MASK_RESET_2, \sc_reg
    .endif
    .if (\op != enable) && (\op != disable)
    .error invalid operation
    .endif
.endm
#if 0
.macro local_irq op sc_reg
    movei \sc_reg, 0
    .if \op == disable
    nor \sc_reg, \sc_reg, \sc_reg
    .else
      .if \op != enable
      .error invalid operation
      .endif
    .endif
    mtspr SPR_INTERRUPT_MASK_2, \sc_reg
.endm
#endif

.macro cpu_lock sc_reg
    movei \sc_reg, 1
    mtspr INTERRUPT_CRITICAL_SECTION, \sc_reg
.endm

.macro cpu_unlock sc_reg
    movei \sc_reg, 0
    mtspr INTERRUPT_CRITICAL_SECTION, \sc_reg
.endm

    //
    // Push/pop registers on/off a stack.
    //
    // Note that the the ABI specifies that when calling a function,
    // the sp points at the bottom word of the caller's stack frame.
    // This macro always decrements after storing, instead of before, so
    // you'll see that when we push a bunch of stuff on the stack, we
    // first decrement the sp; then we do a bunch of push_regs; then the
    // last thing that gets pushed gets pushed with "st sp, <foo>" rather
    // than "push_reg <foo>".  This makes the stack pointer end up
    // in the right spot.  The pop_reg macro does not have this problem,
    // and doesn't need any special pre- or postamble.
    //
.macro push reg, ptr=sp
    addi \ptr, \ptr, -8
    st \ptr, \reg
.endm

.macro pop reg, ptr=sp
    ld \reg, \ptr
    addi   \ptr, \ptr, 8
 .endm

.macro push_callee_regs
    push r30
    push r31
    push r32
    push r33
    push r34
    push r35
    push r36
    push r37
    push r38
    push r39
    push r40
    push r41
    push r42
    push r43
    push r44
    push r45
    push r46
    push r47
    push r48
    push r49
    push r50
    push r51
    push r52
.endm

.macro pop_callee_regs
    pop r52
    pop r51
    pop r50
    pop r49
    pop r48
    pop r47
    pop r46
    pop r45
    pop r44
    pop r43
    pop r42
    pop r41
    pop r40
    pop r39
    pop r38
    pop r37
    pop r36
    pop r35
    pop r34
    pop r33
    pop r32
    pop r31
    pop r30
.endm

.macro push_caller_regs_except_lr
    push r0
    push r1
    push r2
    push r3
    push r4
    push r5
    push r6
    push r7
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push r16
    push r17
    push r18
    push r19
    push r20
    push r21
    push r22
    push r23
    push r24
    push r25
    push r26
    push r27
    push r28
    push r29
//    push lr
.endm

.macro pop_caller_regs_except_lr
//    pop lr
    pop r29
    pop r28
    pop r27
    pop r26
    pop r25
    pop r24
    pop r23
    pop r22
    pop r21
    pop r20
    pop r19
    pop r18
    pop r17
    pop r16
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop r7
    pop r6
    pop r5
    pop r4
    pop r3
    pop r2
    pop r1
    pop r0
.endm
