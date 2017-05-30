/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.h 540 2010-02-17 10:48:07Z ertl-honda $
 */


/*
 *		�ץ��å���¸�⥸�塼���SH4A�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

/*
 * �ץ��å��μ���
 */
#define SH4A

#ifdef FPU_ENABLE

/*
 *  FPSCR��PR�ӥåȤν����
 */
#ifdef FPU_DOUBLE
#define FPSCR_PR_INIT 0x00080000  /* ������ */
#else  /* FPU_SINGLE FPU_SINGLE_ONLY */
#define FPSCR_PR_INIT 0x0000000   /* ñ���� */
#endif /* FPU_DOUBLE */

/*
 *  FPSCR��PR�ӥåȰʳ�����������
 */
#ifndef FPSCR_INIT
#define FPSCR_INIT 0x00040000
#endif  /* FPSCR_INIT */

#endif /* FPU_ENABLE */

/*
 * ����ߥϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_INHNO(iintno) (CAST(uint16_t, (iinhno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INHNO(intno)  (CAST(uint16_t, (inhno) >> 5))  /* ����ɽ��������ɽ���� */

/*
 * ������ֹ������������ɽ������Ѵ�
 */
#define EXT_INTNO(iintno)   (CAST(uint16_t, (iintno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INTNO(intno)    (CAST(uint16_t, (intno) >> 5))  /* ����ɽ��������ɽ���� */

/*
 * ������֥�ǳ�����ֹ椫�� inh_tbl ���������Υޥ���
 * reg�ˤϡ�������ֹ���ݻ����Ƥ���
 * �쥸��������ꤹ�� 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_intno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */
     
/*
 * CPU�㳰�ϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_EXCNO 0x040U
#define TMAX_EXCNO 0x820U
#define TNUM_EXC   0x42U
     
/*
 * CPU�㳰�ϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_EXCNO(iexcno)  (CAST(uint16_t, (iexcno) << 5)) /* ����ɽ������ɽ���� */
#define INT_EXCNO(excno)   (CAST(uint16_t, (excno)  >> 5)) /* ����ɽ��������ɽ���� */

/*
 * ������֥��CPU�㳰�ֹ椫�� exch_tbl ���������Υޥ���
 * reg�ˤϡ�EXPEVT�쥸�������ͤ��ݻ����Ƥ���
 * �쥸��������ꤹ�� 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_excno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */

#ifndef TOPPERS_MACRO_ONLY
  
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ���ݡ��Ȥ��뵡ǽ�����
 */
#define SUPPORT_DIS_INT            /* dis_int�򥵥ݡ��Ȥ��� */
#define SUPPORT_ENA_INT            /* ena_int�򥵥ݡ��Ȥ��� */


/*
 *  ����å���⡼�ɤ�����
 *    P1(0x8..)              : �饤�ȥ��롼
 *    P0(0x0..),U0,P3(0x3..) : ���ԡ��Хå�
 */
#ifdef ENABLE_CACHE_WRITE_BACK

#ifdef ENABLE_CACHE_COHERENCE
#define CCR_MODE  UINT_C(0x00000101) /* ���ҡ����ͭ�����饤�ȥХå� */
#else  /* ENABLE_CACHE_COHERENCE */
#define CCR_MODE  UINT_C(0x00010101) /* ���ҡ����̵�����饤�ȥХå� */
#endif /* ENABLE_CACHE_COHERENCE */

#else /* ENABLE_CACHE_WRITE_BACK */

#ifdef ENABLE_CACHE_COHERENCE
#define CCR_MODE  UINT_C(0x00000103) /* ���ҡ����ͭ�����饤�ȥ��롼 */
#else  /* ENABLE_CACHE_COHERENCE */
#define CCR_MODE  UINT_C(0x00010103) /* ���ҡ����̵�����饤�ȥ��롼 */
#endif /* ENABLE_CACHE_COHERENCE */

#endif /* ENABLE_CACHE_WRITE_BACK */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#include "prc_insn.h"

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

/* CPU�ֳ�����ѥ쥸����  */
static const uint_t int_ici_tbl[TNUM_PRCID] = {
	C0INTICI,
#if TNUM_PRCID >= 2 
	C1INTICI,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	C2INTICI,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	C3INTICI,
#endif /* TNUM_PRCID >= 4 */
};

static const uint_t int_ici_clr_tbl[TNUM_PRCID] = {
	C0INTICICLR,
#if TNUM_PRCID >= 2
	C1INTICICLR,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	C2INTICICLR,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	C3INTICICLR,
#endif /* TNUM_PRCID >= 4 */
};

Inline void
ici_int(uint_t prcindex)
{
	sil_wrw_mem((void *)int_ici_tbl[prcindex], (1 << (prcindex<<2)));
}

Inline void
ici_int_clr(void)
{
	uint_t prcindex = x_prc_index();

	sil_wrw_mem((void *)int_ici_clr_tbl[prcindex],
				sil_rew_mem((void *)int_ici_tbl[prcindex]));
}

/*
 *  �󥿥�������ƥ������ѤΥ����å������
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char *)(istk) + (istksz)))

/*
 *  ������ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INTNO_MASK(intno) (intno & 0xffffU)

/*
 *  ����ߥϥ�ɥ��ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INHNO_MASK(intno) (intno & 0xffffU)

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	void	*sp;		/* �����å��ݥ��� */
	FP		pc;			/* �ץ���५���� */
} CTXB;

/*
 *  sta_ker ��ǤΥХꥢƱ��
 */
