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
 *  @(#) $Id: target_config.h 564 2010-04-14 00:53:34Z ertl-honda $
 */

/*
 *  �������åȰ�¸�⥸�塼���SH7786_DEV�ѡ�
 *
 *  �����ͥ�Υ������åȰ�¸���Υ��󥯥롼�ɥե����롥kernel_impl.h�Υ���
 *  ���åȰ�¸���ΰ����դ��Ȥʤ롥
 */

#ifndef TOPPERS_TARGET_CONFIG_H
#define TOPPERS_TARGET_CONFIG_H

/*
 *  �������åȥ����ƥ�Υϡ��ɥ������񸻤����
 */
#include "sh7786_dev.h"

/*
 *  get_utm�򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define SUPPORT_GET_UTM

/*
 *  FMP�����ͥ�ư����Υ���ޥåפȴ�Ϣ�������
 *       
 *      0x08000000 -  �������ΰ�
 *      0x08050000 -  �ǡ����ΰ�
 */

/*
 *  �ǥե���Ȥ��󥿥�������ƥ������ѤΥ����å��ΰ�����
 */
#define DEFAULT_PRC1_ISTKSZ  (1024 * 8)  /* 8KB */
#define DEFAULT_PRC2_ISTKSZ  (1024 * 8)  /* 8KB */
#define DEFAULT_PRC3_ISTKSZ  (1024 * 8)  /* 8KB */
#define DEFAULT_PRC4_ISTKSZ  (1024 * 8)  /* 8KB */

/*
 *  ����å���Υ饤�ȥХå���ͭ����
 */
#define ENABLE_CACHE_WRITE_BACK

/*
 *  ����å���Υ��ҡ���󥷤�ͭ����
 */
#define ENABLE_CACHE_COHERENCE

/*
 *  �ǥ����ѥå�����FPU�ΥХ󥯥쥸��������¸��ͭ����
 */
//#define FPU_SAVE_BANKED_REG

/*
 *  ��å�������
 */
//#define TTYPE_KLOCK G_KLOCK
#define TTYPE_KLOCK P_KLOCK
//#define TTYPE_KLOCK F_KLOCK

/*
 *  ���ԥ��å���ǽ������
 */
#define TTYPE_SPN NATIVE_SPN
//#define TTYPE_SPN EMULATE_SPN

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN  256

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ��å����르�ꥺ���FIFO��å������
 */
//#define ENABLE_FIFO_LOCK

/*
 *  str_ker()�����ǥޥ����ץ��å��ǹԤ������
 */
extern void target_mprc_initialize(void);

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

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥���GDB STUB�ƽФ��Ǽ�
 *  �����롥
 */
extern void target_putc(char c);

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1     11
#define SIL_DLY_TIM2     9
     
/*
 *  �ץ��å���¸�⥸�塼���SH4A�ѡ�
 */
#include "sh4a_gcc/sh7786_config.h"

/*
 *  �ȥ졼�����˴ؤ�������
 */
#ifdef TOPPERS_ENABLE_TRACE
#include "logtrace/trace_config.h"
#endif /* TOPPERS_ENABLE_TRACE */
     
#endif  /* TOPPERS_TARGET_CONFIG_H */
