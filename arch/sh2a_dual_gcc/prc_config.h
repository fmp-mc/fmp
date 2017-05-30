/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2007-2011 by Industrial Technology Institute,
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
 *	$Id: prc_config.h 878 2011-08-18 07:35:12Z mit-kimai $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH2A-DUAL�ѡ�
 *
 *	���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *	�롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *	ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_TARGET_CONFIG_H
#error  target_config.h is not included!
#endif	/*  TOPPERS_TARGET_CONFIG_H  */

/*
 *  ���顼�����å���ˡ�λ���
 */
#define CHECK_STKSZ_ALIGN	4	/* �����å��������Υ��饤��ñ�� */
#define CHECK_FUNC_ALIGN	2	/* �ؿ��Υ��饤��ñ�� */
#define CHECK_FUNC_NONNULL		/* �ؿ�����NULL�����å� */
#define CHECK_STACK_ALIGN	4	/* �����å��ΰ�Υ��饤��ñ�� */
#define CHECK_STACK_NONNULL		/* �����å��ΰ����NULL�����å� */
#define CHECK_MPF_ALIGN		4	/* ����Ĺ����ס����ΰ�Υ��饤��ñ�� */
#define CHECK_MPF_NONNULL		/* ����Ĺ����ס����ΰ����NULL�����å� */
#define CHECK_MB_ALIGN		4	/* �����ΰ�Υ��饤��ñ�� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *	�ץ��å����ü�̿��Υ���饤��ؿ����
 */
#include "prc_insn.h"

/*
 *	����ȥ�(start.S)
 */
extern void start(void);

/*
 *	̤��Ͽ�γ�����ѤΥ���ȥ�
 */
extern void default_int_handler_entry(void);

/*
 *	�󥿥�������ƥ������ѤΥ����å������
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *	����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	void	*sp;		/* �����å��ݥ��� */
	FP		pc;			/* �ץ���५���� */
} TSKCTXB;


#define USE_TSKINICTXB	/*  TSKINICTXB����Ѥ���  */

/*
 *	���������������ƥ����ȥ֥�å�
 */
typedef struct task_initialization_context_block {
	SIZE	stksz;			/* �����å��ΰ�Υ������ʴݤ᤿�͡� */
	void	*stk_bottom;	/* �����å��ݥ��󥿤ν���͡ʥ����å�����ν���͡� */
} TSKINICTXB;


/*
 *  �ޥ������ץ��å������֤�
 */