extern void sta_ker_barrier_sync(void);

extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);
#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ͥ���٥ޥ������饤�֥��
 *  
 *  SH34�Ǥϡ����ơ������쥸������SR�ˤ�4��7�ӥåȤ��4�ӥåȤ˳����ͥ����
 *  �ޥ����ʥϡ��ɥ������γ����ͥ���٥ޥ�����IPM�ˤ��֤���Ƥ��롥IPM����
 *  ¸���Ƥ�������ˡ������ͥ���٤γ���ɽ����-1����Ϣ³��������͡ˤ�Ȥ�
 *  ���Ȥ��ǽ�Ǥ��뤬��;�פʺ����ӥåȥ��եȤ����ȿž��ɬ�פˤʤ롥����
 *  ���򤱤뤿��ˡ�IPM����¸������ˤϡ�SR��4��7�ӥåȤ����Ф�����
 *  ��Ȥ����Ȥˤ��롥�����ͤ�����ͥ���٥ޥ���������ɽ���ȸƤӡ�IIPM�Ƚ�
 *  �����Ȥˤ��롥
 */

/*
 *  �����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 *
 *  ������֥����Υ������ե����뤫�饤�󥯥롼�ɤ�����Τ���ˡ�CAST�����
 */
#define EXT_IPM(iipm)    (-CAST(PRI,(iipm) >> 4))       /* ����ɽ������ɽ���� */
#define INT_IPM(ipm)     (CAST(uint16_t, -(ipm)) << 4)  /* ����ɽ��������ɽ���� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint8_t
current_iipm(void)
{
	return((uint8_t)(current_sr() & 0xF0U));
}

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_iipm(uint8_t iipm)
{
	set_sr((current_sr() & ~0xF0U) | iipm);
}

/*
 *  TOPPERSɸ�����߽�����ǥ�μ¸�
 *
 *  SH34�ϥ��ơ������쥸����(SR)��˳����ͥ���٥ޥ���(IPM)����äƤ��롥
 *  CPU��å��ե饰��������ǽ������ʤ������Τ��ᡤ����Ū��CPU��å���
 *  �饰��¸����롥
 *
 *  �ޤ���CPU��å����֤������������ѿ�(lock_flag)���Ѱդ��롥
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ���֤ϡ�IPM���ǥ��γ����ͥ����
 *  �ޥ������ͤ����ꤹ�롥���δ֤ϡ���ǥ��γ����ͥ���٥ޥ����ϡ�
 *  IPM���Ѥ��롥
 * 
 *  ������Ф���CPU��å��ե饰�����åȤ��줤��֤ϡ�IPM�򡤥����ͥ��
 *  �����Τ�Τ�������٤Ƥγ�����׵��ޥ���������(TIPM_LOCK)�ȡ����
 *  ���γ����ͥ���٥ޥ����Ȥι⤤�������ꤹ�롥���δ֤Υ�ǥ��γ�
 *  ����ͥ���٥ޥ����ϡ����Τ�����ѿ�(saved_iipm, ����ɽ�����ݻ�)����
 *  �դ����ݻ����롥
 */

/*
 *  ����ƥ����Ȥλ���
 *
 *  SH34�Ǥϡ�����ƥ����Ȥ�Ƚ��ˡ�����ߤΥͥ��Ȳ�����������
 *  R7_BANK1���Ѥ��롥
 * 
 */
Inline bool_t
sense_context(void)
{
	uint32_t nest;

	Asm("stc r7_bank,%0" : "=r"(nest));
	return(nest > 0U);
}

/*
 *  CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
    return(get_my_p_tpcb()->lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  CPU��å����֤Ǥγ����ͥ���٥ޥ���
 *
 *  TIPM_LOCK�ϡ�CPU��å����֤Ǥγ����ͥ���٥ޥ��������ʤ����������
 *  ��������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������ͤ�������롥
 */
#define TIPM_LOCK    TMIN_INTPRI

/*
 *  CPU��å����֤Ǥγ����ͥ���٥ޥ���������ɽ��
 */
#define IIPM_LOCK    INT_IPM(TIPM_LOCK)

/*
 *  TIPM_ENAALL�ʳ����ͥ���٥ޥ���������ˤ�����ɽ��
 */
#define IIPM_ENAALL  INT_IPM(TIPM_ENAALL)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 * 
 *  �������ѿ��ϡ�CPU��å����֤λ��Τ߽񤭴����Ƥ�褤�Ȥ��롥
 *  ����饤��ؿ���ǡ����������ν�����Ѳ����ʤ��褦��volatile ����ꡥ 
 */

/*
 *  CPU��å����֤ؤΰܹ�
 *
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�saved_iipm����¸��������
 *  �ͥ�������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������͡�TIPM_LOCK�ˤ���
 *  �ꤹ�롥�ޤ���lock_flag��true�ˤ��롥
 *
 *  IPM�����ǽ餫��TIPM_LOCK��Ʊ����������⤤���ˤϡ������
 *  saved_iipm����¸����Τߤǡ�TIPM_LOCK�ˤ����ꤷ�ʤ�������ϥ�ǥ�
 *  ��γ����ͥ���٥ޥ�������TIPM_LOCK��Ʊ����������⤤��٥������
 *  ����Ƥ�����֤ˤ����롥
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǸƤФ�뤳�Ȥ�
 *  �ʤ���Τ����ꤷ�Ƥ��롥
 */
