/*
 * pthread_cond.c
 *
 *  Created on: Nov 27, 2015
 *      Author: liyixiao
 */

// TOPPERS/FMP kernel
#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"

#include <pthread.h>
#include <sys/errno.h> // Error numbers from Newlib
#include "posix_cfg.h"

//#define DEBUG_PTHREAD_COND

int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr) {
	// Preconditions
	assert(cond != NULL);
	assert(attr == NULL);  // No attributes are supported currently.

	ER ercd = pget_mpf(PTHREAD_COND_MPF, cond);

	switch(ercd) {
	case E_OK:
		return 0;

	case E_TMOUT:
		assert(false);
		return EAGAIN;

	default:
		assert(false);
		return ercd;
	}
}

int pthread_cond_destroy(pthread_cond_t *cond) {
	// Preconditions
	assert(cond != NULL);

	/**
	 * The status of semaphore will not be checked according to:
	 * It shall be safe to destroy an initialized condition variable upon which no threads are cur‐
     * rently blocked. Attempting to destroy a condition variable upon which other threads are cur‐
     * rently blocked results in undefined behavior.
	 * Reference: PTHREAD_COND_DESTROY(3P) POSIX Programmer's Manual
	 */
	ER ercd = rel_mpf(PTHREAD_COND_MPF, *cond);

	switch(ercd) {
	case E_OK:
		return 0;

	case E_PAR:
		return EINVAL;

	default:
		assert(false);
		return ercd;
	}

	/*
	   TODO:
       If  an  implementation  detects  that  the  value  specified   by   the   cond   argument   to
       pthread_cond_destroy()  does not refer to an initialized condition variable, it is recommended
       that the function should fail and report an [EINVAL] error.

       If  an  implementation  detects  that  the  value  specified   by   the   cond   argument   to
       pthread_cond_destroy()  or  pthread_cond_init()  refers to a condition variable that is in use
       (for example, in a pthread_cond_wait() call) by another thread,  or  detects  that  the  value
       specified  by the cond argument to pthread_cond_init() refers to an already initialized condi‐
       tion variable, it is recommended that the function should fail and report an [EBUSY] error.
	 */
}

int pthread_cond_broadcast(pthread_cond_t *cond) {
#if defined(DEBUG_PTHREAD_COND)
	ID tskid; get_tid(&tskid);
	syslog(LOG_NOTICE, "tid %d call %s(), cond semid %d", tskid, __FUNCTION__, cond->cb->waiters);
#endif
	ER ercd = ini_sem_by_cb((*cond)->waiters_semcb); // TODO: check performance of this operation
	assert(ercd == E_OK);
	return ercd;
}

int pthread_cond_signal(pthread_cond_t *cond) {
#if defined(DEBUG_PTHREAD_COND)
	syslog(LOG_NOTICE, "%s() called, cond semid %d", __FUNCTION__, cond->cb->waiters);
#endif
	ER ercd = sig_sem_by_cb((*cond)->waiters_semcb); // TODO: check performance of this operation
	assert(ercd == E_OK || ercd == E_QOVR);
	return ercd;
}

int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex) {
#if defined(DEBUG_PTHREAD_COND)
	ID tskid; get_tid(&tskid);
	syslog(LOG_NOTICE, "tid %d call %s(), mutex semid %d, cond semid %d", tskid, __FUNCTION__, mutex->cb->semid, cond->cb->waiters);
#endif
	ER ercd = sig_and_wai_sem_by_cb((*mutex)->semcb, (*cond)->waiters_semcb);
#if defined(DEBUG_PTHREAD_COND)
	syslog(LOG_NOTICE, "tid %d call %s(), get waiters", tskid, __FUNCTION__);
#endif
	assert(ercd == E_OK || ercd == E_DLT);
	ercd = pthread_mutex_lock(mutex);
#if defined(DEBUG_PTHREAD_COND)
	syslog(LOG_NOTICE, "tid %d call %s(), get mutex", tskid, __FUNCTION__);
#endif
	assert(ercd == 0);
	return 0;
}

pthread_cond_t pthread_cond_initializer() {
	syslog(LOG_NOTICE, "%s() called", __FUNCTION__);
	pthread_cond_t cond;
	int res = pthread_cond_init(&cond, NULL);
	assert(res == 0);
	return cond;
}

#if 0


/**
 * Since spurious wakeups are permitted,
 * 'waiters' is not protected by lock.
 * TODO: use counters to improve performance
 */

static int pthread_cond_unblock(pthread_cond_t *cond, bool_t unblock_all) {
	/**
	 * TODO:
	 RATIONALE
       If an implementation detects that the value specified by the  cond  argument  to
       pthread_cond_broadcast()  or pthread_cond_signal() does not refer to an initial‐
       ized condition variable, it is recommended that the  function  should  fail  and
       report an [EINVAL] error.
	 */
	ER ercd;
#if 0
	ercd = wai_sem(cond->waiters_lock);
	assert(ercd == E_OK);
#endif

	if (unblock_all) {
		ercd = ini_sem(cond->waiters); // TODO: check performance of this operation
		assert(ercd == E_OK);
	} else {
		T_RSEM resm;
		ercd = ref_sem(cond->waiters, &resm); // TODO: this SVC is for debug purpose
		assert(ercd == E_OK);
		if (resm.wtskid != TSK_NONE) {
			ercd = sig_sem(cond->waiters);
			assert(ercd == E_OK);
		}
	}

#if 0
	ercd = sig_sem(cond->waiters_lock);
	assert(ercd == E_OK);
#endif
	return 0;
}
#endif
