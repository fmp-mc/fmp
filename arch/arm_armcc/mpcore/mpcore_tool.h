/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: mpcore.h 844 2011-07-15 05:00:49Z ertl-honda $
 */

/*
 *  MPCORE のハードウェア資源のツール依存部の定義
 */

#ifndef TOPPERS_MPCORE_TOOL_H
#define TOPPERS_MPCORE_TOOL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  コプロへのアクセスマクロ
 */
#define CP15_CONTROL_READ(x) do {										\
	register uint32_t cp15_control __asm("cp15:0:c1:c0:0");				\
	x = cp15_control;													\
} while(false)

#define CP15_CONTROL_WRITE(x) do {										\
	register uint32_t cp15_control __asm("cp15:0:c1:c0:0");				\
	cp15_control = x;													\
} while(false)

#define CP15_AUXILIARY_READ(x) do {										\
	register uint32_t cp15_auxiliary __asm("cp15:0:c1:c0:1");			\
	x = cp15_auxiliary;													\
} while(false)

#define CP15_AUXILIARY_WRITE(x) do {									\
	register uint32_t cp15_auxiliary __asm("cp15:0:c1:c0:1");			\
	cp15_auxiliary = x;													\
} while(false)

#define CP15_ICACHE_INVALIDATE() do {									\
	register uint32_t cp15_icache_invalidate __asm("cp15:0:c7:c5:0");	\
	cp15_icache_invalidate = 0;											\
} while(false)

#if __TARGET_ARCH_ARM == 6

#define CP15_DCACHE_INVALIDATE() do {									\
	register uint32_t cp15_dcache_invalidate __asm("cp15:0:c7:c6:0");	\
	cp15_dcache_invalidate = 0;											\
} while(false)

#define CP15_DCACHE_CLEAN_AND_INVALIDATE() do {							\
	register uint32_t cp15_dcache_c_and_i __asm("cp15:0:c7:c14:0");		\
	cp15_dcache_c_and_i = 0;											\
} while(false)

#elif __TARGET_ARCH_ARM == 7

#define CP15_DCACHE_INVALIDATE(x) do {									\
	register uint32_t cp15_dcache_invalidate __asm("cp15:0:c7:c6:2");	\
	cp15_dcache_invalidate = x;											\
} while(false)

#define CP15_DCACHE_CLEAN_AND_INVALIDATE(x) do {						\
	register uint32_t cp15_dcache_c_and_i __asm("cp15:0:c7:c14:2");		\
	cp15_dcache_c_and_i = x;											\
} while(false)

#endif /* __TARGET_ARCH_ARM == 7 */

#if __TARGET_ARCH_ARM == 6

#define CP15_PBUFFER_FLUSH()  do {										\
	register uint32_t cp15_pbuffer_flush __asm("cp15:0:c7:c5:4");		\
	cp15_pbuffer_flush = 0;												\
} while(false)

#define CP15_DATA_SYNC_BARRIER() do {									\
	register uint32_t cp15_data_sync_barrier __asm("cp15:0:c7:c10:4");	\
	cp15_data_sync_barrier = 0;											\
} while(false)

#define CP15_DATA_MEMORY_BARRIER() do {									\
	register uint32_t cp15_data_memory_barrier __asm("cp15:0:c7:c10:5");\
	cp15_data_memory_barrier = 0;										\
} while(false)
#elif __TARGET_ARCH_ARM == 7

#define CP15_PBUFFER_FLUSH()               __isb(0xf)
#define CP15_DATA_SYNC_BARRIER()           __dsb(0xf)
#define CP15_DATA_MEMORY_BARRIER()         __dmb(0xf)

#endif /* __TARGET_ARCH_ARM == 7 */

#define CP15_INVALIDATE_UNIFIED_TLB() do {								\
	register uint32_t cp15_i_unified_tlb __asm("cp15:0:c8:c7:0");		\
	cp15_i_unified_tlb = 0;												\
} while(false)

#define CP15_TTBCR_WRITE(x) do {										\
	register uint32_t cp15_ttbcr __asm("cp15:0:c2:c0:2");				\
	cp15_ttbcr = x;														\
} while(false)

#define CP15_TTB0_READ(x) do {											\
	register uint32_t cp15_ttb0 __asm("cp15:0:c2:c0:0");				\
	x = cp15_ttb0;														\
} while(false)

#define CP15_TTB0_WRITE(x) do {											\
	register uint32_t cp15_ttb0 __asm("cp15:0:c2:c0:0");				\
	cp15_ttb0 = x;														\
} while(false)

#define CP15_DOMAINS_WRITE(x) do {										\
	register uint32_t cp15_domains __asm("cp15:0:c3:c0:0");				\
	cp15_domains = x;													\
} while(false)

#define CP15_CPUID_READ(x) {											\
	register uint32_t cp15_cpuid __asm("cp15:0:c0:c0:5");				\
	x = cp15_cpuid;														\
} while(false)

#define CP15_CACHE_SIZE_ID_READ(x) do {									\
	register uint32_t cp15_cache_size __asm("cp15:1:c0:c0:0");			\
	x = cp15_cache_size;												\
} while(false)

#if __TARGET_ARCH_ARM == 7

#define CP15_CACHE_SIZE_SELECTION_WRITE(x) do {							\
	register uint32_t cp15_cache_size_sel __asm("cp15:2:c0:c0:0");		\
	cp15_cache_size_sel = x;											\
} while(false)

#define CP15_CACHE_SIZE_SELECTION_READ(x) do {							\
	register uint32_t cp15_cache_size_sel __asm("cp15:2:c0:c0:0");		\
	x = cp15_cache_size_sel;											\
} while(false)

#endif /* __TARGET_ARCH_ARM == 7 */

#define CPU15_PONLY_THREAD_ID_READ(x) do {								\
	register uint32_t cp15_ponly_thread_id __asm("cp15:0:c13:c0:4");	\
	x = cp15_ponly_thread_id;											\
} while(false)

#define CPU15_PONLY_THREAD_ID_WRITE(x)  do {							\
	register uint32_t cp15_ponly_thread_id __asm("cp15:0:c13:c0:4");	\
	cp15_ponly_thread_id = x;											\
} while(false)

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_MPCORE_TOOL_H */