Inline void
x_lock_cpu(void)
{
	uint8_t iipm;

	/*
	*  current_iipm()���֤��ͤ�ľ��saved_iipm����¸����������ѿ�iipm
	*  ���Ѥ��Ƥ���Τϡ�current_iipm()��Ƥ��ľ��˳���ߤ�ȯ������
	*  ��ư���줿����߽�����saved_iipm���ѹ�������ǽ�������뤿���
	*  ���롥
	*/
	iipm = current_iipm();
	if (IIPM_LOCK > iipm) {
		set_iipm(IIPM_LOCK);
	}
	get_my_p_tpcb()->saved_iipm = iipm;
	get_my_p_tpcb()->lock_flag = true;
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPU��å����֤β��
 *
 *  lock_flag��false�ˤ���IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�
 *  saved_iipm����¸�����ͤ��᤹��
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǤΤ߸ƤФ���
 *  �Τ����ꤷ�Ƥ��롥
 */
Inline void
x_unlock_cpu(void)
{
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
	get_my_p_tpcb()->lock_flag = false;
	set_iipm(get_my_p_tpcb()->saved_iipm);
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  chg_ipm��ͭ���ʳ����ͥ���٤��ϰϤ�Ƚ��
 *
 *  TMIN_INTPRI���ͤˤ�餺��chg_ipm�Ǥϡ�-15��TIPM_ENAALL�ʡ�0�ˤ��ϰ�
 *  ������Ǥ��뤳�ȤȤ���ʥ������å�����γ�ĥ�ˡ�
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				((-15 <= (intpri) && (intpri) <= TIPM_ENAALL))

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ���������
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϡ��ϡ��ɥ������γ����ͥ���٥�
 *  ���������ꤹ�롥CPU��å��ե饰�����åȤ���Ƥ�����ϡ�saved_iipm
 *  �����ꤷ������ˡ��ϡ��ɥ������γ����ͥ���٥ޥ��������ꤷ�褦��
 *  �����ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����TIPM_LOCK�ι⤤�������ꤹ�롥
 */
Inline void
x_set_ipm(PRI intpri)
{
	uint8_t   iipm = INT_IPM(intpri);

	if (!get_my_p_tpcb()->lock_flag) {
	set_iipm(iipm);
	}
	else {
		get_my_p_tpcb()->saved_iipm = iipm;
#if TIPM_LOCK == -15
		/*
		*  TIPM_LOCK��-15�ξ��ˤϡ����λ����ǥϡ��ɥ������γ����ͥ��
		*  �٥ޥ�����ɬ��15�����ꤵ��Ƥ��뤿�ᡤ���ꤹ��ɬ�פϤʤ���
		*/
      
#else /* TIPM_LOCK == -15 */
		set_iipm(iipm > IIPM_LOCK ? iipm : IIPM_LOCK);
#endif /* TIPM_LOCK == -15 */
	}
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ����λ���
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϥϡ��ɥ������γ����ͥ���٥�
 *  �����򡤥��åȤ���Ƥ������saved_iipm�򻲾Ȥ��롥
 */
Inline PRI
x_get_ipm(void)
{
	uint8_t iipm;

	if (!get_my_p_tpcb()->lock_flag) {
		iipm = current_iipm();
	}
	else {
		iipm = get_my_p_tpcb()->saved_iipm;
	}
	return(EXT_IPM(iipm));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 * �����ͥ���٥쥸����������
 */
Inline void
set_irc_ipr(uint32_t address, uint32_t offset, uint8_t val)
{
	uint32_t ipr_val;
	SIL_PRE_LOC;
	SIL_LOC_INT();

	ipr_val = sil_rew_mem((void *) address);
	ipr_val &= ~(0x0FU << offset);
	ipr_val |= (uint32_t)val << offset;    
	sil_wrw_mem((void *) address, ipr_val);

	SIL_UNL_INT();
}

/*
 *  ����������ƥ����� ���� CPU��å�������֤ʤ� true
 *  t_sense_lock()���PCB�򥢥��������뤿�ᡤ����ߤ�ػߤ��Ƽ¹Ԥ��롥   
 */
Inline bool_t
sense_tskctx_unl(void)
{
	bool_t result;
	uint8_t iipm;

	/* CPU��å����� */
	iipm = current_iipm();
	if (IIPM_LOCK > iipm) {
		set_iipm(IIPM_LOCK);
	}

	result = (!sense_context() && !t_sense_lock());

	/* CPU��å�������� */
	if (IIPM_LOCK > iipm) {
		set_iipm(iipm);
	}

	return(result);
}



/*
 *  �󥿥�������ƥ����� ���� CPU��å�������֤ʤ� true
 *  t_sense_lock()���PCB�򥢥��������뤿�ᡤ����ߤ�ػߤ��Ƽ¹Ԥ��롥 
 */
Inline bool_t
sense_intctx_unl(void)
{
	bool_t result;

	uint8_t iipm;

	/* CPU��å����� */
	iipm = current_iipm();
	if (IIPM_LOCK > iipm) {
		set_iipm(IIPM_LOCK);
	}

	result = (sense_context() && !t_sense_lock());

	/* CPU��å�������� */
	set_iipm(iipm);

	return(result);
}

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���prc_support.S��
 *
 *  dispatch�ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ������������
 *  ��ƤӽФ��٤���Τǡ�����������ƥ����ȡ�CPU��å����֡��ǥ����ѥ�
 *  �����ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ���
 *  ����Фʤ�ʤ���
 */
extern void dispatch(void);

/*
 *  ���������Υޥ����졼������core_support.S��
 */
extern void dispatch_and_migrate(ID prcid);

/*
 *  ���ߤΥ���ƥ����Ȥ�Τƥޥ����졼������core_support.S��
 */
extern void exit_and_migrate(ID prcid);

/*
 *  �ǥ����ѥå����ư��ϡ�prc_support.S��
 *
 *  start_dispatch�ϡ������ͥ뵯ư���˸ƤӽФ��٤���Τǡ����٤Ƥγ��
 *  �ߤ�ػߤ������֡ʳ���ߥ�å����֤�Ʊ���ξ��֡ˤǸƤӽФ��ʤ����
 *  �ʤ�ʤ���
 */
extern void start_dispatch(void) NoReturn;

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���prc_support.S��
 *
 *  exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�����������ƥ�
 *  ���ȡ�CPU��å����֡��ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ��
 *  �٥ޥ�����������֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *  �����ͥ�ν�λ�����θƽФ���prc_support.S��
 *
 *  call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *  ����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *  ����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  ����������ƥ����Ȥν����
 *
 *  ���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥���λ���
 *  �ǥ����å��ΰ��ȤäƤϤʤ�ʤ���
 *
 *  activate_context�򡤥���饤��ؿ��ǤϤʤ��ޥ�������Ȥ��Ƥ���Τϡ�
 *  ���λ����Ǥ�TCB���������Ƥ��ʤ�����Ǥ��롥
 */
extern void    start_r(void);

#define activate_context(p_tcb)                                         \
{                                                                       \
	(p_tcb)->tskctxb.sp = (void *)((char *)((p_tcb)->p_tinib->stk)      \
                                        + (p_tcb)->p_tinib->stksz);     \
	(p_tcb)->tskctxb.pc = (void *) start_r;                             \
}

/*
 *  calltex�ϻ��Ѥ��ʤ�
 */
#define OMIT_CALLTEX

/*
 * �������å����¸���˴ޤޤ��ɸ����㳰������ǽ�ν�����������Ѥ��ʤ�
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 * CPU�㳰�ϥ�ɥ�ν����
 */
Inline void
initialize_exception(void)
{
}
     
/*
 *  SH34�γ���ߥ������ƥ�����ȳ���߽�����ǥ�μ¸�
 * 
 *  SH34�γ���ߤϡ��������ե⥸�塼�����ߡ�IRQ�����, PINT����ߤ�ʬ
 *  ��Ǥ������줾�찷�����ۤʤ롥���Τ��ᡤ����ߥϥ�ɥ��ֹ椫�顤��
 *  �γ���ߤ�ʬ�ह�뤿��Υޥ�����Ѱդ��롥
 * 
 *  PINT����ߤ�15bit�Υץ��å��ؤγ�����׵�饤��Ǽ¸�����Ƥ��뤬��
 *  IRC�ؤγ�����׵�饤���PINT0��PINT7��PINT0��PINT7�Ȥ��ä�2�ܤˤʤ�
 *  �Ƥ��롥���Τ��ᡤ�����ͥ�Ǥ���̤ˤϰ��鷺��2�ܤγ���ߤȤ��ư�����
 *  PINT�ϡ����̤�PINTER�쥸�����ˤ����Ķػ߲�ǽ�Ǥ��뤬�������ͥ��
 *  �ϡ�PINTER�쥸����������ϼ�갷��ʤ������Τ��ᡤPINTER�쥸������
 *  ����ϡ��桼�����ץ����ǹԤ�ɬ�פ����롥Ʊ�ͤ�PINT���׵��٥�
 *  �����ꤹ��ICR2�������桼�����ץ����ǹԤ�ɬ�פ���롥�ʤ��������
 *  ������ߤ����ꤷ���ݤγ���ߥϥ�ɥ��������Ǥ�IRR0�Υ��ꥢ��
 *  i_begin_int()�ǹԤ���PINT����ߤ��ɤ�����Ƚ�ꤹ��ޥ�����Ѱդ��롥
 *
 *  Ʊ�ͤ�IRQ����ߤ���Ƚ�ꤹ��ޥ�����Ѱդ��롥
 */

/*
 *  PINT����ߤ��ɤ�����Ƚ�ꤹ�뤿��Υޥ���
 */
#define INTNO_PINT(intno) ((0x700 == (intno)) || (0x720 == (intno)))
#define INTNO_PINT_OFFSET(intno) (((INTNO_MASK(intno)) - 0x700) >> 5)

/*
 *  IRQ����ߤ��ɤ�����Ƚ�ꤹ�뤿��Υޥ���
 */
#define INTNO_IRQ(intno) ((0x600 <= (intno)) && ((intno) <= 0x6A0))
#define INTNO_IRQ_OFFSET(intno) (((INTNO_MASK(intno)) - 0x600) >> 5)
     
/*
 *  �����ͥ����
 *
 *  �Ƴ���ߤγ����ͥ���٤ϳ����ͥ�������쥸����(IPRXX)�ˤ�ä���
 *  �ꤹ�롥�������ե⥸�塼��ξ�硤���ե⥸�塼����������ǽ�Ǥ��롥
 *  �㤨��SCIF�ϡ�ERI2, RXI2, BRI2, TXI2�Ȥ���4�Ĥγ�����׵�饤���
 *  �ݡ��Ȥ��뤬�����Ƥγ�����׵�饤����Ф���Ʊ���ͥ���٤��������
 *  ���ʤ������Τ��ᡤ�Ƴ�����׵�饤����ˤɤγ����ͥ�������쥸��
 *  �������ꤹ�뤫����������ơ��֥���Ѱդ��롥�ޤ���������ֹ��Ϣ³
 *  ���Ƥ����ᡤ���ݡ��Ȥ��Ƥ��ʤ��ֹ�ˤϡ�number��-1�����ꤹ�롥�ơ�
 *  �֥�
 */

/*
 *  �Ƴ�����ֹ�������ꤹ��IPR�ξ�������Τ���ι�¤��  
 */
typedef struct {
	/* IPRA:0, IPRB:1, IPRC:2, IPRD:3, IPRE:4, IPRF:5, IPRG:6 */
	uint32_t address; 
	/* bit5��12:3, bit11��8:2, bit7��4:1, bit3��0:0 */
	uint8_t  offset;
} IPR_INFO;
/*
 *  �Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 */
extern const IPR_INFO ipr_info_tbl[TNUM_INH];

/*
 *  �Ƴ�����ֹ�������ꤹ��MSKCLR�ξ�������Τ���ι�¤��  
 */
typedef struct {
	uint32_t address; 
	uint32_t  mask;
} MSK_INFO;
/*
 *  �Ƴ�����ֹ����MSKCLR�ξ�������ơ��֥�
 */
extern const MSK_INFO mskclr_info_tbl[TNUM_INH];

/*
 *  ����ߥ���ȥ���ν����
 *  ToDo ��ö�������ѿ��˥���ȥ���Υ��ɥ쥹������롥
 */
Inline void
init_irc(void)
{
	/* ����ߥ���ȥ���쥸������������ */
	sil_wrw_mem((void*)ICR0, 0x00800000U);
	/* ����ߥ���ȥ���쥸������������ */
	sil_wrh_mem((void*)ICR1, 0x00000000U);

	/*
	 *  ����ߥޥ����쥸�����ν����
	 */
	init_int2msk();
}

/*
 *  ������ֹ桦����ߥϥ�ɥ��ֹ�
 *
 *  ����ߥϥ�ɥ��ֹ�(inhno)�ȳ�����ֹ�(intno)�ϡ������ȯ�����˳��
 *  �߻��ݥ쥸���������ꤵ����ͤ��Ѥ��롥����߻��ݥ쥸�����ϡ�INTEVT
 *  ��INTEVT2��2���ब���ꡤ���줾�����ꤵ����ͤ��ۤʤ롥�����SH34��
 *  ��INTEVT����Ѥ��Ƥ����������ߤ�INTEVT2���Ѥ��롥���Τ��ᡤ�ץ�
 *  �å��η����������ե�������Ѱդ��ơ��ɤ���Υ쥸�������Ѥ��뤬��
 *  �ꤹ�뤳�ȤȤ��롥�ޤ������ݡ��Ȥ������ߤκ������ۤʤ뤿�ᡤ
 *  �����ͤ�ץ��å��η����������ե������������롥
 *
 *  INTENT�����ꤵ����ͤϥ��ѡ������ͤǤ��뤿�ᡤ���Τޤޤ��ͤ�ͥ����
 *  �������Υơ��֥�Υ���ǥå������Ѥ���ȡ�̵�̤��ΰ褬ȯ�����롥��
 *  �Τ��ᡤ�����ͥ������Ǥϡ�INTENT�����ꤵ����ͤ򥷥եȤ����ͤ��Ѥ�
 *  �롥���եȤ����ͤ�ץ��å���˰ۤʤ뤿��ץ��å��η���������
 *  �ե������������롥
 *
 *  ����ɽ����̾���ϡ�iintno,iinhno�Ȥ��롥
 */

/*
 *  ������ֹ���ϰϤ�Ƚ��
 * 
 *  TMIN_INTNO��TMAX_INTNO���ϰϤǤ��äƤ�ͭ�����ֹ�Ǥʤ���礬���뤿
 *  �ᡤipr_info_tbl[]��ͭ�����ֹ椫������å�����
 */
#define VALID_INTNO(intno) \
        ((TMIN_INTNO <= (INTNO_MASK(intno))) && ((INTNO_MASK(intno)) <= TMAX_INTNO) && (ipr_info_tbl[INT_INTNO(INTNO_MASK(intno))].address != 0U))
#define VALID_INTNO_DISINT(intno)    VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)    VALID_INTNO(intno)

/*
 *  CPU�㳰�ϥ�ɥ��ֹ�
 *
 *  CPU�㳰�ϥ�ɥ��ֹ�Ȥ��Ƥϡ��㳰���ݥ쥸���������ꤹ���㳰�����ɤ�
 *  �Ѥ��롥���ݡ��Ȥ���CPU�㳰�ϥ�ɥ���ϥץ��å��ο����˰ۤʤ뤎�
 *  �ǡ��ץ��å��η����������ե������������롥
 *
 *  ����ߥϥ�ɥ��ֹ��Ʊ������CPU�㳰�ϥ�ɥ��ֹ�⥹�ѡ����Ǥ��뤿�ᡤ
 *  �����ͥ������Ǥ��ͤ򥷥եȤ�������ɽ�����Ѥ��롥 
 */
#define VALID_EXCNO_DEFEXC(excno) \
        (TMIN_EXCNO <= (excno) && (excno) <= TMAX_EXCNO)

/*
 *  ����ߥϥ�ɥ�
 *
 *  ����ߥϥ�ɥ����Ͽ���롥����ߥϥ�ɥ�ơ��֥���Τϥ���ե�����
 *  �졼������Ū����������
 */ 
extern const FP inh_tbl[TNUM_INH];

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ�inhno�γ���ߥϥ�ɥ�ε�ư����inthdr�����ꤹ�롥�����
 *  �ϥ�ɥ�ơ��֥�
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{
  	assert(((TMIN_INHNO <= INHNO_MASK(inhno)) && (INHNO_MASK(inhno) <= TMAX_INHNO)));
}

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) extern void inthdr(void);



/*
 *  ������׵�ػߥե饰
 *
 *  SH34��IRC�ϳ�����׵�ػߥե饰������ʤ�������ߤ�ػߤ�����ϡ�
 *  �����ͥ�������쥸����(IPRXX)��0�����ꤹ��ɬ�פ����롥�����ͥ
 *  �������쥸������0�ˤ��뤳�Ȥǳ�����׵�ػߥե饰��¸�����Ȥ���
 *  �֡������ͥ���٤򵭲����Ƥ����ΰ褬ɬ�פȤʤ롥����ե�����졼��
 *  �Ǥ��Υơ��֥���Ѱդ��롥�ʤ������Υơ��֥�ϳ���ߤ�������ǳ��
 *  ���װ��˱�����SR�����ꤹ��ɬ�פ����뤿�ᡤ����ɽ���Ȥ��롥�ޤ�����
 *  ���ߥϥ�ɥ��������Ǥ��������Τ��ᡤIPM�����ǤϤʤ�������ߥϥ��
 *  ��¹Ի���SR�������Ʊ���˻��ġ����Τ��ᡤIPM���ͤΤߤ������������
 *  ��ϡ�����8bit�Τߤ򻲾Ȥ���ɬ�פ����롥���Ƥϥ���ե�����졼����
 *  ��Ū���������롥
 */
extern const uint32_t int_iipm_tbl[TNUM_INT];

/*
 *  ������׵�ػߥե饰�Υ��å�
 *
 *  �����ͥ�������쥸����(IPRA��G)��0�����ꤹ�롥
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	uint16_t iintno  = INT_INTNO(INTNO_MASK(intno));
	uint32_t address = ipr_info_tbl[iintno].address;
	uint32_t offset  = ipr_info_tbl[iintno].offset;
	uint32_t iipm    = int_iipm_tbl[iintno];

	/*
	 *  �����°�������ꤵ��Ƥ��ʤ����
	 */
	if ((iipm & 0x01U) != 0) {
		return(false);
	}
    
	/* 
	*  ������ֹ���б�����IPR���ͤ�0�ˤ��롥
	*/
	set_irc_ipr(address, offset, 0x00);

	return(true);
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *  ������׵�ػߥե饰�β��
 *
 *  �����ͥ�������쥸����(IPRA��G)�򸵤��ͤ��᤹��
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	uint16_t iintno  = INT_INTNO(INTNO_MASK(intno));
	uint32_t address = ipr_info_tbl[iintno].address;
	uint32_t offset  = ipr_info_tbl[iintno].offset;
	uint32_t iipm    = int_iipm_tbl[iintno];

	/*
	 *  �����°�������ꤵ��Ƥ��ʤ����
	 */
	if ((iipm & 0x01U) != 0) {
		return(false);
	}

	/* 
	*  ������ֹ���б�����IPR���ͤ򥻥åȤ���
	*/
	set_irc_ipr(address, offset, (-EXT_IPM(iipm & 0xF0U)));
    
	return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)
/*
 * ����ߥޥ����쥸����������
 */
Inline void
set_target_irc(INTNO intno, uint_t cpuindex)
{
	uint16_t iintno  = INT_INTNO(INTNO_MASK(intno));
	uint32_t address = mskclr_info_tbl[iintno].address;
	uint32_t mask  = mskclr_info_tbl[iintno].mask;

	address = address + CALC_CPU_MSKCLR_OFFSET(cpuindex);
	sil_wrw_mem((void *) address, mask);
}


/*
 *  ����ߥϥ�ɥ�������ɬ�פ�IRC���
 *
 *  PINT��IRQ����ߤǤ��ġ����å��ȥꥬ�ξ��ϳ�����׵�򥯥ꥢ���롥
 *  ���å��ȥꥬ��Ƚ�Ǥ���Τ����ݤʤΤǡ���˥��ꥢ���롥
 */
Inline void
i_begin_int(INTNO intno)
{
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  CPU�㳰�ϥ�ɥ�ط�
 */ 

/*
 *  �㳰�ϥ�ɥ���� p_excinf ����Ƽ�������Ф�����Υޥ���
 */
#ifdef FPU_ENABLE

#ifdef FPU_SAVE_BANKED_REG

#define P_EXCINF_OFFSET_SSR     (12U + 14U + 16U)
#define P_EXCINF_OFFSET_SPC     (14U + 14U + 16U)
#define P_EXCINF_OFFSET_PR      (13U + 14U + 16U)
#define P_EXCINF_OFFSET_EXPEVT    0U 

#else

#define P_EXCINF_OFFSET_SSR     (12U + 14U)
#define P_EXCINF_OFFSET_SPC     (14U + 14U)
#define P_EXCINF_OFFSET_PR      (13U + 14U)
#define P_EXCINF_OFFSET_EXPEVT    0U

#endif /* FPU_SAVE_BANKED_REG */

#else

#define P_EXCINF_OFFSET_SSR     12U
#define P_EXCINF_OFFSET_SPC     14U
#define P_EXCINF_OFFSET_PR      13U
#define P_EXCINF_OFFSET_EXPEVT   0U

#endif /* FPU_ENABLE */

/*
 *  CPU�㳰�ϥ�ɥ����Ͽ�ѥơ��֥�
 */
extern const FP exch_tbl[TNUM_EXC];

/*
 *  CPU�㳰�ϥ�ɥ������
 */
Inline void
x_define_exc(EXCNO excno, FP exchdr)
{       
}

/*
 *  CPU�㳰�ϥ�ɥ�����������������ޥ���
 */
#define EXC_ENTRY(excno, exchdr)    exchdr
#define EXCHDR_ENTRY(excno, exchdr) extern void exchdr(void *p_excinf);

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 *
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥ�������������ƥ����Ȥλ���false��
 *  �����Ǥʤ�����true���֤���
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	uint32_t nest;

	Asm("stc r7_bank,%0" : "=r"(nest));
	return(nest > 1U);
}

/*
 *  CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ
 *  ���ˤλ���
 */
Inline uint16_t
exc_get_iipm(void *p_excinf)
{
	return(*(((uint32_t *) p_excinf) + P_EXCINF_OFFSET_SSR) & 0x00F0U);
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߤΥޥ������֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ����ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ����ʥ�
 *  �ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ������true
�������Ǥʤ���
 *  ��false���֤���CPU�㳰�������ͥ�������γ���߽������ȯ���������
 *  �ˤ�false���֤��ˡ�
 *
 *  SH�Ǥϡ�CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ�����
 *  �����٤Ƥγ���ߤ���Ĥ�����֤Ǥ��뤳�Ȥ�����å����뤳�Ȥǡ�����
 *  �ͥ�¹���Ǥʤ����ȡ�����ߥ�å����֤Ǥʤ����ȡ�CPU��å����֤Ǥ�
 *  �����ȡ��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ��뤳�Ȥ�4�Ĥ�
 *  ��������å����뤳�Ȥ��Ǥ����CPU�㳰��ȯ����������lock_flag��
 *  �Ȥ���ɬ�פϤʤ��ˡ�
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) == IIPM_ENAALL);
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߡ�CPU��å����֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ����ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ�����
 *  true�������Ǥʤ�����false���֤���CPU�㳰�������ͥ�������γ���߽�
 *  �����ȯ���������ˤ�false���֤��ˡ�
 *
 *  SH34�Ǥϡ�CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥�
 *  �����ˤ�TIPM_LOCK����㤤���Ȥ�����å����뤳�Ȥǡ������ͥ�¹����
 *  �ʤ����ȡ�����ߥ�å����֤Ǥʤ����ȡ�CPU��å����֤Ǥʤ����Ȥ�3��
 *  �ξ�������å����Ƥ����CPU�㳰��ȯ����������lock_flag�ϻ��Ȥ���
 *  ���ʤ��ˡ�����ˤ�ꡤ�ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����TIPM_LOCK��
 *  ������ꤷ�ƥ�������¹Ԥ��Ƥ�����ˤ�false���֤äƤ��ޤ�����Ƚ�Ǥ�
 *  ���Τˤ��뤿��Υ����Хإåɤ��礭�����Ȥ��顤���Ƥ��뤳�Ȥˤ��롥
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) < IIPM_LOCK);
}

