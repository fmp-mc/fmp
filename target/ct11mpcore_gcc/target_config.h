/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.h 881 2011-12-31 14:06:52Z ertl-honda $
 */

/*
 *  ���åװ�¸�⥸�塼���CT11MPCORE�ѡ�
 *
 *  �����ͥ�Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  �������åȰ�¸���Υϡ��ɥ������񸻤����
 */
#include "ct11mpcore.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */

/*
 *  ipi_hanlder�ΥХ��ѥ���������Ѥ��뤫
 */
#define USE_IPI_DIS_HANDER_BYPASS

/*
 *  ���ԥ��å���ǽ������
 */
#define TTYPE_SPN NATIVE_SPN
//#define TTYPE_SPN EMULATE_SPN

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN   256

/*
 *  FMP�����ͥ�ư����Υ���ޥåפȴ�Ϣ�������
 *
 *  0x00000000 - 0x0FFFFFFF : DRAM 
 *  0x40000000 - 0x43FFFFFF : NOR flash
 *  0x44000000 - 0x47FFFFFF : DOC flash
 *  0x48000000 - 0x4BFFFFFF : SRAM
 *  0x70000000 - 0x7FFFFFFF : DRAM(mirror)
 */

/*
 *  �ǥե���Ȥ��󥿥�������ƥ������ѤΥ����å��ΰ�����
 */
#define DEFAULT_PRC1_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC2_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC3_ISTKSZ      (1024 * 8)   /* 8KB */
#define DEFAULT_PRC4_ISTKSZ      (1024 * 8)   /* 8KB */

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    20
#define SIL_DLY_TIM2    10

/*
 *  ���åװ�¸�⥸�塼���MPCORE�ѡ�
 */
#include "arm_gcc/mpcore/chip_config.h"

#ifndef TOPPERS_MACRO_ONLY

/*
 * ����ޥåפν������chip��¸������ƤӽФ�����
 * Ʊ���˥���å����ͭ���ˤ���
 */
extern void target_mmu_init(void);

/*
 *  �������åȥ����ƥ��¸�ν����
 */
extern void target_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���
 */
extern void target_exit(void) NoReturn;

#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_TARGET_CONFIG_H */