Inline bool_t
x_sense_mprc(void)
{
	if (x_prc_index() == (TOPPERS_MASTER_PRCID - 1)) {
		return true;
	}
	else {
		return false;
	}
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *	�����ͥ���٥ޥ������饤�֥��
 *	
 *	SH2A-DUAL�Ǥϡ����ơ������쥸������SR�ˤ�4��7�ӥå��ܤ�4�ӥåȤ˳����
 *	ͥ���٥ޥ����ʥϡ��ɥ������γ����ͥ���٥ޥ�����IPM�ˤ��֤���Ƥ�
 *	�롥IPM����¸���Ƥ�������ˡ������ͥ���٤γ���ɽ����-1����Ϣ³��
 *	������͡ˤ�Ȥ����Ȥ��ǽ�Ǥ��뤬��;�פʺ����ӥåȥ��եȤ����ȿ
 *	ž��ɬ�פˤʤ롥������򤱤뤿��ˡ�IPM����¸������ˤϡ�SR��4��7
 *	�ӥå��ܤ���Ф����ͤ�Ȥ����Ȥˤ��롥�����ͤ�����ͥ���٥ޥ���
 *	������ɽ���ȸƤӡ�IIPM�Ƚ񤯤��Ȥˤ��롥
 */

/*
 *	�����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 *
 *	������֥����Υ������ե����뤫�饤�󥯥롼�ɤ�����Τ���ˡ�CAST�����
 */
#define EXT_IPM(iipm)	 (-CAST(PRI,(iipm) >> 4))		/* ����ɽ������ɽ���� */
#define INT_IPM(ipm)	 (CAST(uint32_t, -(ipm)) << 4)	/* ����ɽ��������ɽ���� */

/*
 *	CPU��å����֤Ǥγ����ͥ���٥ޥ���
 *
 *	TIPM_LOCK�ϡ�CPU��å����֤Ǥγ����ͥ���٥ޥ��������ʤ����������
 *	��������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������ͤ�������롥
 */
#define TIPM_LOCK	 TMIN_INTPRI

/*
 *	�����ͥ�������γ���ߤ򥵥ݡ��Ȥ��뤫�ݤ��������̤������
 */
#if TIPM_LOCK != -15
#define TOPPERS_SUPPORT_NONKERNEL_INT
#endif

/*
 *	CPU��å����֤Ǥγ����ͥ���٥ޥ���������ɽ��
 */
#define IIPM_LOCK	 INT_IPM(TIPM_LOCK)

/*
 *	�����ͥ���٥ޥ����������TIPM_ENAALL�ˤ�����ɽ��
 */
#define IIPM_ENAALL  INT_IPM(TIPM_ENAALL)

/*
 *	������ߥ�å�������ɽ��
 */
#define IIPM_DISALL  UINT_C(0xf0)


#ifndef TOPPERS_MACRO_ONLY

/*
 *	IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint32_t
current_iipm(void)
{
	return((uint32_t)(current_sr() & 0xF0U));
}

/*
 *	IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_iipm(uint32_t iipm)
{
	uint32_t sr = current_sr();

	sr = (sr & ~0xF0U) | iipm;
	set_sr(sr);
}

Inline void
set_iipm_with_nop(uint32_t iipm)
{
	uint32_t sr = current_sr();

	sr = (sr & ~0xF0U) | iipm;
	set_sr_with_nop(sr);
}

/*
 *	TOPPERSɸ�����߽�����ǥ�μ¸�
 *
 *	SH2A-DUAL�ϥ��ơ������쥸����(SR)��˳����ͥ���٥ޥ���(IPM)����äƤ��롥
 *	CPU��å��ե饰��������ǽ������ʤ������Τ��ᡤ����Ū��CPU��å���
 *	�饰��¸����롥
 *
 *	�ޤ���CPU��å����֤������������ѿ�(lock_flag)���Ѱդ��롥
 *
 *	CPU��å��ե饰�����ꥢ����Ƥ���֤ϡ�IPM���ǥ��γ����ͥ����
 *	�ޥ������ͤ����ꤹ�롥���δ֤ϡ���ǥ��γ����ͥ���٥ޥ����ϡ�
 *	IPM���Ѥ��롥
 *	
 *	������Ф���CPU��å��ե饰�����åȤ���Ƥ���֤ϡ�IPM�򡤥����ͥ��
 *	�����Τ�Τ�������٤Ƥγ�����׵��ޥ���������(TIPM_LOCK)�ȡ����
 *	���γ����ͥ���٥ޥ����Ȥι⤤�������ꤹ�롥���δ֤Υ�ǥ��γ�
 *	����ͥ���٥ޥ����ϡ����Τ�����ѿ�(saved_iipm, ����ɽ�����ݻ�)����
 *	�դ����ݻ����롥
 *
 *	������Ф���CPU��å��ե饰�����åȤ���Ƥ���֤ϡ�
 *	 ����IPM�򡤥����ͥ�������Τ�Τ�������٤Ƥγ�����׵��ޥ���
 *	 ����������(TIPM_LOCK)
 *	 ������ǥ��γ����ͥ���٥ޥ���
 *	�Σ��Ĥ��⡢�⤤�������ꤹ�롥���δ֤Υ�ǥ��γ����ͥ���٥ޥ���
 *	�ϡ����Τ�����ѿ�(saved_iipm, ����ɽ�����ݻ�)���Ѱդ����ݻ����롥
 *	����������ƥ����ȤǤϡ�CPU��å����ְʳ��Ǥϡ�saved_iipm�Ͼ��IPM
 *	��Ʊ���ͤˤʤ�褦�ˤ��롥
 */

/*
 *	�ץ��å����ֻ��Ȥκݤ��������ȸ����
 *	���ޥ���ץ��å��Ǥϡ��ץ��å����ֻ��Ȥκݤ˥ޥ����졼������
 *	����θ���ơ�CPU��å������ˤ���ɬ�פ����롣
 *	
 *����Ʊ���ѥ��������ˤ˸���뤿�ᡢ�������ȸ�����򥤥�饤��ؿ�
 *	��pre_lock()��post_lock()�Ȥ��ơ��ޤȤ᤿��
 *	
 *	��������ˡ
 *	����uint32_t iimp = pre_lock():
 *	�������󥰥�ץ��å������ν���
 *	����post_lock();
 *	
 */

/*
 *	�ץ��å����ֻ��Ȥκݤ�������
 */
Inline uint32_t
pre_lock(void)
{
	uint32_t sr, iipm;
	/*
	 *	�ޥ����졼�������θ���ơ�CPU��å������ˤ��롣
	 */
	sr = current_sr();
	iipm = sr & 0xF0U;
#ifndef TOPPERS_SUPPORT_NONKERNEL_INT
						/*  �����ͥ�������γ���ߤ򥵥ݡ��Ȥ��ʤ����  */
	set_sr(sr | 0xF0U);		/*  ������߶ػ�  */
#else /* TOPPERS_SUPPORT_NONKERNEL_INT */
						/*  �����ͥ�������γ���ߤ򥵥ݡ��Ȥ�����  */
	/*
	 *  ���������ͥ��������߶ػߤǤʤ���С�
	 *  �����ͥ��������ߤΤߡ��ػߤ��롣
	 */
	if (IIPM_LOCK > iipm) {
		set_iipm(IIPM_LOCK);
	}
#endif /* TOPPERS_SUPPORT_NONKERNEL_INT */
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
	return(iipm);
}


/*
 *	�ץ��å����ֻ��Ȥκݤθ����
 */
Inline void
post_lock(uint32_t iipm)
{
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
	set_iipm(iipm);		/*  ����CPU��å����֤��᤹��  */
}


/*
 *	����ƥ����Ȥλ���
 *
 *	SH2A-DUAL�Ǥϡ�����ƥ����Ȥ�Ƚ��˳����/CPU�㳰�Υͥ��Ȳ������Ѥ���
 *	
 */
Inline bool_t
sense_context(void)
{
	uint32_t iipm;
	PCB *my_p_pcb;
	bool_t ret;
	
	iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	if ((my_p_pcb->target_pcb.excnest_count) != 0U) {
		ret = true;			/*  �󥿥�������ƥ�����  */
	} else {
		ret = false;		/*  ����������ƥ�����  */
	}
	post_lock(iipm);		/*  ����CPU��å����֤��᤹��  */

	return(ret);
}

/*
 *	CPU��å����֤ؤΰܹ�
 *
 *	IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�saved_iipm����¸��������
 *	�ͥ�������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������͡�TIPM_LOCK�ˤ���
 *	�ꤹ�롥�ޤ���lock_flag��true�ˤ��롥
 *
 *	IPM�����ǽ餫��TIPM_LOCK��Ʊ����������⤤���ˤϡ������
 *	saved_iipm����¸����Τߤǡ�TIPM_LOCK�ˤ����ꤷ�ʤ�������ϡ���ǥ�
 *	��γ����ͥ���٥ޥ�������TIPM_LOCK��Ʊ����������⤤��٥������
 *	����Ƥ�����֤ˤ����롥
 *
 *	���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǸƤФ�뤳�Ȥ�
 *	�ʤ���Τ����ꤷ�Ƥ��롥
 */
Inline void
x_lock_cpu(void)
{
	uint32_t iipm;
	PCB *my_p_pcb;

	/*
	 *	pre_lock()���֤��ͤ�ľ��saved_iipm����¸����������ѿ�iipm��
	 *	�Ѥ��Ƥ���Τϡ��ʲ�����ͳ�ˤ�롣
	 *	
	 *	�������󥰥�ץ��å���Ʊ����ͳ
	 *	��pre_lock()��Ƥ��ľ��˳���ߤ�ȯ��������ư���줿����߽���
	 *	����PCB���saved_iipm���ѹ�������ǽ�������뤿��
	 *	�����ޥ���ץ��å���ͭ����ͳ
	 *	��pre_lock()������Ǥʤ��ȡ�my_p_pcb�˥��������Ǥ��ʤ���
	 *	����pre_lock()������ͤ���¸���Ƥ���ɬ�פ����롣��
	 */
	iipm = pre_lock();	/*  �׸�Ƥ���������Ū�Ȱ㤦������ˡ  */

	my_p_pcb = get_my_p_pcb();
	my_p_pcb->target_pcb.saved_iipm = iipm;
	my_p_pcb->target_pcb.lock_flag = true;
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
}

#define t_lock_cpu()	x_lock_cpu()
#define i_lock_cpu()	x_lock_cpu()

/*
 *	CPU��å����֤β��
 *
 *	lock_flag��false�ˤ���IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�
 *	saved_iipm����¸�����ͤ��᤹��
 *
 *	���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǤΤ߸ƤФ���
 *	�Τ����ꤷ�Ƥ��롥
 */
Inline void
x_unlock_cpu(void)
{
	PCB *my_p_pcb;
	uint32_t saved_iipm;

	my_p_pcb = get_my_p_pcb();
	my_p_pcb->target_pcb.lock_flag = false;
	saved_iipm = my_p_pcb->target_pcb.saved_iipm;

	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
	set_iipm_with_nop(saved_iipm);
}

#define t_unlock_cpu()	  x_unlock_cpu()
#define i_unlock_cpu()	  x_unlock_cpu()

/*
 *	CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
	uint32_t iipm;
	PCB *my_p_pcb;
	bool_t lock_flag;

	iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	lock_flag = my_p_pcb->target_pcb.lock_flag;
	post_lock(iipm);		/*  ����CPU��å����֤��᤹��  */

	return(lock_flag);
}