/*
 * Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
extern void default_exc_handler(void *p_excinf);

/*
 * ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
extern void default_int_handler(void *p_excinf);

/*
 *  str_ker()�����ǥޥ����ץ��å��ǹԤ������
 */
extern void prc_mprc_initialize(void);

/*
 *  �ץ��å���¸�ν����
 */
extern void prc_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void prc_terminate(void);

/*
 *  ��å��������˻��Ѥ�����ߡ��ѿ�
 */
extern  uint32_t dangling_dummy;

/*
 *  1���ܤΥ�å������ʥ��������󥿥�������ƥ����ȶ��ѡˡ��̾��ǡ�
 */
Inline void
x_acquire_lock(LOCK *p_lock)
{
	bool_t    result;

	while(true){
		Asm("     movli.l	@%2,r0             \n"
		"\t   mov		#0,r3              \n"
		"\t   cmp/eq	r3,r0              \n"
		"\t   bf		1f                 \n"
		"\t   mov		#1,r0              \n"
		"\t   movco.l	r0,@%2             \n"
		"\t   bf		2f                 \n"  //����
		"\t   mov		#0,%1              \n"
		"\t   bra		3f                 \n"
		"\t    nop                         \n"
		"1:\t                              \n"  //���󥰥�󥰡�
		"\t   movco.l	r0,%0              \n"
		"2:\t                              \n"  //���ԤΥѥ�����
		"\t   mov		#1,%1              \n"
		"3:\t                              \n"  //��λ
		:"=m"(dangling_dummy),"=r"(result)
		:"r"(p_lock):"r0","r3", "cc");

		if(!result){
			return;
		}
		/* ����ߤε��� */
		x_unlock_cpu();
		x_lock_cpu();
	}
}

