#include <kernel.h>
#include "kernel/kernel_impl.h"
#include "kernel/pcb.h"
#include "kernel/task.h"
#include "arch_config.h"
#include <t_syslog.h>
#include "hv/hypervisor.h"
#include "hv/pagesize.h"
#include "spr_def.h"
#include <arch/spr_def.h>
//#include "arch/interrupts_64.h"
#include "arch_debug.h"
#include "kernel_cfg.h"

#if 0
static char stack[4096 * 2];
void *boot_sp = stack + 4096;

void raise_int() {
#if 1
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
	//__insn_mtspr(SPR_IPI_EVENT_2, 0x1 << 1);
#endif
#endif
}
#endif

extern void *_end;

HV_PTE _kernel_page_table[HV_L0_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN))); // _TILESTATE, #define _TILESTATE   __attribute__((section(".tilestate")))

static void memory_set_home(uintptr_t p, size_t size, ID home) {
#define PRCID_TO_LOTAR(prcid) HV_XY_TO_LOTAR(((prcid) - 1) % TILEGX_CLIENT_WD, ((prcid) - 1) / TILEGX_CLIENT_WD)
    assert((p & (HV_PAGE_SIZE_LARGE - 1)) == 0);
    assert(size % HV_PAGE_SIZE_LARGE == 0);

    assert((p & (HV_PAGE_SIZE_SMALL - 1)) == 0);
    assert(p + size < 0x100000000UL); // area is in first 4 GB

    // L0, jumbo page
    assert(size < 0x100000000UL); // area is in a single jumbo page
    HV_PTE l0_entry = _kernel_page_table[0]; // TODO: _ker_p_t->root
    assert(!hv_pte_get_page(l0_entry));
    uintptr_t l1_start = 0x0;
    HV_PTE *l1_table = hv_pte_get_pa(l0_entry);

    // L1, large page
    if (((p & (HV_PAGE_SIZE_LARGE - 1)) == 0) && (size % HV_PAGE_SIZE_LARGE == 0)) { // use large page when possible
        for (uintptr_t pa = p; pa < p + size; pa += HV_PAGE_SIZE_LARGE) {
            HV_PTE *l1_entry_ptr = &l1_table[(pa - l1_start) / HV_PAGE_SIZE_LARGE];

        	HV_PTE l1_pte = hv_pte(0
        			|HV_PTE_PRESENT
        			|HV_PTE_PAGE
        			|HV_PTE_GLOBAL
        			//|HV_PTE_NC
        			//|HV_PTE_NO_ALLOC_L1
        			//|HV_PTE_NO_ALLOC_L2
        			|HV_PTE_CACHED_PRIORITY // TODO: check this
        			|HV_PTE_READABLE
        			|HV_PTE_WRITABLE
        			|HV_PTE_EXECUTABLE
        			);
        	l1_pte = hv_pte_set_mode(l1_pte, HV_PTE_MODE_CACHE_HASH_L3);
        	l1_pte = hv_pte_set_pa(l1_pte, pa);

            // set home
            *l1_entry_ptr = hv_pte_set_lotar(hv_pte_set_mode(l1_pte, HV_PTE_MODE_CACHE_TILE_L3), PRCID_TO_LOTAR(home));
            __insn_flush(l1_entry_ptr); // TODO: this flush is very IMPORTANT, find a way to flush all cache
        }
        return;
    }

    // L2, small page
    for (uintptr_t pa = p; pa < p + size; pa += HV_PAGE_SIZE_SMALL) {
        HV_PTE *l1_entry_ptr = &l1_table[(pa - l1_start) / HV_PAGE_SIZE_LARGE];

        // split the large page
        if (hv_pte_get_page(*l1_entry_ptr)) {
        	static HV_PTE l2_page_tables[100][HV_L2_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN)));
        	static uint_t l2_page_tables_left = 100;
        	if (l2_page_tables_left == 0) {
        		assert(false);
        		debug_loop();
        	}
        	HV_PTE *l2_page_table = l2_page_tables[--l2_page_tables_left];
        	for (int i = 0; i < HV_L2_ENTRIES; i++) {
        		HV_PTE l2_pte = hv_pte(0
        				|HV_PTE_PRESENT
        				|HV_PTE_PAGE
        				|HV_PTE_GLOBAL
        				//|HV_PTE_NC
        				//|HV_PTE_NO_ALLOC_L1
        				//|HV_PTE_NO_ALLOC_L2
        				|HV_PTE_CACHED_PRIORITY // TODO: check this
        				|HV_PTE_READABLE
        				|HV_PTE_WRITABLE
        				|HV_PTE_EXECUTABLE
        				);
        		l2_pte = hv_pte_set_mode(l2_pte, HV_PTE_MODE_CACHE_HASH_L3);
        		l2_pte = hv_pte_set_pa(l2_pte, (pa & ~(HV_PAGE_SIZE_LARGE - 1ULL)) + HV_PAGE_SIZE_SMALL * i);
        		l2_page_table[i] = l2_pte;
        	}
        	for (int i = 0; i < HV_L2_ENTRIES; i++) __insn_flush(&l2_page_table[i]); // TODO: this flush is very IMPORTANT, find a way to flush all cache
        	*l1_entry_ptr = hv_pte_set_pa(hv_pte_clear_page(*l1_entry_ptr), l2_page_table);
        }

        // set home
        HV_PTE *l2_entry_ptr = ((HV_PTE*)hv_pte_get_pa(*l1_entry_ptr)) + (((pa - l1_start) / HV_PAGE_SIZE_SMALL) % HV_L2_ENTRIES);
        assert(hv_pte_get_mode(*l2_entry_ptr) == HV_PTE_MODE_CACHE_HASH_L3);
        *l2_entry_ptr = hv_pte_set_lotar(hv_pte_set_mode(*l2_entry_ptr, HV_PTE_MODE_CACHE_TILE_L3), PRCID_TO_LOTAR(home));
        __insn_flush(l2_entry_ptr); // TODO: this flush is very IMPORTANT, find a way to flush all cache
    }
}

