/*
 * newlib_allocator.c
 *
 *  Created on: Apr 5, 2016
 *      Author: liyixiao
 */

#include <errno.h>
#include <unistd.h>
//#include <sys/stat.h>
#include <kernel.h>
#include <t_syslog.h>
//#include "syssvc/serial.h"
#include "tlsf.h"
#include "arch_debug.h"

#undef errno
extern int errno;

#include "kernel_cfg.h"
#include "kernel/kernel_impl.h"
//#include "arch_sil.h"

#if 0
static LOCK malloc_lock;
#define TLSF_INIT_LOCK() x_initialize_lock(&malloc_lock)
#define TLSF_ACQUIRE_LOCK(lock) x_acquire_lock_without_preemption(&malloc_lock)
#define TLSF_RELEASE_LOCK(lock) x_release_lock(&malloc_lock)
#else
//#define TLSF_MLOCK_T ID
//#define TLSF_CREATE_LOCK(lock) (*lock = TLSF_SEM)
//#define TLSF_DESTROY_LOCK(lock) ini_sem(TLSF_SEM)
#define TLSF_INIT_LOCK() do{}while(0)
#define TLSF_ACQUIRE_LOCK(lock) SVC_PERROR(wai_sem(TLSF_SEM))
#define TLSF_RELEASE_LOCK(lock) SVC_PERROR(sig_sem(TLSF_SEM))
#endif

/**
 * Override the default allocator in newlib
 */

static unsigned char   *mem_pool;
static size_t  HEAP_SIZE;

//#define MALLOC_PROFILE
static uint64_t mallocator_cycles = 0;
static uint64_t exec_cycles = 0;
static uint64_t spin_cycles = 0;

#if !defined(USE_TLSF_ALLOCATOR) && 1 // Use Newlib default allocator

void* _sbrk_r (struct _reent* reent, ptrdiff_t incr )
{
	__malloc_lock(reent);
  static unsigned char *heap = NULL;
  unsigned char *prev_heap;
//  syslog(LOG_NOTICE, "%s(): incr %d bytes, %lu bytes left", __FUNCTION__, incr, HEAP_SIZE - (heap - mem_pool));

  if (heap == NULL) {
    heap = mem_pool;
  }
  prev_heap = heap;

  heap += incr;

  if (heap - mem_pool > HEAP_SIZE) {
      errno = ENOMEM;
      syslog(LOG_EMERG, "%s(): incr %d bytes, %lu bytes left", __FUNCTION__, incr, HEAP_SIZE - (heap - incr - mem_pool));
      assert(false);
      debug_loop();
      return (void *) -1;
  }
	__malloc_unlock(reent);

  return prev_heap;
}

void tlsf_initialize(intptr_t unused) {
	extern void  *uma_heap;
	extern size_t uma_heap_size;
	mem_pool = uma_heap;
	HEAP_SIZE = uma_heap_size;
	syslog(LOG_NOTICE, "%s(): mem_pool=%p, HEAP_SIZE=%lu", __FUNCTION__, mem_pool, HEAP_SIZE);
	TLSF_INIT_LOCK();
} // TODO: remove this dummy

// TODO: make sure this value is not used by other places
#define LOCAL_MALLOC_LOCK_COUNT _r->_new._unused._nmalloc[0]

void __malloc_lock ( struct _reent *_r ) {
	assert(_r != NULL);
	if (LOCAL_MALLOC_LOCK_COUNT == 0) { // lock not hold by me
		TLSF_ACQUIRE_LOCK(lock);
	}
	LOCAL_MALLOC_LOCK_COUNT++;
}

void __malloc_unlock ( struct _reent *_r ) {
	assert(_r != NULL);
	if ((--LOCAL_MALLOC_LOCK_COUNT) == 0) {
		TLSF_RELEASE_LOCK(lock);
	}
}

#if 0 // legacy
static int locks = 0;
static void *holder = NULL;

void __malloc_lock ( struct _reent *_r ) {
	__insn_mf();
	assert(_r != NULL);
	if (holder != _r) {
		TLSF_ACQUIRE_LOCK(lock);
		syslog(LOG_NOTICE, "%s(%p) called", __FUNCTION__, _r);
		holder = _r;
	}
	locks++;
}

void __malloc_unlock ( struct _reent *_r ) {
	__insn_mf();
	assert(_r != NULL);
	if ((--locks) == 0) {
		syslog(LOG_NOTICE, "%s(%p) called", __FUNCTION__, _r);
		holder = NULL;
		TLSF_RELEASE_LOCK(lock);
	}
}
#endif

#if defined(MALLOC_PROFILE)

void *malloc(size_t nbytes) {
	struct _reent *_r = __getreent();
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
	__malloc_lock(_r);
	spin_cycles += __insn_mfspr(SPR_CYCLE) - cycle_counter;

	void *p = _malloc_r(_r, nbytes);

	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	__malloc_unlock(_r);

	return p;
}

//void _free_r(void *reent, void *aptr) {
void free(void *aptr) {
	struct _reent *_r = __getreent();
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
	__malloc_lock(_r);
	spin_cycles += __insn_mfspr(SPR_CYCLE) - cycle_counter;

	_free_r(_r, aptr);

	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	__malloc_unlock(_r);
}

