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
 *  @(#) $Id: serial.c 898 2012-02-24 05:15:21Z ertl-honda $
 */

/*
 *		���ꥢ�륤�󥿥ե������ɥ饤��
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "kernel_cfg.h"

/*
 *  �ݥ��󥿤Υ��󥯥����
 */
#define INC_PTR(ptr, bufsz)		do {					\
	if (++(ptr) == (bufsz)) { (ptr) = 0; }				\
} while(false)

/*
 *  ���ꥢ��ݡ��Ƚ�����֥�å�
 */
typedef struct serial_port_initialization_block {
	ID		rcv_semid;		/* �����Хåե������ѥ��ޥե���ID */
	ID		snd_semid;		/* �����Хåե������ѥ��ޥե���ID */
	uint_t	rcv_bufsz;		/* �����Хåե������� */
	char_t	*rcv_buffer;	/* �����Хåե� */
	uint_t	snd_bufsz;		/* �����Хåե������� */
	char_t	*snd_buffer;	/* �����Хåե� */
} SPINIB;

/*
 *  ���ꥢ��ݡ��ȴ����֥�å�
 */
typedef struct serial_port_control_block {
	const SPINIB *p_spinib;		/* ���ꥢ��ݡ��Ƚ�����֥�å� */
	SIOPCB	*p_siopcb;			/* ���ꥢ��I/O�ݡ��ȴ����֥�å� */
	bool_t	openflag;			/* �����ץ�Ѥߥե饰 */
	bool_t	errorflag;			/* ���顼�ե饰 */
	uint_t	ioctl;				/* ư������������� */

	uint_t	rcv_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	rcv_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	rcv_count;			/* �����Хåե����ʸ���� */
	char_t	rcv_fc_chr;			/* ����٤�START/STOP */
	bool_t	rcv_stopped;		/* STOP�����ä����֤��� */

	uint_t	snd_read_ptr;		/* �����Хåե��ɽФ��ݥ��� */
	uint_t	snd_write_ptr;		/* �����Хåե�����ߥݥ��� */
	uint_t	snd_count;			/* �����Хåե����ʸ���� */
	bool_t	snd_stopped;		/* STOP�������ä����֤��� */
} SPCB;

/*
 *  ���ꥢ��ݡ��Ȥ����������ǽ������Хå� (Task context version)
 */
void
sio_rdy_snd(intptr_t exinf)
{
	SPCB	*p_spcb;

	p_spcb = (SPCB *) exinf;
	if (p_spcb->rcv_fc_chr != '\0') {
		/*
		 *  START/STOP ���������롥
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb, p_spcb->rcv_fc_chr);
		p_spcb->rcv_fc_chr = '\0';
	}
	else if (!(p_spcb->snd_stopped) && p_spcb->snd_count > 0U) {
		/*
		 *  �����Хåե��椫��ʸ������Ф����������롥
		 */
		(void) sio_snd_chr(p_spcb->p_siopcb,
					p_spcb->p_spinib->snd_buffer[p_spcb->snd_read_ptr]);
		INC_PTR(p_spcb->snd_read_ptr, p_spcb->p_spinib->snd_bufsz);
		if (p_spcb->snd_count == p_spcb->p_spinib->snd_bufsz) {
			if (sig_sem(p_spcb->p_spinib->snd_semid) < 0) {
				p_spcb->errorflag = true;
			}
		}
		p_spcb->snd_count--;
	}
	else {
		/*
		 *  �������٤�ʸ�����ʤ����ϡ�������ǽ������Хå���
		 *  �ػߤ��롥
		 */
		sio_dis_cbr(p_spcb->p_siopcb, SIO_RDY_SND);
	}
}
