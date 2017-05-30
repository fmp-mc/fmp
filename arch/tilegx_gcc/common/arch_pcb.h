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
#include "arch_serial.h"

typedef struct processor_control_block PCB;

typedef struct target_processor_control_block {
	uint64_t  excpt_nest_count; // nesting depth of interrupts (exceptions)
	STK_T*    istkpt;           // initial stack pointer for interrupt context
	const FP* p_inh_tbl;        // pointer of interrupt handler table
	SIOPCB    siopcb;
} TPCB;

/**
 * Re-implement of get_my_p_pcb().
 * Speed up with tp register.
 */
#define OMIT_GET_MY_P_PCB
static inline
PCB* get_my_p_pcb() {
	register intptr_t tp asm ("tp");
    return (PCB*)tp;
}

/**
 * Define x_lock_cpu() & x_unlock_cpu() here for spin lock headers
 */

static inline
bool_t x_sense_lock(void) {
    return __insn_mfspr(SPR_INTERRUPT_CRITICAL_SECTION) & 0x1;
}

static inline
void x_lock_cpu() {
	// TODO: why ARM_MEMORY_CHANGED ?
	//asm("":::"memory"); // barrier for critical section, see ASP design.txt TODO: should use mf()?
	__insn_mtspr(SPR_INTERRUPT_CRITICAL_SECTION, 1);
}

static inline
void x_unlock_cpu() {
	// TODO: why ARM_MEMORY_CHANGED ?
	//asm("":::"memory"); // barrier for critical section, see ASP design.txt TODO: should use mf()?
	__insn_mtspr(SPR_INTERRUPT_CRITICAL_SECTION, 0);
}

/**
 * Back-off delay function
 */

/*
 * The mfspr in __spinlock_relax() is 5 or 6 cycles plus 2 for loop
 * overhead.
 */
#ifdef __tilegx__
#define CYCLES_PER_RELAX_LOOP 7
#else
#define CYCLES_PER_RELAX_LOOP 8
#endif

/*
 * Idle the core for CYCLES_PER_RELAX_LOOP * iterations cycles.
 */
static inline void
relax(int iterations)
{
    for (/*above*/; iterations > 0; iterations--)
        __insn_mfspr(SPR_PASS);
    __asm__ __volatile__("" ::: "memory");
    //#define barrier() __asm__ __volatile__("" ::: "memory") // TODO: maybe wrong!
    //barrier();
}

/* Perform bounded exponential backoff.*/
static void delay_backoff(int iterations)
{
    uint32_t exponent, loops;

    /*
     * 2^exponent is how many times we go around the loop,
     * which takes 8 cycles.  We want to start with a 16- to 31-cycle
     * loop, so we need to go around minimum 2 = 2^1 times, so we
     * bias the original value up by 1.
     */
    exponent = iterations + 1;

    /*
     * Don't allow exponent to exceed 7, so we have 128 loops,
     * or 1,024 (to 2,047) cycles, as our maximum.
     */
    if (exponent > 8)
        exponent = 8;

    loops = 1 << exponent;

    /* Add a randomness factor so two cpus never get in lock step. */
#define get_cycles_low() __insn_mfspr(SPR_CYCLE)   /* just get all 64 bits */
    register unsigned long stack_pointer __asm__("sp");
    loops += __insn_crc32_32(stack_pointer, get_cycles_low()) &
        (loops - 1);

    relax(loops);
}

/**
 * Supported spin lock implementations
 */

// Memory barrier for TILE-Gx
#define barrier() __insn_mf() // __asm__ __volatile__("" ::: "memory") // TODO: maybe wrong! or __insn_mf()

// CAS (compare-and-swap) atomic instruction for TILE-Gx
static inline
uint64_t cmpxchg(volatile void *dest, uint64_t cmpval, uint64_t newval) {
#if defined(USE_GCC_BUILTIN_CAS)
	//__insn_mtspr(SPR_CMPEXCH_VALUE, cmpval);
	//return __insn_cmpexch(dest, newval);
    return __sync_val_compare_and_swap((uint64_t*)dest, cmpval, newval);
#else
	bool_t TOPPERS_int_locked = x_sense_lock();
	if (!TOPPERS_int_locked) x_lock_cpu();
	__insn_mtspr(SPR_CMPEXCH_VALUE, cmpval);
	barrier();
	uint64_t oldval = __insn_cmpexch(dest, newval);
	if (!TOPPERS_int_locked) x_unlock_cpu();
	return oldval;
#endif
}
static inline
uint64_t cmpxchg4(volatile void *dest, uint32_t cmpval, uint32_t newval) {
#if defined(USE_GCC_BUILTIN_CAS)
	//__insn_mtspr(SPR_CMPEXCH_VALUE, cmpval);
	//return __insn_cmpexch4(dest, newval);
    return __sync_val_compare_and_swap((uint32_t*)dest, cmpval, newval);
#else
	bool_t TOPPERS_int_locked = x_sense_lock();
	if (!TOPPERS_int_locked) x_lock_cpu();
	__insn_mtspr(SPR_CMPEXCH_VALUE, cmpval);
	barrier();
	uint64_t oldval = __insn_cmpexch4(dest, newval);
	if (!TOPPERS_int_locked) x_unlock_cpu();
	return oldval;
#endif
}

#include "arch_spinlock_tas.h"
#include "arch_spinlock_tatas.h"
#include "arch_spinlock_backoff.h"
#include "arch_spinlock_k42.h"
#include "arch_spinlock_mcs.h"

// Select an implementation for kernel
#if defined(KERNEL_SPIN_LOCK_TAS)
#define PREFIX_SPIN_LOCK_NAME(x)   tas##_##x
#endif
#if defined(KERNEL_SPIN_LOCK_TATAS)
#define PREFIX_SPIN_LOCK_NAME(x)   tatas##_##x
#endif
#if defined(KERNEL_SPIN_LOCK_BACKOFF)
#define PREFIX_SPIN_LOCK_NAME(x)   backoff##_##x
#endif
#if defined(KERNEL_SPIN_LOCK_K42)
#define PREFIX_SPIN_LOCK_NAME(x)   k42##_##x
#endif

typedef PREFIX_SPIN_LOCK_NAME(lock) LOCK;

#define x_initialize_lock(p_lock) 				  PREFIX_SPIN_LOCK_NAME(initialize_lock(p_lock))
#define x_acquire_lock(p_lock) 					  PREFIX_SPIN_LOCK_NAME(acquire_lock(p_lock))
#define x_try_acquire_lock(p_lock) 				  PREFIX_SPIN_LOCK_NAME(try_acquire_lock(p_lock))
#define x_acquire_lock_without_preemption(p_lock) PREFIX_SPIN_LOCK_NAME(acquire_lock_without_preemption(p_lock))
#define x_release_lock(p_lock) 					  PREFIX_SPIN_LOCK_NAME(release_lock(p_lock))

#if TTYPE_KLOCK == F_KLOCK

#define X_ACQUIRE_NESTED_LOCK PREFIX_SPIN_LOCK_NAME(ACQUIRE_NESTED_LOCK)

#endif
