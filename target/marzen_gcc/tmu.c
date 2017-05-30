/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: tmu.c 943 2012-10-19 07:50:40Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�SH34�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"
#ifdef TRACE_ENABLE
#endif /* TRACE_ENABLE */

/*
 *  TMU������֥��å�
 */
const TMUINIB tmuinib_table[] = {
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU0_BASE + TMU_TCOR),
		(uint32_t*)(TMU0_BASE + TMU_TCNT),
		(uint16_t*)(TMU0_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU1_BASE + TMU_TCOR),
		(uint32_t*)(TMU1_BASE + TMU_TCNT),
		(uint16_t*)(TMU1_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU012_BASE + TMU_TSTR),
		(uint32_t*)(TMU2_BASE + TMU_TCOR),
		(uint32_t*)(TMU2_BASE + TMU_TCNT),
		(uint16_t*)(TMU2_BASE + TMU_TCR),
		(uint8_t)(0x04)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU3_BASE + TMU_TCOR),
		(uint32_t*)(TMU3_BASE + TMU_TCNT),
		(uint16_t*)(TMU3_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU4_BASE + TMU_TCOR),
		(uint32_t*)(TMU4_BASE + TMU_TCNT),
		(uint16_t*)(TMU4_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU345_BASE + TMU_TSTR),
		(uint32_t*)(TMU5_BASE + TMU_TCOR),
		(uint32_t*)(TMU5_BASE + TMU_TCNT),
		(uint16_t*)(TMU5_BASE + TMU_TCR),
		(uint8_t)(0x04)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU6_BASE + TMU_TCOR),
		(uint32_t*)(TMU6_BASE + TMU_TCNT),
		(uint16_t*)(TMU6_BASE + TMU_TCR),
		(uint8_t)(0x01)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU7_BASE + TMU_TCOR),
		(uint32_t*)(TMU7_BASE + TMU_TCNT),
		(uint16_t*)(TMU7_BASE + TMU_TCR),
		(uint8_t)(0x02)  
	},
	{
		(uint8_t*)(TMU678_BASE + TMU_TSTR),
		(uint32_t*)(TMU8_BASE + TMU_TCOR),
		(uint32_t*)(TMU8_BASE + TMU_TCNT),
		(uint16_t*)(TMU8_BASE + TMU_TCR),
		(uint8_t)(0x03)  
	}
};


/*
 *  �����ͥ륿���ޤ�ID�����ơ��֥�
 */
const uint32_t
target_sys_clk_timer_id_table[] = {
	PRC1_TMU_NO,
	PRC2_TMU_NO,
	PRC3_TMU_NO,
	PRC4_TMU_NO,
};

/*
 *  �����ͥ륿���ޤγ�����ֹ�μ����ơ��֥�
 */
const uint32_t
target_sys_clk_timer_intno_table[] = {
	INTNO_TIMER_PRC1,
	INTNO_TIMER_PRC2,
	INTNO_TIMER_PRC3,
	INTNO_TIMER_PRC4
};

/*
 * [�����ޥ������ȥ쥸��������¾�����ѥ��å�(������3,4,5��)]
 * �������륿���������Ǥϡ�����1,2,3��������3,4,5����Ѥ��롥
 * ������3,4,5�ǻ��Ѥ��륿���ޥ������ȥ쥸������tstr1�Ƕ��̤Τ��ᡤ
 * ����1,2,3�δ֤���¾���椬ɬ�ס�
 */
SPNLOCK tmu_tstr_lock;

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];

	/*
	 *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	 */
	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) & ~(p_tmuinib->tstr_bit)));  /* ��������� */
	assert(cyc <= MAX_CLOCK);             /* �����޾���ͤΥ����å� */

	/* ʬ�������ꡢ�����ߵ��� */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h), TCR_UNIE);
    
	sil_wrw_mem((void*)(p_tmuinib->tcor_w), cyc); /* timer constant�쥸�����򥻥å� */
	sil_wrw_mem((void*)(p_tmuinib->tcnt_w), cyc); /* �����󥿡��򥻥å� */


	/* �������׵�򥯥ꥢ */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));

	x_lock_spin(&tmu_tstr_lock);
	/* �����ޥ������� */
	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) | (p_tmuinib->tstr_bit)));
	x_unlock_spin(&tmu_tstr_lock);
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];

	sil_wrb_mem((void*)(p_tmuinib->tstr_b),
				(sil_reb_mem((void*)(p_tmuinib->tstr_b)) & ~(p_tmuinib->tstr_bit)));  /* ��������� */
	/* �������׵�򥯥ꥢ */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
	const TMUINIB *p_tmuinib = &tmuinib_table[target_sys_clk_timer_id_table[x_prc_index()]];
	uint32_t intno = target_sys_clk_timer_intno_table[x_prc_index()];

	/* �������׵�򥯥ꥢ */
	sil_wrh_mem((void*)(p_tmuinib->tcr_h),
				(sil_reh_mem((void*)(p_tmuinib->tcr_h)) & ~TCR_UNF));
      
	i_begin_int(intno);
	signal_time();                    /* ������ƥ��å��ζ��� */
	i_end_int(intno);
}