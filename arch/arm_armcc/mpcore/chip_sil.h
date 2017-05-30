/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2004-2012 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: chip_sil.h 843 2011-07-15 03:17:19Z ertl-honda $
 */

/*
 *   sil.h�Υ��åװ�¸����MPCORE�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�sil.h����Ƭ�ǥ��󥯥롼�ɤ���롥¾�Υե�
 *  ���뤫���ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥󥯥롼
 *  �ɤ������ˡ�t_stddef.h�����󥯥롼�ɤ����Τǡ������˰�¸���Ƥ�
 *  �褤��
 */

#ifndef TOPPERS_CHIP_SIL_H
#define TOPPERS_CHIP_SIL_H

/*
 *  ARM�Ƕ��̤����
 */
#include "arm_armcc/common/core_sil.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ץ��å�ID�μ���
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	register uint32_t cp15_cpuid __asm("cp15:0:c0:c0:5");

	*p_prcid = (cp15_cpuid & 0x0f) + 1;
}

/*
 *  ���ԥ��å��ѿ���chip_config.c��
 */
extern uint32_t TOPPERS_spn_var;

/*
 *  ���ԥ��å��μ���
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint32_t irq_fiq_mask; 
	register uint32_t locked;
	uint32_t pre_cpsr_c;
	uint32_t dis_cpsr_c;
	ID       prcid;
	register uint32_t cpsr __asm("cpsr");

	sil_get_pid(&prcid);

	/* �ƤӽФ�����cpsr��bit0��7�ξ��� */
	pre_cpsr_c = cpsr;

	/* ������ߥ�å����֤� */
	irq_fiq_mask = TOPPERS_disint();

	/* ������ߥ�å����ְܹԸ��cpsr��bit0��7�ξ��� */
	dis_cpsr_c = cpsr;

	while(true) {
		locked = __ldrex(&TOPPERS_spn_var);
		if (locked != 0) {
			cpsr = pre_cpsr_c;  /* �ƤӽФ����ξ��֤ءʳ���ߵ��ġ� */
			__wfe();
			cpsr = dis_cpsr_c;  /* ������ߥ�å����֤� */
		} else {
			locked = __strex(prcid, &TOPPERS_spn_var);
		}

		if (locked == 0) {
			/* ���ԥ��å����������� */
			/* Data meory barrier */
#if __TARGET_ARCH_ARM == 6
			{
				register uint32_t cp15_dmb __asm("cp15:0:c7:c10:5");
				cp15_dmb = 0;
			}
#elif __TARGET_ARCH_ARM == 7
			__dmb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
			__memory_changed();
			return irq_fiq_mask;
		}
	}
}

/*
 *  ���ԥ��å����ֵ�
 */
Inline void
TOPPERS_sil_unl_spn(uint32_t irq_fiq_mask)
{
	/* ��������Ƥ��񤭴�����ǽ�������� */
	__memory_changed();
	/* Data meory barrier */
#if __TARGET_ARCH_ARM == 6
	{
		register uint32_t cp15_dmb __asm("cp15:0:c7:c10:5");
		cp15_dmb = 0;
	}
#elif __TARGET_ARCH_ARM == 7
	__dmb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
	TOPPERS_spn_var = 0U;
	/* Data Sync Barrier */
#if __TARGET_ARCH_ARM == 6
	{
		register uint32_t cp15_dsb __asm("cp15:0:c7:c10:5");
		cp15_dsb = 0;
	}
#elif __TARGET_ARCH_ARM == 7
	__dsb(0xf)
#endif /* __TARGET_ARCH_ARM == 7 */
	/* ���ԥ��å��Ԥ��Υ������إ��٥�Ȥ����� */
	__sev();

	/* ���ԥ��å��μ������ξ��֤� */
	TOPPERS_set_fiq_irq(irq_fiq_mask);
}

/*
 *  ���ԥ��å��ζ�������
 *  ���ץ��å������ԥ��å���������Ƥ�����˲������롥 
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID prcid;

	sil_get_pid(&prcid);

	if (TOPPERS_spn_var == prcid) {
		TOPPERS_spn_var = 0U;
		/* ���ԥ��å��Ԥ��Υ������إ��٥�Ȥ����� */
		__sev();
	}
}

/*
 *  ���ԥ��å�
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_irq_fiq_mask = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_irq_fiq_mask))

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_CHIP_SIL_H */
