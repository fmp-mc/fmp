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
 *  $Id: sh2a_dual_config.h 880 2011-09-02 07:37:42Z mit-kimai $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH2A-DUAL�ѡ�
 *
 *	���Υ��󥯥롼�ɥե�����ϡ�sh7xxx_config.h�ʤޤ��ϡ��������饤��
 *	�롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *	ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_SH2A_DUAL_CONFIG_H
#define TOPPERS_SH2A_DUAL_CONFIG_H

/*  sh2a_dual_config.h��sh7xxx_config.h(target_config.h)���饤�󥯥롼�ɤ����  */
#ifndef TOPPERS_TARGET_CONFIG_H
#error  sh7xxx_config.h(target_config.h) is not included!
#endif	/*  TOPPERS_TARGET_CONFIG_H  */
/*
 *	�����μ���
 */
#define SH2A_DUAL

/*
 *	���ѤǤ���̿�᥻�å�
 *	��SH1��̿��ˤĤ��Ƥϡ����٤ƤΥ����ǥ��ݡ��Ȥ����Τǡ�
 *	��������ʤ���
 */
#define TOPPERS_SUPPORT_SH2_INSTRUCTION
#define TOPPERS_SUPPORT_SH2E_INSTRUCTION
#define TOPPERS_SUPPORT_SH2A_INSTRUCTION

/*
 *	������ʳ�����ֹ桿����ߥϥ�ɥ��ֹ桿CPU�㳰�ֹ����Ф�����Υޥ���
 */
#define LOCAL_INTNO_MASK	0xffffU
#define LOCAL_INHNO_MASK	0xffffU
#define LOCAL_EXCNO_MASK	0xffffU

/*
 *	�����Х�ʳ�����ֹ桿CPU�㳰�ֹ��
 *	������ʳ�����ֹ桿CPU�㳰�ֹ���Ѵ�����ޥ���
 */
#define LOCAL_INTNO(intno)		((intno) & LOCAL_INTNO_MASK)
#define LOCAL_EXCNO(excno)		((excno) & LOCAL_EXCNO_MASK)


/*
 *	������ֹ椫�����߼��̤�Ƚ�̤��뤿��Υޥ���
 *	��prc_config.h��������٤����������Υե��������
 *	��LOCAL_INTNO_TO_XXXXX����Ѥ��뤿�ᡢ�����˵��Ҥ��Ƥ��롣
 */
/*	IRQ�����  */
#define LOCAL_INTNO_IS_IRQ(intno) 								\
		((TMIN_INTNO_IRQ <= (intno)) && ((intno) <= TMAX_INTNO_IRQ))
#define INTNO_IS_IRQ(intno)		LOCAL_INTNO_IS_IRQ(LOCAL_INTNO(intno))

/*	��¢���ե⥸�塼��	*/
#define LOCAL_INTNO_IS_PERIPHERAL(intno) 								\
		((TMIN_INTNO_PERIPHERAL <= (intno)) && ((intno) <= TMAX_INTNO_PERIPHERAL))
#define INTNO_IS_PERIPHERAL(intno)	LOCAL_INTNO_IS_PERIPHERAL(LOCAL_INTNO(intno))

/*	PINT�����	*/
#define LOCAL_INTNO_IS_PINT(intno) 								\
		((TMIN_INTNO_PINT <= (intno)) && ((intno) <= TMAX_INTNO_PINT))
#define INTNO_IS_PINT(intno)	LOCAL_INTNO_IS_PINT(LOCAL_INTNO(intno))

/*	�ץ��å��ֳ����	*/
#define LOCAL_INTNO_IS_IPI(intno) 								\
		((TMIN_INTNO_IPI <= (intno)) && ((intno) <= TMAX_INTNO_IPI))
#define INTNO_IS_IPI(intno)		LOCAL_INTNO_IS_IPI(LOCAL_INTNO(intno))

/*
 *	������ֹ椫��IRQ�ֹ�ؤ��Ѵ�
 */
#define LOCAL_INTNO_TO_IRQNO(intno) (((intno) - TMIN_INTNO_IRQ))
#define INTNO_TO_IRQNO(intno) 	LOCAL_INTNO_TO_IRQNO(LOCAL_INTNO(intno))

/*
 *	������ֹ椫��PINT������ֹ�ؤ��Ѵ�
 */
#define LOCAL_INTNO_TO_PINTNO(intno) (((intno) - TMIN_INTNO_PINT))
#define INTNO_TO_PINTNO(intno) 	LOCAL_INTNO_TO_PINTNO(LOCAL_INTNO(intno))

/*
 *	������ֹ椫��IDCNT�쥸�������������ѥ���ǥå����ؤ��Ѵ�
 */
