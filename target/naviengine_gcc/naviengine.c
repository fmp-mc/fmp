/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: naviengine.c 447 2009-10-16 08:51:47Z ertl-honda $
 */

#include "kernel_impl.h"
#include "naviengine.h"

#ifdef G_SYSLOG

#define my_prc_uart_base	UART0_BASE

#else

/*
 *  ���٥���Ϥǥץ��å���˻��Ѥ���UART�Υ��ɥ쥹
 */
const uint32_t prc_uart_base_tbl[TNUM_PRCID] = {
	UART0_BASE,
#if TNUM_PRCID >= 2
	UART1_BASE,
#endif /* TNUM_PRCID >= 2 */
#if TNUM_PRCID >= 3
	UART2_BASE,  
#endif /* TNUM_PRCID >= 3 */
#if TNUM_PRCID >= 4
	UART3_BASE,
#endif /* TNUM_PRCID >= 4 */
};

/*
 *  ���ץ��å������Ѥ���UART�Υ��ɥ쥹
 */
#define my_prc_uart_base	(prc_uart_base_tbl[x_prc_index()])

#endif /* G_SYSLOG */


/*
 *  UART����Υݡ���󥰽���
 */
void
naviengine_uart_putc(char_t c)
{
	/* �Хåե��������Τ��Ԥ� */
	while((sil_reb_mem((void *)(my_prc_uart_base + UART_LSR_REG)) & 0x20U)
          == 0x00U);
	/* �񤭹��� */
	sil_wrb_mem((void *)(my_prc_uart_base + UART_THR_REG), c);
	/* �Хåե��������Τ��Ԥ� */
	while((sil_reb_mem((void *)(my_prc_uart_base + UART_LSR_REG)) & 0x20U)
		  == 0x00U);
}


/*
 * �ݡ���󥰽��ϤΤ���ν����
 */
void
naviengine_uart_init(void)
{
	sil_wrb_mem((void *)(my_prc_uart_base + UART_LCR_REG), 0x83);
	sil_wrb_mem((void *)(my_prc_uart_base + UART_DLL_REG), 0xD8);
	sil_wrb_mem((void *)(my_prc_uart_base + UART_DLM_REG), 0x00);
	sil_wrb_mem((void *)(my_prc_uart_base + UART_LCR_REG), 0x03);
	sil_wrb_mem((void *)(my_prc_uart_base + UART_IER_REG), 0x00);
	sil_wrb_mem((void *)(my_prc_uart_base + UART_FCR_REG), 0x00);
}
