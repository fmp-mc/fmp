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
 * �������åȰ�¸�⥸�塼���KZM_CA9�ѡ�
 */
#include "kernel_impl.h"
#include <sil.h>

extern void *vector_table;

#define CP15_SET_VBAR(x)    Asm("mcr p15, 0, %0, c12, c0, 0"::"r"(x))

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
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x10000000 /* 256MB */


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
	 *  Enable caching for the DDR
	 */
	m_attribute.pa   = DDR_ADDR;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = DDR_SIZE;
	m_attribute.s    = 1;		  /* ��ͭ		 */
	m_attribute.ap   = 3;		  /* �ե륢������ */
	m_attribute.tex  = 1;		  /* Outer and Inner */
	m_attribute.c    = 1;		  /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);
}

#ifdef TOPPERS_SAFEG_SECURE
void
target_tzpc_initialize(void)
{
    /*
     * [TZPC CONFIGURATIONS]
     * TZPC Base Address = 0x100E6000
     */
    //
    *((volatile unsigned int *) 0x100E6000) = 0x0;

    // Decode Protection 0 Set Register(TZPCDECPROT0Set)
    //   * System configuration controller {TZPCDECPROT0Set[2]} is [secure]
    //   * TZPC {TZPCDECPROT0Set[6]} is [secure]
    //    *((unsigned int *) 0x100E6804) = 0xFFBB;
    *((volatile unsigned int *) 0x100E6804) = 0xFFFF;

    // Decode Protectio 1 Set Register(TZPCDECPROT1Set)
    //   * PL351 APB {TZPCDECPROT0[7]} is [secure]
    //     ^ ToDo: ����ˤ��SMC�Х�����³����뤹�٤ƤΥǥХ��������������ػߤˤʤ롣
    //             �����ϡ��ȥ饹��¦�Υ��ꥢ��ݡ��Ȥ򥻥��奢�ˤ��뤿���
    //             �ԤäƤ��뤬������Ū�ˤϥȥ饹��¦�λ��Ѥ���ݡ��Ȥ�UART0���ѹ�����٤���
    //   *
    //    *((unsigned int *) 0x100E6810) = 0xFF7F;
    *((volatile unsigned int *) 0x100E6810) = 0xFFFF;

    // Decode Protectio 2 Set Register(TZPCDECPROT2Set)
    *((volatile unsigned int *) 0x100E681C) = 0xFFFF;
}

void
target_tzasc_initialize(void)
{
    /*
     * [TZASC CONFIGURATIONS]
     * TZASC Base Address = 0x100EC000
     */

    // Action Register
    //*((volatile unsigned int *)0x100EC004) = 2;

    // Region Attributes Register
    //   * region 0
    //     * Secure and Non-secure R/W is [Yes]
    *((volatile unsigned int *)0x100EC108) = 0xF0000000;
    //   * region 1
    //     * region base address is [0x0]
    //     * region size is [4MB]
    //     * Secure R/W is [Yes], Non-secure R/W is [No]
    //     * This field is [enable]
    //*((volatile unsigned int *)0x100EC110) = 0x0;
    //*((volatile unsigned int *)0x100EC118) = 0xC000002B;
}

void
target_gic_initialize(void)
{
	int i;
	unsigned int add;

	/* ����ߤ����ƶػ� */
	for(i = 0; i < 32/32; i++){
		sil_wrw_mem((void *)(DIC_CE + (4 * i)), 0xffffffff);
	}

	/* �ڥ�ǥ��󥰤򥯥ꥢ */
	for(i = 0; i < 32/32; i++){
		sil_wrw_mem((void *)(DIC_CP + (4 * i)), 0xffffffff);
	}

	/* ͥ���ٺ��������  */
    /* Linux����������ʤ���������˽���� */
	for(i = 0; i < 32/4; i++){
        /*
         * �����0xffffffff�Ǥ褤����Linux����������ꥳ���ʹߤ�
         * �����γ����ͥ���٤����ꤷ�ʤ����ᡤ���������ꤹ�롥
         * (Linux�Ǥϡ�0xa0a0a0a0�Ǥ��٤Ƥγ���ߤ��������Ƥ��뤬
         *  �Υ󥻥��奢¦�����ͥ���ٳ���ߤϥ����奢¦���鸫���
         *  1�ӥåȥ��եȤ�����̥ӥåȤ�1�Ȥʤä���Τ˸����뤿��
         *  0xd0d0d0d0���ͤˤʤ�)
         */
		sil_wrw_mem((void *)(DIC_IPR + (4 * i)), 0xd0d0d0d0);
	}
}
#endif /* TOPPERS_SAFEG_SECURE */

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

#ifdef TOPPERS_SAFEG_SECURE
    /*
     * �ǥХ����ؤΥ����������¤�����(TrustZone)
     */
    target_tzpc_initialize();
    target_tzasc_initialize();

    /*
     * ����ߥ������ƥ�������
     * (�Υ󥻥��奢¦�γ����ͥ���٤˹�碌�ơ�SGI��PPI������)
     */
    target_gic_initialize();
#endif /* TOPPERS_SAFEG_SECURE */
        
	/*
	 *  UART������
	 */
#ifdef G_SYSLOG
	if (x_sense_mprc()) {
		kzm_ca9_uart_init();
	}
#else
	kzm_ca9_uart_init();
#endif /* G_SYSLOG */

    /*
     * ����ߥ٥����ơ��֥�� VECTOR_TABLE_BASE �쥸���������ꤹ��
     */
	CP15_SET_VBAR((uint32_t) &vector_table);
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
	kzm_ca9_exit();

	while(1);
}

/*
 *  �����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char_t c)
{
	if (c == '\n') {
		kzm_ca9_putc('\r');
	}
	kzm_ca9_putc(c);
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼����Ѥ���¬���ѥ����ޤν�����ؿ�
 */
void
perf_timer_initialize(intptr_t exinf)
{
	timer_sp804_init();
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼���ѤΥ����󥿤ˤ���¬
 */
void
perf_timer_get(uint32_t *p_time)
{
	*p_time = timer_sp804_get_current();
}

/*
 *  �¹Ի���ʬ�۽��ץ⥸�塼���ѤΥ����󥿤ˤ��¬���̤�ñ���Ѵ�
 *  nsec���Ѵ� 
 */
uint32_t
perf_timer_conv_tim(uint32_t time)
{
	/* 100Mhz�ǥ������ */
	return (time * 10);
}
