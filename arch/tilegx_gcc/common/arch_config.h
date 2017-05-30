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

#include "tilegx.h"

#if defined(SUPPORT_GET_P_RUNTSK_SPR)
#define SPR_SAVE_P_RUNTSK SPR_SYSTEM_SAVE_K_1
#endif

#ifndef TOPPERS_MACRO_ONLY

#include "kernel/kernel_impl.h"
#include <reent.h>

/**
 * ISTKPT (SP register)
 * Ref: The ABI requires that a program’s stack grow downward. Thus, the stack pointer starts at a high address and decreases as stack frames are pushed on by decrementing the stack pointer
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/**
 * Task context block
 */
typedef struct task_context_block {
	void*  sp; // stack pointer
	FP     pc; // program counter
	void*  try_lock; // spin lock (or sth. like mutex) tried (or polled) last time
	uint_t try_lock_times;
#if OPTIMIZE_PAGE_TABLE >= 1
	struct _reent reent; // context for Newlib
#endif
} TSKCTXB;

/**
 * Interrupt (handler) numbers
 */

#define TMIN_INTNO  TILEGX_TMIN_INTNO
#define TMAX_INTNO  TILEGX_TMAX_INTNO
#define TNUM_INT    TILEGX_TNUM_INT

#define TMIN_INHNO  TILEGX_TMIN_INTNO
#define TMAX_INHNO  TILEGX_TMAX_INTNO
#define TNUM_INH    TILEGX_TNUM_INT

extern const FP* const _kernel_p_inh_table[];

/**
 * Lock & Unlock CPU
 */

#define t_lock_cpu() x_lock_cpu()
#define i_lock_cpu() x_lock_cpu()

#define t_unlock_cpu() x_unlock_cpu()
#define i_unlock_cpu() x_unlock_cpu()

/**
 * Sense context
 */



#define t_sense_lock() x_sense_lock()
#define i_sense_lock() x_sense_lock()

static inline
bool_t sense_context() {
	uint64_t excpt_nest_count;

	// TODO: dirty
	bool_t locked = x_sense_lock();
	if (!locked) x_lock_cpu();
	__insn_mf();
	excpt_nest_count = get_my_p_pcb()->target_pcb.excpt_nest_count;
	if (!locked) x_unlock_cpu();

	return excpt_nest_count > 0;
}

static inline
bool_t sense_intctx_unl(void) {
    return sense_context() && !i_sense_lock();
}

static inline
bool_t sense_tskctx_unl(void) {
    return !sense_context() && !i_sense_lock();
}

#include "arch_sil.h"

/**
 * Spin lock operations for kernel
 * TODO: use static inline
 */

#if TTYPE_KLOCK == G_KLOCK
#define x_initialize_giant_lock(p_giant_lock) x_initialize_lock(p_giant_lock)
#elif TTYPE_KLOCK == F_KLOCK
#define x_initialize_obj_lock(p_obj_lock) x_initialize_lock(p_obj_lock)
#define x_initialize_tsk_lock(p_tsk_lock) x_initialize_lock(p_tsk_lock)
#else
#error unsupported TTYPE_KLOCK
#endif

#define t_acquire_lock(p_lock)  x_acquire_lock(p_lock)
#define i_acquire_lock(p_lock)  x_acquire_lock(p_lock)

#if TTYPE_KLOCK == F_KLOCK

static inline
bool_t x_acquire_nested_lock(LOCK *p_lock) {
	X_ACQUIRE_NESTED_LOCK;
}

#define t_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)
#define i_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)

#endif

/**
 * Spin lock function
 */

#define TTYPE_SPN       NATIVE_SPN
#define TMAX_NATIVE_SPN (1024)
typedef LOCK SPNLOCK;

static inline
void x_initialize_spin(ID spnid, SPNLOCK *p_spn_lock) {
	return x_initialize_lock(p_spn_lock);
}

static inline
void x_lock_spin(SPNLOCK *p_spn_lock) {
	x_acquire_lock(p_spn_lock);
}

#define t_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)
#define i_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)

static inline
bool_t x_try_lock_spin(SPNLOCK *p_lock) {
	return x_try_acquire_lock(p_lock);
}

static inline
void x_unlock_spin(SPNLOCK *p_spn_lock) {
	x_release_lock(p_spn_lock);
}

// DUMMY BELOW THIS LINE


static inline
uint_t x_prc_index(void) {
	// TODO: use tp to eliminate processor index
    return __insn_mfspr(SPR_SYSTEM_SAVE_K_0);
//	return get_my_p_pcb()->prcid - 1;
}


extern void _kernel_default_int_handler(void);

#define INT_ENTRY(inhno, inthdr) inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)

/* must work even if task migration happens */
static inline TCB* get_my_p_runtsk() {
#if defined(SUPPORT_GET_P_RUNTSK_SPR)
	return (TCB*)__insn_mfspr(SPR_SAVE_P_RUNTSK);
#elif defined(SUPPORT_GET_P_RUNTSK_FAST)
	TCB *p_runtsk;
	SIL_PRE_LOC;
	SIL_LOC_INT();
	p_runtsk = get_my_p_pcb()->p_runtsk;
	SIL_UNL_INT();
	return p_runtsk;
#else
	extern TCB* const p_tcb_table[];
	ID tid;
	ER ercd = get_tid(&tid);
	assert(ercd == E_OK);
	return p_tcb_table[tid-1];
#endif
}

/*
 *  トレースログに関する設定
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

#endif
