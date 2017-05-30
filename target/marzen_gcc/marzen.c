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
 *  @(#) $Id: marzen.c 943 2012-10-19 07:50:40Z ertl-honda $
 */

#include "kernel_impl.h"
#include "marzen.h"
#include "sh_scif.h"

#ifndef G_SYSLOG
#error Must use G_SYSLOG!!
#endif /* !G_SYSLOG */


/*
 *  UART����Υݡ���󥰽���
 */
void
marzen_uart_putc(char_t c)
{
	sh_scif_pol_putc(c, 1);
}


/*
 *  �ݡ���󥰽��ϤΤ���ν����
 */
void
marzen_uart_init(void)
{
	/* ����� */
	sh_scif_init(1);
}

static void
pin_init(void)
{
	set_guard_reg(MOD_SEL, 0x01c00000, 0x00800000);
	set_guard_reg(MOD_SEL2, 0x0c000000, 0x04000000);
	set_guard_reg(GPSR0, 0x80000000, 0x00000000);
	set_guard_reg(IPSR3, 0xe0000000, 0x60000000);
	set_guard_reg(GPSR0, 0x00000000, 0x80000000);
	set_guard_reg(GPSR1, 0x00000002, 0x00000000);
	set_guard_reg(IPSR4, 0x0000001c, 0x0000000c);
	set_guard_reg(GPSR1, 0x00000000, 0x00000002);
	set_guard_reg(GPSR3, 0x0c000000, 0x00000000);
	set_guard_reg(IPSR1, 0x01e00000, 0x01400000);
	set_guard_reg(GPSR3, 0x00000000, 0x0c000000);
	set_guard_reg(GPSR4, 0x00000020, 0x00000000);
	set_guard_reg(IPSR6, 0x00038000, 0x00028000);
	set_guard_reg(GPSR4, 0x00000000, 0x00000020);
}


/*
 *  �ܡ��ɰ�¸�ν����
 */
void
marzen_init(void)
{
	/* �ԥ�ν���� */
	pin_init();

	if ((sil_rew_mem((void*)MODEMR) & MD1) == MD1) {
		timer_rate_hz = 62500000 / 4;
	}
	else {
		timer_rate_hz = 46875000/ 4;
	}
}
