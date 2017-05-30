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

#include <sys/features.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include "kernel_cfg.h"
#include "posix_cfg.h"
#include "arch_spinlock_mcs.h"

//#define MCS_LOCK_BARRIER

//#define PTHREAD_BARRIER_PROFILE
uint64_t per_task_barrier_wait_cycles[TNUM_TSKID];

struct pthread_barrier {
	unsigned max;
	volatile unsigned n;
	volatile bool_t   is_arrival_phase;
#if defined(MCS_LOCK_BARRIER)
	mcs_lock lock;
#else
	LOCK lock;
#endif
};

int pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned count) {
	assert(attr == NULL);
	pthread_barrier_t pb = malloc(sizeof(struct pthread_barrier));

	if (pb == NULL) {
		assert(false);
		return ENOMEM;
	}

	pb->max = count;
	pb->n = 0;
	pb->is_arrival_phase = true;
#if defined(MCS_LOCK_BARRIER)
	__insn_mf();
	pb->lock = NULL;
#else
	x_initialize_lock(&(pb->lock));
#endif

	*barrier = pb;
	return 0;
}

int pthread_barrier_destroy(pthread_barrier_t *barrier) {
	free(*barrier);
	return 0;
}

int pthread_barrier_wait(pthread_barrier_t *barrier) {
#if defined(PTHREAD_BARRIER_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif

	// Enter arrival phase
	while(!((*barrier)->is_arrival_phase)); // TODO: try flag?

	unsigned local_n;

#if defined(MCS_LOCK_BARRIER)
	mcs_lock_t me;
	lock_mcs(&((*barrier)->lock), &me, false);
	local_n = ++((*barrier)->n);
	unlock_mcs(&((*barrier)->lock), &me);
#else
	x_acquire_lock_without_preemption(&((*barrier)->lock));
	local_n = ++((*barrier)->n);
	x_release_lock(&((*barrier)->lock));
#endif

	if (local_n == (*barrier)->max) { // last thread is arrived
		(*barrier)->is_arrival_phase = false;
	}

	// Enter departure phase
	while(((*barrier)->is_arrival_phase));

#if defined(MCS_LOCK_BARRIER)
	lock_mcs(&((*barrier)->lock), &me, false);
	local_n = --((*barrier)->n);
	unlock_mcs(&((*barrier)->lock), &me);
#else
	x_acquire_lock_without_preemption(&((*barrier)->lock));
	local_n = --((*barrier)->n);
	x_release_lock(&((*barrier)->lock));
#endif

	if (local_n == 0) { // last thread is leaved
		(*barrier)->is_arrival_phase = true;
	}

#if defined(PTHREAD_BARRIER_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_barrier_wait_cycles[INDEX_TSK(TSKID(get_my_p_runtsk()))] += now - cycle_counter;
#endif

	return 0;
}
