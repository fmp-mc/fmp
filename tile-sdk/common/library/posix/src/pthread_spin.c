/**
 * POSIX support for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2016 by Yixiao Li (liyixiao@ertl.jp)
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

#include <sys/features.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#include "kernel/kernel_impl.h"
#include "posix_cfg.h"

//#define PTHREAD_SPIN_USE_MCS
#if defined(PTHREAD_SPIN_USE_MCS)
#define LOCK tl_mcs_lock
#define x_initialize_lock(p_lock) 				  (tl_mcs_initialize_lock(p_lock))
#define x_acquire_lock(p_lock) 					  (tl_mcs_acquire_lock(p_lock))
#define x_try_acquire_lock(p_lock) 				  (tl_mcs_try_acquire_lock(p_lock))
#define x_acquire_lock_without_preemption(p_lock) (tl_mcs_acquire_lock_without_preemption(p_lock))
#define x_release_lock(p_lock) 					  (tl_mcs_release_lock(p_lock))
#endif

struct pthread_spinlock {
	LOCK lock;
};

int pthread_spin_init(pthread_spinlock_t *lock, int pshared) {
	assert(pshared == PTHREAD_PROCESS_PRIVATE); // pshared is ignored
	pthread_spinlock_t ps = malloc(sizeof(struct pthread_spinlock));

	if (ps == NULL) {
		assert(false);
		return ENOMEM;
 	}

	x_initialize_lock(&(ps->lock));
	*lock = ps;
	return 0;
} 

int pthread_spin_destroy(pthread_spinlock_t *lock) {
	/**
	 * The results are undefined if pthread_spin_destroy() is called when a thread holds the lock,
	 * or if this function is called with an uninitialized thread spin lock.
	 */
	free(*lock);
	return 0;
/* TODO:
RATIONALE
       If an implementation detects that the value specified by the lock argument to pthread_spin_destroy() does not refer to an initialized spin lock object, it is recommended  that  the  function  should
       fail and report an [EINVAL] error.

       If  an  implementation detects that the value specified by the lock argument to pthread_spin_destroy() or pthread_spin_init() refers to a locked spin lock object, or detects that the value specified
       by the lock argument to pthread_spin_init() refers to an already initialized spin lock object, it is recommended that the function should fail and report an [EBUSY] error.
 */
}

int pthread_spin_lock(pthread_spinlock_t *lock) {
#if 0 // might solve a deadlock problem -- ertl-liyixiao
	ID tid; get_tid(&tid);
	chg_pri(tid, PTHREAD_TASK_PRIORITY_WAIT_SPIN); // yield CPU to holders
#endif
	x_acquire_lock_without_preemption(&((*lock)->lock));
	//while(x_try_acquire_lock(&((*lock)->lock))); dly_tsk(1);
#if 0 // might solve a deadlock problem -- ertl-liyixiao
	chg_pri(tid, PTHREAD_TASK_PRIORITY);
#endif
	return 0;
/* TODO:
RATIONALE
       If an implementation detects that the value specified by the lock argument to pthread_spin_lock() or pthread_spin_trylock() does not refer to an initialized spin lock object, it is recommended  that
       the function should fail and report an [EINVAL] error.

       If  an implementation detects that the value specified by the lock argument to pthread_spin_lock() refers to a spin lock object for which the calling thread already holds the lock, it is recommended
       that the function should fail and report an [EDEADLK] error.
 */
}

#if 0 // NOTE: may lead to dead lock if not yield CPU
// TODO: support mcs lock
int pthread_spin_trylock(pthread_spinlock_t *lock) {
	return x_try_acquire_lock(&((*lock)->lock)) ? EBUSY : 0;
}
#endif

int pthread_spin_unlock(pthread_spinlock_t *lock) {
	x_release_lock(&((*lock)->lock));
	return 0;
/* TODO:
RATIONALE
       If an implementation detects that the value specified by the lock argument to pthread_spin_unlock() does not refer to an initialized spin lock object, it is recommended that the function should fail
       and report an [EINVAL] error.

       If  an  implementation  detects  that the value specified by the lock argument to pthread_spin_unlock() refers to a spin lock object for which the current thread does not hold the lock, it is recom‐
       mended that the function should fail and report an [EPERM] error.
 */
}
