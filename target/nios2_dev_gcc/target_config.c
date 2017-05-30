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
 *  @(#) $Id: target_config.c 458 2009-11-04 09:05:06Z ertl-honda $
 */

/*
 * ���åװ�¸�⥸�塼���NIOS2_DEV�ѡ�
 */

#include "kernel_impl.h"
#include <sil.h>
#include "jtag_uart.h"
#include "mp.h"

/*
 *  target_fput_log() ���Ѥ���UART�Υ١������ɥ쥹
 */
const uint32_t target_fput_log_base_table[TNUM_PRCID] = {
	JTAG_UART_1_BASE,
#if TNUM_PRCID >= 2
	JTAG_UART_2_BASE,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	JTAG_UART_3_BASE,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	JTAG_UART_4_BASE,
#endif /* TNUM_PRCID >= 4 */
};

/*
 *  �ץ��å��ֳ����HW�Υ١������ɥ쥹
 */
const uint32_t target_prc_int_base_table[TNUM_PRCID] = {
	PRC_INT_1_BASE,
#if TNUM_PRCID >= 2
	PRC_INT_2_BASE,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	PRC_INT_3_BASE,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	PRC_INT_4_BASE,
#endif /* TNUM_PRCID >= 4 */
};

/*
 *  ��������å��Υơ��֥�
 */
const uint32_t target_tsk_lock_table[TNUM_PRCID] = {
	TSK_MUTEX_1_BASE,
#if TNUM_PRCID >= 2
	TSK_MUTEX_2_BASE,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	TSK_MUTEX_3_BASE,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	TSK_MUTEX_4_BASE,
#endif /* TNUM_PRCID >= 4 */
};

/*
 *  ���֥������ȥ�å��Υơ��֥�
 */
const uint32_t target_obj_lock_table[TNUM_PRCID] = {
	OBJ_MUTEX_1_BASE,
#if TNUM_PRCID >= 2
	OBJ_MUTEX_2_BASE,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	OBJ_MUTEX_3_BASE,
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	OBJ_MUTEX_4_BASE,
#endif /* TNUM_PRCID >= 4 */
};

/*
 *  str_ker() �����ǥޥ����ץ��å��ǹԤ������
 */
void
target_mprc_initialize(void)
{

}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{   
	/*
	 *  Nios2��¸�ν����
	 */
	prc_initialize();
}

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	/*
	 *  Nios2��¸�ν�λ����
	 */
	prc_terminate();

	while(1);
}

/*
 *  �������åȰ�¸��ʸ������
 */
void
target_fput_log(char_t c)
{
	uint32_t base = target_fput_log_base_table[x_prc_index()];

	if (c == '\n') {
		jtag_uart_putc(base, '\r');
	}
	jtag_uart_putc(base, c);
}