#define t_sense_lock()	  x_sense_lock()
#define i_sense_lock()	  x_sense_lock()

/*
 *  ����������ƥ����� ���� CPU��å�������֤ʤ� true
 *  
 *  (!sense_context() && !t_sense_lock())�Ǥ�Ƚ��Ǥ��뤬
 *  ����߶ػߡ����ĤΥ����С��إåɤ򸺤餹���ᡢ
 *  ���ĤˤޤȤ�Ƥ��롣
 */
Inline bool_t
sense_tskctx_unl(void)
{
	uint32_t iipm;
	PCB *my_p_pcb;
	bool_t ret;

	iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	/*
	 *  CPU��å���֤�û�����뤿�ᡢ
	 *  ����ifʸ�Υ��å���CPU��å���֤γ��˰�ư���뤳�Ȥ�
	 *  ��Ƥ���������󥿥�������ƥ����Ȥξ���lock_flag��
	 *  �ɤ߽Ф�ɬ�פ����ꡢ��Ψ���������ᡢ���ΤޤޤȤ��Ƥ��롣
	 */
	if ((my_p_pcb->target_pcb.excnest_count == 0)	/*  ����������ƥ�����  */
		&& !(my_p_pcb->target_pcb.lock_flag)) {		/*  CPU��å��������  */
		ret = true;
	} else {
		ret = false;
	}
	post_lock(iipm);		/*  ����CPU��å����֤��᤹��  */

	return(ret);
}

/*
 *  �󥿥�������ƥ����� ���� CPU��å�������֤ʤ� true
 *  
 *  (sense_context() && !i_sense_lock())�Ǥ�Ƚ��Ǥ��뤬
 *  ����߶ػߡ����ĤΥ����С��إåɤ򸺤餹���ᡢ
 *  ���ĤˤޤȤ�Ƥ��롣
 */
Inline bool_t
sense_intctx_unl(void)
{
	uint32_t iipm;
	PCB *my_p_pcb;
	bool_t ret;

	iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	/*
	 *  CPU��å���֤�û�����뤿�ᡢ
	 *  ����ifʸ�Υ��å���CPU��å���֤γ��˰�ư���뤳�Ȥ�
	 *  ��Ƥ������������������ƥ����Ȥξ���lock_flag��
	 *  �ɤ߽Ф�ɬ�פ����ꡢ��Ψ���������ᡢ���ΤޤޤȤ��Ƥ��롣
	 */
	if ((my_p_pcb->target_pcb.excnest_count != 0)	/*  �󥿥�������ƥ�����  */
		&& !(my_p_pcb->target_pcb.lock_flag)) {		/*  CPU��å��������  */
		ret = true;
	} else {
		ret = false;
	}
	post_lock(iipm);		/*  ����CPU��å����֤��᤹��  */

	return(ret);
}


/*
 *	chg_ipm��ͭ���ʳ����ͥ���٤��ϰϤ�Ƚ��
 *
 *	TMIN_INTPRI���ͤˤ�餺��chg_ipm�Ǥϡ�-15��TIPM_ENAALL�ʡ�0�ˤ��ϰ�
 *	������Ǥ��뤳�ȤȤ���ʥ������å�����γ�ĥ�ˡ�
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				((-15 <= (intpri)) && ((intpri) <= TIPM_ENAALL))

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ���������
 *
 *	CPU��å��ե饰�����ꥢ����Ƥ�����ϡ��ϡ��ɥ������γ����ͥ���٥�
 *	���������ꤹ�롥
 *	
 *	CPU��å��ե饰�����åȤ���Ƥ�����ϡ��ϡ��ɥ������γ����ͥ���٥�
 *	���������ꤷ�褦�Ȥ����ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����TIPM_LOCK
 *	�ι⤤�������ꤹ�롥
 *
 */
