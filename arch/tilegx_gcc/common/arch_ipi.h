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

#define IPI_EVENT_DISREQ (0)
#define IPI_EVENT_HVC    (1)

#define INTNO_ARCH_IPI  INTNO_IPI_2
#define INHNO_ARCH_IPI  (INTNO_ARCH_IPI)
#define INTPRI_ARCH_IPI (-1)
#define INTATR_ARCH_IPI TA_ENAINT

// TODO: for debug only, should be generated!

#define TILE_0_0_CLS (1)
#define TILE_0_0_INTNO_IPI_2  INTNO_IPI_2
#define TILE_0_0_INHNO_IPI_2  (TILE_0_0_INTNO_IPI_2 | 0x1 << (sizeof(INHNO) * 4))
#define TILE_1_0_INHNO_IPI_2  (TILE_0_0_INTNO_IPI_2 | 0x2 << (sizeof(INHNO) * 4))
#define TILE_0_0_INTATR_IPI_2 TA_ENAINT
#define TILE_0_0_INTPRI_IPI_2 (-1)

void arch_ipi_initialize(intptr_t);
void arch_ipi_handler();

void* arch_ipi_gen_l1_page_table(int l0index);

//#define OMIT_BARRIER_SYNC

