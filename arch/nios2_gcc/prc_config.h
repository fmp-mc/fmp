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
 *  @(#) $Id: prc_config.h 896 2012-02-24 01:59:56Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���Nios2�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#include "nios2.h"

/*
 *  ���顼�����å���ˡ�λ���
 */
#define CHECK_STKSZ_ALIGN	8	/* �����å��������Υ��饤��ñ�� */
#define CHECK_FUNC_ALIGN	4	/* �ؿ��Υ��饤��ñ�� */
#define CHECK_FUNC_NONNULL		/* �ؿ�����NULL�����å� */
#define CHECK_STACK_ALIGN	4	/* �����å��ΰ�Υ��饤��ñ�� */
#define CHECK_STACK_NONNULL		/* �����å��ΰ����NULL�����å� */
#define CHECK_MPF_ALIGN		4	/* ����Ĺ����ס����ΰ�Υ��饤��ñ�� */
#define CHECK_MPF_NONNULL		/* ����Ĺ����ס����ΰ����NULL�����å� */
#define CHECK_MB_ALIGN		4	/* �����ΰ�Υ��饤��ñ�� */

/*
 *  �㳰�θĿ�
 */
#define TNUM_EXCH  18U

/*
 *  ����ߥϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_INHNO 0U
#define TMAX_INHNO 31U
#define TNUM_INH   32U

/*
 *  ������ֹ�˴ؤ������
 */ 
#define TMIN_INTNO 0U
#define TMAX_INTNO 31U
#define TNUM_INT   32U

/*
 *  �����ͥ���٤θĿ�
 */
#define  TNUM_INT_PRI  8U

/*
 *  ������ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INTNO_MASK(intno) (intno & 0xffffU)

/*
 *  ������ֹ����³�ץ��å��Υץ��å�ID�ʾ��16bit��
 */
#define INTNO_PRCID(intno) (intno >> 16U)

/*
 *  ����ߥϥ�ɥ��ֹ�Υޥ����ʲ���16bit�Τߤ�ͭ����
 */
#define INHNO_MASK(intno) (intno & 0xffffU)

/*
 *  ������ֹ���ϰϤ�Ƚ��
 */
#define VALID_INTNO(prcid, intno) (((TMIN_INTNO <= (INTNO_MASK(intno)) && (INTNO_MASK(intno)) <= TMAX_INTNO)) \
                                    && (INTNO_PRCID(intno) == prcid))
#define VALID_INTNO_DISINT(prcid, intno)	VALID_INTNO(prcid, intno)
#define VALID_INTNO_CFGINT(prcid, intno)	VALID_INTNO(prcid, intno)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ޥ����ץ��å������֤�
 */
/*
 * �ޥ����ץ��å������֤�
 */
Inline bool_t
x_sense_mprc(void)
{
	return (x_prc_index() == (TOPPERS_MASTER_PRCID - 1));
}

/*
 *  �󥿥�������ƥ������ѤΥ����å����ϥ��ɥ쥹����ޥ���
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#if TTYPE_KLOCK == G_KLOCK

/*
 *  ���㥤����ȥ�å��ν������G_LOCK�ξ���
 */
Inline void
x_initialize_giant_lock(LOCK *p_giant_lock)
{
	*p_giant_lock = GIANT_LOCK;
	mutex_init(GIANT_LOCK);
}

#endif /* TTYPE_KLOCK == G_KLOCK */

#if TTYPE_KLOCK == P_KLOCK

/*
 *  ��������å��Υơ��֥�
 *  �������åȰ�¸��������� 
 */
extern const uint32_t target_tsk_lock_table[];

/*
 *  ��������å��ν������P_LOCK�ξ���
 */
Inline void
x_initialize_tsk_lock(LOCK *p_tsk_lock)
{
	*p_tsk_lock = target_tsk_lock_table[x_prc_index()];
	mutex_init(*p_tsk_lock);
}

/*
 *  ���֥�����å��Υơ��֥�
 *  �������åȰ�¸��������� 
 */
extern const uint32_t target_obj_lock_table[];

/*
 *  ���֥������ȥ�å��ν����
 */
Inline void
x_initialize_obj_lock(LOCK *p_obj_lock)
{
	*p_obj_lock = target_obj_lock_table[x_prc_index()];
	mutex_init(*p_obj_lock);
}

#endif /* TTYPE_KLOCK == P_KLOCK */

/*
 *  TOPPERSɸ�����߽�����ǥ�μ¸�
 *
 *  �����ͥ�������γ���ߤ��ߤ��ʤ���
 */

