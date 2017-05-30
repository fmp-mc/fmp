/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2007-2010 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  $Id: prc_kernel.h 689 2010-09-16 06:11:56Z mit-kimai $
 */

/*
 *		kernel.h�Υץ��å���¸����SH2A-DUAL�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_kernel.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_KERNEL_H
#define TOPPERS_PRC_KERNEL_H

#ifndef TOPPERS_TARGET_KERNEL_H
#error  target_kernel.h is not included!
#endif	/*  TOPPERS_TARGET_KERNEL_H  */

/*
 *  ���ݡ��Ȥ��뵡ǽ�����
 */
#define TOPPERS_TARGET_SUPPORT_DIS_INT 		   /* dis_int�򥵥ݡ��Ȥ��� */
#define TOPPERS_TARGET_SUPPORT_ENA_INT 		   /* ena_int�򥵥ݡ��Ȥ��� */

/*
 *  �����ͥ�����γ����ͥ���٤��ϰ�
 *
 *  TMIN_INTPRI��������ѹ����뤳�Ȥǡ��ɤΥ�٥����⤤�����ͥ����
 *  ����Ĥ�Τ򥫡��ͥ�������γ���ߤȤ��뤫���ѹ��Ǥ��롥
 *����̤������
 *
 *  TMIN_INTPRI������Ǥ����ͤϡ�-15��-1���ϰϤǤ��롥�㤨��TMIN_INTPRI
 *  ��-14�����ꤹ��ȡ�NMI�˲ä��ƥ�٥�15�γ���ߤ������ͥ�������Ȥ�
 *  �롥TMIN_INTPRI��-15�����ꤹ��ȡ�NMI�ʳ��˥����ͥ�������γ���ߤ�
 *  �ߤ��ʤ����Ȥˤʤ롥
 */
#ifndef TMIN_INTPRI
#define TMIN_INTPRI		(-15)		/* �����ͥ���٤κǾ��͡ʺǹ��͡�*/
#endif /* TMIN_INTPRI */

#define TMAX_INTPRI		(-1)		/* �����ͥ���٤κ����͡ʺ����͡�*/

/*
 *  �����°��
 *    �ºݤ˻��ѤǤ�������°���ϡ�������¸����shxx.tf��������롣
 *  
 *    TA_POSEDGE��TA_NEGEDGE��TA_EDGE���̤��ͤˤ��Ƥ���Τϡ�
 *    �Ȥ߹�碌���Ȥ��ˡ�TA_BOTHEDGE�ȶ��̤��뤿��
 */
						/*  0x01��TA_ENAINT��ͽ��  */
						/*  0x02��TA_EDGE��ͽ��  */
#define	TA_POSEDGE		UINT_C(0x04)	/* �ݥ��ƥ��֥��å��ȥꥬ */
#define	TA_NEGEDGE		UINT_C(0x08)	/* �ͥ��ƥ��֥��å��ȥꥬ */
#define	TA_BOTHEDGE		(TA_POSEDGE | TA_NEGEDGE) /* ξ���å��ȥꥬ */

#define	TA_LOWLEVEL		UINT_C(0x10)	/* ����٥�ȥꥬ */
#define	TA_HIGHLEVEL	UINT_C(0x20)	/* �ϥ���٥�ȥꥬ */

/*  �ץ��å���  */
#define TNUM_PRCID	2

/*
 *  �ޥ����ץ��å���ID��
 */
#define TOPPERS_MASTER_PRCID  1

/*
 *  ���饹��ID���
 */
#define TCL_1   		1
#define TCL_2   		2
#define TCL_ADMIN_PRC   3

/*
 *  �����ƥ����δ�������
 */
#define TOPPERS_SYSTIM_GLOBAL			/* �����Х륿���������Υ����ƥ���� */

/*
 *  �����Х륿�����������Υ����ƥ��������ץ��å���ID��
 */
#define TOPPERS_SYSTIM_PRCID  TOPPERS_MASTER_PRCID


#endif /* TOPPERS_PRC_KERNEL_H */
