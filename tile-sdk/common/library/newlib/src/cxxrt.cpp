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

/**
 * C++ ABI support
 * Reference: http://wiki.osdev.org/C++
 */

#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "arch_debug.h"
#include "kernel_cfg.h"

#include <stdlib.h>
#include <cxxabi.h>

/**
 * Support the routines specified in the C++ ABI for thread-safe initialization of local statics
 */

using __cxxabiv1::__guard;

extern "C" {

// TODO: we use malloc_lock as a quick fix
struct _reent;
extern void __malloc_lock(struct _reent *);
extern void __malloc_unlock(struct _reent *);

int __cxa_guard_acquire(__guard *g) {
	struct _reent *_r = __getreent();
	__malloc_lock(_r);
//syslog(LOG_NOTICE, "%s() called", __FUNCTION__);
	//SVC_PERROR(wai_sem(CXA_GUARD_SEM));
	if (!_GLIBCXX_GUARD_TEST(g)) { // not initialized yet, hold the lock
		return true;
	} else {                       // initialized is completed, release the lock (and do nothing)
		__malloc_unlock(_r);
		//SVC_PERROR(sig_sem(CXA_GUARD_SEM));
		return false;
	}
}

void __cxa_guard_release(__guard *g) {
//syslog(LOG_NOTICE, "%s() called", __FUNCTION__);
	struct _reent *_r = __getreent();
	_GLIBCXX_GUARD_SET(g); // initialization should be completed
	__malloc_unlock(_r);
	//SVC_PERROR(sig_sem(CXA_GUARD_SEM));
}

extern "C" void __cxa_pure_virtual() { assert(false); }

}


/**
 * The Operators 'new' and 'delete'
 */

void *operator new(size_t size) {
    return malloc(size);
}

void *operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void *p) {
    free(p);
}

void operator delete[](void *p) {
    free(p);
}