#define t_acquire_lock(p_lock) x_acquire_lock(p_lock)
#define i_acquire_lock(p_lock) x_acquire_lock(p_lock)

#if TTYPE_KLOCK != G_KLOCK

/*
 *  2���ܰʾ�Υ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline bool_t
x_acquire_nested_lock(LOCK *p_lock)
{
	bool_t    result;
	PCB		*p_pcb;

	while(true){
		Asm("     movli.l	@%2,r0             \n"
		"\t   mov		#0,r3              \n"
		"\t   cmp/eq	r3,r0              \n"
		"\t   bf		1f                 \n"
		"\t   mov		#1,r0              \n"
		"\t   movco.l	r0,@%2             \n"
		"\t   bf		2f                 \n"  //����
		"\t   mov		#0,%1              \n"
		"\t   bra		3f                 \n"
		"\t    nop                         \n"
		"1:\t                              \n"  //���󥰥�󥰡�
		"\t   movco.l	r0,%0              \n"
		"2:\t                              \n"  //���ԤΥѥ�����
		"\t   mov		#1,%1              \n"
		"3:\t                              \n"  //��λ
		:"=m"(dangling_dummy),"=r"(result)
		:"r"(p_lock):"r0","r3", "cc");

		if(!result){
			return(false);
		}
		/* ����ߤε��� */
		x_unlock_cpu();
		x_lock_cpu();

		/*
		 *  �ޥ����졼����󤹤��ǽ��������ΤǤ�����������  
		 *  �󥿥�������ƥ����Ȥξ�硤�ޥ����졼����󤷤ʤ����ᡤ
		 *  while���˼¹Ԥ��Ƥ�褤����1��ǥ�å����Ȥ줿��硤
		 *  ��Ψ�������Τǡ������Ǽ������롥
		 */
		p_pcb = get_my_p_pcb(); 
		if (p_pcb->p_firstlock == NULL) {
			return(true);
		}
	}
}