/*
 *  ����ƥ����Ȥλ���
 *
 *   �㳰�ʳ����/CPU�㳰�ˤΥͥ��Ȳ���򥫥���Ȥ����ѿ���except_nest_count�ˤ�
 *   �Ѱդ����㳰��������ǥ��󥯥���Ȥ��뤳�Ȥǡ�����ƥ����Ȥ�Ƚ�ꤹ�롥
 */
Inline bool_t
sense_context(void)
{
	uint32_t tmp;
	uint32_t saved_status;
	TPCB *p_tpcb;

	/*
	 *  �ޥ����졼����󤵤�뤳�Ȥ��θ���Ƴ���ߤ�ػߤ��Ƥ��������
	 *  �����롥
	 */
	saved_status = current_status();
	set_status(saved_status & ~STATUS_PIE);
	Asm("":::"memory");
	p_tpcb = get_my_p_tpcb();
	tmp = p_tpcb->except_nest_count;
	set_status(saved_status);
	Asm("":::"memory");

	return(tmp > 0U);
}

/*
 *  CPU��å����֤ؤΰܹ�
 */
Inline void
x_lock_cpu(void)
{
	set_status(current_status() & ~STATUS_PIE);
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
}

#define t_lock_cpu()   x_lock_cpu()
#define i_lock_cpu()   x_lock_cpu()

/*
 *  CPU��å����֤β��
 */
