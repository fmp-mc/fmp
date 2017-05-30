/**
 * Newlib support for TOPPERS/FMP Kernel
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

#include <stdio.h>
#include <stdlib.h>
#include <reent.h>
#include <unistd.h>

#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include "arch_pcb.h"
#include "arch_debug.h"
#include "kernel_cfg.h"

//#define NEWLIB_PROFILE
uint64_t per_task_getreent_cycles[TNUM_TSKID];

struct _reent *__getreent() {
	// TODO: optimize overhead by update impure?
#if defined(NEWLIB_PROFILE)
	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
#endif

	TCB *runtsk = get_my_p_runtsk();

#if OPTIMIZE_PAGE_TABLE >= 1
	struct _reent *reent = &(runtsk->tskctxb.reent);
#else
	static struct _reent reent_tab[TNUM_TSKID];
	struct _reent *reent = &reent_tab[INDEX_TSK(TSKID(runtsk))];
#endif

	// Initialize stdio
	if (!reent->__sdidinit) {
		__sinit(reent);
		assert(stderr == reent->_stderr);
	}

#if defined(NEWLIB_PROFILE)
	uint64_t now = __insn_mfspr(SPR_CYCLE);
	per_task_getreent_cycles[INDEX_TSK(TSKID(runtsk))] += now - cycle_counter;
#endif

	return reent;
}

void _exit(int stat) {
	syslog(LOG_EMERG, "Unsupported syscall %s() called!", __FUNCTION__);
	ext_ker();
}

int _getpid_r(struct _reent *reent) {
	syslog(LOG_EMERG, "Unsupported syscall %s() called!", __FUNCTION__);
	ext_ker();
	return -1;
}

int _kill_r(struct _reent *reent, int pid, int sig) {
	syslog(LOG_EMERG, "Unsupported syscall %s() called!", __FUNCTION__);
	ext_ker();
	return -1;
}

/**
 * rand48() functions without thread-safety
 */

static struct _reent reent_rand48;

void srand48(long seed) {
	_srand48_r(&reent_rand48, seed); // reent_tab is safe, since it won't call malloc_lock/unlock for !REENT_SMALL
}

long lrand48() {
	return _lrand48_r(&reent_rand48);
}

// TODO: dummy code for compilation
#if defined(USE_GLIBC_LIBM)
#undef stderr
int stderr;
int __errno_location() { assert(false); }

// TODO: a deperated symbol for Newlib when using libm(glibc)
intptr_t __infinity; // should never be used
size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                     FILE *stream) { return 0; }
#endif