#define t_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)
#define i_acquire_nested_lock(p_lock) x_acquire_nested_lock(p_lock)

#endif /* TTYPE_KLOCK != G_KLOCK */

/*
 *  �������Ĥ��ʤ���å������ؿ�
 */
Inline void 
x_acquire_lock_without_preemption(LOCK *p_lock)
{
	bool_t    result;

	while(true){
		Asm("     movli.l	@%2,r0             \n"
		"\t   mov		#0,r3              \n"
		"\t   cmp/eq	r3,r0              \n"
		"\t   bf		1f                 \n"
		"\t   mov		#1,r0              \n"
		"\t   movco.l	r0,@%2             \n"
		"\t   bf		2f                 \n"  //����
		"\t   mov		#0,%1              \n"
		"\t   bra		3f                 \n"
		"\t    nop                         \n"
		"1:\t                              \n"  //���󥰥�󥰡�
		"\t   movco.l	r0,%0              \n"
		"2:\t                              \n"  //���ԤΥѥ�����
		"\t   mov		#1,%1              \n"
		"3:\t                              \n"  //��λ
		:"=m"(dangling_dummy),"=r"(result)
		:"r"(p_lock):"r0","r3", "cc");

		if(!result){
			return;
		}
	}
}

/*
 *  ��å��β������̾��ǡ�
 */
