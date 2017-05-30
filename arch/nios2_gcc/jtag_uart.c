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
 *  @(#) $Id: jtag_uart.c 238 2009-04-28 08:26:25Z ertl-honda $
 */

/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�JTAG UART�ѡ�
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block 
{
	const SIOPINIB  *p_siopinib;  /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	intptr_t        exinf;        /* ��ĥ���� */
	bool_t    openflag;             /* �����ץ�Ѥߥե饰 */
	bool_t    sendflag;             /* ��������ߥ��͡��֥�ե饰 */
	bool_t    getready;             /* ʸ��������������� */
	bool_t    putready;             /* ʸ���������Ǥ������ */
	/*
	 *  JTAG_UART �ϥ��ơ������ȥǡ�����Ʊ���˼������뤿�ᡤ���ơ�������
	 *  �����å�����ȥǡ������ɤ߹���Ǥ��ޤ������Τ��ᡤuart_getready()
	 *  ��¹Ԥ�����Υǡ���������롥
	 */ 
	int8_t    jtag_uart_buf;
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB	siopcb_table[TNUM_PORT];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 * ʸ�������������?
 */ 
Inline bool_t
uart_getready(SIOPCB *p_siopcb)
{
	uint32_t tmp = sil_rew_iop(p_siopcb->p_siopinib->data);
	p_siopcb->jtag_uart_buf = (uint8_t)tmp;
	return ((tmp & JTAG_UART_DATA_RVALID) != 0);
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline bool_t
uart_putready(SIOPCB *p_siopcb)
{
		return((sil_rew_iop(p_siopcb->p_siopinib->ctrl)
				& JTAG_UART_CONTROL_WSAPCE) > 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline uint8_t
uart_getchar(SIOPCB *p_siopcb)
{
	return((uint8_t)(sil_rew_iop(p_siopcb->p_siopinib->data)));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
uart_putchar(SIOPCB *p_siopcb, uint8_t c)
{
	sil_wrw_iop(p_siopcb->p_siopinib->data, c);
}

/*
 * ��������ؿ�
 */
/*
 *  ��������ߵ���
 */
Inline void
uart_enable_send(SIOPCB *p_siopcb)
{
	sil_wrw_iop(p_siopcb->p_siopinib->ctrl,
				sil_rew_iop(p_siopcb->p_siopinib->ctrl)
				|JTAG_UART_CONTROL_WIE);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_send(SIOPCB *p_siopcb)
{
	sil_wrw_iop(p_siopcb->p_siopinib->ctrl,
				sil_rew_iop(p_siopcb->p_siopinib->ctrl)
				& ~JTAG_UART_CONTROL_WIE);
}


/*
 *  ��������ߵ���
 */
Inline void
uart_enable_rcv(SIOPCB *p_siopcb)
{
	sil_wrw_iop(p_siopcb->p_siopinib->ctrl,
				sil_rew_iop(p_siopcb->p_siopinib->ctrl)
				| JTAG_UART_CONTROL_RIE);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_rcv(SIOPCB *p_siopcb)
{
	sil_wrw_iop(p_siopcb->p_siopinib->ctrl,
				sil_rew_iop(p_siopcb->p_siopinib->ctrl)
				& ~JTAG_UART_CONTROL_RIE);
}


/*
 *  SIO�ɥ饤�Фν����
 */
void
sio_initialize(intptr_t exinf)
{
	SIOPCB  *p_siopcb;
	uint_t  i;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (p_siopcb = siopcb_table, i = 0; i < TNUM_PORT; p_siopcb++, i++) {
		p_siopcb->p_siopinib = &(siopinib_table[i]);
		p_siopcb->openflag = false;
		p_siopcb->sendflag = false;
		p_siopcb->jtag_uart_buf = -1;
	}
}

/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
jtag_uartl_opn_por(SIOPCB *p_siopcb, intptr_t exinf)
{
	const SIOPINIB  *p_siopinib;
	p_siopinib = p_siopcb->p_siopinib;

	p_siopcb->exinf = exinf;
	p_siopcb->getready = p_siopcb->putready = false;
	p_siopcb->openflag = true;
	

	return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
	SIOPCB  *p_siopcb = get_siopcb(siopid);
	bool_t    opnflg;
	ER      ercd;

	/*
	 *  �����ץ󤷤��ݡ��Ȥ����뤫��opnflg���ɤ�Ǥ�����
	 */
	opnflg = p_siopcb->openflag;

	/*
	 *  �ǥХ�����¸�Υ����ץ������
	 */
	jtag_uartl_opn_por(p_siopcb, exinf);

	/*
	 *  ���ꥢ��I/O����ߤΥޥ����������롥
	 */
	if (!opnflg) {
		ercd = ena_int(p_siopcb->p_siopinib->intno);
		assert(ercd == E_OK);
	}
	return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
	const SIOPINIB  *p_siopinib;

	p_siopinib = p_siopcb->p_siopinib;
	
	/* ����ߤζػ� */
	sil_wrw_iop(p_siopcb->p_siopinib->ctrl, 0x00);

	p_siopcb->openflag = false;

	/*
	 *  ���ꥢ��I/O����ߤ�ޥ������롥
	 */
	dis_int(p_siopcb->p_siopinib->intno);
}

/*
 *  SIO�γ���ߥϥ�ɥ�
 */
void
sio_isr(intptr_t siopid)
{
	SIOPCB *p_siopcb = get_siopcb(siopid);

	if (uart_getready(p_siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sio_irdy_rcv(p_siopcb->exinf);
	}
	if (uart_putready(p_siopcb)) {
		/*
		 *  ������ǽ������Хå��롼�����ƤӽФ���
		 */
		sio_irdy_snd(p_siopcb->exinf);
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
sio_snd_chr(SIOPCB *p_siopcb, char_t c)
{
	if (uart_putready(p_siopcb)) {
		uart_putchar(p_siopcb, c);
		return(true);
	}
	return(false);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int_t
sio_rcv_chr(SIOPCB *p_siopcb)
{
	uint8_t tmp;

	if (p_siopcb->jtag_uart_buf != -1) {
		tmp = p_siopcb->jtag_uart_buf;
		p_siopcb->jtag_uart_buf = -1;
		return tmp;
	}
	return(false);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sio_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	  case SIO_RDY_SND:
		uart_enable_send(p_siopcb);
		break;
	  case SIO_RDY_RCV:
		uart_enable_rcv(p_siopcb);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sio_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
	switch (cbrtn) {
	  case SIO_RDY_SND:
		uart_disable_send(p_siopcb);
		break;
	  case SIO_RDY_RCV:
		uart_disable_rcv(p_siopcb);
		break;
	}
}
