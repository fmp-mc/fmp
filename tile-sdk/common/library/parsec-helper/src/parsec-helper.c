/**
 * PARSEC helper for TOPPERS/FMP Kernel
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

#include <kernel.h>
#include <t_syslog.h>
#include "hv/hypervisor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: include header file(s) for these functions
extern void posix_initialize();
extern void my_ramfs_init();

void run_parsec_app(int argc, char **argv, char *nthreads_buf) {
	int cores;

	// Parse command line
	static char cmd[HV_COMMAND_LINE_LEN];
	int cmdlen = hv_get_command_line((HV_VirtAddr)cmd, sizeof(cmd));
#if defined(DEBUG_PERF)
    static char events[4][64];
#endif
	if (cmd[0] == '\0') {
		syslog(LOG_NOTICE, "cmdline is empty, use all cores");
		cores = TNUM_PRCID;
	} else {
		cores = atoi(cmd);
#if defined(DEBUG_PERF)
        sscanf(cmd, "%*d %s %s %s %s", events[0], events[1], events[2], events[3]);
#endif
	}
//cores = 32;
    // Run application
	posix_initialize();
	my_ramfs_init();
	sprintf(nthreads_buf, "%d", cores); // Fill nthreads buffer
    syslog(LOG_NOTICE, "Application start, THREADS=%d.", cores);
#if defined(DEBUG_PERF)
    perf_initialize(events[0], events[1], events[2], events[3]);
#endif
    uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
    extern int main (int argc, char **argv);
    main(argc, argv);
    cycle_counter = __insn_mfspr(SPR_CYCLE) - cycle_counter;
    syslog(LOG_NOTICE, "Application terminated, THREADS=%d, %lu cycles, %d ms.", cores, cycle_counter, cycle_counter / (hv_sysconf(HV_SYSCONF_CPU_SPEED) / 1000)/*1200000   */);

#if 0 // Dump output.txt
    {
        const char *filename = "output.txt";
        syslog(LOG_EMERG, "====== DUMP %s ======", filename);
        char buf[1024];
        FILE *file = fopen(filename, "r");
        while (fgets(buf, sizeof(buf), file) != NULL) {
            syslog(LOG_EMERG, "%s", buf);
        }
        fclose(file);
    }
#endif
#if defined(DEBUG_PERF)
    perf_dump();
#endif
	syslog(LOG_NOTICE, "Sample program ends.");

	// Flush output
	memset(cmd, ' ', sizeof(cmd));
	cmd[sizeof(cmd) - 1] = '\0';
	syslog(LOG_NOTICE, "%s", cmd);

	// Wait log task
	while (1) {
		T_SYSLOG_RLOG rlog;
		syslog_ref_log(&rlog);
		if (rlog.count == 0) break;
		dly_tsk(100);
	}

	ext_ker();
}