Inline void
x_set_ipm(PRI intpri)
{
	PCB *my_p_pcb;
	uint32_t saved_iipm;
	uint32_t iipm = INT_IPM(intpri);

	saved_iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	
	if (!(my_p_pcb->target_pcb.lock_flag)) {
		/*  ����CPU��å��������  */
		set_iipm(iipm);
	}
	else {
		/*
		 *	����CPU��å����֤ʤΤǡ������ͥ�����γ���ߤ�����ʤ���
		 *	��target_pcb.saved_iipm��������������ʤ�����
		 */
		my_p_pcb->target_pcb.saved_iipm = iipm;
#ifndef TOPPERS_SUPPORT_NONKERNEL_INT
						/*  �����ͥ�������γ���ߤ򥵥ݡ��Ȥ��ʤ����  */
		/*
		 *	���λ����ǥϡ��ɥ������γ����ͥ���٥ޥ�����ɬ��15��
		 *	���ꤵ��Ƥ��뤿�ᡤ���ꤷľ��ɬ�פ��ʤ���
		 */
#else /* TOPPERS_SUPPORT_NONKERNEL_INT */
						/*  �����ͥ�������γ���ߤ򥵥ݡ��Ȥ�����  */
		set_iipm((iipm > IIPM_LOCK) ? iipm : IIPM_LOCK);
#endif /* TOPPERS_SUPPORT_NONKERNEL_INT */
	}
	/* IPM��񤭴���������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
}

#define t_set_ipm(intpri)	 x_set_ipm(intpri)
#define i_set_ipm(intpri)	 x_set_ipm(intpri)

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ����λ���
 *
 *	CPU��å��ե饰�����ꥢ����Ƥ�����ϥϡ��ɥ������γ����ͥ���٥�
 *	�����򡤥��åȤ���Ƥ������PCB���saved_iipm�򻲾Ȥ��롥
 */
Inline PRI
x_get_ipm(void)
{
	PCB *my_p_pcb;
	uint32_t saved_iipm;
	uint32_t iipm;

	saved_iipm = pre_lock();		/*  CPU��å�����  */
	my_p_pcb = get_my_p_pcb();
	if (!(my_p_pcb->target_pcb.lock_flag)) {
		/*  ����CPU��å��������  */
		iipm = saved_iipm;
	}
	else {
		/*  ����CPU��å�����  */
		iipm = my_p_pcb->target_pcb.saved_iipm;
	}
	post_lock(saved_iipm);			/*  ����CPU��å����֤��᤹��  */
	return(EXT_IPM(iipm));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 *	�ǹ�ͥ���̥������ؤΥǥ����ѥå���prc_support.S��
 *
 *	dispatch�ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ������������
 *	��ƤӽФ��٤���Τǡ�
 *	 ������������ƥ�����
 *	 ��CPU��å�����
 *	 ���ǥ����ѥå����ľ���
 *	 ���ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
 *	�ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void dispatch(void);

/*
 *  ���������Υޥ����졼������prc_support.S��
 */
extern void dispatch_and_migrate(ID prcid);

/*
 *  ���ߤΥ���ƥ����Ȥ�Τƥޥ����졼������prc_support.S��
 */
extern void exit_and_migrate(ID prcid);

/*
 *	�ǥ����ѥå����ư��ϡ�prc_support.S��
 *
 *	start_dispatch�ϡ������ͥ뵯ư���˸ƤӽФ��٤���Τǡ����٤Ƥγ��
 *	�ߤ�ػߤ������֡�������ߥ�å����֤�Ʊ���ξ��֡ˤǸƤӽФ��ʤ����
 *	�ʤ�ʤ���
 */
extern void start_dispatch(void) NoReturn;

/*
 *	���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���prc_support.S��
 *
 *	exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�
 *	 ������������ƥ�����
 *	 ��CPU��å�����
 *	 ���ǥ����ѥå����ľ���
 *	 ���ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
 *	�ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *	�����ͥ�ν�λ�����θƽФ���prc_support.S��
 *
 *	call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *	����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *	����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *	����������ƥ����Ȥν����
 *
 *	���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥���λ���
 *	�ǥ����å��ΰ��ȤäƤϤʤ�ʤ���
 *
 *	activate_context�򡤥���饤��ؿ��ǤϤʤ��ޥ�������Ȥ��Ƥ���Τϡ�
 *	���λ����Ǥ�TCB���������Ƥ��ʤ�����Ǥ��롥
 */
extern void    start_r(void);

#define activate_context(p_tcb) 										\
do {																	\
	(p_tcb)->tskctxb.sp = (p_tcb)->p_tinib->tskinictxb.stk_bottom;		\
	(p_tcb)->tskctxb.pc = (FP)start_r;									\
} while(false)

/*
 *	calltex�ϻ��Ѥ��ʤ�
 */
#define OMIT_CALLTEX

/*
 * �������å����¸���˴ޤޤ��ɸ����㳰������ǽ�ν�����������Ѥ��ʤ�
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 * CPU�㳰�ϥ�ɥ�ν����
 * �����ޥ���ˤ���������asp/kernel/exception.h�ǥץ�ȥ��������
 * ������Ƥ��뤿�ᡢ�ؿ��Ȥ���������ʤ���Фʤ�ʤ���
 */
extern void initialize_exception(void);

/*
 *	SH2A-DUAL�γ���ߥ������ƥ�����ȳ���߽�����ǥ�μ¸�
 */

/*
 *	�����ͥ����
 *
 *	�Ƴ���ߤγ����ͥ���٤ϳ����ͥ���٥�����쥸����(IPRXX)�ˤ��
 *	�����ꤹ�롥���Τ��ᡤ�Ƴ�����׵�饤����ˤɤγ����ͥ���٥���
 *	��쥸�����ΤɤΥե�����ɤ��б����Ƥ��뤫�ξ����IPR_INFO���ˤ�
 *	�ơ��֥�ipr_info_tbl[]���Ѱդ��롥
 *	������ֹ��Ϣ³���Ƥ��ʤ����ᡤ���ݡ��Ȥ��Ƥ��ʤ��ֹ�ˤϡ�
 *	address����ȥ��0�����ꤷ������ˤ�������ֹ����������Ƚ�̤Ǥ�
 *	�롣
 *	�ʥ��ݡ��Ȥ��������ֹ�ϥ��ץꥱ�������ˤ�餺���ץ��å���
 *	�ϡ��ɥ��������ͤˤ�äƷ�ޤ�Τǡ�����ǡ����Ȥ����ݻ����롣��
 *	���Υơ��֥�Υ���ǥå����ˤϡ�������ֹ������ɽ�����Ѥ��롣
 */

/*
 *	�Ƴ�����ֹ�������ꤹ��IPR�ξ�������Τ���ι�¤��
 *	
 *	�����ݡ��Ȥ��ʤ�������ֹ�ξ��ϡ�address����ȥ��0�����ꤹ�롣
 *	
 *	������offset��8�ӥåȤ���н�ʬ��������������ͳ��32�ӥåȤˤ���
 *	�����롣
 *	���������ι�¤�Τ�����ˤ���ȷ�֤��Ǥ�������ǡ�����������
 *	�������ʤ�ʤ���
 *	������SH�Ǥ�32�ӥåȥǡ����Ǥʤ���̵�̤�̿�᤬��������롣
 */
typedef struct {
	/* �����ͥ���٥�����쥸�����Υ��ɥ쥹 */
	uint32_t address;
	/* ���ե��å� */
	uint32_t  offset;
} IPR_INFO;

/*
 *	�Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 */
extern const IPR_INFO ipr_info_tbl[TNUM_INT];

/*
 *	������ֹ桦����ߥϥ�ɥ��ֹ�
 *
 *	����ߥϥ�ɥ��ֹ�(inhno)�ȳ�����ֹ�(intno)�ϡ��٥����ֹ���Ѥ��롥
 *
 *	�٥����ֹ��TMIN_INTNO(=64)����Ϥޤ뤿�ᡤ���Τޤޤ��ͤ�ͥ���ٴ�
 *	�����Υơ��֥�Υ���ǥå������Ѥ���ȡ�̵�̤��ΰ褬ȯ�����롥
 *	���Τ��ᡤ�����ͥ������Ǥϡ�TMIN_INTNO�򺹤��������͡�����ɽ����
 *	���Ѥ��롥
 *
 *	����ɽ����̾���ϡ�iintno,iinhno�Ȥ��롥
 */

/*
 * ����ߥϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
											/* ����ɽ������ɽ���� */
#define EXT_INHNO(iintno) (CAST(uint32_t, (iinhno) + TMIN_INHNO))
											/* ����ɽ��������ɽ���� */
#define INT_INHNO(intno)  (CAST(uint32_t, (inhno) - TMIN_INHNO))

/*
 * ������ֹ������������ɽ������Ѵ�
 */
											/* ����ɽ������ɽ���� */
#define EXT_INTNO(iintno)	(CAST(uint32_t, (iintno) + TMIN_INTNO))
											/* ����ɽ��������ɽ���� */
#define INT_INTNO(intno)	(CAST(uint32_t, (intno) - TMIN_INTNO))


/*
 *	������ֹ���ϰϤ�Ƚ��
 *	
 *	TMIN_INTNO��TMAX_INTNO���ϰϤǤ��äƤ�ͭ�����ֹ�Ǥʤ���礬���뤿
 *	�ᡤipr_info_tbl[]��ͭ�����ֹ椫������å�����
 */

/*  ������ֹ椫��ץ��å�ID����Ф��ޥ���  */
#define PRCID_IN_INTNO(intno)	((intno) & ~LOCAL_INTNO_MASK)

/*  ����դ���ǽ�ץ��å��Υ����å� �׸�Ƥ���ץ��å�����¸ */
#define VALID_AFFINITY_MASK(intno)							\
		(PRCID_IN_INTNO(intno) <= 0x20000U)					\
		&& (PRCID_IN_INTNO(intno) != 0x0U)
		/*  ���եȥ�����Ū�˥�����IRC�����ꤷ�Ƥ���  */

/*  IRQ�ޤ�����¢���ե⥸�塼��γ�����ֹ��Ƚ��  */
#define VALID_LOCAL_INTNO_IRQ_OR_PERIPHERAL(local_intno)	\
		((TMIN_INTNO <= (local_intno)) 						\
		&& ((local_intno) <= TMAX_INTNO) 					\
		&& (ipr_info_tbl[INT_INTNO(local_intno)].address != 0U))

/*  �ץ��å��ֳ���ߤγ�����ֹ��Ƚ��  */
#define VALID_LOCAL_INTNO_IPI(local_intno) 					\
		LOCAL_INTNO_IS_IPI(local_intno)

#define VALID_LOCAL_INTNO(local_intno) 					\
		(VALID_LOCAL_INTNO_IRQ_OR_PERIPHERAL(local_intno)	\
		 || VALID_LOCAL_INTNO_IPI(local_intno))

#define VALID_INTNO(intno) 									\
		(VALID_AFFINITY_MASK(intno) && VALID_LOCAL_INTNO(LOCAL_INTNO(intno)))

/*  �׸�Ƥ��prcid���Ѥ���Ƚ���Ԥ���  */
#define VALID_INTNO_DISINT(prcid, intno)	VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(prcid, intno)	VALID_INTNO(intno)

/*
 *	CPU�㳰�ϥ�ɥ��ֹ�
 *
 *	CPU�㳰�ϥ�ɥ��ֹ�Ȥ��Ƥϡ��٥����ֹ���Ѥ��롥
 *	���ݡ��Ȥ���CPU�㳰�ϥ�ɥ���ϥץ��å��η�����˰ۤʤ�Τǡ��ץ�
 *	���å��η����������ե������������롥
 *	
 *	TMIN_EXCNO��TMAX_EXCNO���ϰϤǤ��äƤ�ͭ�����ֹ�Ǥʤ���礬���뤬��
 *	�����å����ά���Ƥ��롣
 *
 */
#define VALID_LOCAL_EXCNO_DEFEXC(local_excno) \
		((TMIN_EXCNO <= (local_excno)) && ((local_excno) <= TMAX_EXCNO))
#define VALID_EXCNO_DEFEXC(excno) 	\
		(VALID_AFFINITY_MASK(excno)	\
		&& VALID_LOCAL_EXCNO_DEFEXC(LOCAL_EXCNO(excno)))

/*
 *	����ߥϥ�ɥ������
 *
 *	����ߥϥ�ɥ��ֹ�inhno�γ���ߥϥ�ɥ�ε�ư����int_entry��
 *	���ꤹ�롥
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{
#ifndef NDEBUG
	uint_t prcid_in_inhno = inhno >> 16U;
	uint_t bitptn = 1U << (prcid_in_inhno - 1U);

	assert((bitptn & affinity_mask) != 0);
#endif /* NDEBUG */
}

/*
 *	����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INT_ENTRY(inhno, inthdr)	 _kernel_##inthdr##_##inhno
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)					\
		extern void _kernel_##inthdr##_##inhno(void);

/*
 *	������׵�ػߥե饰
 *
 *	SH2A-DUAL��IRC�ϳ�����׵�ػߥե饰������ʤ�������ߤ���̤˶ػߤ���
 *	���ϡ������ͥ���٥�����쥸����(IPRXX)��0�����ꤹ��ɬ�פ����롥
 *	�����ͥ���٥�����쥸������0�ˤ��뤳�Ȥǳ�����׵�ػߥե饰��
 *	�¸�����ȡ����δ֡���ǥ��γ����ͥ���٤򵭲����Ƥ����ΰ褬ɬ��
 *	�Ȥʤ롥����ե�����졼���Ǥ��Τ����uint8_t���Υơ��֥�
 *	int_iipm_tbl[]���Ѱդ��롥
 *	�����ͥ���٤����ꤵ��Ƥ��뤫�ɤ����ϥӥå�7���ݻ����롣
 *	�ʥ��ץꥱ�������˰�¸���������
 *	
 *	�ӥåȳ�����Ƥ������ͥ���٤γ���ɽ���Ȥ�����ɽ���Ȥ�ۤʤ�Τǡ�
 *	��դ��뤳�ȡ�������ȿž���Ƥ��뤬���ӥåȥ��եȤ��Ƥ��ʤ�����
 *	
 *	�ơ��֥�int_iipm_tbl[][]�˳�Ǽ�����ͤΥӥåȳ�����ơ�
 *	�������ӥå�0��3��IPRXX�����ꤹ��ӥåȥѥ�����
 *	�������������������ʳ����ͥ���٥��
 *	�������ӥå�7��NOT_CFG_INT_BIT
 *	����������������0:CFG_INT�ǳ����ͥ���٤����ꤵ��Ƥ��롣
 *	����������������1:CFG_INT�ǳ����ͥ���٤����ꤵ��Ƥ��ʤ���
 */
extern const uint8_t int_iipm_tbl[TNUM_PRCID][TNUM_INT];

/*	CFG_INT�ǳ����ͥ���٤����ꤵ��Ƥ��ʤ����Ȥ򼨤��ӥå�  */
#define NOT_CFG_INT_BIT		0x80U

/*
 * �����ͥ���٥�����쥸����������
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint32_t val��IPR�쥸���������ꤹ����
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 */
Inline void
irc_set_ipr(INTNO local_intno, uint32_t val, uint_t prcindex)
{
	uint32_t ipr_val;
	uint32_t iintno  	= INT_INTNO(local_intno);
	uint32_t address 	= ipr_info_tbl[iintno].address;
	uint32_t offset  	= ipr_info_tbl[iintno].offset;

   	/*	prcindex=1�ξ���IPR�Υ��ɥ쥹�˥��ե��å�0x100��ä���  */
   	/*	���׸�Ƥ���ץ��å����˰�¸  */
	if (prcindex != 0) {
		address += PRC_IPR_OFFSET;
	}
	ipr_val = sil_reh_reg((uint16_t *)address);
	ipr_val &= ~(0x0FU << offset);
	ipr_val |= (val << offset);
	sil_wrh_reg((uint16_t *)address, ipr_val);
}

/*
 *	������׵�ػߥե饰�Υ��å�
 *
 *	������װ���˳���߶ػߤ���ˡ���ۤʤ롣
 *
 *	IRQ�����
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	��0�����ꤹ�롥
 *
 *	��¢���ե⥸�塼��
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥯥ꥢ���롣
 *
 *	PINT�����
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥯥ꥢ���롣
 *
 *	�ץ��å��ֳ����
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥯥ꥢ���롣
 *
 *	�׸�Ƥ
 *	������Ū�ˤϡ��ޥ�������sh2a_dual_config.h�˰�ư���롣
 */

/*
 *	IRQ����ߤζػ�
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	��0�����ꤹ�롥
 */
Inline void
x_disable_int_irq(INTNO local_intno, uint_t prcindex)
{
	/*
	 *	������ֹ���б�����IPR���ͤ�0�ˤ��롥
	 */
	irc_set_ipr(local_intno, 0x00, prcindex);
}

/*
 *	��¢���ե⥸�塼�����ߤζػ�
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥯥ꥢ���롣
 */
Inline void
x_disable_int_peripheral(INTNO local_intno, uint_t prcindex)
{
	int_t index 		= LOCAL_INTNO_TO_IDCNT(local_intno);
	uint16_t *p_idcnt_h = idcnt_tbl_h[index];
	
	sil_anh_reg(p_idcnt_h, ~IDCNT_INTEN);
}
	
/*
 *	PINT����ߤζػ�
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥯥ꥢ���롣
 */
Inline void
x_disable_int_pint(INTNO local_intno, uint_t prcindex)
{
	uint_t pintno 		 = LOCAL_INTNO_TO_PINTNO(local_intno);
	uint16_t *p_pinter_h = irc_reg_tbl[prcindex].pinter_h;
	
	sil_clrh_bit(p_pinter_h, pintno);
}

/*
 *	�ץ��å��ֳ���ߤζػ�
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥯥ꥢ���롣
 */
Inline void
x_disable_int_ip(INTNO local_intno, uint_t prcindex)
{
	uint_t intlevel		= LOCAL_INTNO_TO_IP_INT_LEVEL(local_intno);
	uint16_t *p_iper_h 	= irc_reg_tbl[prcindex].iper_h;
	
	sil_clrh_bit(p_iper_h, intlevel);
}

/*
 *	������׵�ػߥե饰�Υ��å�
 *
 *	�����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *	�ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 *
 *	������װ���˳���߶ػߤ���ˡ���ۤʤ롣
 *
 *	IRQ�����
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	��0�����ꤹ�롥
 *
 *	��¢���ե⥸�塼��
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥯥ꥢ���롣
 *
 *	PINT�����
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥯥ꥢ���롣
 *
 *	�ץ��å��ֳ����
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥯥ꥢ���롣
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	INTNO iintno;
	uint32_t iipm;
	INTNO local_intno  	= LOCAL_INTNO(intno);
	uint_t prcindex		= x_prc_index();

	/*
	 *	�ץ��å��ֳ���ߤξ��
	 *	�������ͥ���٥뤬����ǥơ��֥�int_iipm_tbl�˴ޤޤ�ʤ��Τǡ�
	 *	��¾�γ�����װ������˥����å����롣
	 */
	if (LOCAL_INTNO_IS_IPI(local_intno)) {
		x_disable_int_ip(local_intno, prcindex);
		return(true);
	}

	iintno = INT_INTNO(local_intno);
	iipm = int_iipm_tbl[prcindex][iintno];

	/*
	 *	�����°�������ꤵ��Ƥ��ʤ����
	 */
	if ((iipm & NOT_CFG_INT_BIT) != 0) {
		return(false);
	}
	
	/*
	 *	�Ĥ�γ�����װ���˽����򿶤�ʬ���롣
	 */
	if (LOCAL_INTNO_IS_IRQ(local_intno)) {
		/*	IRQ�ξ��  */
		x_disable_int_irq(local_intno, prcindex);
	}
	else if (LOCAL_INTNO_IS_PERIPHERAL(local_intno)) {
		/*	��¢���ե⥸�塼��ξ��  */
		x_disable_int_peripheral(local_intno, prcindex);
	}
	else if (LOCAL_INTNO_IS_PINT(local_intno)) {
		/*	PINT����ߤξ��  */
		x_disable_int_pint(local_intno, prcindex);
	}
	else {
		return(false);
	}

	return(true);
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *	������׵�ػߥե饰�β��
 *
 *	������װ���˳���ߵ��Ĥ���ˡ���ۤʤ롣
 *
 *	IRQ�����
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	���ͤ򸵤��᤹��
 *
 *	��¢���ե⥸�塼��
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥻥åȤ��롣
 *
 *	PINT�����
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥻥åȤ��롣
 *
 *	�ץ��å��ֳ����
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥻥åȤ��롣
 *
 *	�׸�Ƥ
 *	������Ū�ˤϡ��ޥ�������sh2a_dual_config.h�˰�ư���롣
 */

/*
 *	IRQ����ߤε���
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *	 uint32_t ipr_val��IPRx�쥸���������ꤹ����
 *
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	���ͤ򸵤��᤹��
 */
Inline void
x_enable_int_irq(INTNO local_intno, uint_t prcindex, uint32_t ipr_val)
{
	/*
	 *	������ֹ���б�����IPR���ͤ�ipr_val�ˤ��롥
	 */
	irc_set_ipr(local_intno, ipr_val, prcindex);
}

/*
 *	��¢���ե⥸�塼�����ߤε���
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥻥åȤ��롣
 */
Inline void
x_enable_int_peripheral(INTNO local_intno, uint_t prcindex)
{
	int_t index 		= LOCAL_INTNO_TO_IDCNT(local_intno);
	uint16_t *p_idcnt_h	= idcnt_tbl_h[index];
	
	sil_orh_reg(p_idcnt_h, IDCNT_INTEN);
}
	
/*
 *	PINT����ߤε���
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥻥åȤ��롣
 */
Inline void
x_enable_int_pint(INTNO local_intno, uint_t prcindex)
{
	uint_t pintno 		 = LOCAL_INTNO_TO_PINTNO(local_intno);
	uint16_t *p_pinter_h = irc_reg_tbl[prcindex].pinter_h;
	
	sil_seth_bit(p_pinter_h, pintno);
}

/*
 *	�ץ��å��ֳ���ߤε���
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 *
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥻥åȤ��롣
 */
Inline void
x_enable_int_ip(INTNO local_intno, uint_t prcindex)
{
	uint_t intlevel		= LOCAL_INTNO_TO_IP_INT_LEVEL(local_intno);
	uint16_t *p_iper_h 	= irc_reg_tbl[prcindex].iper_h;
	
	sil_seth_bit(p_iper_h, intlevel);
}

/*
 *	������׵�ػߥե饰�β��
 *
 *	�����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *	�ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 *
 *	������װ���˳���ߵ��Ĥ���ˡ���ۤʤ롣
 *
 *	IRQ�����
 *	������߶ػߥե饰���ʤ����ᡢ�����ͥ���٥�����쥸����(IPRx)��
 *	���ͤ򸵤��᤹��
 *
 *	��¢���ե⥸�塼��
 *	��IDCNTn�쥸������INTEN�ӥåȤ򥻥åȤ��롣
 *
 *	PINT�����
 *	��CnPINTER�쥸������PINTnE�ӥåȤ򥻥åȤ��롣
 *
 *	�ץ��å��ֳ����
 *	��CnIPER�쥸������CIPEn�ӥåȤ򥻥åȤ��롣
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	INTNO iintno;
	uint32_t iipm;
	INTNO local_intno  	= LOCAL_INTNO(intno);
	uint_t prcindex		= x_prc_index();

	/*
	 *	�ץ��å��ֳ���ߤξ��
	 *	�������ͥ���٥뤬����ǥơ��֥�int_iipm_tbl�˴ޤޤ�ʤ��Τǡ�
	 *	��¾�γ�����װ������˥����å����롣
	 */
	if (LOCAL_INTNO_IS_IPI(local_intno)) {
		x_enable_int_ip(local_intno, prcindex);
		return(true);
	}

	iintno = INT_INTNO(local_intno);
	iipm = int_iipm_tbl[prcindex][iintno];

	/*
	 *	�����°�������ꤵ��Ƥ��ʤ����
	 */
	if ((iipm & NOT_CFG_INT_BIT) != 0) {
		return(false);
	}
	
	/*
	 *	�Ĥ�γ�����װ���˽����򿶤�ʬ���롣
	 */
	if (LOCAL_INTNO_IS_IRQ(local_intno)) {
		/*	IRQ�ξ��  */
		x_enable_int_irq(local_intno, prcindex, iipm);
	}
	else if (LOCAL_INTNO_IS_PERIPHERAL(local_intno)) {
		/*	��¢���ե⥸�塼��ξ��  */
		x_enable_int_peripheral(local_intno, prcindex);
	}
	else if (LOCAL_INTNO_IS_PINT(local_intno)) {
		/*	PINT����ߤξ��  */
		x_enable_int_pint(local_intno, prcindex);
	}
	else {
		return(false);
	}

	return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *	������׵�饤���°��������
 *
 *	SH2A-DUAL�Ǥϡ������ͥ�ǰ���������ͥ���٤�16�ʳ��Ǥ��뤿�ᡤintpri
 *	�Ȥ���Ϳ���뤳�Ȥ��Ǥ����ͤ�-15��-1��ɸ��Ǥ��롥
 *	
 *	SH2A-DUAL�γ���ߤϡ���¢���ե⥸�塼�����ߡ�IRQ����ߤ�ʬ��Ǥ�����
 *	�줾�찷�����ۤʤ롥���Τ��ᡤ������ֹ椫�顤�ɤγ���ߤ�ʬ�ह��
 *	����Υޥ���INTNO_IS_IRQ(intno)�򥳥���¸�����Ѱդ��롥
 *	����Ϥ��Υե������������٤�������������¸���Τ�shx_config.h���
 *	x_config_intatr()�ǻ��Ѥ��뤿�ᡢshx_config.h�˵��Ҥ��Ƥ��롣
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);

