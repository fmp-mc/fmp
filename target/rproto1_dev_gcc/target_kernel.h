/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
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
 *  @(#) $Id: target_kernel.h 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *  kernel.h�Υ������åȰ�¸����RPROTO1_DEV�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�kernel.h�ǥ��󥯥롼�ɤ���롥¾�Υե�
 *  ���뤫��ľ�ܥ��󥯥롼�ɤ��뤳�ȤϤʤ������Υե�����򥤥󥯥롼��
 *  �������ˡ�t_stddef.h�����󥯥롼�ɤ����Τǡ������˰�¸���Ƥ��
 *  ����
 */

#ifndef TOPPERS_TARGET_KERNEL_H
#define TOPPERS_TARGET_KERNEL_H

/*
 *  ������ƥ��å������
 */
#define TIC_NUME   1U            /* ������ƥ��å��μ�����ʬ�� */
#define TIC_DENO   1U            /* ������ƥ��å��μ�����ʬ�� */

/*
 *  �����Х륿�����������Υ����ƥ��������ץ��å���ID��
 */
#define TOPPERS_SYSTIM_PRCID  1

/*
 *  �ޥ����ץ��å���ID��
 */
#define TOPPERS_MASTER_PRCID  1

/*
 *  ���饹��ID���
 */
#define TCL_1  1
#define TCL_2  2
#define TCL_3  3
#define TCL_4  4

/*
 *  �����ƥ����δ�������
 */
#define TOPPERS_SYSTIM_LOCAL			/* �����륿���������Υ����ƥ���� */
//#define TOPPERS_SYSTIM_GLOBAL			/* �����Х륿���������Υ����ƥ���� */

/*
 *  �ץ��å��Ƕ��̤����
 */
#include "sh4a_gcc/prc_kernel.h"

/*
 * �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �¹Ի���ʬ�۽����ѤΥ������ͤ��Ѵ�
 */
Inline uint_t
target_convert_hist_count(uint_t pcount)
{
  //�ʥΤ��飱���ʥ�ñ�̤��Ѵ� 10-8��
//	return  pcount / 10;
	return  pcount; 
}

#define HIST_CONV_TIM    target_convert_hist_count
#define HIST_INIT_TIM    perf_timer_initialize
#define HIST_GET_TIM     get_ntim
#define HIST_BM_HOOK     synco_asm

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_TARGET_KERNEL_H */
