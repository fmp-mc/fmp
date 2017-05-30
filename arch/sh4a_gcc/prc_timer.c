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
 *  @(#) $Id: prc_timer.c 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�SH4A�ѡ�
 */
#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"

#ifdef TOPPERS_TRACE_ENABLE
SYSTIM target_time;
#endif /* TOPPERS_TRACE_ENABLE */

/*
 *  �����ޥݡ��Ƚ�����֥�å������
 */
typedef struct tim_initialization_block {
	void  *tcor_w;   /* �����ޥ��󥹥���ȥ쥸���� */
	void  *tcnt_w;   /* �����ޥ����� */
	void  *tcr_h;    /* �����ޥ���ȥ���쥸���� */
	void  *tstr_b;
	uint8_t str;
} TIMINIB;

/*
 *  �����޽�����֥�å�
 */
const TIMINIB timinib_table[6] = {
	{
		(void *)(TIM0_BASE + TIM_TCOR),
		(void *)(TIM0_BASE + TIM_TCNT),
		(void *)(TIM0_BASE + TIM_TCR),
		(void *)(TMU_TSTR0),
		TMU_STR0
	},
	{
		(void *)(TIM1_BASE + TIM_TCOR),
		(void *)(TIM1_BASE + TIM_TCNT),
		(void *)(TIM1_BASE + TIM_TCR),
		(void *)(TMU_TSTR0),
		TMU_STR1
	},
	{
		(void *)(TIM2_BASE + TIM_TCOR),
		(void *)(TIM2_BASE + TIM_TCNT),
		(void *)(TIM2_BASE + TIM_TCR),
		(void *)(TMU_TSTR0),
		TMU_STR2
	},
	{
		(void *)(TIM3_BASE + TIM_TCOR),
		(void *)(TIM3_BASE + TIM_TCNT),
		(void *)(TIM3_BASE + TIM_TCR),
		(void *)(TMU_TSTR1),
		TMU_STR0
	},
	{
		(void *)(TIM4_BASE + TIM_TCOR),
		(void *)(TIM4_BASE + TIM_TCNT),
		(void *)(TIM4_BASE + TIM_TCR),
		(void *)(TMU_TSTR1),
		TMU_STR1
	},
	{
		(void *)(TIM5_BASE + TIM_TCOR),
		(void *)(TIM5_BASE + TIM_TCNT),
		(void *)(TIM5_BASE + TIM_TCR),
		(void *)(TMU_TSTR1),
		TMU_STR2
	}
};

/*
 *  CPUID��������֥�å�����Ф�����Υޥ���
 */
#define get_timinib (&(timinib_table[x_prc_index()]))
#define get_timinib_atr(intatr) (&(timinib_table[intatr]))

int_t const tmu_intevt[6] = {
	TMU0_INTEVT,
	TMU1_INTEVT,
	TMU2_INTEVT,
	TMU3_INTEVT,
	TMU4_INTEVT,
	TMU5_INTEVT
};

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
	CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);
	const TIMINIB *p_timinib;
	p_timinib =   &(timinib_table[(int)exinf - 1]);
	SIL_PRE_LOC;

	/*
	*  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	*/
	sil_wrb_mem(p_timinib->tstr_b,
                (sil_reb_mem(p_timinib->tstr_b) & ~p_timinib->str));  /* ��������� */
	assert(cyc <= MAX_CLOCK);             /* �����޾���ͤΥ����å� */

    /* ʬ�������ꡢ�����ߵ��� */
	sil_wrh_mem(p_timinib->tcr_h,(0x020 | TCR0_TPSC));
	sil_wrw_mem(p_timinib->tcor_w, cyc); /* timer constant�쥸�����򥻥å� */
	sil_wrw_mem(p_timinib->tcnt_w, cyc); /* �����󥿡��򥻥å� */    

	/* �����ޥ������� */
	/* �����ޥ������ȥ쥸������ʣ�������Ƕ�ͭ���Ƥ���Τ���¾���椬ɬ�� */

	SIL_LOC_SPN();
	sil_wrb_mem(p_timinib->tstr_b,
                (sil_reb_mem(p_timinib->tstr_b) | p_timinib->str));
	SIL_UNL_SPN();

	/*
	*  �����޳�����׵�򥯥ꥢ���롥
	*/
	
	/* �������׵�򥯥ꥢ */
	sil_wrh_mem(p_timinib->tcr_h,
                (sil_reh_mem(p_timinib->tcr_h) & ~TCR_UNF));
 
#ifdef TOPPERS_TRACE_ENABLE
	target_time = 0;
#endif /* TOPPERS_TRACE_ENABLE */    
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
	const TIMINIB *p_timinib;
	p_timinib =   &(timinib_table[(int)exinf - 1]);
  
	/* �����ޤ���� */
	sil_wrb_mem(p_timinib->tstr_b,
                (sil_reb_mem(p_timinib->tstr_b) & ~p_timinib->str));
	/* �������׵�򥯥ꥢ */
	sil_wrh_mem(p_timinib->tcr_h,0);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(intptr_t exinf)
{
	const TIMINIB *p_timinib;

	p_timinib =   &(timinib_table[exinf - 1]);
  
	/* �������׵�򥯥ꥢ */
	sil_wrh_mem(p_timinib->tcr_h,
                (sil_reh_mem(p_timinib->tcr_h) & ~TCR_UNF));

#ifdef TOPPERS_TRACE_ENABLE    
	target_time++;
#endif /* TOPPERS_TRACE_ENABLE */    

	i_begin_int(tmu_intevt[exinf - 1]);
	signal_time();                    /* ������ƥ��å��ζ��� */
	i_end_int(tmu_intevt[exinf - 1]);
}


/*
 *  ��ǽɾ���ѥ����ޤε�ư����
 */
void
perf_timer_initialize(intptr_t exinf)
{
	CLOCK    cyc = 0xffffffff;
	const TIMINIB *p_timinib;
	p_timinib =   &(timinib_table[4]);

	/*
	*  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
	*/
	sil_wrb_mem(p_timinib->tstr_b,
                (sil_reb_mem(p_timinib->tstr_b) & ~p_timinib->str));  /* ��������� */
	assert(cyc <= MAX_CLOCK);             /* �����޾���ͤΥ����å� */

	/* ʬ�������ꡢ�����ߵ��� */
 
	sil_wrh_mem(p_timinib->tcr_h,(0x020 | TCR0_TPSC)); //1/4ʬ��
	sil_wrw_mem(p_timinib->tcor_w, cyc); /* timer constant�쥸�����򥻥å� */
	sil_wrw_mem(p_timinib->tcnt_w, cyc); /* �����󥿡��򥻥å� */    

	/* �����ޥ������� */
	sil_wrb_mem(p_timinib->tstr_b,
                (sil_reb_mem(p_timinib->tstr_b) | p_timinib->str));

	/*
	*  �����޳�����׵�򥯥ꥢ���롥
	*/
	/* �������׵�򥯥ꥢ */
	sil_wrh_mem(p_timinib->tcr_h,
                (sil_reh_mem(p_timinib->tcr_h) & ~TCR_UNF));
}

void
synco_asm(void)
{
	Asm("synco");
}
