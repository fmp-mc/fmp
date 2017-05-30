/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2010 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
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
 *  $Id: prc_ipi.h 816 2011-06-30 02:46:57Z mit-kimai $
 */

/*
 *  �ץ��å��ֳ���ߥɥ饤�С�SH2A-DUAL�ѡ�
 */

#ifndef TOPPERS_PRC_IPI_H
#define TOPPERS_PRC_IPI_H

/*
 *  make depend����cfg1_out.c�ǥ���ܥ�irc_reg_tbl��
 *  ���Ĥ����ʤ��ʤ뤿�ᡢ�ɲ�
 *  ���׸�Ƥ������Ϥ���ʤ��Ϥ���
 */
#include "prc_rename.h"		/*  irc_reg_tbl�Υ�͡���  */
#include "prc_config.h"

/*
 *  ������ֹ�ȳ���ߥϥ�ɥ��ֹ�
 */
#define INTNO_IPI_PRC1  (0x10000|IPI08_VECTOR)  /* ������ֹ� */
#define INHNO_IPI_PRC1  INTNO_IPI_PRC1  		/* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC1 (-8)					/* �����ͥ���� */

#define INTNO_IPI_PRC2  (0x20000|IPI08_VECTOR)  /* ������ֹ� */
#define INHNO_IPI_PRC2  INTNO_IPI_PRC2  		/* ����ߥϥ�ɥ��ֹ� */
#define INTPRI_IPI_PRC2 (-8)					/* �����ͥ���� */

/*
 *  �ץ��å��ֳ���ߤ�ȯ��
 */
Inline void
target_ipi_raise(uint_t procid)
{
	uint16_t *p_ipcr8_h = irc_reg_tbl[procid - 1].ipcr8_h;
	
	sil_wrh_mem((uint16_t *)p_ipcr8_h, IPCR_CI);
}

/*
 *  �ץ��å��ֳ���ߤΥ��ꥢ
 */
Inline void
target_ipi_clear(void)
{

}

#endif /* TOPPERS_PRC_IPI_H */