#define LOCAL_INTNO_TO_IDCNT(intno) (((intno) - TMIN_INTNO_IDCNT))
#define INTNO_TO_IDCNT(intno) 	LOCAL_INTNO_TO_IDCNT(LOCAL_INTNO(intno))

/*
 *	������ֹ椫��ץ��å��ֳ���ߤγ����ͥ���٥�ؤ��Ѵ�
 */
#define LOCAL_INTNO_TO_IP_INT_LEVEL(intno) \
		(15U - ((intno) - IPI15_VECTOR))
#define INTNO_TO_IP_INT_LEVEL(intno) 	LOCAL_INTNO_TO_IP_INT_LEVEL(LOCAL_INTNO(intno))

/*
 *	�������ȥ�������IPR�쥸�����Υ��ɥ쥹�κ�
 */
#define PRC_IPR_OFFSET	(C1IPR01_h - C0IPR01_h)


#ifndef TOPPERS_MACRO_ONLY

#include <sil.h>

/*
 *	����ߥ���ȥ���Υ쥸�������
 *	��
 * ���ڥ�ե����ο��ˤ�äơ�����ߥ���ȥ���Υ쥸����������
 * ���ۤʤ뤿�ᡢ���åװ�¸����������롣
 */
extern const IRC_REG irc_reg_tbl[TNUM_PRCID];

/*
 *	����߸�������쥸���������
 */
extern uint16_t *const idcnt_tbl_h[TNUM_IDCNT];

/*
 *	���ޥե�����쥸���������
 */
extern uint8_t *const semr_tbl_b[TNUM_SEMR];

/*
 *  str_ker() �����ǥޥ����ץ��å��ǹԤ������
 */
extern void prc_mprc_initialize(void);


/*
 * IRC�ν����
 */
Inline void
irc_initialize(uint_t prcindex)
{
   	uint_t i;
   	const IRC_REG * p_irc_reg = &irc_reg_tbl[prcindex];
	
	/*	�׸�Ƥ������Ū��������	*/
	/*	�׸�Ƥ��ξ�ץ��å���Ʊ���ͤˤ���	*/
	sil_wrh_reg(p_irc_reg->icr0_h, 0x0000U);
	sil_wrh_reg(p_irc_reg->icr1_h, 0x0000U);
	sil_wrh_reg(p_irc_reg->icr2_h, 0x0000U);
	
#ifdef USE_BANKED_REG
	/*
	 * ��NMI,UBC�ʳ��Τ��٤Ƥγ���ߤǥ쥸�����Х󥯤λ��Ѥ����
	 * ���쥸�����Х󥯡������С��ե��㳰�����
	 */
	sil_wrh_reg(p_irc_reg->ibnr_h, (IBNR_BE0 | IBNR_BOVE));
#else
	/* �쥸�����Х󥯻��Ѷػ� */
	sil_wrh_reg(p_irc_reg->ibnr_h, 0x0000U);
#endif /* USE_BANKED_REG */

   	/*	�����ͥ���٥�����쥸�����ν����  */
	for (i=0; i < TNUM_IPR; ++i) {
		sil_wrh_reg(p_irc_reg->ipr_h[i], 0x0000U);
	}
}


/*
 *	IRQ����ߤ�°������
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 ATR intatr�������°��
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 */
Inline void
x_config_int_irq(INTNO local_intno, ATR intatr, uint_t prcindex)
{
	uint16_t *p_irqer_h, *p_irqrr_h;
	uint32_t icr1_val	= sil_reh_reg((uint16_t *)C0ICR1_h);
	uint32_t irqno		= LOCAL_INTNO_TO_IRQNO(local_intno);
	uint32_t offset		= irqno << 1U;	/*	irqno * 2  */

	/*
	 *	���å��ȥꥬ�λ��꤬�ʤ���С��ǥե���Ȥǥ���٥�ȥꥬ
	 *	�Ȥ��롣
	 *	�����ӥåȤ򥯥ꥢ�����ޤޤǤ���С�����٥�ȥꥬ�Ȥʤ롣
	 */
	icr1_val &=  ~(0x03U << offset);
	
	if((intatr & TA_POSEDGE) != 0U) {
		/*
		 *	�ݥ��ƥ��֥��å�
		 */
		icr1_val |= (IRQ_POSEDGE << offset);
	}

	/*
	 *	�ͥ��ƥ��֥��å��λ��꤬���롢
	 *	�ޤ��ϡ����å��ȥꥬ�ǡ������λ��꤬�ʤ���С�
	 *	�ͥ��ƥ��֥��å��Ȥ��롣
	 */
	if(((intatr & TA_NEGEDGE) != 0U) ||
	   (((intatr & TA_EDGE) != 0U) && ((intatr & TA_BOTHEDGE) == 0U))) {
		/*
		 *	�ͥ��ƥ��֥��å�
		 */
		icr1_val |= (IRQ_NEGEDGE << offset);
	}
	/*
	 *	C0ICR1��C0ICR1��Ʊ�����Ƥ����ꤷ�ʤ���Фʤ�ʤ���
	 *	���׸�Ƥ���ץ��å��֤���¾���椹��ɬ�פ����롣
	 */
	sil_wrh_reg((uint16_t *)C0ICR1_h, icr1_val);
	sil_wrh_reg((uint16_t *)C1ICR1_h, icr1_val);
	
	/*
	 *	CnIRQER�쥸������IRQn�ӥåȤ򥻥åȤ��롣
	 */
	p_irqer_h = irc_reg_tbl[prcindex].irqer_h;
	sil_seth_bit(p_irqer_h, irqno);
	
	/*
	 *	������׵�Υ��ꥢ
	 *	��CnIRQRR�쥸������IRQnF�ӥåȤ򥯥ꥢ���롣
	 */
	p_irqrr_h = irc_reg_tbl[prcindex].irqrr_h;
	sil_clrh_bit(p_irqrr_h, irqno);
}

