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
#include "spr_def.h"
#include "hv/hypervisor.h"
#include "hv/pagesize.h"
#include "arch_ipi.h"

#define IPI_REGISTER_INDEX 2 // ipi_2 is used by default.

// Registers
#define IPI_EVENT_SPR SPR_IPI_EVENT_2
#define IPI_RESET_SPR SPR_IPI_EVENT_RESET_2

void arch_ipi_initialize(intptr_t unused) {
	/**
	 * Set Hypervisor virtual console IPI for master tile
	 */
	if (x_sense_mprc()) {
		HV_Coord coord;
		coord.x = 0;
		coord.y = 0;
		int ret = hv_console_set_ipi(IPI_REGISTER_INDEX, IPI_EVENT_HVC, coord);
		assert(ret == 0);

        // Print local cached section size for debug
#if 0 && OPTIMIZE_PAGE_TABLE > 0
        uint64_t max_bss_size = 0;
        extern void *_local_cached_prc_bss_start_table[TNUM_PRCID];
        extern void *_local_cached_prc_bss_end_table[TNUM_PRCID];
        for (uint_t i = 0; i < TNUM_PRCID; ++i) {
            uint64_t bss_size = _local_cached_prc_bss_end_table[i] - _local_cached_prc_bss_start_table[i];
            if (bss_size > max_bss_size) max_bss_size = bss_size;
        }
        syslog(LOG_NOTICE, "Max local cached section is %lu KiB", max_bss_size / 1024);
#endif
	}
#if 0
	HV_Topology topo = hv_inquire_topology();
	for (int x = 0; x < topo.width; ++x)
		for (int y = 0; y < topo.height; ++y) {
			HV_Coord coord;
			coord.x = x;
			coord.y = y;
			int ret = hv_console_set_ipi(IPI_REGISTER_INDEX, IPI_EVENT_HVC, coord);
			assert(ret == 0);
		}
#endif

	// Reset IPI mask
#if 0
	if (x_sense_mprc()) {
		syslog(LOG_EMERG, "SPR_INTERRUPT_MASK_2: %p", __insn_mfspr(SPR_INTERRUPT_MASK_2));
		syslog(LOG_EMERG, "SPR_IPI_EVENT_2: %p", __insn_mfspr(SPR_IPI_EVENT_2));
		syslog(LOG_EMERG, "SPR_IPI_MASK_2: %p", __insn_mfspr(SPR_IPI_MASK_2));
	}
#endif
	__insn_mtspr(SPR_IPI_MASK_2,  0x0000000000000000UL);
#if 0
		syslog(LOG_NOTICE, "prcid %d SPR_INTERRUPT_MASK_2: %p", x_prc_index() + 1, __insn_mfspr(SPR_INTERRUPT_MASK_2));
		syslog(LOG_NOTICE, "prcid %d SPR_IPI_EVENT_2: %p",  x_prc_index() + 1, __insn_mfspr(SPR_IPI_EVENT_2));
		syslog(LOG_NOTICE, "prcid %d SPR_IPI_MASK_2: %p",  x_prc_index() + 1, __insn_mfspr(SPR_IPI_MASK_2));
#endif
}

// TODO: This is shared memory.
static volatile uint64_t *ipi_event_set_spr[TILEGX_CLIENT_WD][TILEGX_CLIENT_HT];

