/**
 * TILEGx Architecture Support Package for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2015 by Yixiao Li
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

#include "kernel/kernel_impl.h"
#include "kernel/pcb.h"
#include "kernel/task.h"
#include <t_syslog.h>
#include "arch_debug.h"

bool_t x_sense_mprc(void) {
	return x_prc_index() == 0;
}

void target_fput_log(char_t c) {
	hv_console_putc(c);
}

void activate_context(TCB *p_tcb) {
	extern void* start_r;
	p_tcb->tskctxb.sp =  (void *)((char_t *)((p_tcb)->p_tinib->stk) + (p_tcb)->p_tinib->stksz);
    p_tcb->tskctxb.pc = &start_r;
}

void
arch_initialize(void) {
	/**
	 * Initialize target PCB here
	 */

	TPCB *p_tpcb = get_my_p_tpcb();
    uint32_t index = x_prc_index();

    p_tpcb->excpt_nest_count = 1;           // set to 1 because the kernel is started from interrupt context
    p_tpcb->istkpt = istkpt_table[index];   // initialize the stack pointer of interrupt context
    p_tpcb->p_inh_tbl = _kernel_p_inh_table[index]; // initialize the pointer of interrupt handler table
}

#if TTYPE_KLOCK == F_KLOCK

void release_pcb_two_locks() {
	PCB *pcb = get_my_p_pcb();
	if (pcb->p_firstlock != NULL) {
		x_release_lock(pcb->p_firstlock);
		pcb->p_firstlock = NULL;
		if (pcb->p_secondlock != NULL) {
			x_release_lock(pcb->p_secondlock);
			pcb->p_secondlock = NULL;
		}
	}
}

#endif

/* must work even if task migration happens */
ID x_get_my_tid() {
#if defined(SUPPORT_GET_P_RUNTSK_SPR) || defined(SUPPORT_GET_P_RUNTSK_FAST)
	return TSKID(get_my_p_runtsk());
#else
	TCB *p_runtsk;
	SIL_PRE_LOC;
	SIL_LOC_INT();
	p_runtsk = get_my_p_pcb()->p_runtsk;
	SIL_UNL_INT();
	return TSKID(p_runtsk);
    /*
	ID tid;
	ER ercd = get_tid(&tid);
	assert(ercd == E_OK);
	return tid;*/
#endif
}



// ----------- DUMMY BELOW THIS LINE

LOCK TOPPERS_kernel_lock; // TODO: should be somewhere else?

struct pt_regs {

};

struct bme_saved_regs_full {

};

void
_kernel_default_int_handler(void){
	register int int_num asm ("r0");
	ID prc_id = (x_prc_index());

	syslog(LOG_EMERG, "Processor %d i%d: Unregistered Interrupt occurs. int_num %d", prc_id, int_num, int_num);
	debug_loop();
	target_exit();
}

void do_trap(struct pt_regs *regs, int fault_num,
               unsigned long reason) {
	syslog(LOG_EMERG, "Unexpected do_trap interrupt number %d", fault_num);
}

void do_page_fault(struct pt_regs *regs, int fault_num,
           unsigned long address, unsigned long write) {
	syslog(LOG_EMERG, "Unexpected do_page_fault interrupt number %d", fault_num);
}

void do_double_fault(struct pt_regs *regs, int fault_num,
                   unsigned long reason) {
	syslog(LOG_EMERG, "Unexpected do_double_fault interrupt number %d", fault_num);
}

void do_nmi(struct pt_regs *regs, int fault_num, unsigned long reason) {
	syslog(LOG_EMERG, "Unexpected do_nmi interrupt number %d", fault_num);
}

void do_breakpoint(struct pt_regs* regs, int fault_num) {
	syslog(LOG_EMERG, "Unexpected do_breakpoint interrupt number %d", fault_num);
}

void do_timer_interrupt(struct pt_regs *regs, int fault_num) {
    const char *str = "Hello World!\n";
    hv_console_write(str, strlen(str));
	syslog(LOG_EMERG, "Unexpected do_timer_interrupt interrupt number %d", fault_num);
}

void gx_singlestep_handle(struct pt_regs *regs, int fault_num) {
	syslog(LOG_EMERG, "Unexpected gx_singlestep_handle interrupt number %d", fault_num);
}

void tile_dev_intr(struct pt_regs *regs, int intnum) {
	syslog(LOG_EMERG, "Unexpected tile_dev_intr interrupt number %d", intnum);
}

