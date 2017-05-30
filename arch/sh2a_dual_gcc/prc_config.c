/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *								Toyohashi Univ. of Technology, JAPAN
 *	Copyright (C) 2005-2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2001-2011 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
 *	
 *	�嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *	�����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *	�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *	(1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *		��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *		����������˴ޤޤ�Ƥ��뤳�ȡ�
 *	(2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *		�ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *		��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	(3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *		�ȡ�
 *	  (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *		  �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	  (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *		  ��𤹤뤳�ȡ�
 *	(4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *		������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *		�ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *		ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *		���դ��뤳�ȡ�
 *	
 *	�ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *	���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *	���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *	�������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *	����Ǥ�����ʤ���
 *	
 *	$Id: prc_config.c 872 2011-08-18 06:48:55Z mit-kimai $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH2A-DUAL�ѡ�
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include <sil.h>

/*
 *  SIL���ԥ��å������֥�å���prc_config.c��
 */
TOPPERS_SIL_SPN_CB TOPPERS_sil_spn_cb = {0U, 0U};

/*
 *	�Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 *	�����Ƥ�����ϡ��ץ��å�������˰ۤʤ�Τ��ᡤ
 *	���ץ��å������������ե�������������
 */
const IPR_INFO ipr_info_tbl[TNUM_INT] = {
	IPR_INFO_TBL_DATA
};

extern PCB* const p_pcb_table[TNUM_PRCID];
extern const FP* const p_vectors_table[TNUM_PRCID];

/*
 *	�ץ��å���¸�ν����
 */
void
prc_initialize(void)
{
	uint_t pindex;
	PCB *my_p_pcb;
	TPCB *my_p_tpcb;
	
	pindex = sil_get_pindex();
	my_p_pcb = p_pcb_table[pindex];
	my_p_tpcb = &(my_p_pcb->target_pcb);
	set_gbr(my_p_pcb);	/*  �׸�Ƥ��gcc��¸  */

   /*
	*  ����ƥ����Ȥν����
	*  �������ͥ뵯ư�����󥿥�������ƥ����ȤȤ���ư����뤿�ᡢ
	*  ��excnest_count��1�ˤ��Ƥ�����
	*/
	my_p_tpcb->excnest_count = 1;
	my_p_tpcb->istkpt = istkpt_table[pindex];
	
	/*
	 *	CPU��å��ե饰�¸��Τ�����ѿ��ν����
	 */
	my_p_tpcb->lock_flag = true;
	my_p_tpcb->saved_iipm = IIPM_ENAALL;
	
	/*
	 *	����ߥ���ȥ���ν����
	 *	���ץ��å�����������
	 */
	irc_initialize(pindex);

	/*
	 *	�٥������١����쥸�����ν����
	 */
	set_vbr(p_vectors_table[pindex]);
}

/*
 *	�ץ��å���¸�ν�λ����
 */
void
prc_exit(void)
{
	/*
	 *	software_term_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
	 *	�����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
	 *	��Ǥ��롥
	 */
	if (x_sense_mprc()) {
		extern void    software_term_hook(void);
		void (*volatile fp)(void) = &software_term_hook;

		if (fp != 0) {
			(*fp)();
		}
	}
}

/*
 * CPU�㳰�ϥ�ɥ�ν����
 * �����ޥ���ˤ���������asp/kernel/exception.h�ǥץ�ȥ��������
 * ������Ƥ��뤿�ᡢ�ؿ��Ȥ���������ʤ���Фʤ�ʤ���
 */
void
initialize_exception(void)
{
	/* ���⤷�ʤ� */
}

#ifndef OMIT_DEFAULT_EXC_HANDLER
/*
 *	��Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void
default_exc_handler(void *p_excinf)
{
	uint32_t *sp	= (uint32_t*)p_excinf;
	uint32_t excno  = *(sp + P_EXCINF_OFFSET_VECTOR);
	uint32_t pc 	= *(sp + P_EXCINF_OFFSET_PC);
	uint32_t sr 	= *(sp + P_EXCINF_OFFSET_SR);
	uint32_t pr 	= *(sp + P_EXCINF_OFFSET_PR);
	uint32_t *sp_val = sp + P_EXCINF_OFFSET_SP;
	uint32_t prcid, local_excno, reg, i;
	char 	 *msg;
	
	local_excno = excno & 0xffffU;
	prcid = excno >> 16U;
	
	switch(local_excno) {
		case POWER_ON_RESET_VECTOR:
			msg = "Power on reset exception occurs.";
			break;
		case MANUAL_RESET_VECTOR:
			msg = "Manual reset exception occurs.";
			break;
		case GENERAL_ILLEGAL_INSTRUCTION_VECTOR:
			msg = "General illegal instruction exception occurs.";
			break;

#ifdef RAM_ERROR_VECTOR
		case RAM_ERROR_VECTOR:
			msg = "RAM error exception occurs.";
			break;
#endif	/*	RAM_ERROR_VECTOR  */

		case SLOT_ILLEGAL_INSTRUCTION_VECTOR:
			msg = "Slot illegal instruction exception occurs.";
			break;
		case CPU_ADDRESS_ERROR_VECTOR:
			msg = "CPU address error exception occurs.";
			break;
		case NMI_VECTOR:
			msg = "NMI occurs.";
			break;
		case USER_BREAK_VECTOR:
			msg = "User break interrupt occurs.";
			break;
		case H_UDI_VECTOR:
			msg = "H-UDI interrupt occurs.";
			break;
		case DIVIDE_BY_ZERO_VECTOR:
			msg = "Divided by 0 exception occurs.";
			break;
		case OVER_FLOW_VECTOR:
			msg = "Over flow exception occurs.";
			break;
		case SLEEP_ERROR_VECTOR:
			msg = "Sleep error occurs.";
			break;

#ifdef DMA_ADDRESS_ERROR_VECTOR
		case DMA_ADDRESS_ERROR_VECTOR:
			msg = "DMA address error exception occurs.";
			break;
#endif	/*	DMA_ADDRESS_ERROR_VECTOR  */

#ifdef FPU_VECTOR
		case FPU_VECTOR:
			msg = "FPU exception occurs.";
			break;
#endif /*  FPU_VECTOR  */

#if defined(SH2A) || defined(SH2A_DUAL)
		case BANK_OVER_FLOW_VECTOR:
			msg = "Bank over flow exception occurs.";
			break;
		case BANK_UNDER_FLOW_VECTOR:
			msg = "Bank under flow exception occurs.";
			break;
#endif /*  defined(SH2A) || defined(SH2A_DUAL)	*/

		default:
   			msg = "Unregistered exception occurs.";
   			break;
   	}
	syslog_1(LOG_EMERG, "%s", msg);

	syslog_2(LOG_EMERG, "(prcid = %d, Local EXCNO = %d)",
							prcid, local_excno);
	syslog_3(LOG_EMERG, "EXCNO = 0x%08x PC = 0x%08x SP = 0x%08p",
		   excno, pc, sp_val);
	syslog_2(LOG_EMERG, "SR = 0x%08x PR=0x%08x", sr, pr);
	for(i = 0; i < 8; ++i) {
		reg = *(sp + P_EXCINF_OFFSET_R0 + i);
		syslog_2(LOG_EMERG, " r%d=0x%08x", i, reg);
	}
	target_exit();
}
#endif /* OMIT_DEFAULT_EXC_HANDLER */

#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *	̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
void
default_int_handler(INTNO intno)
{
	INTNO local_intno  	= LOCAL_INTNO(intno);
	uint_t prcid		= ((uint_t)intno) >> 16U;
	
	syslog_0(LOG_EMERG, "Unregistered Interrupt occurs.");
	syslog_1(LOG_EMERG, "INTNO = %d",intno);
	syslog_2(LOG_EMERG, "(prcid = %d, Local INTNO = %d)",
							prcid, local_intno);
	target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */
