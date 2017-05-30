/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007-2011 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.c 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 * �������åȰ�¸�⥸�塼���CT11MPCORE�ѡ�
 */
#include "kernel_impl.h"
#include <sil.h>

/*
 *  str_ker() �����ǥޥ����ץ��å��ǹԤ������
 */
void
target_mprc_initialize(void)
{
	/* MPCore��¸���Ǥν���� */
	chip_mprc_initialize();
}

/*
 * ����Υ١������ɥ쥹�ȥ�����
 */
#define SDRAM_ADDR 0x00000000
#define SRAM_ADDR  0x48000000

#define SDRAM_SIZE 0x08000000 /* 128MB */
#define SRAM_SIZE  0x00200000 /*   1MB */

/*
 * ����ޥåפν������chip��¸������ƤӽФ�����
 * Ʊ���˥���å����ͭ���ˤ���
 */
void
target_mmu_init(void)
{
	MEMORY_ATTRIBUTE m_attribute;

	/*
	 * ������������ʪ�����ɥ쥹 = ���ۥ��ɥ쥹
	 * �Υ󥭥�å���֥롤�Υ�Хåե��֥�Ȥ��� 
	 */
	m_attribute.pa   = 0x00000000;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = 0x80000000;
	m_attribute.ns   = 0;		  /* Secure       */    
	m_attribute.s    = 1;          /* ��ͭ         */
	m_attribute.ap   = 3;          /* �ե륢������ */
	m_attribute.tex  = 0;          /* Strongly Ordered */
	m_attribute.c    = 0;
	m_attribute.b    = 0;

	mmu_map_memory (&m_attribute);

	m_attribute.pa   = 0x80000000;
	m_attribute.va   = m_attribute.pa;

	mmu_map_memory (&m_attribute);

	/*
	 *  Enable caching for the SDRAM
	 */
	m_attribute.pa   = SDRAM_ADDR;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SDRAM_SIZE;
	m_attribute.s    = 1;		  /* ��ͭ		 */
	m_attribute.ap   = 3;		  /* �ե륢������ */
	m_attribute.tex  = 1;		  /* Outer and Inner */
	m_attribute.c    = 1;		  /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);

	/*
	 *  Enable caching for the SRAM
	 */
	m_attribute.pa   = SRAM_ADDR;	 /* pa is started from 0x48000000 (SRAM) */
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SRAM_SIZE;	 /* 2MB */
	m_attribute.ap   = 3;			 /* �ե륢������ */
	m_attribute.tex  = 1;			 /* Outer and Inner */
	m_attribute.c    = 1;			 /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);
}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	/*
	 * EB�Ȥ���³������
	 */
	if (x_sense_mprc()) {
		eb_init_int_mode();
	}

	/*
	 * ���åװ�¸�ν����
	 */
	chip_initialize();
        
	/*
	 *  UART������
	 */
	ct11mpcore_uart_init();
}

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
#ifndef TOPPERS_ENABLE_SEMIHOSTING
	/*
	 *  ���åװ�¸�ν�λ����
	 */
	chip_exit();

	/*
	 *  ��ȯ�Ķ���¸�ν�λ����
	 */
	ct11mpcore_exit();

	while(1);

#else /* TOPPERS_ENABLE_SEMIHOSTING */
	extern void exit(int);
	if (x_sense_mprc()) {
		exit(0);
	}
	else {
		while(1);
	}
#endif /* TOPPERS_ENABLE_SEMIHOSTING */
}

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char_t c)
{
	if (c == '\n') {
		ct11mpcore_putc('\r');
	}
	ct11mpcore_putc(c);
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼����Ѥ���¬���ѥ����ޤν�����ؿ�
 */
void
perf_timer_initialize(intptr_t exinf)
{
	scu_counter_init();
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼���ѤΥ����󥿤ˤ���¬
 */
void
perf_timer_get(uint32_t *p_time)
{
	*p_time = scu_counter_get_current();
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼���ѤΥ����󥿤ˤ��¬���̤�ñ���Ѵ�
 *  nsec���Ѵ� 
 */
uint32_t
perf_timer_conv_tim(uint32_t time)
{
	return (time * 1000) / CT11MPCORE_CORE_CLK;
}

#ifdef TOPPERS_ENABLE_SEMIHOSTING
extern void start_master(void);

/*
 *  ����ѥ���Υ������ȥ��åץ롼���󤫤�ƤӽФ���롥
 *  sta_ker()��ƤӽФ��ƥ����ͥ�򥹥����Ȥ����롥 
 */
int
main(void)
{
	start_master();
	return 1;
}
#endif /* TOPPERS_ENABLE_SEMIHOSTING */
