/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_ipi.h 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 *  �ץ��å��ֳ���ߥɥ饤�С�KZM_CA9�ѡ�
 */

#ifndef TOPPERS_TARGET_IPI_H
#define TOPPERS_TARGET_IPI_H

#include "mpcore.h"

/*
 *  ���Ѥ���SGI���ֹ�
 */
#ifdef TOPPERS_SAFEG_SECURE
#define IPINO_DIS  DIC_IRQNO_IPI2
#define IPINO_EXT  DIC_IRQNO_IPI3
#else  /* !TOPPERS_SAFEG_SECURE */
#define IPINO_DIS  DIC_IRQNO_IPI0
#define IPINO_EXT  DIC_IRQNO_IPI1
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  �ǥ����ѥå��׵��ѤΥץ��å��ֳ���ߤγ����ͥ����
 */
#ifdef TOPPERS_SAFEG_SECURE
#define INTPRI_IPI_DIS_PRC1   (-16)
#define INTPRI_IPI_DIS_PRC2   (-16)
#define INTPRI_IPI_DIS_PRC3   (-16)
#define INTPRI_IPI_DIS_PRC4   (-16)
#else  /* !TOPPERS_SAFEG_SECURE */
#define INTPRI_IPI_DIS_PRC1   (-2)
#define INTPRI_IPI_DIS_PRC2   (-2)
#define INTPRI_IPI_DIS_PRC3   (-2)
#define INTPRI_IPI_DIS_PRC4   (-2)
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  �����ͥ뽪λ�ѤΥץ��å��ֳ���ߤγ����ͥ����
 */
#ifdef TOPPERS_SAFEG_SECURE
#define INTPRI_IPI_EXT_PRC1   (-31)
#define INTPRI_IPI_EXT_PRC2   (-31)
#define INTPRI_IPI_EXT_PRC3   (-31)
#define INTPRI_IPI_EXT_PRC4   (-31)
#else  /* !TOPPERS_SAFEG_SECURE */
#define INTPRI_IPI_EXT_PRC1   (-15)
#define INTPRI_IPI_EXT_PRC2   (-15)
#define INTPRI_IPI_EXT_PRC3   (-15)
#define INTPRI_IPI_EXT_PRC4   (-15)
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  ���åװ�¸�⥸�塼���MPCORE�ѡ�
 */
#include "arm_gcc/mpcore/chip_ipi.h"

#endif /* TOPPERS_TARGET_IPI_H */
