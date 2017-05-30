#pragma once

/**
 * K42 spin lock
 */

#define xchg_64(dest, newval) __insn_exch(dest, newval)

#if 0
static inline void sil_dly_nse(ulong_t dlytim) {
	for (volatile ulong_t i = 0; i < dlytim * 1; i++) {
		__insn_mfspr(SPR_PASS);
	}
}

static inline
void cpu_relax() {
	//sil_dly_nse(1);
}
#endif

#define cpu_relax() do{}while(0)

/**
 * TODO: Following K42 lock code is modified from locklessinc.com, which should be GPL v3.
 */

typedef struct k42lock k42lock;
struct k42lock
{
	k42lock * volatile next;
	k42lock * volatile tail;
};

static inline
void _k42_lock(k42lock *l, bool_t preemption)
{
	k42lock me;
	k42lock *pred, *succ;
	me.next = NULL;

	barrier();

	pred = (k42lock*)xchg_64((uint64_t*)&l->tail, (uint64_t)&me);
	if (pred)
	{
		me.tail = (k42lock *) 1;

		barrier();
		pred->next = &me;
		barrier();

		while (me.tail) {
			if (preemption) {
				x_unlock_cpu();
				x_lock_cpu();
			}
			cpu_relax();
		}
	}

	succ = me.next;

	if (!succ)
	{
		barrier();
		l->next = NULL;

		if (cmpxchg(&l->tail, (uint64_t)&me, (uint64_t)&l->next) != (uint64_t)&me)
		{
			while (!me.next) {
				if (preemption) {
					x_unlock_cpu();
					x_lock_cpu();
				}
				cpu_relax();
			}

			l->next = me.next;
		}
	}
	else
	{
		l->next = succ;
	}
}


static inline
void k42_unlock(k42lock *l)
{
	k42lock *succ = l->next;

	barrier();

	if (!succ)
	{
		if (cmpxchg(&l->tail, (uint64_t)&l->next, (uint64_t)NULL) == (uint64_t) &l->next) return;

		while (!l->next) cpu_relax();
		succ = l->next;
	}

	succ->tail = NULL;
}

static inline
bool_t k42_trylock(k42lock *l)
{
	barrier();
	if (!cmpxchg(&l->tail, (uint64_t)NULL, (uint64_t)&l->next)) return false;

	return true;
}

/**
 * Interface of TOPPERS/FMP kernel
 */

#define PREFIX_SPIN_LOCK_NAME(x) k42##_##x
#define LOCK PREFIX_SPIN_LOCK_NAME(lock)

typedef k42lock LOCK /*__attribute__((aligned(CHIP_L2_LINE_SIZE())))*/;

static inline
void PREFIX_SPIN_LOCK_NAME(initialize_lock)(LOCK *p_lock) {
	barrier();
	p_lock->next = NULL;
	p_lock->tail = NULL;
}

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock)(LOCK *p_lock) {
	_k42_lock(p_lock, true);
}

/* IMPORTANT: 'true' means 'failure' as in x_try_lock_spin() */
static inline
bool_t PREFIX_SPIN_LOCK_NAME(try_acquire_lock)(LOCK *p_lock) {
	return k42_trylock(p_lock);
}

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock_without_preemption)(LOCK *p_lock) {
	_k42_lock(p_lock, false);
}

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

static inline
void PREFIX_SPIN_LOCK_NAME(release_lock)(LOCK *p_lock) {
	k42_unlock(p_lock);
}

#undef LOCK
#undef PREFIX_SPIN_LOCK_NAME

