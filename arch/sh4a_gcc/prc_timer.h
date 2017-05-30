/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_timer.h 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�SH4A�ѡ�
 */
#ifndef TOPPERS_PRC_TIMER_H
#define TOPPERS_PRC_TIMER_H

#include <sil.h>

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
#define INHNO_TIMER0     TMU0_INTEVT   /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER0     TMU0_INTEVT   /* ������ֹ� */
#define INHNO_TIMER1     TMU1_INTEVT   /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER1     TMU1_INTEVT   /* ������ֹ� */
#define INHNO_TIMER2     TMU2_INTEVT   /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER2     TMU2_INTEVT   /* ������ֹ� */
#define INHNO_TIMER3     TMU3_INTEVT   /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER3     TMU3_INTEVT   /* ������ֹ� */

#define INTPRI_TIMER    (-6)          /* �����ͥ���� */
#define INTATR_TIMER    0U            /* �����°�� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �������ͤ�����ɽ���η�
 */
typedef uint32_t    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *
 */
#define TO_CLOCK(nume, deno)    ((CLOCK)(TIMER_CLOCK * (nume) / (deno)))

/*
 *  �ʥ�ñ�̤��Ѵ���10��-9
 */
#define TO_USEC(clock)          (((SYSUTM) clock) * 80U) 

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK    ((CLOCK) 0xffffU)

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
extern void target_timer_initialize(intptr_t exinf);

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
extern void target_timer_terminate(intptr_t exinf);

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
target_timer_get_current(void)
{
	return(0xffffffff - sil_rew_mem((void*)TMU_TCNT4));
}

/*
 *  ��ǽɾ���ѥʥ��û��ּ���
 */
Inline void
get_ntim(SYSUTM *p_sysutm)
{
	uint32_t	clock1;

	clock1 = target_timer_get_current();

	/*
	 *  1�������80n��
	 */
	*p_sysutm = clock1 * 80;
}

/*
 *  �����޳�����׵�Υ����å�(��ǽɾ����)
 */
Inline bool_t
target_timer_probe_int(void)
{
	return(sil_reh_mem((void*)TMU_TCR4) & TCR_UNF);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
extern void target_timer_handler(intptr_t exinf);
extern void perf_timer_initialize(intptr_t exinf);
extern void synco_asm(void);

#ifdef TOPPERS_TRACE_ENABLE
extern SYSTIM target_time;
#endif /* TOPPERS_TRACE_ENABLE */

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_TIMER_H */
