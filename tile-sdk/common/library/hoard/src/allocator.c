/*
 * newlib_allocator.c
 *
 *  Created on: Apr 5, 2016
 *      Author: liyixiao
 */

#include <errno.h>
#include <unistd.h>
//#include <sys/stat.h>
#include "kernel_cfg.h"
#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include <t_syslog.h>
//#include "syssvc/serial.h"
#include "arch_debug.h"
#include "string.h"
#include "hoard_bme.h"

#undef errno
extern int errno;

//#define MALLOC_PROFILE

#if defined(MALLOC_PROFILE)
static uint64_t per_task_mallocator_cycles[TNUM_TSKID];
static uint64_t per_task_exec_cycles[TNUM_TSKID];
static uint64_t per_task_spin_cycles[TNUM_TSKID];
static uint64_t per_task_tls_cycles[TNUM_TSKID];
static uint64_t map_cycles;
extern uint64_t per_task_getreent_cycles[TNUM_TSKID]; // TODO: should be somewhere else
#endif

// TODO: impl or resolve
unsigned int pthread_self() { // TODO: should be in POSIX library
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	ID tid = TSKID(get_my_p_runtsk());
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_tls_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
	return tid;
}

void sched_yield(){} // TODO: yield CPU to avoid dead lock

/**
 * Implement Hoard for BME interfaces
 */

/**
 * TODO: this is a stupid implementation that never releases used memory
 */
//static LOCK malloc_lock;
//#define TLSF_ACQUIRE_LOCK(lock) x_acquire_lock_without_preemption(&malloc_lock)
//#define TLSF_RELEASE_LOCK(lock) x_release_lock(&malloc_lock)
#define TLSF_ACQUIRE_LOCK(lock) SVC_PERROR(wai_sem(TLSF_SEM))
#define TLSF_RELEASE_LOCK(lock) SVC_PERROR(sig_sem(TLSF_SEM))

static unsigned char   *mem_pool;
static size_t  HEAP_SIZE;

void *hl_mmapwrapper_map(size_t sz) {
//	if (sz > 10 * 1024 * 1024) syslog(LOG_NOTICE, "%s() called sz:%lu", __FUNCTION__, sz);
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	TLSF_ACQUIRE_LOCK(lock);
#if defined(BUILD_PARSEC_DEDUP)
	unsigned char *rv = ((uint64_t)mem_pool + 65535UL) >> 16UL << 16UL;
    sz += rv - mem_pool;
#else
	unsigned char *rv = mem_pool;
#endif
	assert(HEAP_SIZE > sz);
	mem_pool  += sz;
	HEAP_SIZE -= sz;
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	map_cycles += now - cycle_counter;
#endif
//	syslog(LOG_NOTICE, "%s() called left sz:%lu", __FUNCTION__, HEAP_SIZE);
	TLSF_RELEASE_LOCK(lock);
	return rv;
}

void hl_mmapwrapper_unmap(void * ptr, size_t sz) {
	/* do nothing */
#if defined(BUILD_PARSEC_DEDUP)
//	syslog(LOG_NOTICE, "%s() called sz:%lu", __FUNCTION__, sz);
	TLSF_ACQUIRE_LOCK(lock);
    if (ptr + sz == mem_pool) {
        mem_pool = ptr;
        HEAP_SIZE +=sz;
//	    syslog(LOG_NOTICE, "%s() called sz:%lu OK", __FUNCTION__, sz);
    }
	TLSF_RELEASE_LOCK(lock);
#endif
}
///

static void *thread_heaps[TNUM_TSKID];

void hoard_set_thread_heap(void *heap) {
//	syslog(LOG_NOTICE, "%s() called, heap:0x%p", __FUNCTION__, heap);
	ID tid = TSKID(get_my_p_runtsk());
	thread_heaps[INDEX_TSK(tid)] = heap;
}

void *hoard_get_thread_heap() {
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	ID tid = TSKID(get_my_p_runtsk());
//	syslog(LOG_NOTICE, "%s() called, tid=%d, heap:0x%p", __FUNCTION__, tid, thread_heaps[INDEX_TSK(tid)]);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_tls_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
	return thread_heaps[INDEX_TSK(tid)];
}

inline void hl_lock_create(intptr_t *lock)  {
//	syslog(LOG_NOTICE, "%s() called lock: %p", __FUNCTION__, lock);
//    call_backtracer();
	x_initialize_lock((uint32_t*)lock);
}

