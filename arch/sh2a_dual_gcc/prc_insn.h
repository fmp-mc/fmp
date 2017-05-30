/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: prc_insn.h 867 2011-08-09 05:53:10Z mit-kimai $
 */

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ������SH2A-DUAL�ѡ�
 */

#ifndef TOPPERS_PRC_INSN_H
#define TOPPERS_PRC_INSN_H

/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ɽФ�
 */
Inline uint32_t
current_sr(void)
{
	uint32_t sr;
	Asm("stc  sr,%0" : "=r"(sr));
	return(sr);
}

/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ѹ�
 */
Inline void
set_sr(uint32_t sr)
{
	Asm("ldc %0, sr" : : "r"(sr): "t");
}

#ifdef ENABLE_CACHE
Inline void
set_sr_with_nop(uint32_t sr)
{
	Asm("ldc %0, sr;"
		"nop; nop"		/*  CPU����INTC����ã�����ޤǤ��ٱ�  */
		 : : "r"(sr): "t");
}
#else	/*  ENABLE_CACHE  */
#define set_sr_with_nop(sr)		set_sr(sr)
#endif	/*  ENABLE_CACHE  */

/*
 *  �٥����١����쥸������VBR�ˤθ����ͤ��ɽФ�
 */
Inline void *
current_vbr(void)
{
	void *vbr;
	Asm("stc vbr,%0" : "=r"(vbr));
	return(vbr);
}

/*
 *  �٥����١����쥸������VBR�ˤ�����
 */
Inline void
set_vbr(const FP *vbr)
{
	Asm("ldc  %0, vbr" : : "r"(vbr));
}

/*
 *  �����Х롦�١����쥸������GBR�ˤθ����ͤ��ɽФ�
 */
Inline void *
current_gbr(void)
{
	void *gbr;
	Asm("stc gbr,%0" : "=r"(gbr));
	return(gbr);
}

/*
 *  �����Х롦�١����쥸������GBR�ˤ�����
 */
Inline void
set_gbr(void *gbr)
{
	Asm("ldc  %0, gbr" : : "r"(gbr));
}

#endif /* TOPPERS_PRC_INSN_H */