void hv_message_intr(struct pt_regs *regs, int intnum) {
	syslog(LOG_EMERG, "Unexpected hv_message_intr interrupt number %d", intnum);
}

void handle_syscall(struct pt_regs *regs, int intnum) {
	syslog(LOG_EMERG, "Unexpected handle_syscall interrupt number %d", intnum);
}

#if 0
void handle_interrupt(struct pt_regs *regs, int intnum) {
	syslog(LOG_EMERG, "%s(): Unexpected interrupt number %d", __FUNCTION__, intnum);
	__insn_mtspr(SPR_INTERRUPT_CRITICAL_SECTION, (0UL));
}
#endif

void handle_nmi(struct pt_regs *regs, int intnum) {
	syslog(LOG_EMERG, "Unexpected handle_nmi interrupt number %d", intnum);
}

void do_unaligned(struct pt_regs *regs, int vecnum) {
	syslog(LOG_EMERG, "Unexpected do_unaligned interrupt number %d", vecnum);
}

void bad_intr(struct pt_regs *regs, int vecnum) {
	syslog(LOG_EMERG, "Unexpected bad_intr interrupt number %d", vecnum);
}

int do_work_pending(struct pt_regs *regs, uint32_t thread_info_flags) {
	syslog(LOG_EMERG, "%s() called",  __FUNCTION__);
}

void
bme_bad_intr(int int_number, struct bme_saved_regs_full *sr)
{
	syslog(LOG_EMERG, "%s() called intnum: %d",  __FUNCTION__, int_number);
	debug_loop();
	target_exit();
}

#if 0 // Legacy code

#if 0 // barrier code from arch/tile/asm/barrier.h

#define __sync()    __insn_mf()

#include <hv/syscall_public.h>
/*
 * Issue an uncacheable load to each memory controller, then
 * wait until those loads have completed.
 */
static inline void __mb_incoherent(void)
{
    long clobber_r10;
    asm volatile("swint2"
             : "=R10" (clobber_r10)
             : "R10" (HV_SYS_fence_incoherent)
             : "r0", "r1", "r2", "r3", "r4",
               "r5", "r6", "r7", "r8", "r9",
               "r11", "r12", "r13", "r14",
               "r15", "r16", "r17", "r18", "r19",
               "r20", "r21", "r22", "r23", "r24",
               "r25", "r26", "r27", "r28", "r29");
}

#define CHIP_HAS_TILE_WRITE_PENDING() 0 // from arch/tile/include/arch/chip_tilegx.h
/* Fence to guarantee visibility of stores to incoherent memory. */
static inline void
mb_incoherent(void)
{
    __insn_mf();

    {
#if CHIP_HAS_TILE_WRITE_PENDING()
        const unsigned long WRITE_TIMEOUT_CYCLES = 400;
        unsigned long start = get_cycles_low();
        do {
            if (__insn_mfspr(SPR_TILE_WRITE_PENDING) == 0)
                return;
        } while ((get_cycles_low() - start) < WRITE_TIMEOUT_CYCLES);
#endif /* CHIP_HAS_TILE_WRITE_PENDING() */
        (void) __mb_incoherent();
    }
}

#endif

#if TTYPE_KLOCK == G_KLOCK

// From /manycore/fmp-tilegx/fmp/arch/tilegx_gcc/common/linux-3.12/arch/tile/lib

#define barrier() __asm__ __volatile__("" ::: "memory") // TODO: maybe wrong!

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
    barrier();
}

typedef uint32_t u32;
#define get_cycles_low() __insn_mfspr(SPR_CYCLE)   /* just get all 64 bits */

/* Perform bounded exponential backoff.*/
static void delay_backoff(int iterations)
{
#if 0
    u32 exponent, loops;

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
    register unsigned long stack_pointer __asm__("sp");
    loops += __insn_crc32_32(stack_pointer, get_cycles_low()) &
        (loops - 1);

    relax(loops);
#endif
}

// From glibc-2.12-1.80.get (pthread spin lock)

#define atomic_full_barrier() __sync_synchronize()

/* Pick appropriate 8- or 4-byte instruction. */
#define __atomic_update(mem, v, op)                                     \
  ((__typeof (*(mem))) (__typeof (*(mem) - *(mem)))                     \
   ((sizeof (*(mem)) == 8) ?                                            \
    __insn_##op ((void *) (mem), (int64_t) (__typeof((v) - (v))) (v)) : \
    (sizeof (*(mem)) == 4) ?                                            \
    __insn_##op##4 ((void *) (mem), (int32_t) (__typeof ((v) - (v))) (v)) : \
    __atomic_error_bad_argument_size()))


