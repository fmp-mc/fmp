/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007-2012 by Embedded and Real-Time Systems Laboratory
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
 * �������åȰ�¸�⥸�塼���NaviEngine�ѡ�
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

	/* NaviEngine ��� MPCore Status �ν���� */
	sil_wrw_mem((void *)NAVIENGINE_MPCORE_STATUS, 0x00);
}

/*
 * ����Υ١������ɥ쥹�ȥ�����
 */
#define SDRAM_PADDR 0x80000000
#define SDRAM_SIZE  0x10000000 /* 256MB */

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
	m_attribute.pa   = SDRAM_PADDR;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SDRAM_SIZE;
	m_attribute.s    = 1;		  /* ��ͭ		 */
	m_attribute.ap   = 3;		  /* �ե륢������ */
	m_attribute.tex  = 1;		  /* Outer and Inner */
	m_attribute.c    = 1;		  /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);

	/*
	 *  �٥������ơ��֥��0x0000���֤����ᡤSDRAM��
	 *  0x0000�������֤��� 
	 */
	m_attribute.pa   = 0x81000000;
	m_attribute.va   = 0x00000000;   
	m_attribute.size = 0x10000000 - 0x01000000;
	m_attribute.ap   = 3;          /* �ե륢������ */
	m_attribute.tex  = 1;          /* Outer and Inner */
	m_attribute.c    = 1;          /* Inner Write-Back, Write Allocate */ 
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
	 * ���åװ�¸�ν����
	 */
	chip_initialize();
        
	/*
	 *  UART������
	 */
#ifdef G_SYSLOG
	if (x_sense_mprc()) {
		naviengine_uart_init();
	}
#else
	naviengine_uart_init();
#endif /* G_SYSLOG */
}

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	/*
	 *  ���åװ�¸�ν�λ����
	 */
	chip_exit();

	/*
	 *  ��ȯ�Ķ���¸�ν�λ����
	 */
	naviengine_exit();

	while(1);
}

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char_t c)
{
	if (c == '\n') {
		naviengine_uart_putc('\r');
	}
	naviengine_uart_putc(c);
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
	return (time * 1000) / NAVIENGINE_CORE_CLK;
}
