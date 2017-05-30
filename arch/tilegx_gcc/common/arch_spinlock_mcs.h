#pragma once

#define xchg_64(dest, newval) __insn_exch(dest, newval)

#if 0
static inline void sil_dly_nse(ulong_t dlytim) {
	for (volatile ulong_t i = 0; i < dlytim * 1; i++) {
		__insn_mfspr(SPR_PASS);
	}
}

static inline
void cpu_relax() {
//	delay_backoff(3);
//	sil_dly_nse(1);
}
#endif

#define cpu_relax() do{}while(0)

/**
 * TODO: Following K42 lock code is modified from locklessinc.com, which should be GPL v3.
 */

typedef struct mcs_lock_t mcs_lock_t;
struct mcs_lock_t
{
	mcs_lock_t * volatile next;
	volatile int spin;
};
typedef struct mcs_lock_t *mcs_lock;

static inline
void lock_mcs(mcs_lock *m, mcs_lock_t *me, bool_t preemption)
{
	mcs_lock_t *tail;

	me->next = NULL;
	me->spin = 0;

	barrier(); // -- ertl-liyixiao

	tail = (mcs_lock_t*)xchg_64((void*)m, (uint64_t)me);

	/* No one there? */
	if (!tail) {
//		barrier(); // -- ertl-liyixiao
		return;
	}

	/* Someone there, need to link in */
	tail->next = me;

	/* Make sure we do the above setting of next. */
//	barrier();

	/* Spin on my spin variable */
	while (!me->spin) {
		if (preemption) {
			x_unlock_cpu();
			x_lock_cpu();
		}
        cpu_relax();
    }

//	barrier(); // -- ertl-liyixiao

	return;
}

static inline
void unlock_mcs(mcs_lock *m, mcs_lock_t *me)
{
	barrier(); // ensure all operations are done before unlocking -- ertl-liyixiao

	/* No successor yet? */
	if (!me->next)
	{
		/* Try to atomically unlock */
		if ((void*)cmpxchg(m, (uint64_t)me, NULL) == me) return;

		/* Wait for successor to appear */
		while (!me->next) cpu_relax();
	}

//	barrier(); // -- ertl-liyixiao

	/* Unlock next one */
	me->next->spin = 1;

//	barrier(); // -- ertl-liyixiao
}

#if 0
static bool_t trylock_mcs(mcs_lock *m, mcs_lock_t *me)
{
	mcs_lock_t *tail;

	me->next = NULL;
	me->spin = 0;

	/* Try to lock */
	tail = (mcs_lock_t*)cmpxchg(m, NULL, (uint64_t)&me);

	/* No one was there - can quickly return */
	if (!tail) return false;

	return true;
}
#endif

/**
 * Interface of TOPPERS/FMP kernel
 */

#define PREFIX_SPIN_LOCK_NAME(x) tl_mcs##_##x
#define LOCK PREFIX_SPIN_LOCK_NAME(lock)
extern ID x_get_my_tid();
typedef mcs_lock_t mcs_node/* __attribute__((aligned(CHIP_L2_LINE_SIZE())))*/; //TODO: optimize false shared cache line

#define MCS_MAX_TASKS (512) /* FIXME: use TNUM_TSKID */
typedef struct {
    mcs_lock lock;
    mcs_node nodes[MCS_MAX_TASKS];
} LOCK /*__attribute__((aligned(CHIP_L2_LINE_SIZE())))*/;

static inline
void PREFIX_SPIN_LOCK_NAME(initialize_lock)(LOCK *p_lock) {
	barrier();
    p_lock->lock = NULL;
}

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock)(LOCK *p_lock) {
    ID tid = x_get_my_tid();
    lock_mcs(&(p_lock->lock), &(p_lock->nodes[tid-1/*INDEX_TSK(tid)*/]), true);
}

#if 0 // not supported yet
/* IMPORTANT: 'true' means 'failure' as in x_try_lock_spin() */
static inline
bool_t PREFIX_SPIN_LOCK_NAME(try_acquire_lock)(LOCK *p_lock) {
	return k42_trylock(p_lock);
}
#endif

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock_without_preemption)(LOCK *p_lock) {
    ID tid = x_get_my_tid();
	lock_mcs(&(p_lock->lock), &(p_lock->nodes[tid-1/*INDEX_TSK(tid)*/]), false);
}

#if 0 // not supported yet
// Reference: 'arch/arm_gcc/mpcore/chip_config_tool.h'
#define k42_ACQUIRE_NESTED_LOCK do { \
	int i = 0; \
	PCB     *p_pcb; \
	while(k42_trylock(p_lock)) { \
		p_pcb = get_my_p_pcb(); \
		if (p_pcb->p_firstlock == NULL) { \
			return true; \
		} \
		delay_backoff(i++); \
	} \
	return false; \
} while(0)
#endif

static inline
void PREFIX_SPIN_LOCK_NAME(release_lock)(LOCK *p_lock) {
    ID tid = x_get_my_tid();
	unlock_mcs(&(p_lock->lock), &(p_lock->nodes[tid-1/*INDEX_TSK(tid)*/]));
}

#undef LOCK
#undef PREFIX_SPIN_LOCK_NAME

