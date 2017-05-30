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
//#include "kernel/kernel_impl.h"

/**
 * System timer interrupt
 */

#define INTNO_TIMER  INTNO_TILE_TIMER
#define INHNO_TIMER  (INTNO_TIMER)
#define INTATR_TIMER TA_ENAINT
#define INTPRI_TIMER (-1)

#ifndef TOPPERS_MACRO_ONLY

extern void target_timer_initialize(intptr_t);
extern void arch_timer_handler(void);

static inline uint64_t cpu_hz() { // CPU frequency in Hz
	extern uint64_t _cpu_hz;
	return _cpu_hz;
}

/**
 * TODO: For debug, should not really be here
 */

extern void ill_handler(void);

#endif

#if 0 // Legacy code
#define TILE_1_0_CLS (2)
#define TILE_1_0_INTNO_TIMER  (INTNO_TIMER | 0x2 << (sizeof(INHNO) * 4))
#define TILE_1_0_INHNO_TIMER  TILE_1_0_INTNO_TIMER
#define TILE_1_0_INTATR_TIMER TA_ENAINT
#define TILE_1_0_INTPRI_TIMER (-1)

#define INHNO_TIMER_TEST  (INTNO_TILE_TIMER | 0x1 << (sizeof(INHNO) * 4))
#endif
