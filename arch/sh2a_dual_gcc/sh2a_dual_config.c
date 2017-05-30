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
 *  $Id: sh2a_dual_config.c 800 2011-05-02 08:08:34Z mit-kimai $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH2A-DUAL�ѡ�
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"


/*
 *	����ߥ���ȥ���Υ쥸�������
 */
const IRC_REG irc_reg_tbl[TNUM_PRCID] = {
	IRC_REG_DATA
};

/*
 *	����߸�������쥸���������
 */
uint16_t *const idcnt_tbl_h[TNUM_IDCNT] = {
	IDCNT_REG_DATA
};

/*
 *	���ޥե�����쥸���������
 */
uint8_t *const semr_tbl_b[TNUM_SEMR] = {
	SEMR_REG_DATA
};


/*
 *  str_ker() �μ¹����˥ޥ����ץ��å��Τ߼¹Ԥ������������
 */
void
prc_mprc_initialize(void)
{
	int_t i;
	uint16_t *p_idcnt_h;
	
	/*
	 *	���ޥե�����쥸�����ν����
	 *	��SEMRn��SEMF�ӥåȢ�1�ǡ��꥽�����β�����ɽ����
	 */
	for(i = 0; i < TNUM_SEMR; ++i) {
		sil_wrb_mem(semr_tbl_b[i], SEMR_SEMF_BIT);
	}

	/*
	 * ����߸�������쥸����������
	 * ���ڥ�ե����ο��ˤ�äơ�����߸�������쥸�����ι�����
	 * ���ۤʤ뤿�ᡢ���åװ�¸����������롣
	 */
	for (i = 0; i < TNUM_IDCNT; ++i) {
		p_idcnt_h = idcnt_tbl_h[i];
		if (p_idcnt_h != NULL) {
			/*
			 *	IDCNTn�쥸������INTEN�ӥåȤ򥯥ꥢ
			 *    INTEN�ӥåȤ�����8�ӥåȤ˼��ޤäƤ��ʤ����ᡢ
			 *    sil_clrh_bit���Ѥ��Ƥ⡢��Ŭ������ʤ���
			 *    ��~IDCNT_INTEN�򥳥�ѥ�����˵�᤿����������
			 */
			sil_anh_reg(p_idcnt_h, ~IDCNT_INTEN);
		}
	}
}

/*
 *	������׵�饤��°��������
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri, uint_t affinity_mask)
{
	SIL_PRE_LOC;
	INTNO iintno, local_intno;
	uint_t prcindex;
	uint32_t ipr_val;
#ifndef NDEBUG
	bool_t ret;
	uint_t prcid_in_intno = intno >> 16U;
	uint_t bitptn = 1U << (prcid_in_intno - 1U);

	assert((bitptn & affinity_mask) != 0);
	assert(VALID_INTNO_CFGINT(prcid_in_intno, intno));
	assert((-15 <= intpri) && (intpri <= TMAX_INTPRI));
#endif /* NDEBUG */

	local_intno	= LOCAL_INTNO(intno);
	prcindex = x_prc_index();

	SIL_LOC_INT();

	/*
	 *	��ö�����̤˳���ߤ�ػߤ���ʳ���߶ػߥե饰�򥻥åȡ�
	 */
#ifdef NDEBUG
	(void)x_disable_int(intno);
#else /* NDEBUG */
	ret = x_disable_int(intno);
	assert(ret == true);
#endif /* NDEBUG */

	/*
	 *	������װ���˳����°�������ꤹ�롣
	 *	���ץ��å��ֳ���ߤΤ߳����ͥ���٥뤬����ʤΤǡ�
	 *	����˿���ʬ���롣
	 */
	if (LOCAL_INTNO_IS_IPI(local_intno)) {
		/*
		 *	�ץ��å��ֳ���ߤξ��
		 *���������⤷�ʤ���
		 */
	}
	else {
		iintno = INT_INTNO(local_intno);			/*	�׸�Ƥ��NMI�ϳ������ʤ�  */
		ipr_val = int_iipm_tbl[prcindex][iintno];	/*	�׸�Ƥ��NMI�ϳ������ʤ�  */
		/*
		 *	�����ͥ���٥������
		 *������������ֹ���б�����IPR���ͤ����ꤹ�롥
		 *������IRQ����ߤξ�硢����߶ػߥե饰�����ꥢ����뤬��
		 *������(x_enable_int_irq( )������������ߥ�å����֤ʤΤǡ�
		 *���������Ϥʤ���(�׸�Ƥ��������������ʤ�����
		 */
		irc_set_ipr(local_intno, ipr_val, prcindex);
		
		/*
		 *	�Ĥ�γ�����װ���˽����򿶤�ʬ���롣
		 */
		if (LOCAL_INTNO_IS_IRQ(local_intno)) {
			/*	IRQ�ξ��  */
			x_config_int_irq(local_intno, intatr, prcindex);
		}
		else if (LOCAL_INTNO_IS_PERIPHERAL(local_intno)) {
			/*	��¢���ե⥸�塼��ξ��  */
			x_config_int_peripheral(local_intno, intatr, prcindex);
		}
		else if (LOCAL_INTNO_IS_PINT(local_intno)) {
			/*	PINT����ߤξ��  */
			x_config_int_pint(local_intno, intatr, prcindex);
		}
		else {
			/*	����¾�����⤷�ʤ�	*/
			assert(0);
		}
	}

	/*
	 *	����߶ػߥե饰�򥯥ꥢ(ɬ�פʾ��)
	 */
	if ((intatr & TA_ENAINT) != 0U) {
#ifdef NDEBUG
		(void) x_enable_int(intno);
#else /* NDEBUG */
		ret = x_enable_int(intno);
		assert(ret == true);
#endif /* NDEBUG */
	}

	SIL_UNL_INT();
}

