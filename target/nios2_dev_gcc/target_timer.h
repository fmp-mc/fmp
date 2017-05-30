/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2008-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_timer.h 722 2010-10-14 04:43:29Z ertl-honda $
 */

/*
 *  �����ޥɥ饤��
 */

#ifndef TOPPERS_TARGET_TIMER_H
#define TOPPERS_TARGET_TIMER_H

#include "nios2_system.h"

/*
 *  �����޳���ߥϥ�ɥ���Ͽ�Τ�������
 */
/*
 *  �����륿���������Ѥ����
 */
#define INHNO_TIMER1     (0x10000 | SYS_CLK_TIMER_1_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER1     (0x10000 | SYS_CLK_TIMER_1_INT)  /* ������ֹ� */
#define INTPRI_TIMER1    (-6)            /* �����ͥ���� */
#define INTATR_TIMER1    0U              /* �����°�� */

#define INHNO_TIMER2     (0x20000 | SYS_CLK_TIMER_2_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER2     (0x20000 | SYS_CLK_TIMER_2_INT)  /* ������ֹ� */
#define INTPRI_TIMER2    (-6)            /* �����ͥ���� */
#define INTATR_TIMER2    0U              /* �����°�� */

#define INHNO_TIMER3     (0x30000 | SYS_CLK_TIMER_3_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER3     (0x30000 | SYS_CLK_TIMER_3_INT)  /* ������ֹ� */
#define INTPRI_TIMER3    (-6)            /* �����ͥ���� */
#define INTATR_TIMER3    0U              /* �����°�� */

#define INHNO_TIMER4     (0x40000 | SYS_CLK_TIMER_4_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER4     (0x40000 | SYS_CLK_TIMER_4_INT)  /* ������ֹ� */
#define INTPRI_TIMER4    (-6)            /* �����ͥ���� */
#define INTATR_TIMER4    0U              /* �����°�� */

/*
 *  �����Х륿���������Ѥ����
 */
#if TOPPERS_SYSTIM_PRCID == 1
#define INHNO_TIMER_SYSTIM    (0x10000|SYS_CLK_TIMER_1_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x10000|SYS_CLK_TIMER_1_INT)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 2
#define INHNO_TIMER_SYSTIM    (0x20000|SYS_CLK_TIMER_2_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x20000|SYS_CLK_TIMER_2_INT)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 3
#define INHNO_TIMER_SYSTIM    (0x30000|SYS_CLK_TIMER_3_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x30000|SYS_CLK_TIMER_3_INT)  /* ������ֹ� */
#elif TOPPERS_SYSTIM_PRCID == 4
#define INHNO_TIMER_SYSTIM    (0x40000|SYS_CLK_TIMER_4_INT)  /* ����ߥϥ�ɥ��ֹ� */
#define INTNO_TIMER_SYSTIM    (0x40000|SYS_CLK_TIMER_4_INT)  /* ������ֹ� */
#endif /* TOPPERS_SYSTIM_PRCID == 1 */

#define INTPRI_TIMER_SYSTIM   -6    /* �����ͥ���� */
#define INTATR_TIMER_SYSTIM    0U   /* �����°�� */

/*
 * �ץ��å���¸�����������
 */ 
#include "nios2_gcc/avalon_timer.h"

#endif /* TOPPERS_TARGET_TIMER_H */