static void optimize_page_table() {
    HV_PTE *root = _kernel_page_table;

#if OPTIMIZE_PAGE_TABLE == 1
    // Home task stack locally
    for (uint_t i = 0; i < TNUM_TSKID; ++i) {
    	TINIB *tinib = _kernel_tinib_table + i;
    	memory_set_home(tinib->stk, tinib->stksz, tinib->iaffinity);
    }

    for (uint_t i = 0; i < TNUM_PRCID; ++i) {
    	// Home PCB locally
    	memory_set_home(_kernel_p_pcb_table[i], sizeof(PCB), i + 1);
    	// Home interrupt stack locally
		memory_set_home(_kernel_istk_table[i], _kernel_istksz_table[i], i + 1);
    }
#elif OPTIMIZE_PAGE_TABLE == 2
    extern void *_local_cached_prc_bss_start_table[TNUM_PRCID];
    extern void *_local_cached_prc_bss_end_table[TNUM_PRCID];
    for (uint_t i = 0; i < TNUM_PRCID; ++i) {
    	memory_set_home(_local_cached_prc_bss_start_table[i], _local_cached_prc_bss_end_table[i] - _local_cached_prc_bss_start_table[i], i + 1);
    }
#endif
}

#define USE_UMA_AS_HEAP
#if defined(USE_UMA_AS_HEAP)
void  *uma_heap;
size_t uma_heap_size;
#endif

