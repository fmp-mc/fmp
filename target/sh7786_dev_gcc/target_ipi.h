/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2009 by Embedded and Real-Time Systems Laboratory
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: target_ipi.h 513 2010-02-01 05:42:13Z ertl-honda $
 */

/*
 *  �ץ����å��ֳ���ߥɥ饤�С�SH7786_DEV�ѡ�
 */

#ifndef TOPPERS_TARGET_IPI_H
#define TOPPERS_TARGET_IPI_H

#include "kernel_impl.h"

#define INHICI0_INTEVT     (0x00010000 | ICI0_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INHICI1_INTEVT     (0x00020000 | ICI1_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INHICI2_INTEVT     (0x00030000 | ICI2_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INHICI3_INTEVT     (0x00040000 | ICI3_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */

#define INTICI0_INTEVT     (0x00000000 | ICI0_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INTICI1_INTEVT     (0x00000000 | ICI1_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INTICI2_INTEVT     (0x00000000 | ICI2_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */
#define INTICI3_INTEVT     (0x00000000 | ICI3_INTEVT) 	/* ����ߥϥ�ɥ��ֹ� */

#ifndef TOPPERS_MACRO_ONLY
/*
 *  �ץ����å��ֳ���ߤ�ȯ��
 */
Inline void
target_ipi_raise(uint_t prcid)
{
	ici_int(prcid - 1);
}

/*
 *  �ץ����å��ֳ���ߤΥ��ꥢ
 */
Inline
void target_ipi_clear(void)
{
	ici_int_clr();
}
#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_IPI_H */