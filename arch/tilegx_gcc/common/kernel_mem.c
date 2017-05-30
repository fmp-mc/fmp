/*
 * kernel_mem.c
 *
 *  Created on: Mar 9, 2016
 *      Author: liyixiao
 */

static HV_PTE first_l1_page_table[HV_L1_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN)));
/* [[[cog
import cog, pass0
HV_L0_ENTRIES = 1024 # TODO: import from C code
HV_L1_ENTRIES = 256
cog.outl('#define TMAX_POSIX_THREAD  (%d)' % pass0.max_posix_thread)
cog.outl('#define TMAX_PTHREAD_MUTEX (%d)' % pass0.max_pthread_mutex)
cog.outl('#define TMAX_PTHREAD_COND  (%d)' % pass0.max_pthread_cond)
]]] */
/* [[[end]]] */

/**
 *
 */
HV_PTE _kernel_page_table[HV_L0_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN))) = {
		hv_pte(((first_l1_page_table >> HV_LOG2_PAGE_TABLE_ALIGN) << HV_PTE_INDEX_PTFN) // hv_pte_set_pa()
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
					|(HV_PTE_MODE_CACHE_HASH_L3 << HV_PTE_INDEX_MODE) // hv_pte_set_mode()
					),
};