/*
 *	��¢���ե⥸�塼�뤫��γ���ߤ�°������
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 ATR intatr�������°��
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 */
Inline void
x_config_int_peripheral(INTNO local_intno, ATR intatr, uint_t prcindex)
{
	int_t index 		= LOCAL_INTNO_TO_IDCNT(local_intno);
	uint16_t *p_idcnt_h	= idcnt_tbl_h[index];

	/*
	 *	������׵������դ���CPU�����ꤹ�롣
	 */
	if (prcindex == 0) {
		sil_anh_reg(p_idcnt_h, ~IDCNT_CPUN);
	}
	else {
		sil_orh_reg(p_idcnt_h, IDCNT_CPUN);
	}
}

/*
 *	PINT����ߤ�°������
 *	 INTNO local_intno���ץ��å���ǤΥ�����ʳ�����ֹ�
 *	 ATR intatr�������°��
 *	 uint_t prcindex���ץ��å�������ǥå�����0���ꥸ���
 */
Inline void
x_config_int_pint(INTNO local_intno, ATR intatr, uint_t prcindex)
{
	uint32_t icr2_val	= sil_reh_reg((uint16_t *)C0ICR2_h);
	uint_t pintno 		= LOCAL_INTNO_TO_PINTNO(local_intno);
	uint32_t bitptn		= 1U << pintno;

	/*
	 *	��٥�ȥꥬ�ζ���������
	 *	
	 *	�ǥե���Ȥǥ���٥�ȥꥬ��
	 *	����Ū�ʻ��꤬����С��ϥ���٥�ȥꥬ�Ȥ��롣
	 */
	if((intatr & TA_HIGHLEVEL) != 0U) {
		/*
		 *	�ϥ���٥�ȥꥬ
		 */
		icr2_val |= bitptn;
	}
	else {
		/*
		 *	����٥�ȥꥬ
		 */
		icr2_val &= ~bitptn;
	}

	/*
	 *	C0ICR2��C0ICR2��Ʊ�����Ƥ����ꤷ�ʤ���Фʤ�ʤ���
	 *	���׸�Ƥ���ץ��å��֤���¾���椹��ɬ�פ����롣
	 */
	sil_wrh_reg((uint16_t *)C0ICR2_h, icr2_val);
	sil_wrh_reg((uint16_t *)C1ICR2_h, icr2_val);
}

/*
 *	����ߥϥ�ɥ�������ɬ�פ�IRC���
 *
 *����������׵�Υ��ꥢ���ϰʲ����̤�Ǥ��롣
 *����
 *������IRQ����ߤξ��
 *������������٥븡�Фξ��
 *���������������ꥢ���
 *��������������IRQn���Ϥ����٥뤫��ϥ���٥�ˤ��롣
 *�������������å����Фξ��
 *���������������ꥢ���
 *��������������(1)IRQRR�쥸������IRQnF=1�ξ��֤�꡼�ɸ��0��
 *���������������� �饤�Ȥ��롣
 *��������������(2)IRQn�������㳰������¹Ԥ��롣
 *�����������������ʼ�ưŪ�˥��ꥢ������
 *����
 *��������¢�ڥ�ե���뤫��γ�����׵�ξ��
 *���������ڥ�ե������˳�����׵�Υ��ꥢ��郎�ۤʤ롣
 *����
 *�������äơ�i_begin_int()�Ǥϡ��ä˳���ߥ���ȥ��������
 *����ɬ�פ��ʤ���
 */
Inline void
i_begin_int(INTNO intno)
{
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *	�ץ��å���¸�⥸�塼���SH2A-DUAL�ѡ�
 */
#include "prc_config.h"

#endif /* TOPPERS_SH2A_DUAL_CONFIG_H */
