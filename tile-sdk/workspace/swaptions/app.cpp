
/**
 * TOPPERS/FMP Kernel
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

extern "C" {
#include "app.h"
#include "parsec-helper.h"
#include <stdio.h>
#include <string.h>
}

void main_task(intptr_t exinf) {
	// Prepare arguments
	char nthreads[10];
    char *argv[] = { "swaptions", "-ns",
#if defined(TEST_RUNCONF)  // test.runconf
            "1", "-sm", "5",
#elif defined(SIMSMALL_RUNCONF) // simsmall.runconf
            "16", "-sm", "10000",
#elif defined(SIMMEDIUM_RUNCONF) // simmedium.runconf
            "32", "-sm", "20000",
#elif defined(SIMLARGE_RUNCONF) // simlarge.runconf
            "64", "-sm", "40000",
#elif defined(NATIVE_RUNCONF) || 1 // native.runconf
            "128", "-sm", "1000000",
#else
#error Must specify runconf!
#endif
    		"-nt", nthreads };

    int argc = sizeof(argv) / sizeof(argv[0]);

    // Run PARSEC application
    run_parsec_app(argc, argv, nthreads);
}
