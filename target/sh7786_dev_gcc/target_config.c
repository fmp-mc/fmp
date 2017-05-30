/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: target_config.c 516 2010-02-03 05:57:37Z ertl-honda $
 */

/*
 *  �������åȰ�¸�⥸�塼���SH7786_DEV�ѡ�
 */

#include "kernel_impl.h"
#include <sil.h>
#include "mp.h"
#include "sh7786_dev.h"
#include "../pdic/sh/sh_scif.h"

#ifdef ROM_BOOT
uint32_t __dummy = 1;
#endif

/*
 *  ���٥���Ϥǻ��Ѥ���ݡ����ֹ�
 */
static const ID prc_fput_log_uart_table[2] = {
	1,
	2
};

/*
 *  ���ץ��å������Ѥ������٥���ϥݡ��Ȥμ���
 */
Inline ID
get_my_prc_fput_log_uart(void)
{
	return (prc_fput_log_uart_table[x_prc_index()]);
}

/*
 * str_ker()�����ǥޥ����ץ��å��ǹԤ������
 */
void
target_mprc_initialize(void)
{
	/*
	 *  SH4A��¸���Ǥν����
	 */
	prc_mprc_initialize();

	/*
	 *  GPIO�Υ쥸���������ꤷ��SCIF1�Υԥ��ͭ���ˤ���
	 */
	sil_wrh_mem((void *)GPIO_PDCR,
                (sil_reh_mem((void *)GPIO_PDCR) & GPIO_PDCR_SCIF1_ENABLE));
	/*
	 *  GPIO�Υ쥸���������ꤷ��SCIF0�Υԥ��ͭ���ˤ���
	 */
	sil_wrh_mem((void *)GPIO_PHCR,
                (sil_reh_mem((void *)GPIO_PHCR) & GPIO_PHCR_SCIF0_ENABLE));

	/* ������Х�����ȥ���쥸������Light Sleep�⡼�ɤ� */
	sil_wrw_mem((void *)C0STBCR,
                (sil_rew_mem((void *)C0STBCR) | CSTBCR_LIGHT_SLEEP));
	sil_wrw_mem((void *)C1STBCR,
                (sil_rew_mem((void *)C1STBCR) | CSTBCR_LIGHT_SLEEP));

	/*
	 *  SCIF0��ͭ����
	 */
	sil_wrh_mem((void *)SPCAR, 0x0044U);/* enable SCIF0 clock=1.842 MHz */
}

/*
 *  �������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	/*
	 *  �ץ��å���¸�ν����
	 */
	prc_initialize();

	/*
	 *  ���٥�����ѤΥ��ꥢ�륳��ȥ���ν����
	 */
	sh_scif_init(get_my_prc_fput_log_uart());
}

/*
 *  �������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	extern void    software_term_hook(void);
	void (*volatile fp)(void) = software_term_hook;

	/*
	 *  software_term_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
	 *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
	 *  ��Ǥ��롥
	 */
	if (fp != 0) {
		(*fp)();
	}

	/*
	 *  �ץ��å���¸�ν�λ����
	 */
	prc_terminate();

	/*
	 *  ��ȯ�Ķ���¸�ν�λ����
	 */
	sh7786_dev_exit();

	/*
	 * �����ˤ���ʤ�
	 */
	while(1);
}

/*
 *  �������åȰ�¸��ʸ������
 */
void
target_fput_log(char c)
{
	ID siopid = get_my_prc_fput_log_uart();

	if (c == '\n') {
		sh_scif_pol_putc('\r', siopid);
	}
	sh_scif_pol_putc(c, siopid);
}