/*
 *	����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 *	��������ɬ�פ�IRC���i_begin_int()�ϡ�������¸�������
 */
Inline void
i_end_int(INTNO intno)
{
}
#endif /* TOPPERS_MACRO_ONLY */

/*
 *	CPU�㳰�ϥ�ɥ�ط�
 */

/*
 *	�㳰�ϥ�ɥ���� p_excinf ����Ƽ�������Ф�����Υޥ���
 */
#define P_EXCINF_OFFSET_VECTOR UINT_C( 0)
#define P_EXCINF_OFFSET_PR	   UINT_C( 1)
#define P_EXCINF_OFFSET_PC	   UINT_C(12)
#define P_EXCINF_OFFSET_SR	   UINT_C(13)

#define P_EXCINF_OFFSET_R0	   UINT_C( 4)

/*	CPU�㳰ȯ�����Υ����å��ݥ��󥿤��ͤ�p_excinf�κ�ʬ  */
#define P_EXCINF_OFFSET_SP	   (P_EXCINF_OFFSET_SR + 1)


#ifndef TOPPERS_MACRO_ONLY
/*
 *	CPU�㳰�ϥ�ɥ������
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{
	assert(VALID_EXCNO_DEFEXC(excno));
}

/*
 *	CPU�㳰�ϥ�ɥ�����������������ޥ���
 */
