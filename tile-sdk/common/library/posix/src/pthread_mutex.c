/*
 * pthread_mutex.c
 *
 *  Created on: Nov 27, 2015
 *      Author: liyixiao
 */

// TOPPERS/FMP kernel
#include <kernel.h>
#include <t_syslog.h>
#include "kernel_cfg.h"
#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include "kernel/semaphore.h"
#include "semaphore_by_cb.h"

#include <pthread.h>
#include <sys/errno.h> // Error numbers from Newlib
#include "posix_cfg.h"

//#define DEBUG_PTHREAD_MUTEX

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) {
#if defined(DEBUG_PTHREAD_MUTEX)
	syslog(LOG_DEBUG, "%s() called", __FUNCTION__);
#endif

	// Preconditions
	assert(mutex != NULL);
	assert(attr == NULL);  // No attributes are supported currently.

	ER ercd = pget_mpf(PTHREAD_MUTEX_MPF, mutex);

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

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
#if defined(DEBUG_PTHREAD_MUTEX)
	syslog(LOG_DEBUG, "%s() called, semid %d", __FUNCTION__, mutex->cb->semid);
#endif

	// Preconditions
	assert(mutex != NULL);
	assert(*mutex != NULL);

	/**
	 * The status of semaphore will not be checked according to:
	 * It shall be safe to destroy an  initialized  mutex  that  is  unlocked.
     * Attempting to destroy a locked mutex or a mutex that is referenced (for
     * example,  while   being   used   in   a   pthread_cond_timedwait()   or
     * pthread_cond_wait()) by another thread results in undefined behavior.
     * Reference: PTHREAD_MUTEX_DESTROY(3P) POSIX Programmer's Manual
	 */
	ER ercd = rel_mpf(PTHREAD_MUTEX_MPF, *mutex);

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
	   If an implementation detects that the  value  specified  by  the  mutex
       argument to pthread_mutex_destroy() or pthread_mutex_init() refers to a
       locked mutex or a mutex that is referenced (for  example,  while  being
       used  in  a pthread_cond_timedwait() or pthread_cond_wait()) by another
       thread, or detects that the value specified by the  mutex  argument  to
       pthread_mutex_init() refers to an already initialized mutex, it is rec‐
       ommended that the function should fail and report an [EBUSY] error.

       If an implementation detects that the value specified by the attr argu‐
       ment  to  pthread_mutex_init()  does  not refer to an initialized mutex
       attributes object, it is recommended that the function should fail  and
       report an [EINVAL] error.
	 */
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
#if defined(DEBUG_PTHREAD_MUTEX)
	ID tid; get_tid(&tid);
	T_RSEM rsem;
	ref_sem(mutex->cb->semid, &rsem);
	syslog(LOG_NOTICE, "tid %d call %s(), semid %d", tid, __FUNCTION__);
#endif

	ER ercd = wai_sem_by_cb((*mutex)->semcb);

	switch(ercd) {
	case E_OK:
		return 0;
	default:
		syslog(LOG_NOTICE, "%s(): ercd %d", __FUNCTION__, ercd);
		return ercd;
	}
}

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
	TCB *runtsk = get_my_p_runtsk();
	TMO tmout = (runtsk->tskctxb.try_lock == mutex && runtsk->tskctxb.try_lock_times >= 10) ? 1 : TMO_POL;
	ER ercd = twai_sem_by_cb((*mutex)->semcb, tmout);

#if defined(DEBUG_PTHREAD_MUTEX)
	T_RSEM rsem;
	ref_sem(mutex->cb->semid, &rsem);
	syslog(LOG_NOTICE, "%s() called, semid %d, count after trylock %d", __FUNCTION__, mutex->cb->semid, rsem.semcnt);
#endif


	switch(ercd) {
	case E_OK:
		if (runtsk->tskctxb.try_lock == mutex) runtsk->tskctxb.try_lock = NULL;
		return 0;
	case E_TMOUT:
		if (runtsk->tskctxb.try_lock != mutex) {
			runtsk->tskctxb.try_lock = mutex;
			runtsk->tskctxb.try_lock_times = 1;
		} else {
			runtsk->tskctxb.try_lock_times++;
		}
		return EBUSY;
	default:
		assert(false);
		return ercd;
	}
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
#if defined(DEBUG_PTHREAD_MUTEX)
    register int lr_ asm ("lr");
    int lr = lr_; // NOTE: This is IMPORTANT! Snapshot.
	T_RSEM rsem;
	ref_sem(mutex->cb->semid, &rsem);
	syslog(LOG_NOTICE, "%s() called, semid %d, count before unlock %d", __FUNCTION__, mutex->cb->semid, rsem.semcnt);
#endif
	ER ercd = sig_sem_by_cb((*mutex)->semcb);

	switch(ercd) {
	case E_OK:
		return 0;
	default:
#if defined(DEBUG_PTHREAD_MUTEX)
		syslog(LOG_NOTICE, "%s(): ercd %d, lr=%016x", __FUNCTION__, ercd, lr);
#else
		syslog(LOG_NOTICE, "%s(): ercd %d", __FUNCTION__, ercd);
#endif
		return ercd;
	}
}

pthread_mutex_t pthread_mutex_initializer() {
	syslog(LOG_NOTICE, "%s() called", __FUNCTION__);
	pthread_mutex_t mutex;
	int res = pthread_mutex_init(&mutex, NULL);
	assert(res == 0);
	return mutex;
}