void init_mmu() {
	// Dump information
	if (x_sense_mprc()) {
		HV_PhysAddrRange range;
		for (int i = 0; (range = hv_inquire_physical(i)).size != 0; i++) {
			syslog(LOG_EMERG, "CPA range %d: start 0x%p, size %d KB, mc %d", i, range.start, range.size / 1024, range.controller);
		}
	}

	/**
	 * Generate L1 page table for first 4 GB.
	 */

	static HV_PTE l1_page_table[HV_L1_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN))); // _TILESTATE, #define _TILESTATE   __attribute__((section(".tilestate")))

	for (int i = 0; i < HV_L1_ENTRIES; ++i) {
		HV_PTE l1_pte = hv_pte(0
					|HV_PTE_PRESENT
					|HV_PTE_PAGE
					|HV_PTE_GLOBAL
					//|HV_PTE_USER
//					|HV_PTE_ACCESSED // TODO: check this
//					|HV_PTE_DIRTY
					//|HV_PTE_CLIENT0
					//|HV_PTE_CLIENT1
					//|HV_PTE_CLIENT2
					//|HV_PTE_NC
					//|HV_PTE_NO_ALLOC_L1
					//|HV_PTE_NO_ALLOC_L2
					|HV_PTE_CACHED_PRIORITY // TODO: check this
					|HV_PTE_READABLE
					|HV_PTE_WRITABLE
					|HV_PTE_EXECUTABLE
					);
		l1_pte = hv_pte_set_mode(l1_pte,
//					HV_PTE_MODE_UNCACHED
					//HV_PTE_MODE_CACHE_NO_L3
					//HV_PTE_MODE_CACHE_TILE_L3
					HV_PTE_MODE_CACHE_HASH_L3
					//HV_PTE_MODE_MMIO
					);
		l1_pte = hv_pte_set_pa(l1_pte, HV_PAGE_SIZE_LARGE * i);
		l1_page_table[i] = l1_pte;
	}

	/**
	 * Create L0 page table whose first entry points to our L1 table.
	 */





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
			|HV_PTE_CACHED_PRIORITY // TODO: check this
			|HV_PTE_READABLE
			|HV_PTE_WRITABLE
			|HV_PTE_EXECUTABLE
			);
	l0_pte = hv_pte_set_mode(l0_pte,
//			HV_PTE_MODE_UNCACHED
//			HV_PTE_MODE_CACHE_NO_L3            // TODO: MUST SET TO THIS VALUE -- ertl-liyixiao
			//HV_PTE_MODE_CACHE_TILE_L3
			HV_PTE_MODE_CACHE_HASH_L3
			//HV_PTE_MODE_MMIO
			);

	l0_pte = hv_pte_set_pa(l0_pte, l1_page_table);

	_kernel_page_table[0] = l0_pte;

    // Set MMIO for IPIs
	HV_PTE *ipi_page_table = arch_ipi_gen_l1_page_table(1);
    l0_pte = hv_pte_set_pa(l0_pte, ipi_page_table);
    _kernel_page_table[1] = l0_pte;


    HV_PhysAddrRange uma_range;
    if ((uma_range = hv_inquire_physical(1)).size != 0) {
    	assert((uma_range.start & 0xFFFFFFFF) == 0); // Check L1 page table aligned
#if defined(USE_UMA_AS_HEAP) // Use UMA as heap
    	HV_PTE l0_pte = hv_pte(0
    			|HV_PTE_PRESENT
    			|HV_PTE_PAGE
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
    			|HV_PTE_CACHED_PRIORITY // TODO: check this
    			|HV_PTE_READABLE
    			|HV_PTE_WRITABLE
    			|HV_PTE_EXECUTABLE
    			);
    	l0_pte = hv_pte_set_mode(l0_pte,
    //			HV_PTE_MODE_UNCACHED
    //			HV_PTE_MODE_CACHE_NO_L3            // TODO: MUST SET TO THIS VALUE -- ertl-liyixiao
    			//HV_PTE_MODE_CACHE_TILE_L3
    			HV_PTE_MODE_CACHE_HASH_L3
    			//HV_PTE_MODE_MMIO
    			);

    	l0_pte = hv_pte_set_pa(l0_pte, uma_range.start);
    	_kernel_page_table[2] = l0_pte;
    	uma_heap = HV_DEFAULT_PAGE_SIZE_JUMBO * 2; // TODO: verify HV_DEFAULT_PAGE_SIZE_JUMBO by HV_DEFAULT_PAGE_SIZE_JUMBO
    	if (uma_range.size > HV_DEFAULT_PAGE_SIZE_JUMBO) uma_range.size = HV_DEFAULT_PAGE_SIZE_JUMBO; // TODO: this will limit the size to 4 GiB
    	uma_heap_size = uma_range.size;

    { // append free space after range1_end
    	static HV_PTE l1_page_table[HV_L1_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN)));
    	HV_PhysAddr start = TOPPERS_ROUND_SZ((HV_PhysAddr)&_end, HV_PAGE_SIZE_LARGE);

    	syslog(LOG_EMERG, "range1 start:%p", start);