#define EXC_ENTRY(excno, exchdr)	 _kernel_##exchdr##_##excno
#define EXCHDR_ENTRY(excno, excno_num, exchdr)					\
		extern void _kernel_##exchdr##_##excno(void *sp);

/*
 *	CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 *
 *	CPU�㳰��ȯ���������Υ���ƥ����Ȥ�������������ƥ����Ȥλ���false��
 *	�����Ǥʤ�����true���֤���
 *	CPU�㳰�ϥ�ɥ餫��ƤФ�뤳�Ȥ����ꤷ�Ƥ���Τǡ������
 *	�ޥ����졼����󤵤�뤳�Ȥ����ꤷ�Ƥ��ʤ���
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	PCB *my_p_pcb = get_my_p_pcb();
	
	return(my_p_pcb->target_pcb.excnest_count > 1U);
}

/*
 *	CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ
 *	���ˤλ���
 *	CPU�㳰�ϥ�ɥ餫��ƤФ�뤳�Ȥ����ꤷ�Ƥ���Τǡ������
 *	�ޥ����졼����󤵤�뤳�Ȥ����ꤷ�Ƥ��ʤ���
 */
Inline uint32_t
exc_get_iipm(void *p_excinf)
{
	uint32_t *sp = (uint32_t *)p_excinf;
	uint32_t sr = *(sp + P_EXCINF_OFFSET_SR);
	uint32_t iimp = sr & 0x00F0U;
	return(iimp);
}

