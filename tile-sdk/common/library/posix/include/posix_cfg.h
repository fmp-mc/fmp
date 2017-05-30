/*
 * posix_cfg.h
 *
 *  Created on: Dec 1, 2015
 *      Author: liyixiao
 */

#pragma once

struct SEMCB;

#define PTHREAD_TERMINATED_FLG (1 << 0UL)

// TODO: data align
struct posix_thread_control_block {
	ID tskid;
	ID status_flgid;
    void *(*start_routine) (void *);
    void *arg;
    void *retval;
};

// TODO: data align
struct pthread_mutex_control_block {
//	ID semid;
	struct SEMCB *semcb;
};

// TODO: data align
struct pthread_cond_control_block {
//	ID waiters;      // Semaphore used to hold waiter tasks
	struct SEMCB *waiters_semcb;      // Semaphore used to hold waiter tasks
	//ID waiters_lock; // Lock (semaphore) for the 'waiters' semaphore
};

/**
 * Macros generated in pass 0
 */
/* [[[cog
import cog, pass0
cog.outl('#define TMAX_POSIX_THREAD  (%d)' % pass0.max_posix_thread)
cog.outl('#define TMAX_PTHREAD_MUTEX (%d)' % pass0.max_pthread_mutex)
cog.outl('#define TMAX_PTHREAD_COND  (%d)' % pass0.max_pthread_cond)
if pass0.dynamic_semcb_allocation:
	cog.outl('#define DYNAMIC_SEMCB_ALLOCATION')
]]] */
#define TMAX_POSIX_THREAD  (360)
#define TMAX_PTHREAD_MUTEX (409600)
#define TMAX_PTHREAD_COND  (204800)
#define DYNAMIC_SEMCB_ALLOCATION
/* [[[end]]] */

extern struct posix_thread_control_block* ptcb_table[TMAX_POSIX_THREAD];

// DUMMY BELOW THIS LINE
#define PTHREAD_TASK_PRIORITY_WAIT_SPIN (PTHREAD_TASK_PRIORITY + 1)
#define PTHREAD_TASK_PRIORITY (5/*MAIN_PRIORITY*/ + 1)
#define PTHREAD_STACK_SIZE    (STACK_SIZE * 1000)
void pthread_task(intptr_t ptid);
