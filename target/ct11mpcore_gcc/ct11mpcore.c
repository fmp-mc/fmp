/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2006 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: ct11mpcore.c 835 2011-07-13 02:56:13Z ertl-honda $
 */

#include "kernel_impl.h"
#include "pdic/arm_primecell_uart/arm_primecell_uart.h"

/*
 * GIC CPU���󥿥ե�������Ϣ
 */

/*
 * CPU���󥿥ե������ν����
 */
void
gic_cpu_init(void)
{
	/* ����ͥ���٤����� */
	gic_cpu_set_priority(0xf);
    
	/* CPU���󥿥ե�������ͭ���� */
	sil_wrw_mem((void *)(GIC_BASE + GIC_CPUIF_CCR), 1);
}

/*
 * CPU���󥿥ե������ν�λ
 */
void
gic_cpu_stop(void)
{
	/* CPU���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(GIC_BASE + GIC_CPUIF_CCR), 0);    
}

/*
 * GIC DIS���󥿥ե�������Ϣ
 */

/*
 * ����߶ػ�
 */
void
gic_dis_disable_int(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_ECR + offset_addr), (1 << offset_bit));
}

/*
 * ����ߵ���
 */
void
gic_dis_enable_int(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;
    
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_ESR + offset_addr), (1 << offset_bit));
}

/*
 * ����ߥڥ�ǥ��󥰥��ꥢ
 */
void
gic_dis_clear_pending(uint8_t id)
{
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_PCR + offset_addr), (1 << offset_bit));
}

/*
 * ����ߥڥ�ǥ��󥰥��å�
 */
void
gic_dis_set_pending(uint8_t id){
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_PSR + offset_addr), (1 << offset_bit));    
}

/*
 * ������׵�Υ����å�
 */
bool_t
gic_dis_probe_int(uint8_t id){
	uint32_t state;
	uint16_t offset_addr;
	uint16_t offset_bit;

	offset_addr = (id / 32) * 4;
	offset_bit  = id % 32;

	state = sil_rew_mem((void *)(GIC_BASE + GIC_DIS_PSR + offset_addr));
    
	if((state & (1 << offset_bit)) == (1 << offset_bit)){
		return(true);
	}else{
		return(false);
	}
}

/*
 * ���������Υ��å�
 */
void
gic_dis_config(uint8_t id, uint8_t config){
	uint16_t offset_addr;
	uint16_t offset_bit;
	uint32_t cfgr_reg_val;

	offset_addr = (id / 16) * 4;
	offset_bit  = (id % 16) * 2;

	cfgr_reg_val  = sil_rew_mem((void *)(GIC_BASE + GIC_DIS_CFGR + offset_addr));
	cfgr_reg_val &= ~(0x03U << offset_bit);
	cfgr_reg_val |= (0x03U & config) << offset_bit;
      
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_CFGR + offset_addr), cfgr_reg_val);
}

/*
 * �����ͥ���٤Υ��å�
 * ����ɽ�����Ϥ��� 
 */
void
gic_dis_set_priority(uint8_t id, int pri){
	uint16_t offset_addr;
	uint16_t offset_bit;
	uint32_t pr_reg_val;

	offset_addr = (id / 4) * 4;
	offset_bit  = (id % 4) * 8;

	pr_reg_val  = sil_rew_mem((void *)(GIC_BASE + GIC_DIS_PR + offset_addr));
	pr_reg_val &= ~(0xffU << offset_bit);
	pr_reg_val |= (0x0fU & pri) << (offset_bit + 4); 
    
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_PR + offset_addr), pr_reg_val);
}

/*
 * DIC���󥿥ե������ν����
 */