#if 1
    	HV_PhysAddrRange range = hv_inquire_physical(0);
    	size_t size = range.size - (start - range.start);
    	if (size > HV_DEFAULT_PAGE_SIZE_JUMBO) size = HV_DEFAULT_PAGE_SIZE_JUMBO; // TODO: this will limit the size to 4 GiB
    	int pages = size / HV_PAGE_SIZE_LARGE;
    	for (int i = 0; i < pages; i++) {
    		HV_PTE l1_pte = hv_pte(0
    					|HV_PTE_PRESENT
    					|HV_PTE_PAGE
    					|HV_PTE_GLOBAL
    					//|HV_PTE_USER
    //					|HV_PTE_ACCESSED // TODO: check this
    //					|HV_PTE_DIRTY
    					//|HV_PTE_CLIENT0
    					//|HV_PTE_CLIENT1
    					//|HV_PTE_CLIENT2
    					//|HV_PTE_NC
    					//|HV_PTE_NO_ALLOC_L1
    					//|HV_PTE_NO_ALLOC_L2
    					|HV_PTE_CACHED_PRIORITY // TODO: check this
    					|HV_PTE_READABLE
    					|HV_PTE_WRITABLE
    					|HV_PTE_EXECUTABLE
    					);
    		l1_pte = hv_pte_set_mode(l1_pte,
    //					HV_PTE_MODE_UNCACHED
    					//HV_PTE_MODE_CACHE_NO_L3
    					//HV_PTE_MODE_CACHE_TILE_L3
    					HV_PTE_MODE_CACHE_HASH_L3
    					//HV_PTE_MODE_MMIO
    					);
    		l1_pte = hv_pte_set_pa(l1_pte, start + HV_PAGE_SIZE_LARGE * i);
    		l1_page_table[i] = l1_pte;
    	}
    	uma_heap_size += size;

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
    			|HV_PTE_CACHED_PRIORITY // TODO: check this
    			|HV_PTE_READABLE
    			|HV_PTE_WRITABLE
    			|HV_PTE_EXECUTABLE
    			);
    	l0_pte = hv_pte_set_mode(l0_pte,
    //			HV_PTE_MODE_UNCACHED
    //			HV_PTE_MODE_CACHE_NO_L3            // TODO: MUST SET TO THIS VALUE -- ertl-liyixiao
    			//HV_PTE_MODE_CACHE_TILE_L3
    			HV_PTE_MODE_CACHE_HASH_L3
    			//HV_PTE_MODE_MMIO
    			);

    	l0_pte = hv_pte_set_pa(l0_pte, l1_page_table);

    	_kernel_page_table[3] = l0_pte;
#endif
    }
#else // Install UMA (User-managed area)
    	int l0_index = uma_range.start >> 32;
    	assert(l0_index > 0);
    	HV_PTE *uma_page_table = uma_gen_l1_page_table(l0_index);
    	l0_pte = hv_pte_set_pa(l0_pte, uma_page_table);
    	_kernel_page_table[l0_index] = l0_pte;
    	for (int i = 0; i < HV_L1_ENTRIES; i++) __insn_flush(&uma_page_table[i]);