Inline void
x_unlock_cpu(void)
{
	/* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
	Asm("":::"memory");
	set_status(current_status() | STATUS_PIE);
}

#define t_unlock_cpu() x_unlock_cpu()
#define i_unlock_cpu() x_unlock_cpu()

/*
 *  CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
	return((current_status() & STATUS_PIE) == 0U);
}

#define t_sense_lock() x_sense_lock()
#define i_sense_lock() x_sense_lock()

/*
 *  ����������ƥ����� ���� CPU��å�������֤ʤ� true
 */
Inline bool_t
sense_tskctx_unl(void)
{
	return((!sense_context() && !t_sense_lock()));
}
  
/*
 *  �󥿥�������ƥ����� ���� CPU��å�������֤ʤ� true
 */
Inline bool_t
sense_intctx_unl(void)
{
	return((sense_context() && !i_sense_lock()));
}

/*
 *  ��å����������ؿ�
 */

/*
 *  1���ܤΥ�å������ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_acquire_lock(LOCK *p_lock)
{
	while(true) {
		if (mutex_try_lock(*p_lock, x_prc_index())) {
			/* ��å��������� */
			Asm("":::"memory");
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
	PCB		*p_pcb;

	while(true) {
		if (mutex_try_lock(*p_lock, x_prc_index())) {
			/* ��å��������� */
			Asm("":::"memory");
			return(false);
		}
		/* ����ߤε��� */
		x_unlock_cpu();
		x_lock_cpu();
		/*
		 * �ޥ����졼����󤹤��ǽ��������ΤǤ�����������  
		 * �󥿥�������ƥ����Ȥξ�硤�ޥ����졼����󤷤ʤ����ᡤ
		 * while���˼¹Ԥ��Ƥ�褤����1��ǥ�å����Ȥ줿��硤
		 * ��Ψ�������Τǡ������Ǽ������롥
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
 *  ��å��β����ʥ��������󥿥�������ƥ����ȶ��ѡ�
 */
Inline void
x_release_lock(LOCK *p_lock)
{
	Asm("":::"memory");
	mutex_unlock(*p_lock, x_prc_index());
}

/*
 *  �������Ĥ��ʤ���å������ؿ�
 */
Inline void 
x_acquire_lock_without_preemption(LOCK *p_lock)
{
	while(true) {
		if (mutex_try_lock(*p_lock, x_prc_index())) {
			/* ��å��������� */
			Asm("":::"memory");
			return;
		}
	}
}


/*
 *  ����ߥϥ�ɥ����Ͽ�ѥơ��֥��kernel_cfg.c��
 */
extern const FP* const p_inh_table[TNUM_PRCID];

/*
 *  ����ߥϥ�ɥ��ͥ���١�kernel_cfg.c��
 */
extern const uint8_t* const p_inh_iipm_table[TNUM_PRCID];

/*
 *  ����ߥϥ�ɥ������
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry, uint_t affinity_mask)
{
}

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr)

/*
 *  �����ͥ���٥ޥ������饤�֥��
 *
 *  XPS Interrupt Controller �ϳ����ͥ���٤γ�ǰ���ʤ����ᡤ
 *  ���եȥ������ǵ���Ū�˼¸����롥 
 */

/*
 *  �����ͥ������Υޥ����ѥ������kernel_cfg.h��
 */
extern const uint32_t* const p_iipm_mask_table[TNUM_PRCID];

#define my_iipm_mask_table (p_iipm_mask_table[x_prc_index()])

/*
 *  IPM��imp_mask_table�Υ���ǥå������Ѵ�����ޥ���
 */
#define INDEX_IPM(ipm)  (-(ipm))

/*
 *  �����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 *
 */
#define EXT_IPM(iipm)    (-((PRI)(iipm)))       /* ����ɽ������ɽ���� */
#define INT_IPM(ipm)     ((uint8_t)(-(ipm)))    /* ����ɽ��������ɽ���� */

/*
 *  (��ǥ���)�����ͥ���٥ޥ���������
 * 
 *  ���ꤵ�줿ͥ���٤����ꤵ�줿������׵�ػߥե饰�Υơ��֥���ͤȡʥ��
 *  ���Ρ˳Ƴ���ߤγ�����׵�ػߥե饰�ξ��֤��ݻ������ѿ����ͤȤ�
 *  OR��IRC�γ�����׵�ػߥե饰�˥��åȤ������ꤷ��ͥ���٤������ѿ�
 *  ipm����¸���롥
 */
Inline void
x_set_ipm(PRI intpri)
{
	TPCB *p_tpcb = get_my_p_tpcb();
	uint32_t ipm_mask = my_iipm_mask_table[INT_IPM(intpri)];


	p_tpcb->iipm = INT_IPM(intpri);

	/*
	 *  XPS INTC �γ���ߥ���ȥ���ϥ��͡��֥�쥸������
	 *  ���ꥢ���쥸���������뤿�ᡤ��ö���Ƥγ���ߤ�ػߤ��Ƥ��顤
	 *  ����γ���ߤΤߵ��Ĥ���ɬ�פ�����
	 */
	/* ������߶ػ� */
	set_ienable(0U);

	/* �ޥ������ꤵ��Ƥ��ʤ�����ߤΤߵ��� */
	set_ienable(~(ipm_mask|p_tpcb->idf));

	p_tpcb->iipm = INT_IPM(intpri);
}

#define t_set_ipm(intpri) x_set_ipm(intpri)
#define i_set_ipm(intpri) x_set_ipm(intpri)

/*
 *  (��ǥ���)�����ͥ���٥ޥ����λ���
 *
 *  ipm���ͤ��֤�
 */
Inline PRI
x_get_ipm(void)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	return(EXT_IPM(p_tpcb->iipm));
}

#define t_get_ipm() x_get_ipm()
#define i_get_ipm() x_get_ipm()

/*
 * �ʥ�ǥ��Ρ˳�����׵�ػߥե饰�Υ��å�
 *
 *  ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��åȤ��ơ�����ߤ�
 *  �ػߤ��롥�ޤ����ʥ�ǥ��Ρ˳�����׵�ػߥե饰���������idf����
 *  ������ӥåȤ�򥻥åȤ��롥
 *  ������׵��ޥ������뵡ǽ�򥵥ݡ��Ȥ��Ƥ��ʤ����ˤϡ�false���֤�
 */
Inline bool_t
x_disable_int(INTNO intno)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	if ((p_tpcb->bitpat_cfgint & INTNO_BITPAT(INTNO_MASK(intno))) == 0U) {
		return(false);
	}

	p_tpcb->idf |= INTNO_BITPAT(INTNO_MASK(intno));
	set_ienable(~(my_iipm_mask_table[p_tpcb->iipm]|p_tpcb->idf));

	return(true);
}

#define t_disable_int(intno)  x_disable_int(intno)
#define i_disable_int(intno)  t_disable_int(intno)

/* 
 * (��ǥ���)����׵�ػߥե饰�β��
 *
 * ���ꤵ�줿��������ֹ�γ�����׵�ػߥե饰�Υ��ꥢ���ơ�����ߤ�
 * ���Ĥ��롥�ޤ����ʥ�ǥ��Ρ˳�����׵�ػߥե饰���������idf����
 * ������ӥåȤ�򥯥ꥢ���롥
 * ������׵��ޥ������뵡ǽ�򥵥ݡ��Ȥ��Ƥ��ʤ����ˤϡ�false���֤�
 */
