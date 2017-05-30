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

#include <kernel.h>
#include <t_syslog.h>
#include "arch_timer.h"
#include "spr_def.h"
#include "hv/hypervisor.h"

uint64_t _cpu_hz;
static uint64_t tick_hz;

/**
 * TODO: This is a global initialization routine.
 * We assume all cores work at same frequency.
 * tick_hz is shared by all cores (!THIS REQUIRE SHARED MEMORY!)
 */
void target_timer_initialize(intptr_t unused) {
	_cpu_hz = hv_sysconf(HV_SYSCONF_CPU_SPEED); // 1000000000; //
	//syslog(LOG_NOTICE, "CPU Frequency: %lu Hz.", cpu_hz);
	assert(_cpu_hz == 1200000000 || _cpu_hz == 1000000000);
	tick_hz = _cpu_hz * TIC_NUME / TIC_DENO / 1000; // cycles per tick

	// Start timer
	__insn_mtspr(SPR_INTERRUPT_MASK_RESET_2, 1ULL << INTNO_TILE_TIMER/*INT_TILE_TIMER*/);
	__insn_mtspr(SPR_TILE_TIMER_CONTROL,  0x0000000000000001UL);
}

void arch_timer_handler(void) {
	__insn_mtspr(SPR_TILE_TIMER_CONTROL,  tick_hz);
	_kernel_signal_time();
}

#if 0 // Legacy code
void arch_timer_handler(void) {
#if 0
	__insn_mtspr(SPR_TILE_TIMER_CONTROL,  tick_hz);
	_kernel_signal_time();
#else  // debug (watchdog) mode
    	static int i = 10000;
    	//syslog(LOG_EMERG, "%s() called.", __FUNCTION__);
    	if (--i > 0) {
    		__insn_mtspr(SPR_TILE_TIMER_CONTROL,  tick_hz);
            _kernel_signal_time();
        } else
    		debug_loop();
#endif
}
#endif
