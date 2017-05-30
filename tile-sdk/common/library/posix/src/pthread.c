/**
 * A lightweight POSIX thread library.
 * Some restrictions exist for performance and complexity
 * of the implementation.
 */

// TOPPERS/FMP kernel
#include <kernel.h>
#include <t_syslog.h>
#include <queue.h>
#include "kernel_cfg.h"
#include "target_config.h"

#include <pthread.h>
#include <sys/errno.h> // Error numbers from Newlib
#include "posix_cfg.h"
#include "kernel/task.h"

#include "kernel/semaphore.h" // For debug
#include "arch_debug.h"

//#define DEBUG_PTHREAD
//#define LOG_NOTICE LOG_EMERG

/**
 * Restrictions:
 * 1. attr MUST be NULL.
 * 2. ONLY master core CAN create thread.
 */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                    void *(*start_routine) (void *), void *arg) {
	// Preconditions
	assert(thread != NULL);
    assert(attr == NULL || attr->is_initialized == 1);   // No attributes are supported currently.
    assert(x_sense_mprc()); // ONLY master core CAN create thread.

	ER ercd = pget_mpf(POSIX_THREAD_MPF, thread);

#if defined(DEBUG_PTHREAD)
	syslog(LOG_NOTICE, "%s(start_routine=0x%x,arg=0x%x) called, tskid=%d.", __FUNCTION__, start_routine, arg, (*thread)->tskid);
	dly_tsk(1);
#endif

	switch(ercd) {
	case E_OK:
		(*thread)->start_routine = start_routine;
		(*thread)->arg = arg;
		ini_flg((*thread)->status_flgid);
		ercd = act_tsk((*thread)->tskid);
		assert(ercd == E_OK);
		return 0;

	case E_TMOUT:
		assert(false);
		return EAGAIN;

	default:
		assert(false);
		return ercd;
	}
}

