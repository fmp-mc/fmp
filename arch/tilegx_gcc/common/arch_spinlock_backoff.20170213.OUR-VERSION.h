#pragma once

/**
 * Test-and-set spin lock with backoff
 */

#define PREFIX_SPIN_LOCK_NAME(x) backoff##_##x
#define LOCK PREFIX_SPIN_LOCK_NAME(lock)

typedef uint32_t LOCK /*__attribute__((aligned(CHIP_L2_LINE_SIZE())))*/;

static inline
void PREFIX_SPIN_LOCK_NAME(initialize_lock)(LOCK *p_lock) {
	__insn_mf();
	*p_lock = 0;
}

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock)(LOCK *p_lock) {
	__insn_mf();
	int iterations = 0;
	while(__insn_exch4(p_lock, 1) != 0) {
			x_unlock_cpu();
			delay_backoff(iterations++);
			x_lock_cpu();
	}
}

/* IMPORTANT: 'true' means 'failure' as in x_try_lock_spin() */
static inline
bool_t PREFIX_SPIN_LOCK_NAME(try_acquire_lock)(LOCK *p_lock) {
	__insn_mf();
	return(__insn_exch4(p_lock, 1) != 0);
}

static inline
void PREFIX_SPIN_LOCK_NAME(acquire_lock_without_preemption)(LOCK *p_lock) {
	__insn_mf();
	int iterations = 0;
	while(__insn_exch4(p_lock, 1) != 0) delay_backoff(iterations++);
}

// Reference: 'arch/arm_gcc/mpcore/chip_config_tool.h'
#define backoff_ACQUIRE_NESTED_LOCK do { \
		int iterations = 0; \
		PCB     *p_pcb; \
		__insn_mf(); /* TODO: check this */ \
		while(__insn_exch4(p_lock, 1) != 0) { \
			p_pcb = get_my_p_pcb(); \
			if (p_pcb->p_firstlock == NULL) { \
				return true; \
			} \
			delay_backoff(iterations++); \
		} \
		return false; \
} while(0)

static inline
void PREFIX_SPIN_LOCK_NAME(release_lock)(LOCK *p_lock) {
	__insn_mf();
	*p_lock = 0;
}

#undef LOCK
#undef PREFIX_SPIN_LOCK_NAME
