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
 *  @(#) $Id: prc_sil.h 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *  sil.h�Υץ��å���¸����SH4A�ѡ�
 */
#ifndef TOPPERS_PRC_SIL_H
#define TOPPERS_PRC_SIL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  NMI��������٤Ƥγ���ߤζػ�
 */
Inline uint8_t
TOPPERS_disint(void)
{
	uint32_t  TOPPERS_sr;

	Asm("stc  sr,%0" : "=r"(TOPPERS_sr));
	Asm("ldc %0, sr" : : "r"(TOPPERS_sr | 0x000000f0U) : "memory");
	return((uint8_t)(TOPPERS_sr & 0x000000f0U));
}

/*
 *  �����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
TOPPERS_set_iipm(uint8_t TOPPERS_iipm)
{
	uint32_t  TOPPERS_sr;

	Asm("stc  sr,%0" : "=r"(TOPPERS_sr));
	Asm("ldc %0, sr" : : "r"((TOPPERS_sr & ~0x000000f0U) | TOPPERS_iipm) : "memory");
}

/*
 *  ����ߥ�å����֤�����
 */
#define SIL_PRE_LOC      uint8_t TOPPERS_iipm
#define SIL_LOC_INT()    ((void)(TOPPERS_iipm = TOPPERS_disint()))
#define SIL_UNL_INT()    (TOPPERS_set_iipm(TOPPERS_iipm))

/*
 *  �ץ��å�ID�μ���
 */
Inline void
sil_get_pid(ID *p_prcid)
{
	*p_prcid = *((volatile uint_t *) 0xFF000048) + 1;
}

/*
 *  ���ԥ��å��ѿ���prc_config.c��
 */
extern uint32_t TOPPERS_spn_var;

/*
 *  ��å��������˻��Ѥ�����ߡ��ѿ�
 */
extern  uint32_t dangling_dummy;

/*
 *  ���ԥ��å��μ������̾��ǡ�
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint8_t   iipm;
	uint32_t  result;

retry:
	/* ������ߥ�å����֤�*/
	iipm = TOPPERS_disint();

	Asm("     movli.l	@%2,r0             \n"
		"\t   mov       #0,r3              \n"
		"\t   cmp/eq	r3,r0              \n"
		"\t   bf		1f                 \n"
		"\t   mov		#1,r0              \n"
		"\t   movco.l	r0,@%2             \n"
		"\t   bf		2f           	   \n"  //����
		"\t   mov		#0,%1          	   \n"
		"\t   bra       3f                 \n"
		"\t    nop                         \n"
		"1:\t                              \n"  //���󥰥�󥰡�
		"\t   movco.l	r0,%0              \n"
		"2:\t                              \n"  //���ԤΥѥ�����
		"\t   mov       #1,%1              \n"
		"3:\t                              \n"  //��λ
		:"=m"(dangling_dummy),"=r"(result)
		:"r"(&TOPPERS_spn_var):"r0","r3", "cc");

	if (result != 0) {
		/* ���ԥ��å��������Ǥ��ʤ��ä���� */
		/* ����ߥ�å����֤����ξ��֤� */
		TOPPERS_set_iipm(iipm);
		goto retry;
	}

	return iipm;
}

/*
 *  ���ԥ��å��β������̾��ǡ�
 *��  ��Ȥ�release_lock��Ʊ��
 */
Inline void
TOPPERS_sil_unl_spn(uint8_t iipm)
{
	TOPPERS_spn_var = 0;
	/* ���ԥ��å����ξ��֤� */
	TOPPERS_set_iipm(iipm);
}

/*
 *  ���ԥ��å�
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_iipm = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_iipm))

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_PRC_SIL_H */