int pthread_join(pthread_t thread, void **retval) {
#if defined(DEBUG_PTHREAD)
	syslog(LOG_NOTICE, "%s(tskid=%d) called.", __FUNCTION__, thread->tskid);
	dly_tsk(1);
#endif

	TCB *tcb = get_tcb(thread->tskid);
	intptr_t last_real_lr = 0x0;
	int      last_real_lr_repeat = 0;

    for (int i = 1;; i++) {
#define PTHREAD_JOIN_TIMEOUT (1000)
    	FLGPTN flgptn;
    	ER ercd = twai_flg(thread->status_flgid, PTHREAD_TERMINATED_FLG, TWF_ANDW, &flgptn, PTHREAD_JOIN_TIMEOUT);
    	if (ercd == E_OK) break;
    	syslog(LOG_NOTICE, "%s(tskid=%d,start=0x%p) has waited for %d ms.", __FUNCTION__, thread->tskid, thread->start_routine, PTHREAD_JOIN_TIMEOUT * i);
    	assert(ercd == E_TMOUT);
#if defined(DEBUG_PTHREAD) || 1
#if 0
        TCB *tcb = get_tcb(thread->tskid);
		syslog(LOG_NOTICE, "  pc=%016x, sp=%016x, lr=%016x, stat=%d, runtsk=%d", tcb->tskctxb.pc, tcb->tskctxb.sp, *(uint64_t*)(tcb->tskctxb.sp), tcb->tstat, TSKID(tcb->p_pcb->p_runtsk));
		//syslog(LOG_NOTICE, "  reqflg=%d, dspflg=%d", tcb->p_pcb->reqflg, tcb->p_pcb->dspflg);
		syslog(LOG_NOTICE, "  ready_primap=0x%x, pri=%d", tcb->p_pcb->ready_primap, tcb->priority);
		if (tcb->p_wobjcb) {
			SEMCB	*semcb = tcb->p_wobjcb;

			syslog(LOG_NOTICE, "  semid=%d, sem=%016x, wait_q_empty=%d", SEMID(semcb), semcb->semcnt, queue_empty(&semcb->wait_queue));
		}
#endif

#define TSTAT_STRING(tstat) (TSTAT_DORMANT(tstat) ? "DORMANT" : (TSTAT_RUNNABLE(tstat) ? "RUNNABLE" : (TSTAT_WAITING(tstat) ? "WAITING" : (TSTAT_SUSPENDED(tstat) ? "SUSPENDED" : "!ILLEGAL!"))))

#define TSKCTXB_PC_STRING(pc) (((pc) == &dispatch_r) ? "dispatch_r" : (((pc) == &ret_int_r) ? "ret_int_r" : ((((pc) == &start_r) ? "start_r" : ("!ILLEGAL!")))))
		extern intptr_t dispatch_r, ret_int_r, start_r; // NOTE: tskctxb.pc can only be one of these

#define TCB_REAL_LR(tskctxb) ((tskctxb).pc == &dispatch_r ? (*((intptr_t*)(tskctxb).sp)) : ((tskctxb).pc == &ret_int_r ? (*((intptr_t*)(tskctxb).sp + 23 /* skip r30-r52 */)) : 0xFFFFFFFFUL))

#if 0
		// detect forever blocking error
		if (!TSTAT_RUNNABLE(tcb->tstat) && i > 100) {

			// detect semaphore queue error
			if (((tcb->tstat) & TS_WAIT_MASK) == TS_WAIT_SEM) {
				SEMCB *semcb = tcb->p_wobjcb;
				if (semcb->semcnt > 0 && (((tcb->tstat) & TS_WAIT_MASK) == TS_WAIT_SEM)) { // no waiter, double check
					syslog(LOG_NOTICE, "FATAL: tid %d semaphore queue error!", thread->tskid);
					syslog(LOG_NOTICE, "semid=%d, sem=%016x, wait_q_empty=%d", SEMID(semcb), semcb->semcnt, queue_empty(&semcb->wait_queue));
					debug_loop();
				}
			}
		}
#endif

		// detect program stuck
		if (TSTAT_RUNNABLE(tcb->tstat)) {

		intptr_t new_real_lr = TCB_REAL_LR(tcb->tskctxb);
		if (last_real_lr == new_real_lr) {
			if (++last_real_lr_repeat > 600) {
				syslog(LOG_EMERG, "  tstat=%s, pc=%s, sp=0x%p, real_lr=0x%p", TSTAT_STRING(tcb->tstat), TSKCTXB_PC_STRING(tcb->tskctxb.pc), tcb->tskctxb.sp, TCB_REAL_LR(tcb->tskctxb));
				syslog(LOG_EMERG, "FATAL: tid %d stuck at real_lr:0x%p!", thread->tskid, last_real_lr);
				debug_loop();
			}
		} else {
			last_real_lr = new_real_lr;
			last_real_lr_repeat = 0;
		}

		}

		if (i >= 1000) { // takes too long, find out what's going on
			syslog(LOG_NOTICE, "  tstat=%s, pc=%s, sp=0x%p, real_lr=0x%p", TSTAT_STRING(tcb->tstat), TSKCTXB_PC_STRING(tcb->tskctxb.pc), tcb->tskctxb.sp, TCB_REAL_LR(tcb->tskctxb));
		}

		// detect pending dispatch
		for (int i = 1; i <= TNUM_PRCID; i++) {
			if (get_mp_p_pcb(i)->p_runtsk != get_mp_p_pcb(i)->p_schedtsk) {

				syslog(LOG_NOTICE, "PRC [%d] should dispatch!", i);
				assert(!get_mp_p_pcb(i)->disdsp);
				assert(!get_mp_p_pcb(i)->reqflg);
				//dispatch_request(get_mp_p_pcb(i));
			}
		}
#endif
    }
    *retval = thread->retval;

    // Free pthread
    while (1) { // Ensure TTS_DMT at first
        T_RTSK rtsk;
        SVC_PERROR(ref_tsk(thread->tskid, &rtsk));
        if (rtsk.tskstat == TTS_DMT) break;
        dly_tsk(1);
    }
    SVC_PERROR(rel_mpf(POSIX_THREAD_MPF, thread));

    syslog(LOG_NOTICE, "%s(tskid=%d) joined.", __FUNCTION__, thread->tskid);
    return 0;
}

void pthread_task(intptr_t ptid) {
	struct posix_thread_control_block *p_ptcb = ptcb_table[ptid];

#if defined(DEBUG_PTHREAD)
	ID tskid;
	get_tid(&tskid);
	syslog(LOG_NOTICE, "%s(tskid=%d) called, start=0x%x, arg=0x%x.", __FUNCTION__, tskid, p_ptcb->start_routine, p_ptcb->arg);
	dly_tsk(1);
#endif

#if defined(MALLOC_USE_HOARD)
	hoard_hook_on_thread_create();
#endif

#if 1
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif

	p_ptcb->retval = p_ptcb->start_routine(p_ptcb->arg);

#if 1
	cycle_counter = __insn_mfspr(SPR_CYCLE) - cycle_counter;
	syslog(LOG_NOTICE, "pthread(tid=%d) exits, exec time: %d ms", p_ptcb->tskid, cycle_counter / (cpu_hz() / 1000));
#endif

	SVC_PERROR(set_flg(p_ptcb->status_flgid, PTHREAD_TERMINATED_FLG));

#if defined(MALLOC_USE_HOARD)
	hoard_hook_on_thread_destroy();
#endif

#if defined(DEBUG_PTHREAD)
    syslog(LOG_NOTICE, "%s(tskid=%d) exits.", __FUNCTION__, tskid);
#endif
}

#if 0 // Legacy code

#endif