#endif
    } else {
    	syslog(LOG_EMERG, "FATAL: CPA range %d does not exist, UMA will not be installed.", 1);
    	debug_loop();
    }

#if OPTIMIZE_PAGE_TABLE
    optimize_page_table();
#endif

    // Flush cache
    for (int i = 0; i < HV_L0_ENTRIES; i++) __insn_flush(&_kernel_page_table[i]);
    for (int i = 0; i < HV_L1_ENTRIES; i++) __insn_flush(&l1_page_table[i]);
    for (int i = 0; i < HV_L1_ENTRIES; i++) __insn_flush(&ipi_page_table[i]);

#if 0
	  // Create one L0 entry which points to our L1 table.
	  HV_PTE l0_pte = hv_pte(0);
	  l0_pte = hv_pte_set_readable(l0_pte);
	  l0_pte = hv_pte_set_writable(l0_pte);
	  l0_pte = hv_pte_set_dirty(l0_pte);
	  l0_pte = hv_pte_set_global(l0_pte);
	  l0_pte = hv_pte_set_present(l0_pte);
	  l0_pte = hv_pte_set_accessed(l0_pte);
	  l0_pte = hv_pte_set_mode(l0_pte, HV_PTE_MODE_CACHE_NO_L3);

	  assert(HV_L0_INDEX(MEM_CODE_VA) == HV_L0_INDEX(MEM_DATA_VA));

	  l0_pte = hv_pte_set_ptfn(l0_pte, HV_CPA_TO_PTFN(l1_page_table));
	  write_pte(_kernel_page_table + HV_L0_INDEX(MEM_CODE_VA) * HV_PTE_SIZE,
	            local_access_pte, l0_pte);
#endif
}

#if 1 // code from arch/tile/include/asm/tlbflush.h

#define __tilegx__

#define __flush_icache() __flush_icache_range(0, CHIP_L1I_CACHE_SIZE())


/**
 * Invalidate the instruction cache for the given range of memory.
 *
 * @param addr The start of memory to be invalidated.
 * @param size The number of bytes to be invalidated.
 * @param page_size The system's page size, e.g. getpagesize() in userspace.
 * This value must be a power of two no larger than the page containing
 * the code to be invalidated. If the value is smaller than the actual page
 * size, this function will still work, but may run slower than necessary.
 */
static __inline void
invalidate_icache(const void* addr, unsigned long size,
                  unsigned long page_size)
{
  const unsigned long cache_way_size =
    CHIP_L1I_CACHE_SIZE() / CHIP_L1I_ASSOC();
  unsigned long max_useful_size;
  const char* start, *end;
  long num_passes;

  if (__builtin_expect(size == 0, 0))
    return;

#ifdef __tilegx__
  /* Limit the number of bytes visited to avoid redundant iterations. */
  max_useful_size = (page_size < cache_way_size) ? page_size : cache_way_size;

  /* No PA aliasing is possible, so one pass always suffices. */
  num_passes = 1;
#else
  /* Limit the number of bytes visited to avoid redundant iterations. */
  max_useful_size = cache_way_size;

  /*
   * Compute how many passes we need (we'll treat 0 as if it were 1).
   * This works because we know the page size is a power of two.
   */
  num_passes = cache_way_size >> __builtin_ctzl(page_size);
#endif

  if (__builtin_expect(size > max_useful_size, 0))
    size = max_useful_size;

  /* Locate the first and last bytes to be invalidated. */
  start = (const char *)((unsigned long)addr & -CHIP_L1I_LINE_SIZE());
  end = (const char*)addr + size - 1;

  __insn_mf();

  do
  {
    const char* p;

    for (p = start; p <= end; p += CHIP_L1I_LINE_SIZE())
      __insn_icoh(p);

    start += page_size;
    end += page_size;
  }
  while (--num_passes > 0);

  __insn_drain();
}