/*
 *	CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߤΥޥ������֤λ���
 *
 *	CPU�㳰��ȯ���������Υ����ƥ���֤���
 *	���������ͥ�¹���Ǥʤ���
 *	��������������ƥ����ȤǤ��ꡤ
 *	����������ߥ�å����֤Ǥʤ���
 *	����CPU��å����֤Ǥʤ���
 *	�����ʥ�ǥ��Ρ˳����ͥ���٥ޥ������������
 *	�Ǥ������true�������Ǥʤ�����false���֤���CPU�㳰�������ͥ������
 *	�γ���߽������ȯ���������ˤ�false���֤��ˡ�
 *
 *	SH2A-DUAL�Ǥϡ�CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥�
 *	�����ˤ����٤Ƥγ���ߤ���Ĥ�����֤Ǥ��뤳�Ȥ�����å����뤳�Ȥǡ�
 *	���������ͥ�¹���Ǥʤ����ȡ�
 *	����������ߥ�å����֤Ǥʤ����ȡ�
 *	����CPU��å����֤Ǥʤ����ȡ�
 *	�����ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ��뤳��
 *	��4�Ĥξ�������å����뤳�Ȥ��Ǥ����CPU�㳰��ȯ����������
 *	lock_flag�򻲾Ȥ���ɬ�פϤʤ��ˡ�
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	bool_t ret = false;
	
	if (!exc_sense_context(p_excinf)) {
		uint32_t iipm = exc_get_iipm(p_excinf);
		if (iipm == IIPM_ENAALL) {
			ret = true;
		}
	}
	
	return(ret);
}

/*
 * Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
extern void default_exc_handler(void *p_excinf);

/*
 * ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 * ��API��ɸ��Ū�ʤ�ΤȰۤʤ뤿�ᡢ�桼�������Ѱդ�����Τ�
 * ���֤���������ϡ��ץ�ȥ���������������롣
 */