Inline void
x_release_lock(LOCK *p_lock)
{
	*p_lock = 0;
}

/*
 *  ���ԥ��å���ǽ�Υͥ��ƥ��֥�å������ǻ��Ѥ���ؿ�
 */

/*
 *  ���ԥ��å��η��ʥͥ��ƥ��֥�å��ξ���
 */
typedef uint32_t SPNLOCK;

/*
 *  ���ԥ��å�ID����ºݤΥ�å���ID�ؤ��Ѵ�
 */
#define TO_NATIVE_ID(spnid)		(spnid * 10)

/*
 *  ���ԥ��å��ν����
 */
Inline void
x_initialize_spin(ID spnid, SPNLOCK *p_spn_lock)
{
	*p_spn_lock = 0;
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
 *  ���ԥ��å��μ����λ�ԡ��̾��å��ǡ�
 */
Inline bool_t
x_try_lock_spin(SPNLOCK *p_spn_lock)
{
	bool_t    result;

	Asm("     movli.l	@%2,r0             \n"
		"\t   mov		#0,r3              \n"
		"\t   cmp/eq	r3,r0              \n"
		"\t   bf		1f                 \n"
		"\t   mov		#1,r0              \n"
		"\t   movco.l	r0,@%2             \n"
		"\t   bf		2f                 \n"  //����
		"\t   mov		#0,%1              \n"
		"\t   bra		3f                 \n"
		"\t    nop                         \n"
		"1:\t                              \n"  //���󥰥�󥰡�
		"\t   movco.l	r0,%0              \n"
		"2:\t                              \n"  //���ԤΥѥ�����
		"\t   mov		#1,%1              \n"
		"3:\t                              \n"  //��λ
		:"=m"(dangling_dummy),"=r"(result)
		:"r"(p_spn_lock):"r0","r3", "cc");

	return result;
}

#define t_try_lock_spin(p_spn_lock) x_try_lock_spin(p_spn_lock)
#define i_try_lock_spin(p_spn_lock) x_try_lock_spin(p_spn_lock)

/*
 *  ���ԥ��å��β���
 */
Inline void
x_unlock_spin(SPNLOCK *p_spn_lock)
{
  x_release_lock(p_spn_lock);
}

#define t_unlock_spin(p_spn_lock) x_unlock_spin(p_spn_lock)
#define i_unlock_spin(p_spn_lock) x_unlock_spin(p_spn_lock)

/*
 *  ���㥤����ȥ�å��ν������G_LOCK�ξ���
 */
Inline void
x_initialize_giant_lock(LOCK *p_giant_lock)
{
	*p_giant_lock = 0;
}



/*
 *  ��������å��ν����
 */
Inline void
x_initialize_tsk_lock(LOCK *p_tsk_lock)
{
	*p_tsk_lock = 0;
}


/*
 *  ���֥������ȥ�å��ν����
 */
Inline void
x_initialize_obj_lock(LOCK *p_obj_lock)
{
	*p_obj_lock = 0;
}


#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