#define PAGE_SHIFT	HV_LOG2_DEFAULT_PAGE_SIZE_SMALL
#define HPAGE_SHIFT	HV_LOG2_DEFAULT_PAGE_SIZE_LARGE
#define PAGE_SIZE       (1UL << PAGE_SHIFT)
#define HPAGE_SIZE      (1UL << HPAGE_SHIFT)

static void __flush_icache_range(unsigned long start, unsigned long end) {
	invalidate_icache((const void *)start, end - start, PAGE_SIZE);
}

/* Flush range of user pages on this cpu. */
static inline void local_flush_tlb_pages(void*vma,
                     unsigned long addr,
                     unsigned long page_size,
                     unsigned long len)
{
    int rc = hv_flush_pages(addr, page_size, len);
    if (rc < 0) {
        syslog(LOG_EMERG, "hv_flush_pages(%#lx,%#lx,%#lx) failed: %d",
              addr, page_size, len, rc);
        debug_loop();
    }
    if (!vma)
        __flush_icache();
}

/*
 * Global pages have to be flushed a bit differently. Not a real
 * performance problem because this does not happen often.
 */
static inline void local_flush_tlb_all(void)
{
    int i;
    for (i = 0; ; ++i) {
        HV_VirtAddrRange r = hv_inquire_virtual(i);
        if (r.size == 0)
            break;
        local_flush_tlb_pages(NULL, r.start, PAGE_SIZE, r.size);
        local_flush_tlb_pages(NULL, r.start, HPAGE_SIZE, r.size);
    }
}

#endif

#if 1 // barrier code from arch/tile/asm/barrier.h

#define __sync()    __insn_mf()

#include <hv/syscall_public.h>
/*
 * Issue an uncacheable load to each memory controller, then
 * wait until those loads have completed.
 */
static inline void __mb_incoherent(void)
{
    long clobber_r10;
    asm volatile("swint2"
             : "=R10" (clobber_r10)
             : "R10" (HV_SYS_fence_incoherent)
             : "r0", "r1", "r2", "r3", "r4",
               "r5", "r6", "r7", "r8", "r9",
               "r11", "r12", "r13", "r14",
               "r15", "r16", "r17", "r18", "r19",
               "r20", "r21", "r22", "r23", "r24",
               "r25", "r26", "r27", "r28", "r29");
}

#define CHIP_HAS_TILE_WRITE_PENDING() 0 // from arch/tile/include/arch/chip_tilegx.h
/* Fence to guarantee visibility of stores to incoherent memory. */
static inline void
mb_incoherent(void)
{
    __insn_mf();

    {
#if CHIP_HAS_TILE_WRITE_PENDING()
        const unsigned long WRITE_TIMEOUT_CYCLES = 400;
        unsigned long start = get_cycles_low();
        do {
            if (__insn_mfspr(SPR_TILE_WRITE_PENDING) == 0)
                return;
        } while ((get_cycles_low() - start) < WRITE_TIMEOUT_CYCLES);
#endif /* CHIP_HAS_TILE_WRITE_PENDING() */
        (void) __mb_incoherent();
    }
}

#endif

