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
 *  @(#) $Id: avalon_timer.c 89 2009-01-25 16:02:00Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�Avalon Timer��
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"
#include "avalon_timer.h"
 
/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	uint32_t base = target_sys_clk_timer_base_table[x_prc_index()];

	/* �����ޡ����ȥå� */
	sil_wrw_iop((void*)(base + AVALON_TIM_CONTROL), AVALON_TIM_CONTROL_STOP);
	/* �����ॢ���ȥ��ơ��������ꥢ */
	sil_wrw_iop((void*)(base + AVALON_TIM_STATUS), 0x00);

	assert(cyc <= MAX_CLOCK);                          /* �����޾���ͤΥ����å� */
	sil_wrw_iop((void*)(base + AVALON_TIM_PERIODL), (cyc & 0xffff)); /* �����󥿡����å� ����16bit */
	sil_wrw_iop((void*)(base + AVALON_TIM_PERIODH), (cyc >> 16));    /* �����󥿡����å� ���16bit */

	/*
	 * �����ޡ��������ȡ������ȥ���ɡ�����ߵ���
	 */
	sil_wrw_iop((void*)(base + AVALON_TIM_CONTROL), AVALON_TIM_CONTROL_START
				|AVALON_TIM_CONTROL_COUNT|AVALON_TIM_CONTROL_ITO);
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	uint32_t base = target_sys_clk_timer_base_table[x_prc_index()];

	/* ��������� */
	sil_wrw_iop((void*)(base + AVALON_TIM_CONTROL), AVALON_TIM_CONTROL_STOP);

	/* ������׵�Υ��ꥢ */
	sil_wrw_iop((void*)(base + AVALON_TIM_STATUS), 0x00);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
	uint32_t base = target_sys_clk_timer_base_table[x_prc_index()];
	uint32_t intno = target_sys_clk_timer_intno_table[x_prc_index()];

	/* TO�ӥåȤΥ��ꥢ */
	sil_wrw_iop((void*)(base + AVALON_TIM_STATUS), 0x00);

	i_begin_int(intno);
	/* ������ƥ��å��ζ��� */
	signal_time();
	i_end_int(intno);
}