void* arch_ipi_gen_l1_page_table(int l0index) {
	static HV_PTE l1_page_table[HV_L1_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN))); // _TILESTATE, #define _TILESTATE   __attribute__((section(".tilestate")))

	static HV_PTE l2_page_table[HV_L2_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN))); // _TILESTATE, #define _TILESTATE   __attribute__((section(".tilestate")))

	// Create one L0 entry describing a jumbo page (4GB)

	HV_PTE l0_pte = hv_pte(0
			|HV_PTE_PRESENT
//			|HV_PTE_PAGE
			|HV_PTE_GLOBAL
			//|HV_PTE_USER
//			|HV_PTE_ACCESSED // TODO: check this
//			|HV_PTE_DIRTY
			//|HV_PTE_CLIENT0
			//|HV_PTE_CLIENT1
			//|HV_PTE_CLIENT2
			//|HV_PTE_NC
			//|HV_PTE_NO_ALLOC_L1
			//|HV_PTE_NO_ALLOC_L2
			//|HV_PTE_CACHED_PRIORITY // TODO: check this
			|HV_PTE_READABLE
			|HV_PTE_WRITABLE
			|HV_PTE_EXECUTABLE
			);
	l0_pte = hv_pte_set_mode(l0_pte,
//			HV_PTE_MODE_UNCACHED
//			HV_PTE_MODE_CACHE_NO_L3            // TODO: MUST SET TO THIS VALUE -- ertl-liyixiao
			//HV_PTE_MODE_CACHE_TILE_L3
			HV_PTE_MODE_CACHE_HASH_L3
//			HV_PTE_MODE_MMIO
			);

	l0_pte = hv_pte_set_pa(l0_pte, l2_page_table);

	l1_page_table[0] = l0_pte; // TODO: rename 'l0_pte' to 'l1_pte'

    for (int x = 0; x < TILEGX_CLIENT_WD; ++x)
        for (int y = 0; y < TILEGX_CLIENT_HT; ++y) {
            HV_Coord tile;
            tile.x = x;
            tile.y = y;
            HV_PTE l2_pte;
            int ret = hv_get_ipi_pte(tile, IPI_REGISTER_INDEX /* TODO: Is this shoul be PL (Protect Level) ? */, &l2_pte);

 //           int ret = hv_get_ipi_pte(tile, IPI_REGISTER_INDEX /* TODO: Is this shoul be PL (Protect Level) ? */, &l1_page_table[x * TILEGX_CLIENT_HT + y]);
            l2_pte = hv_pte_set_present(l2_pte);
            l2_pte = hv_pte_set_page(l2_pte);
            l2_pte = hv_pte_set_readable(l2_pte);
            l2_pte = hv_pte_set_writable(l2_pte);
            l2_page_table[x * TILEGX_CLIENT_HT + y] = l2_pte;
            if (ret != 0) syslog(LOG_EMERG, "ERROR: get_ipi_pte ret: %d", ret);
            ipi_event_set_spr[x][y] = HV_L1_SPAN * l0index + HV_PAGE_SIZE_SMALL * (x * TILEGX_CLIENT_HT + y); // TODO: this assumes L1INDEX == 0.
            __insn_flush(&ipi_event_set_spr[x][y]); // TODO: IMPORTANT!
            syslog(LOG_EMERG, "ipi_event_set_spr[%d][%d]: 0x%p!", x, y, ipi_event_set_spr[x][y]);
        }


    for (int i = 0; i < HV_L2_ENTRIES; i++) __insn_flush(&l2_page_table[i]);

    return l1_page_table;
}

void arch_ipi_handler() {
	// syslog(LOG_EMERG, "%s()!", __FUNCTION__);
	int32_t event = __insn_mfspr(IPI_EVENT_SPR);

	if (event & (0x1 << IPI_EVENT_HVC)) {
		__insn_mtspr(IPI_RESET_SPR, 0x1 << IPI_EVENT_HVC);
		arch_hvc_ipi_handler();
	}

    if (event & (0x1 << IPI_EVENT_DISREQ)) {
#if 0
    	syslog(LOG_NOTICE, "%s() %d recv IPI_EVENT_DISREQ!", __FUNCTION__, x_prc_index());
#endif
        _kernel_ipi_handler();
    }

	assert(__insn_mfspr(IPI_EVENT_SPR) == 0);
}


void target_ipi_raise(uint_t prcid) {
	// debug_loop();
	prcid = prcid - 1;

#if 0 // This (INCLUDE trace_3) seems work, but we don't know why
	trace_3(LOG_TYPE_COMMENT, "target_ipi_raise %d -> %d", x_prc_index() + 1, prcid + 1);
#if 0
	syslog(LOG_NOTICE, "%s() %d->%d!", __FUNCTION__, x_prc_index(), prcid);
#endif

    unsigned long *ipi_mmio = ipi_event_set_spr[prcid % TILEGX_CLIENT_WD][prcid / TILEGX_CLIENT_WD];

	//syslog(LOG_EMERG, "%s() prcid: %d ipi_mmio[0][1]: 0x%p 0x%p!", __FUNCTION__, prcid, ipi_event_set_spr[0][0], ipi_event_set_spr[1][0]);

        //*ipi_event_set_spr[prcid % TILEGX_CLIENT_WD][prcid / TILEGX_CLIENT_HT] |= 0x1 << IPI_EVENT_DISREQ;

	unsigned long *addr =
		&((unsigned long *)ipi_mmio)[IPI_EVENT_DISREQ];
	asm volatile("st %0, zero" :: "r" (addr));
#else
	__insn_mf();
	ipi_event_set_spr[prcid % TILEGX_CLIENT_WD][prcid / TILEGX_CLIENT_WD][IPI_EVENT_DISREQ] = 0;
	//trace_3(LOG_TYPE_COMMENT, "target_ipi_raise %d -> %d", x_prc_index() + 1, prcid + 1);
	//((volatile unsigned long *)(ipi_event_set_spr[prcid % TILEGX_CLIENT_WD][prcid / TILEGX_CLIENT_WD]))[IPI_EVENT_DISREQ] = 0;
#endif
}

void target_ipi_clear(void) {
	__insn_mtspr(IPI_RESET_SPR, 0x1 << IPI_EVENT_DISREQ);
}

#if 0 // Legacy code
void
_kernel_barrier_sync(uint_t phase) {
	// TODO: we do not sync for now
	syslog(LOG_EMERG, "%s() phase %d skipped.", __FUNCTION__, phase);
}
#endif