void boot_pc() {
	/**
	 *
	 */
	//const char *str = "Hello World!\n";

#if 0
	register int tp asm ("tp");
	syslog(LOG_EMERG, "tp = %x", tp);
	syslog(LOG_EMERG, "prcindex: %d",  x_prc_index());
#endif

//	__insn_mtspr(SPR_DSTREAM_PF, 0); // disable data stream prefetcher

	/**
	 * Initialize MMU
	 */
	if (x_sense_mprc()) {
		init_mmu(); // Generate page tables

		{ // // Install page tables
			/** PTE describing how to read/write L1 page tables.
			 * Since they are per-tile, we can always read them through our cache.
			 * At some point we may wish to support something like threads, in
			 * which case we will need to promote all use of local_access_pte
			 * to use a LOTAR to some specific tile instead.
			 */
			HV_PTE local_access_pte  = {
			  HV_PTE_READABLE |
			  HV_PTE_WRITABLE |
			  HV_PTE_PRESENT |
			  (HV_PTE_MODE_CACHE_NO_L3 << HV_PTE_INDEX_MODE)
			};

			HV_ASID asid = hv_inquire_asid(0).start;

			hv_flush_remote(NULL, HV_FLUSH_ALL,
					-1,
					NULL, 0,
					0, NULL,
					NULL, 0);

			// Install the page table
			hv_install_context(_kernel_page_table, local_access_pte, asid, HV_CTX_DIRECTIO);
			hv_flush_all(false);
		}
		mb_incoherent();
		local_flush_tlb_all();
		hv_start_all_tiles();
	} else {
		//mb_incoherent();
		//local_flush_tlb_all();
		//hv_flush_all(false);
	}


	//pos_t my_pos = { .word = __insn_mfspr(SPR_TILE_COORD) };

#if 0
	if (x_sense_mprc()) {
		HV_Topology topo = hv_inquire_topology();
		syslog(LOG_EMERG, "topo w:%d d: %d", topo.width, topo.height);

	}
	/*if (x_sense_mprc())*/
#endif

// It seems this interrupt can't be masked
//	__insn_mtspr(SPR_INTERRUPT_MASK_SET_2, 1ULL << INT_ITLB_MISS); // Use HV to handle ITLB MISS

	// Flush whole memory before start kernel
		// TODO: do it more elegantly, AND SHOULD master core also INV instead of FLUSH ?
	//	for (int_t i = 0; i < 0x10000000 / 10; i++) { __insn_inv(i * 16);}//__insn_flush(i * 16);


    sta_ker();
    {int i;for (i = 0; i < 100000; ++i);}
 //   while (1);
    hv_power_off();
    //while(1) {
    //    hv_console_write(str, strlen(str));
    //}
}

unsigned long long interrupts_enabled_mask = 0x0;

#if 0 // legacy code, which works


/** Type for an interrupt routine. */
typedef void bme_interrupt_handler_t(int interrupt,
                                     void /*struct bme_saved_regs_full*/ *sr);


static bme_interrupt_handler_t* int_handler[NUM_INTERRUPTS];

void _bme_set_state(void* state);

void timer_int(int interrupt,
                                     void /*struct bme_saved_regs_full*/ *sr) {
	syslog(LOG_EMERG, "timer_interrupt\r\n");
	__insn_mtspr(SPR_TILE_TIMER_CONTROL,  0x0000000010000000UL);
}


_bme_set_state(int_handler); // TODO: IMPORTANT! this will change TP register

{
int i;
	for (i = 0; i < NUM_INTERRUPTS; ++i)
	if (int_handler[i] != NULL) hv_console_write("int handler is not null!\r\n", strlen("int handler is not null!\r\n"));
}

int_handler[INT_TILE_TIMER] = timer_int;

hv_console_write(str, strlen(str));

__insn_mtspr(SPR_MPL_WORLD_ACCESS_SET_0, 1);
__insn_mtspr(SPR_MPL_INTCTRL_0_SET_0, 1);

//uint64_t __insn_mfspr(SPR_SYSTEM_SAVE_1_0);
//   __insn_mtspr(SPR_INTERRUPT_MASK_RESET_2, (~0UL));
//   __insn_mtspr(SPR_MPL_AUX_TILE_TIMER_SET_2, (~0UL));
//__insn_mtspr(SPR_INTERRUPT_MASK_K, (0x0000000000000000UL));





__insn_mtspr(SPR_INTERRUPT_MASK_RESET_2, 1ULL << INT_TILE_TIMER);