inline void hl_lock_acquire(intptr_t *lock) { // TODO: yield CPU to avoid dead lock
//	syslog(LOG_NOTICE, "%s() called lock: %p", __FUNCTION__, lock);
#if defined(MALLOC_PROFILE)
	ID tid = TSKID(get_my_p_runtsk());
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	x_acquire_lock_without_preemption((uint32_t*)lock);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_spin_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
}

inline void hl_lock_release(intptr_t *lock) { 
//	syslog(LOG_NOTICE, "%s() called lock: %p", __FUNCTION__, lock);
    x_release_lock((uint32_t*)lock); 
}
inline void hl_lock_destroy(intptr_t *lock) { /* do nothing */ }


// TODO: a magic?
void tlsf_initialize(intptr_t unused) {
	extern void  *uma_heap;
	extern size_t uma_heap_size;
	mem_pool = uma_heap;
	HEAP_SIZE = uma_heap_size;
	syslog(LOG_NOTICE, "%s(): mem_pool=%p, HEAP_SIZE=%lu", __FUNCTION__, mem_pool, HEAP_SIZE);
}

/**
 * Replace default allocator
 */

#if defined(MALLOC_USE_HOARD)

void *malloc(size_t nbytes) {
#if defined(MALLOC_PROFILE)
	ID tid = TSKID(get_my_p_runtsk());
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	void *p = xxmalloc(nbytes);
	assert(p);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_mallocator_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
	return p;
}

//void _free_r(void *reent, void *aptr) {
void free(void *aptr) {
#if defined(MALLOC_PROFILE)
	ID tid = TSKID(get_my_p_runtsk());
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	xxfree(aptr);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_mallocator_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
}

//void *_calloc_r(void *reent, size_t n, size_t s) {
void *calloc(size_t n, size_t s) {
#if defined(MALLOC_PROFILE)
	ID tid = TSKID(get_my_p_runtsk());
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	void *retval = xxmalloc(n * s);
	if (retval) {
		memset(retval, 0, n * s);
	}
	assert(retval);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_mallocator_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
	return retval;
}

//void *_realloc_r(void *reent, void *aptr, size_t nbytes) {
void *realloc(void *aptr, size_t nbytes) {
#if defined(MALLOC_PROFILE)
	ID tid = TSKID(get_my_p_runtsk());
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	void *p = xxrealloc(aptr, nbytes);
	assert(p);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_mallocator_cycles[INDEX_TSK(tid)] += now - cycle_counter;
#endif
	return p;
}

/**
 * _r versions are for internal newlib, may lead to performace
 */

void *_malloc_r(void *reent, size_t nbytes) {
	return malloc(nbytes);
}

void _free_r(void *reent, void *aptr) {
//void free(void *aptr) {
	free(aptr);
}

void *_calloc_r(void *reent, size_t n, size_t s) {
//void *calloc(size_t n, size_t s) {
	return calloc(n, s);
}

void *_realloc_r(void *reent, void *aptr, size_t nbytes) {
//void *realloc(void *aptr, size_t nbytes) {
	return realloc(aptr, nbytes);
}


void mallocator_terminate(intptr_t unused) {
#if defined(MALLOC_PROFILE)
	uint64_t mallocator_cycles = 0;
	uint64_t exec_cycles = 0;
	uint64_t spin_cycles = 0;
	uint64_t tls_cycles = 0;
	uint64_t getreent_cycles = 0;
	extern uint64_t per_task_barrier_wait_cycles[TNUM_TSKID];
	uint64_t barrier_wait_cycles = 0;
	for (int i = 0; i < TNUM_TSKID; i++) {
		mallocator_cycles += per_task_mallocator_cycles[i];
		exec_cycles += per_task_exec_cycles[i];
		spin_cycles += per_task_spin_cycles[i];
		tls_cycles += per_task_tls_cycles[i];
		getreent_cycles += per_task_getreent_cycles[i];
		barrier_wait_cycles += per_task_barrier_wait_cycles[i];
	}
	syslog(LOG_NOTICE, "mallocator: %lu cycles, %d ms", mallocator_cycles, mallocator_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator exec: %lu cycles, %d ms", exec_cycles, exec_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator spin: %lu cycles, %d ms", spin_cycles, spin_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator tls: %lu cycles, %d ms", tls_cycles, tls_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator map: %lu cycles, %d ms", map_cycles, map_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "getreent: %lu cycles, %d ms", getreent_cycles, getreent_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "barrier wait: %lu cycles, %d ms", barrier_wait_cycles, barrier_wait_cycles / (cpu_hz() / 1000));
#endif
}

//void memalign() {}
//void malloc_trim() {}
#endif
