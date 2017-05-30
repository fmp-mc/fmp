/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: mpcore.h 844 2011-07-15 05:00:49Z ertl-honda $
 */

/*
 *  MPCORE �Υϡ��ɥ������񸻤Υġ����¸�������
 */

#ifndef TOPPERS_MPCORE_TOOL_H
#define TOPPERS_MPCORE_TOOL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ���ץ�ؤΥ��������ޥ���
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