Inline bool_t
x_enable_int(INTNO intno)
{
	TPCB *p_tpcb = get_my_p_tpcb();

	if ((p_tpcb->bitpat_cfgint & INTNO_BITPAT(INTNO_MASK(intno))) == 0U) {
		return(false);
	}

	p_tpcb->idf &= ~INTNO_BITPAT(INTNO_MASK(intno));
	set_ienable(~(my_iipm_mask_table[p_tpcb->iipm]|p_tpcb->idf));

	return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 * ������׵�Υ��ꥢ
 */
Inline void
x_clear_int(INTNO intno)
{

}

#define t_clear_int(intno) x_clear_int(intno) 
#define i_clear_int(intno) x_clear_int(intno) 


/*
 *  ������׵�Υ����å�
 */
Inline bool_t
x_probe_int(INTNO intno)
{
	return((current_ipending() & INTNO_BITPAT(INTNO_MASK(intno))) != 0);
}

#define t_probe_int(intno) x_probe_int(intno)
#define i_probe_int(intno) x_probe_int(intno)

/*
 *  ������׵�饤���°��������
 */
extern void x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask);

/*
 *  ����ߥϥ�ɥ���������ɬ�פ�IRC���
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
 *  ̤����γ���ߤ����ä����ν���
 */
extern void default_int_handler(void *p_exinf);

/*
 *  CPU�㳰��ǽ
 */

/*
 *  CPU�㳰�ե졼��Υ��ե��å�
 */
#define CPUEXC_FLM_EXCNO   0x00U
#define CPUEXC_FLM_ESTATUS 0x01U
#define CPUEXC_FLM_NEST    0x02U
#define CPUEXC_FLM_PC      0x03U
#define CPUEXC_FLM_IPM     0x04U

/*
 * �������å����¸���˴ޤޤ��ɸ����㳰������ǽ�ν�����������Ѥ��ʤ�
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 *  CPU�㳰�ϥ�ɥ����Ͽ�ѥơ��֥��kernel_cfg.c��
 */
extern const FP* const p_exch_table[TNUM_PRCID];

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 *
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥ�������������ƥ����Ȥλ���false��
 *  �����Ǥʤ�����true���֤���
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	return((*(((uint32_t *)p_excinf) + CPUEXC_FLM_NEST) != 0U));
}

/*
 *  CPU�㳰��ȯ����������(��ǥ���)�����ͥ���٥ޥ����λ���
 */
Inline uint8_t
exc_get_ipm(void *p_excinf)
{
	return((uint8_t)(*(((uint32_t *)p_excinf) + CPUEXC_FLM_IPM)));
}

/*
 * CPU�㳰��ȯ������������CPU��å����֤λ���
 *
 *  CPU��å����֤ξ���true��CPU��å�������֤ξ��ˤ�false���֤�
 */
Inline bool_t
exc_sense_lock(void *p_excinf)
{
	return((*(((uint32_t *)p_excinf) + CPUEXC_FLM_ESTATUS) & STATUS_PIE) != STATUS_PIE);
}

/*
 * ����ߥ�å����֤�
 */
Inline bool_t
exc_sense_int_lock(void *p_excinf)
{
	return false;
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߤΥޥ������֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ����ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ����ʥ�
 *  �ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ������true�������Ǥʤ���
 *  ��false���֤���CPU�㳰�������ͥ�������γ���߽������ȯ���������
 *  �ˤ�false���֤��ˡ�
 *
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
		   && (exc_get_ipm(p_excinf) == 0U)
		   && !exc_sense_lock(p_excinf)
		   && !exc_sense_int_lock(p_excinf));
}

/*
 *  �ץ��å���¸�ν����
 */
extern void prc_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void prc_terminate(void);

/*
 *  ̤������㳰�����ä����ν���
 */
extern void default_exc_handler(void *p_excinf);

/*
 *  �������ǥ����ѥå���
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���core_support.S��
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
 *  �ǥ����ѥå����ư��ϡ�core_support.S��
 *
 *  start_dispatch�ϡ������ͥ뵯ư���˸ƤӽФ��٤���Τǡ����٤Ƥγ��
 *  �ߤ�ػߤ������֡ʳ���ߥ�å����֤�Ʊ���ξ��֡ˤǸƤӽФ��ʤ����
 *  �ʤ�ʤ���
 */
extern void start_dispatch(void) NoReturn;

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���core_support.S��
 *
 *  exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�����������ƥ�
 *  ���ȡ�CPU��å����֡��ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ��
 *  �٥ޥ�����������֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *  �����ͥ�ν�λ�����θƽФ���core_support.S��
 *
 *  call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *  ����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *  ����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	void	*sp;		/* �����å��ݥ��� */
	FP		pc;			/* �ץ���५���� */
} TSKCTXB;
     
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
    (p_tcb)->tskctxb.sp = (void *)((char_t *)((p_tcb)->p_tinib->stk)    \
                                        + (p_tcb)->p_tinib->stksz);     \
    (p_tcb)->tskctxb.pc = (FP)start_r;                                  \
}

/*
 *  calltex�ϻ��Ѥ��ʤ�
 */
#define OMIT_CALLTEX

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
