/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2008-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: avalon_timer.h 89 2009-01-25 16:02:00Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�Avalon Timer�ѡ�
 */

#ifndef TOPPERS_AVALON_TIMER_H
#define TOPPERS_AVALON_TIMER_H

#include <sil.h>

/*
 *  Avalon Timer �ϡ��ɥ��������
 */

/*
 *  �쥸����
 */
#define AVALON_TIM_STATUS    0x00
#define AVALON_TIM_CONTROL   0x04
#define AVALON_TIM_PERIODL   0x08
#define AVALON_TIM_PERIODH   0x0C
#define AVALON_TIM_SNAPL     0x10
#define AVALON_TIM_SNAPH     0x14

/*
 *  �ӥå����
 */
#define AVALON_TIM_STATUS_RUN 0x02
#define AVALON_TIM_STATUS_TO  0x01

#define AVALON_TIM_CONTROL_STOP  0x08
#define AVALON_TIM_CONTROL_START 0x04
#define AVALON_TIM_CONTROL_COUNT 0x02
#define AVALON_TIM_CONTROL_ITO   0x01


#ifndef TOPPERS_MACRO_ONLY

/*
 *  �����ͥ륿���ޤΥ١������ɥ쥹�μ����ơ��֥�
 *  �������åȰ�¸��������� 
 */
extern const uint32_t target_sys_clk_timer_base_table[];

/*
 *  �����ͥ륿���ޤγ�����ֹ�μ����ơ��֥�
 *  �������åȰ�¸��������� 
 */
extern const uint32_t target_sys_clk_timer_intno_table[];

/*
 *  �������ͤ�����ɽ���η�
 */
typedef uint32_t    CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ��á�����ñ�̤Ȥ��Ѵ�
 *
 */
#define TO_CLOCK(nume, deno)    ((CLOCK)(TIMER_CLOCK * (nume) / (deno)))
#define TO_USEC(clock)          (((SYSUTM) clock) * 1000U / TIMER_CLOCK)

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK    ((CLOCK) 0xffffffffU)

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
	CLOCK count;
	uint32_t base = target_sys_clk_timer_base_table[x_prc_index()];

	/* ���ʥåץ쥸�����˽񤭹�����ͤ�ۡ���ɤ��� */
	sil_wrw_iop((void*)(base + AVALON_TIM_SNAPL), 0x00);

	/* ��������ͤ��ɤ߹��� */
	count = sil_rew_iop((void*)(base + AVALON_TIM_SNAPL));
	count |= sil_rew_iop((void*)(base + AVALON_TIM_SNAPH)) << 16;
    
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - count);
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline bool_t
target_timer_probe_int(void)
{
	uint32_t base = target_sys_clk_timer_base_table[x_prc_index()];
	return(sil_rew_iop((void*)(base + AVALON_TIM_STATUS)) & AVALON_TIM_STATUS_TO);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
extern void target_timer_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_AVALON_TIMER_H */
