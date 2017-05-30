/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2008-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.c 896 2012-02-24 01:59:56Z ertl-honda $
 */

/*
 *  �ץ��å���¸�⥸�塼���Nios2�ѡ�
 */
#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "nios2.h"
#include "mp.h"
#include "prc_ipi.h"

/*
 *  start.S �Ǥ�Ʊ����
 */
volatile uint_t start_sync;

#ifndef NIOS2_USE_INT_VEC_INST
/*
 *  ������װ���Ƚ��Τ���Υӥåȥޥåץ�����̿��
 */
const uint8_t int_bitmap_search_table[] = { 0, 1, 0, 2, 0, 1, 0,
										3, 0, 1, 0, 2, 0, 1, 0 };
#endif

/*
 *  �ץ��å���¸�ν����
 */
void
prc_initialize()
{
	TPCB *p_tpcb = get_my_p_tpcb();
	uint32_t index = x_prc_index();

	/*
	 *  �����ͥ뵯ư�����󥿥�������ƥ����ȤȤ���ư����뤿��1��
	 */ 
	p_tpcb->except_nest_count = 1;

	/*
	 * �Ƴ���ߤγ�����׵�ػߥե饰���ػ�
	 */
	p_tpcb->idf = ~0U;

	/*
	 * �����ͥ���٥ޥ����ν����
	 */ 
	p_tpcb->iipm = 0U;

	/*
	 * ���Ƥγ���ߤ�ޥ���
	 */
	set_ienable(~0U);

	/*
	 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ����������롥
	 */
	p_tpcb->bitpat_cfgint = 0U;

	/*
	 *  �󥿥�������ƥ������ѤΥ����å��ν����
	 */
	p_tpcb->istkpt = istkpt_table[index];

	/*
	 *  ����ߥޥ����ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_iipm_mask_tbl = p_iipm_mask_table[index];

	/*
	 *  ����ߥϥ�ɥ�ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_inh_tbl = p_inh_table[index];

	/*
	 *  �����ͥ���٥ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_inh_iipm_tbl = p_inh_iipm_table[index];

	/*
	 *  CPU�㳰�ϥ�ɥ�ơ��֥�ؤΥݥ��󥿤ν����
	 */
	p_tpcb->p_exch_tbl = p_exch_table[index];

	p_tpcb->prc_int_base = target_prc_int_base_table[index];
}

/*
 *  �ץ��å���¸�ν�λ����
 */
void
prc_terminate(void)
{
	extern void    software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
	 *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
	 *  ��Ǥ��롥
	 */
	if (fp != 0) {
		(*fp)();
	}

	start_sync = 0;

	/*
	 *  ���٤Ƥγ���ߤ�ޥ������롥
	 */
	set_ienable(~0U);
}

/*
 *  ������׵�饤���°��������
 *
 *  ASP�����ͥ�Ǥ����Ѥ����ꤷ�ơ��ѥ�᡼�����顼�ϥ����������ǥ�����
 *  �����Ƥ��롥FI4�����ͥ�����Ѥ�����ˤϡ����顼���֤��褦�ˤ��٤�
 *  �Ǥ�����
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask)
{
	TPCB *p_tpcb;

	p_tpcb = get_my_p_tpcb();

	assert(VALID_INTNO_CFGINT(ID_PRC(x_prc_index()), intno));
	assert(TMIN_INTPRI <= intpri && intpri <= TMAX_INTPRI);

	/*
	 *  �����°�������ꤵ��Ƥ��뤫��Ƚ�̤��뤿����ѿ�������
	 */
	p_tpcb->bitpat_cfgint |= INTNO_BITPAT(INTNO_MASK(intno));

	/* 
	 * ���ä������ߤ�ػߤ���
	 */    
	x_disable_int(intno);

	if ((intatr & TA_ENAINT) != 0U){
		(void)x_enable_int(INTNO_MASK(intno));
	}
}

/*
 * CPU�㳰�ϥ�ɥ�ν����
 */
void
initialize_exception(void)
{
}

/*
 *  CPU�㳰��ȯ�������Υ�����
 *
 *  CPU�㳰�ϥ�ɥ���椫�顤CPU�㳰����ݥ��󥿡�p_excinf�ˤ�����Ȥ�
 *  �ƸƤӽФ����Ȥǡ�CPU�㳰��ȯ�������򥷥��ƥ���˽��Ϥ��롥
 */
#ifdef SUPPORT_XLOG_SYS

void
xlog_sys(void *p_excinf)
{    
}

#endif /* SUPPORT_XLOG_SYS */

#ifndef OMIT_DEFAULT_EXC_HANDLER

/*
 * ̤������㳰�����ä����ν���
 */
void
default_exc_handler(void *p_excinf){
	ID prc_id = ID_PRC(x_prc_index());

	syslog(LOG_EMERG, "Processor %d : Unregistered Exception occurs.", prc_id);
	syslog(LOG_EMERG, " Excno = %d.",
		   *(((uint32_t*)p_excinf) + CPUEXC_FLM_EXCNO));
	syslog(LOG_EMERG, " ESTATUS = 0x%x.",
		   *(((uint32_t*)p_excinf) + CPUEXC_FLM_ESTATUS));
	syslog(LOG_EMERG, " Addr = 0x%x.",
		   *(((uint32_t*)p_excinf) + CPUEXC_FLM_PC));
	syslog(LOG_EMERG, " IPM = 0x%x.",
			 *(((uint32_t*)p_excinf) + CPUEXC_FLM_IPM));
	syslog(LOG_EMERG, " Interrupt/Exception Nest Count = %d",
			 *(((uint32_t*)p_excinf) + CPUEXC_FLM_NEST));
	target_exit();
}

#endif /* OMIT_DEFAULT_EXC_HANDLER */

#ifndef OMIT_DEFAULT_INT_HANDLER

/*
 * ̤����γ���ߤ����ä����ν���
 */
void
default_int_handler(void *p_excinf){
	ID prc_id = ID_PRC(x_prc_index());

	syslog(LOG_EMERG, "Processor %d : Unregistered Interrupt occurs.", prc_id);
	syslog(LOG_EMERG, " Intno = %d.", (int)p_excinf);
	target_exit();
}

void
perf_timer_initialize(intptr_t exinf)
{
	/* �ꥻ�å� */
	sil_wrw_iop((void*)(PERF_COUNTER_BASE), 1);
	/* �������� */
	sil_wrw_iop((void*)(PERF_COUNTER_BASE + 0x04), 0);
}

void
perf_timer_get(uint32_t *p_time)
{
	*p_time = sil_rew_iop((void*)(PERF_COUNTER_BASE));
}

uint32_t
perf_timer_conv_tim(uint32_t time)
{
	return (time * 1000) / PERF_COUNTER_CLOCK;
}

#endif /* OMIT_DEFAULT_INT_HANDLER */