void
gic_dis_init(void)
{
	int i;
    
	/* DIC���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_CR), 0);        

	/* ����ߤ����ƶػ� */
	for(i = 0; i < GIC_TNUM_INT/32; i++){
		sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_ECR + (4 * i)), 0xffffffff);    
	}

	/* �ڥ�ǥ��󥰤򥯥ꥢ */
	for(i = 0; i < GIC_TNUM_INT/32; i++){
		sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_PCR + (4 * i)), 0xffffffff);    
	}

	/* ͥ���ٺ��������  */
	for(i = 0; i < GIC_TNUM_INT/4; i++){
		sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_PR + (4 * i)), 0xffffffff);    
	}

	/* �������åȽ���� */
	for(i = 0; i < GIC_TNUM_INT/4; i++){
		sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_TAR + (4 * i)), 0x01010101);
	}

	/* �⡼�ɽ����(1-N Level) */
	for(i = 0; i < GIC_TNUM_INT/16; i++){
		sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_CFGR + (4 * i)), 0x55555555);
	}

	/* DIC���󥿥ե�������ͭ���� */
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_CR), 1);       
}

/*
 * DIC���󥿥ե������ν�λ
 */
void
gic_dis_stop(void)
{
	/* DIC���󥿥ե�������̵���� */
	sil_wrw_mem((void *)(GIC_BASE + GIC_DIS_CR), 0);    
}

#ifdef G_SYSLOG

#define my_prc_uart_base	UART0_BASE

#else

/*
 *  ���٥���Ϥǥץ��å���˻��Ѥ���UART�Υ��ɥ쥹
 */
static const uint32_t prc_uart_base_table[TNUM_PRCID] = {
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
#define my_prc_uart_base	(prc_uart_base_table[x_prc_index()])

#endif /* G_SYSLOG */

/*
 *  UART����Υݡ���󥰽���
 */
void
ct11mpcore_putc(char_t c){
	/* �Хåե��������Τ��Ԥ� */
	while((sil_rew_mem((void *)(my_prc_uart_base + UART_FR)) & UART_FR_TXFF)
		  == UART_FR_TXFF);
	/* �񤭹��� */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_DR), c);
}

/*
 * �ݡ���󥰽��ϤΤ���ν����
 */
void
ct11mpcore_uart_init(void){
	char_t c;
    
	/* UART��� */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_CR), 0x00);

	/* ���顼�ե饰�򥯥ꥢ */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_RSR), 0x00);
    
	/* FIFO����ˤ��� */
	while((sil_rew_mem((void *)(my_prc_uart_base + UART_FR)) & UART_FR_RXFE)
		  != UART_FR_RXFE){
		/* �Хåե�������ɤ߹��� */
		c = sil_rew_mem((void *)(my_prc_uart_base + UART_DR));
	}

	/* �ܡ��졼�Ȥ����� */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_IBRD), UART_IBRD_38400);
	sil_wrw_mem((void *)(my_prc_uart_base + UART_FBRD), UART_FBRD_38400);
    
    
	/* �ǡ����ե����ޥåȤȡ�FIFO�Υ⡼�ɤ����� */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_LCR_H), UART_LCR_H_WLEN_8);
        
	/* UART�Ƴ� */
	sil_wrw_mem((void *)(my_prc_uart_base + UART_CR),
				(sil_rew_mem((void *)(my_prc_uart_base + UART_CR))
				 | UART_CR_RXE | UART_CR_TXE | UART_CR_UARTEN));
}

/*
 * EB��¢�����ޤν����
 */
void
ebtimer_init(void)
{
	/*
	 * �����󥿡�����å���1MHz��
	 */
	sil_wrw_mem((void *)SYSTEM_CONTROLER, 
				(sil_rew_mem((void *)SYSTEM_CONTROLER)) | SYSTEM_CONTROLER_TIMER01_1MHZ);

	/* ��������� */
	sil_wrw_mem((void *)TIMER01_0_CTRL, 0x00);
	/* ��������ͤ򥻥å� */
	sil_wrw_mem((void *)TIMER01_0_LOAD, 0xffffffff);
	/* �����ޥ������ȡ����������ޡ�����ߵ��ġ�32bit������ */
	sil_wrw_mem((void *)TIMER01_0_CTRL,
				(TIMER_CTRL_TIMER_EN|TIMER_CTRL_PERIODIC|TIMER_CTRL_TIMESIZE_32));
}
