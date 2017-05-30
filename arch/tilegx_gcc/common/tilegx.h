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

/**
 * Hardware resources of TILE-GX processor family
 */

#pragma once

/**
 * Definitions from Linux kernel
 * TODO: GPL v2 code is included!
 */
#include "linux-4.5/arch/tile/include/arch/spr_def.h"
#include "linux-4.5/arch/tile/include/uapi/arch/chip_tilegx.h"
#include "linux-4.5/arch/tile/include/uapi/arch/abi.h"

// TODO: replace with definitions directly
#include "spr_def.h"
//#include <arch/spr_def.h>

/**
 * Interrupts
 */

#define INTNO_MEM_ERROR    0
#define INTNO_SINGLE_STEP_3    1
#define INTNO_SINGLE_STEP_2    2
#define INTNO_SINGLE_STEP_1    3
#define INTNO_SINGLE_STEP_0    4
#define INTNO_IDN_COMPLETE    5
#define INTNO_UDN_COMPLETE    6
#define INTNO_ITLB_MISS    7
#define INTNO_ILL    8
#define INTNO_GPV    9
#define INTNO_IDN_ACCESS   10
#define INTNO_UDN_ACCESS   11
#define INTNO_SWINT_3   12
#define INTNO_SWINT_2   13
#define INTNO_SWINT_1   14
#define INTNO_SWINT_0   15
#define INTNO_ILL_TRANS   16
#define INTNO_UNALIGN_DATA   17
#define INTNO_DTLB_MISS   18
#define INTNO_DTLB_ACCESS   19
#define INTNO_IDN_FIREWALL   20
#define INTNO_UDN_FIREWALL   21
#define INTNO_TILE_TIMER   22
#define INTNO_AUX_TILE_TIMER   23
#define INTNO_IDN_TIMER   24
#define INTNO_UDN_TIMER   25
#define INTNO_IDN_AVAIL   26
#define INTNO_UDN_AVAIL   27
#define INTNO_IPI_3   28
#define INTNO_IPI_2   29
#define INTNO_IPI_1   30
#define INTNO_IPI_0   31
#define INTNO_PERF_COUNT   32
#define INTNO_AUX_PERF_COUNT   33
#define INTNO_INTCTRL_3   34
#define INTNO_INTCTRL_2   35
#define INTNO_INTCTRL_1   36
#define INTNO_INTCTRL_0   37
#define INTNO_BOOT_ACCESS   38
#define INTNO_WORLD_ACCESS   39
#define INTNO_I_ASID   40
#define INTNO_D_ASID   41
#define INTNO_DOUBLE_FAULT   42

#define TILEGX_TMIN_INTNO (INTNO_MEM_ERROR)
#define TILEGX_TMAX_INTNO (INTNO_DOUBLE_FAULT)
#define TILEGX_TNUM_INT   (TILEGX_TMAX_INTNO - TILEGX_TMIN_INTNO + 1)

