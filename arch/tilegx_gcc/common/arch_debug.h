/**
 * TILEGx Architecture Support Package for TOPPERS/FMP Kernel
 *
 * Copyright (C) 2015 by Yixiao Li (liyixiao@ertl.jp)
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

#pragma once

#include "tilegx.h"
#include "kernel/kernel_impl.h"
#include "hv/hypervisor.h"
#include "hv/pagesize.h"

void debug_loop();

/**
 * Interrupts for debug
 */

#define INTATR_DEBUG TA_ENAINT
#define INTPRI_DEBUG (-1)

void ill_handler(void);
void ill_trans_handler(void);
void unalign_data_handler(void);
void itlb_miss_handler(void);

#if defined(DEBUG_CPU_USAGE)
#define CALC_CPU_USAGE_PRD (1000)
void calculate_cpu_usage(intptr_t);
#endif

#if defined(DEBUG_PERF)
void test_perf_initialize(intptr_t);
void perf_initialize(const char *event1, const char *event2, const char *event3, const char *event4);
void perf_dump();
#endif

/**
 * Output svc error
 */
static inline
void
svc_perror(const char *file, int_t line, const char *expr, ER ercd) {
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

/**
 * Check svc error
 */
#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

enum profile_item {
	OVERHEAD_GETREENT = 0,
	TNUM_PROFILE_ITEMS,
};

//extern uint64_t per_task_profile_items[TNUM_TSKID][TNUM_PROFILE_ITEMS];