//void *_calloc_r(void *reent, size_t n, size_t s) {
void *calloc(size_t n, size_t s) {
	struct _reent *_r = __getreent();
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
	__malloc_lock(_r);
	spin_cycles += __insn_mfspr(SPR_CYCLE) - cycle_counter;

	void *retval = _calloc_r(_r, n * s);

	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	__malloc_unlock(_r);

	return retval;
}

//void *_realloc_r(void *reent, void *aptr, size_t nbytes) {
void *realloc(void *aptr, size_t nbytes) {
	struct _reent *_r = __getreent();
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
	__malloc_lock(_r);
	spin_cycles += __insn_mfspr(SPR_CYCLE) - cycle_counter;

	void *p = _realloc_r(_r, aptr, nbytes);

	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	__malloc_unlock(_r);

	return p;
}

#endif

#else

static tlsf_t tlsf;

void tlsf_initialize(intptr_t unused) {
	extern void  *uma_heap;
	extern size_t uma_heap_size;
	mem_pool = uma_heap;
	HEAP_SIZE = uma_heap_size;
	syslog(LOG_NOTICE, "%s(): mem_pool=%p, HEAP_SIZE=%lu", __FUNCTION__, mem_pool, HEAP_SIZE);
	//x_initialize_lock(&malloc_lock);

	tlsf = tlsf_create_with_pool(mem_pool, HEAP_SIZE % (1024 * 1024 * 1024 + 512 * 1024 * 1024));
}

void *_malloc_r(void *reent, size_t nbytes) {
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	TLSF_ACQUIRE_LOCK(lock);
#if defined(MALLOC_PROFILE)
	uint64_t exec_cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	//syslog(LOG_NOTICE, "%s() n=%lu", __FUNCTION__, nbytes);
	void *retval = tlsf_malloc(tlsf, nbytes);
	assert(!nbytes || retval);
	if (!retval) {
		//syslog(LOG_EMERG, "%s() failed, nbytes=%d, used=%lu", __FUNCTION__, nbytes, get_used_size(mem_pool));
	}
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	exec_cycles += now - exec_cycle_counter;
#endif
	TLSF_RELEASE_LOCK(lock);
	return retval;
//	return malloc_ex(nbytes, heap_for_domain(TDOM_SELF)); // TODO: thread safe
}

void _free_r(void *reent, void *aptr) {
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	TLSF_ACQUIRE_LOCK(lock);
#if defined(MALLOC_PROFILE)
	uint64_t exec_cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	tlsf_free(tlsf, aptr);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	exec_cycles += now - exec_cycle_counter;
#endif
	TLSF_RELEASE_LOCK(lock);
//	free_ex(aptr, heap_for_domain(TDOM_SELF));
}

void *_calloc_r(void *reent, size_t n, size_t s) {
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	TLSF_ACQUIRE_LOCK(lock);
#if defined(MALLOC_PROFILE)
	uint64_t exec_cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
//	syslog(LOG_NOTICE, "%s() n=%lu, s=%lu", __FUNCTION__, n, s);
	void *retval = tlsf_malloc(tlsf, n * s);
	assert(retval);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	exec_cycles += now - exec_cycle_counter;
#endif
	TLSF_RELEASE_LOCK(lock);
	return retval;
//	return calloc_ex(n, s, heap_for_domain(TDOM_SELF));
}

void *_realloc_r(void *reent, void *aptr, size_t nbytes) {
#if defined(MALLOC_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	TLSF_ACQUIRE_LOCK(lock);
#if defined(MALLOC_PROFILE)
	uint64_t exec_cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif
	syslog(LOG_NOTICE, "%s() n=%lu", __FUNCTION__, nbytes);
	void *retval = tlsf_realloc(tlsf, aptr, nbytes);
	assert(retval);
#if defined(MALLOC_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	mallocator_cycles += now - cycle_counter;
	exec_cycles += now - exec_cycle_counter;
#endif
	TLSF_RELEASE_LOCK(lock);
	return retval;
//	return realloc_ex(aptr, nbytes, heap_for_domain(TDOM_SELF));
}

#endif


void mallocator_terminate(intptr_t unused) {
#if defined(MALLOC_PROFILE)
	extern uint64_t per_task_barrier_wait_cycles[TNUM_TSKID];
	uint64_t barrier_wait_cycles = 0;
	for (int i = 0; i < TNUM_TSKID; i++) {
		barrier_wait_cycles += per_task_barrier_wait_cycles[i];
	}
	syslog(LOG_NOTICE, "mallocator: %lu cycles, %d ms", mallocator_cycles, mallocator_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator exec: %lu cycles, %d ms", exec_cycles, exec_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "mallocator spin: %lu cycles, %d ms", spin_cycles, spin_cycles / (cpu_hz() / 1000));
	syslog(LOG_NOTICE, "barrier wait: %lu cycles, %d ms", barrier_wait_cycles, barrier_wait_cycles / (cpu_hz() / 1000));
#endif
}