// Debug aux timer
syslog(LOG_EMERG, "SPR_AUX_TILE_TIMER_CONTROL: %p", __insn_mfspr(SPR_TILE_TIMER_CONTROL));
syslog(LOG_EMERG, "SPR_MPL_AUX_TILE_TIMER: %p", __insn_mfspr(SPR_MPL_TILE_TIMER));
syslog(LOG_EMERG, "SPR_INTCTRL_0_STATUS: %p", __insn_mfspr(SPR_INTCTRL_0_STATUS));
syslog(LOG_EMERG, "SPR_INTCTRL_1_STATUS: %p", __insn_mfspr(SPR_INTCTRL_1_STATUS));
syslog(LOG_EMERG, "SPR_INTCTRL_2_STATUS: %p", __insn_mfspr(SPR_INTCTRL_2_STATUS));
syslog(LOG_EMERG, "SPR_INTERRUPT_MASK_0: %p", __insn_mfspr(SPR_INTERRUPT_MASK_0));
syslog(LOG_EMERG, "SPR_INTERRUPT_MASK_1: %p", __insn_mfspr(SPR_INTERRUPT_MASK_1));
syslog(LOG_EMERG, "SPR_INTERRUPT_MASK_2: %p", __insn_mfspr(SPR_INTERRUPT_MASK_2));
syslog(LOG_EMERG, "SPR_INTERRUPT_CRITICAL_SECTION: %p", __insn_mfspr(SPR_INTERRUPT_CRITICAL_SECTION));
__insn_mtspr(SPR_TILE_TIMER_CONTROL,  0x0000000000000001UL);
syslog(LOG_EMERG, "after SPR_AUX_TILE_TIMER_CONTROL: %p", __insn_mfspr(SPR_TILE_TIMER_CONTROL));
//    syslog(LOG_EMERG, "after SPR_LAST_INTERRUPT_REASON: %p", __insn_mfspr(SPR_LAST_INTERRUPT_REASON));

#endif

#if 0

    syslog(LOG_EMERG, "SPR_INTCTRL_0_STATUS: %p", __insn_mfspr(SPR_INTCTRL_0_STATUS));
    syslog(LOG_EMERG, "SPR_INTCTRL_1_STATUS: %p", __insn_mfspr(SPR_INTCTRL_1_STATUS));
    syslog(LOG_EMERG, "SPR_INTCTRL_2_STATUS: %p", __insn_mfspr(SPR_INTCTRL_2_STATUS));

    __insn_mtspr(SPR_IPI_MASK_RESET_K, (~0UL));

    __insn_mtspr(SPR_INTERRUPT_MASK_RESET_0, (~0UL));
    __insn_mtspr(SPR_INTERRUPT_MASK_RESET_1, (~0UL));

	__insn_mtspr(SPR_INTCTRL_0_STATUS, 0);
	__insn_mtspr(SPR_INTCTRL_1_STATUS, 0);
	__insn_mtspr(SPR_INTCTRL_2_STATUS, 0);

	__insn_mtspr(SPR_INTCTRL_0_STATUS, 1);
	__insn_mtspr(SPR_INTCTRL_1_STATUS, 1);
	__insn_mtspr(SPR_INTCTRL_2_STATUS, 1);

	int i;
    asm volatile("swint2"
             : "=R00" (i),
               "=R01" (i), "=R10" (i)
             : "R10" (i), "R01" (i)
             : "memory", "r2", "r3", "r4",
               "r5", "r6", "r7", "r8", "r9",
               "r11", "r12", "r13", "r14",
               "r15", "r16", "r17", "r18", "r19",
               "r20", "r21", "r22", "r23", "r24",
               "r25", "r26", "r27", "r28", "r29");

    HV_Coord xy = {0, 0};
    hv_send_nmi(xy, 0, 0);

    __insn_mtspr(SPR_INTERRUPT_MASK_RESET_0, (~0UL));
    __insn_mtspr(SPR_INTERRUPT_MASK_RESET_1, (~0UL));
#endif