#ifndef OMIT_DEFAULT_INT_HANDLER
extern void default_int_handler(INTNO intno);
#endif /* OMIT_DEFAULT_INT_HANDLER */

/*
 *	�ץ��å���¸�ν����
 */
extern void prc_initialize(void);

/*
 *	�ץ��å���¸�ν�λ������
 */
extern void prc_exit(void);

/*
 *  ��å��ط�
 */

/*  ��å����Ѥ��륻�ޥե��쥸����  */
#define SEMR_LOCK	SEMR1_b

/*
 *  ���㥤����ȥ�å��ν����
 */
Inline void
x_initialize_giant_lock(LOCK *p_giant_lock)
{
		/*
		 *	SEMR == 0 ��������
		 *	SEMR == 1 ������
		 */
	sil_wrb_reg((uint8_t *)SEMR_LOCK, SEMR_SEMF_BIT);
	*p_giant_lock = (uint8_t *)SEMR_LOCK;
}

/*
 *  Test & Set̿��
 *  ��true ��������
 *  ��false������
 */
Inline bool_t
test_and_set(uint8_t *p_semr_b)
{
	uint8_t semr = sil_reb_reg(p_semr_b);
	
	if (semr == 0) {
		return true;
	}
	return false;
}

/*
 *  ��å����������ؿ�
 *  ��x_lock_cpu()/x_unlock_cpu()��Ȥ����ᡤ����餬������줿���
 *  ��������롥 
 */

/*
 *  1���ܤΥ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_acquire_lock(LOCK *p_lock)
{
	uint8_t *p_semr_b = *p_lock;

	while (test_and_set(p_semr_b)) {
		x_unlock_cpu();
		x_lock_cpu();
	}

	/* ��������Ƥ��񤭴�����ǽ�������� */
	Asm("":::"memory");
}

#define t_acquire_lock(p_lock) x_acquire_lock(p_lock)
#define i_acquire_lock(p_lock) x_acquire_lock(p_lock)


/*
 *  ��å��β����ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_release_lock(LOCK *p_lock)
{
	/* ��������Ƥ��񤭴�����ǽ�������� */
	Asm("":::"memory");
	sil_wrb_reg(*p_lock, SEMR_SEMF_BIT);
}

/*
 *  ����ߤ���Ĥ��ʤ���å������ؿ�
 */
Inline void 
x_acquire_lock_without_preemption(LOCK *p_lock)
{
	uint8_t *p_semr = *p_lock;

	/*  ������δ֡��롼�פ򷫤��֤�  */
	while (test_and_set(p_semr));
	
	/* ��������Ƥ��񤭴�����ǽ�������� */
	Asm("":::"memory");
}


/*
 *  ���ԥ��å��ط�
 */

/*
 *  ���ԥ��å���ǽ������
 */
#define TTYPE_SPN NATIVE_SPN

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 *  ��-2���Ƥ���Τϡ���å�����SIL�ǻ��Ѥ���ʬ
 */
#define TMAX_NATIVE_SPN   (32 - 2)

/*
 *  ���ԥ��å��η�
 */
typedef uint8_t *SPNLOCK;

/*
 *  ���ԥ��å��ν����
 */
Inline void
x_initialize_spin(ID spnid, SPNLOCK *p_spn_lock)
{
	uint8_t *p_semr_b = semr_tbl_b[spnid + 2];
	
	*p_spn_lock = p_semr_b;
	sil_wrb_reg(p_semr_b, SEMR_SEMF_BIT);
}

/*
 *  ���ԥ��å��μ���
 */
Inline void
x_lock_spin(SPNLOCK *p_spn_lock)
{
	x_acquire_lock(p_spn_lock);
}

#define t_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)
#define i_lock_spin(p_spn_lock)  x_lock_spin(p_spn_lock)

/*
 *  ���ԥ��å��μ����λ��
 */
Inline bool_t
x_try_lock_spin(SPNLOCK *p_spn_lock)
{
	uint8_t *p_semr_b = *p_spn_lock;

	if (test_and_set(p_semr_b)) {
		/* ���� */
		return(true);
	}
	else {
		/* ���� */
		Asm("":::"memory");
		return(false);
	}
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
x_unlock_spin(SPNLOCK *p_spn_lock)
{
	x_release_lock(p_spn_lock);
}


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