#define TNS(p) atomic_exchange_acq((p), 1)
#define CMPTNS(p) atomic_compare_and_exchange_val_acq((p), 1, 0)

#define atomic_compare_and_exchange_val_acq(mem, n, o)                  \
  ({ __insn_mtspr (SPR_CMPEXCH_VALUE, (int64_t) (__typeof ((o) - (o))) (o)); \
     __atomic_update (mem, n, cmpexch); })

#define atomic_exchange_acq(mem, newvalue) \
  __atomic_update (mem, newvalue, exch)



#define atomic_exchange_rel(mem, n)                             \
  ({                                                            \
    atomic_full_barrier ();                                     \
    atomic_exchange_acq ((mem), (n));                           \
  })

#define SPIN_LOCK_AVAILABLE (0x1)

#define HV_LOCK_C // Use sys/hv/lock.c (without backoff)
//void x_initialize_giant_lock(LOCK *p_giant_lock) {
void x_initialize_lock(LOCK *p_lock) {
//	syslog(LOG_EMERG, "%s() called.", __FUNCTION__);
#if defined(HV_LOCK_C)
	__insn_mf();
	*p_lock = 0;
#else
	atomic_exchange_rel(p_giant_lock, 0);
#if 0

#if 1 // TILE-Gx Hypervisor version

#else // GCC version
	*p_giant_lock = SPIN_LOCK_AVAILABLE;
#endif
#endif
#endif
}

void x_acquire_lock(LOCK *p_lock) {
//	syslog(LOG_EMERG, "%s() called.", __FUNCTION__);
	uint32_t iterations = 0;
#if defined(HV_LOCK_C) // TILE-Gx Hypervisor version
	__insn_mf();
	while(__insn_exch4(p_lock, 1) != 0) {
#else // GCC version
	while(!__sync_bool_compare_and_swap_4(p_lock, SPIN_LOCK_AVAILABLE, 0)) {
#endif
		x_unlock_cpu();
		delay_backoff(iterations++);
		x_lock_cpu();
	}
}

#if 0
void i_acquire_lock(LOCK *p_lock) {
	x_acquire_lock(p_lock);
}

void t_acquire_lock(LOCK *p_lock) {
	x_acquire_lock(p_lock);
}
#endif

bool_t x_try_acquire_lock(LOCK *p_lock) {
#if defined(HV_LOCK_C) || 1 // TILE-Gx Hypervisor version
	__insn_mf();
	return(__insn_exch4(p_lock, 1) == 0);
#endif
}

void x_release_lock(LOCK *p_lock) {
#if defined(HV_LOCK_C) // TILE-Gx Hypervisor version
	__insn_mf();
	//mb_incoherent();
	//__sync_synchronize();
	*p_lock = 0;
#else
	//	syslog(LOG_EMERG, "%s() called.", __FUNCTION__);
	atomic_exchange_rel(p_lock, 0);
#if 0

#if 1 // TILE-Gx Hypervisor version

#else // GCC version
	*p_lock = SPIN_LOCK_AVAILABLE;
#endif
#endif

#endif
}

void x_acquire_lock_without_preemption(LOCK *p_lock) {
//	syslog(LOG_EMERG, "%s() called.", __FUNCTION__);
	uint32_t iterations = 0;
#if 1 // TILE-Gx Hypervisor version
	__insn_mf();
	while(__insn_exch4(p_lock, 1) != 0) delay_backoff(iterations++);
#else // GCC version
	while(!__sync_bool_compare_and_swap_4(p_lock, SPIN_LOCK_AVAILABLE, 0));
#endif
}

#elif TTYPE_KLOCK == F_KLOCK

void release_pcb_two_locks() {
	PCB *pcb = get_my_p_pcb();
	if (pcb->p_firstlock != NULL) {
		x_release_lock(pcb->p_firstlock);
		pcb->p_firstlock = NULL;
		if (pcb->p_secondlock != NULL) {
			x_release_lock(pcb->p_secondlock);
			pcb->p_secondlock = NULL;
		}
	}
}

#else
#error Unsupported TTYPE_KLOCK
#endif

#endif
