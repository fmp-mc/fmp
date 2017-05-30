#pragma once

/**
 * Interface of TOPPERS/FMP kernel
 */


typedef uint32_t LOCK /*__attribute__((aligned(CHIP_L2_LINE_SIZE())))*/;

static inline
void x_initialize_lock(LOCK *p_lock) {
	__insn_mf();
	*p_lock = 0;
}

static inline
void x_acquire_lock(LOCK *p_lock) {
#if defined(BACKOFF_SPIN_LOCK)
	int iterations = 0;
#endif
	__insn_mf(); // TODO: check this
	while(__insn_exch4(p_lock, 1) != 0) {
		x_unlock_cpu();
#if defined(BACKOFF_SPIN_LOCK)
		delay_backoff(iterations++);
#endif
		x_lock_cpu();
	}
}

/* IMPORTANT: 'true' means 'failure' as in x_try_lock_spin() */
static inline
bool_t x_try_acquire_lock(LOCK *p_lock) {
	__insn_mf(); // TODO: check this
	return(__insn_exch4(p_lock, 1) != 0);
}

static inline
void x_acquire_lock_without_preemption(LOCK *p_lock) {
#if defined(BACKOFF_SPIN_LOCK)
	int iterations = 0;
#endif
	__insn_mf(); // TODO: check this
	while(__insn_exch4(p_lock, 1) != 0)
#if defined(BACKOFF_SPIN_LOCK)
		delay_backoff(iterations++)
#endif
	;
}

#if TTYPE_KLOCK == F_KLOCK

#if defined(BACKOFF_SPIN_LOCK)

// Reference: 'arch/arm_gcc/mpcore/chip_config_tool.h'
#define X_ACQUIRE_NESTED_LOCK do { \
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

#else

// Reference: 'arch/arm_gcc/mpcore/chip_config_tool.h'
#define X_ACQUIRE_NESTED_LOCK do { \
		PCB     *p_pcb; \
		__insn_mf(); /* TODO: check this */ \
		while(__insn_exch4(p_lock, 1) != 0) { \
			p_pcb = get_my_p_pcb(); \
			if (p_pcb->p_firstlock == NULL) { \
				return true; \
			} \
		} \
		return false; \
} while(0)

#endif

#endif

static inline
void x_release_lock(LOCK *p_lock) {
	__insn_mf();
	*p_lock = 0;
}
