/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2009-2011 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
 *	
 *	�嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *	�����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *	�ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *	(1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *		��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *		����������˴ޤޤ�Ƥ��뤳�ȡ�
 *	(2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *		�ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *		��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	(3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *		�ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *		�ȡ�
 *	  (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *		  �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *	  (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *		  ��𤹤뤳�ȡ�
 *	(4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *		������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *		�ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *		ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *		���դ��뤳�ȡ�
 *	
 *	�ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *	���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *	���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *	�������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *	����Ǥ�����ʤ���
 * 
 *  $Id: target_config.c 877 2011-08-18 07:28:32Z mit-kimai $
 */

/*
 *	�������åȰ�¸�⥸�塼���APSH2AD�ѡ�
 */

#include "kernel_impl.h"
#include <sil.h>
#include "pdic/sh/sh_scif.h"
#include "apsh2ad.h"
#include "target_syssvc.h"		/*  TNUM_PORT, target_fput_log()  */

/*
 *  �Х������ơ��ȡ�����ȥ���ȥԥ󡦥ե��󥯥���󡦥���ȥ���ν����
 *  
 *  �����δؿ��ϡ�CPU0��hardware_init_hook()����ʲ��ξ���
 *  ���ƤӽФ����Ȥ����ꤷ�Ƥ��롣
 *  �����������å��ݥ��󥿤���¢RAM��ؤ��Ƥ��롣
 *  ������¾���Υץ��å���CPU1�ˤ������Х��˥����������Ƥ��ʤ���
 *  
 *  �����δؿ��ϡ��������ȥ��åץ롼����Ρ�bss/data���������ν�����פ��
 *  �����˼¹Ԥ����ɬ�פ����뤿�ᡢtarget_mprc_initialize()�Ȥ��̴ؿ��Ȥ��Ƥ��롣
 */
extern void target_bsc_pfc_initialize(void);

void target_bsc_pfc_initialize(void)
{
#ifdef ROM_BOOT
	/* �Х�����ȥ�������� */
	sil_wrw_mem((void *)CSMOD0_w, 0x00000000);
				/* CS0�⡼�ɥ쥸���� */
				/* PRMOD  0 =�Ρ��ޥ륢�������ߴ��⡼�� */
				/* PWENB  0 =�ڡ����饤�ȥ��������ػ� */
				/* PRENB  0 =�ڡ����꡼�ɥ��������ػ� */
				/* EWENB  0 =�����������ȶػ� */
				/* WRMOD  0 =�Х��ȥ饤�ȥ��ȥ��֥⡼�� */

	sil_wrw_mem((void *)CS1WCNT0_w, 0x07070000);	
				/* CS1������������쥸����1 */
				/* CSRWAIT  00110=6�������ȥ������� */
				/* CSWWAIT  00110=6�������ȥ������� */
				/* CSPRWAIT   000=0�������ȥ������� */
				/* CSPWWAIT   000=0�������ȥ������� */

	sil_wrw_mem((void *)CS2WCNT0_w, 0x12210011);	
				/* CS2������������쥸����1 */
				/* CSON   001=1�������ȥ������� */
				/* WDON   010=2�������ȥ������� */
				/* WRON   010=2�������ȥ������� */
				/* RDON   001=1�������ȥ������� */
				/* WDOOFF 000=0�������ȥ������� */
				/* CSWOFF 001=1�������ȥ������� */
				/* CSROFF 001=1�������ȥ������� */

#endif /* ROM_BOOT */

	/* I/O������ */
	sil_wrh_mem((void *)PACRL4_h, 0x1111);		/* D31~16 */
	sil_wrh_mem((void *)PACRL3_h, 0x1111);
	sil_wrh_mem((void *)PACRL2_h, 0x1111);
	sil_wrh_mem((void *)PACRL1_h, 0x1111);

	sil_wrh_mem((void *)PBCRH2_h, 0x0001);		/* WDTOVF */
	sil_wrh_mem((void *)PBCRH1_h, 0x0001);		/* PB17 SDWE */
	sil_wrh_mem((void *)PBCRL4_h, 0x1111);		/* CKE CAS RAS WE3 */
	sil_wrh_mem((void *)PBCRL3_h, 0x1111);		/* WE2 WE1 WE0 CS5 */
	sil_wrh_mem((void *)PBCRL2_h, 0x2111);		/* SDCS0 CS3 CS2 CS1 */
	sil_wrh_mem((void *)PBCRL1_h, 0x1111);		/* A22 A21 A1 A0 */

	sil_wrh_mem((void *)PCCRL3_h, 0x0000);		/* PC10~0 */
	sil_wrh_mem((void *)PCCRL2_h, 0x0000);
	sil_wrh_mem((void *)PCCRL1_h, 0x0000);

	sil_wrh_mem((void *)PCIORL_h, 0x07FF);		/* OUT : PC10~0 */

	sil_wrh_mem((void *)PDCRL1_h, 0x0222);		/* A25 A24 A23 */

	sil_wrh_mem((void *)PECRL1_h, 0x1111);		/* RTS0 CTS0 TxD0 RxD0 */

	sil_wrh_mem((void *)PFCRL2_h, 0x0000);		/* LED2 */
	sil_wrh_mem((void *)PFCRL1_h, 0x0330);		/* LED1 CTx0 CRx0 PF0 */

	sil_wrh_mem((void *)PFIORL_h, 0x0019);
						/* OUT : LED2(PF4) LED1(PF3) PF0 */

	sil_wrh_mem((void *)PHIORL_h, 0x0280);
						/* PH7,PH8:USBHOST0 PH9,PH10:USBHOST1 PH6:WP*/

	sil_wrh_mem((void *)PJCRL4_h, 0x0000);		/* PJ12~0 */
	sil_wrh_mem((void *)PJCRL3_h, 0x0000);
	sil_wrh_mem((void *)PJCRL2_h, 0x0000);
	sil_wrh_mem((void *)PJCRL1_h, 0x0000);

	sil_wrh_mem((void *)PJIORL_h, 0x1FFF);		/* OUT : PJ12~0 */

#ifdef ROM_BOOT

	sil_wrw_mem((void *)SDIR0_w, 0x00000082);	/* SDRAM������쥸����0 */
				/* DPC   ������ץ���㡼����������(000=3��������) */
				/* DARFC ����������ȥ�ե�å�����(1000=8��) */
				/* DARFI ����������ȥ�ե�å���ֳ�(0010=5��������) */

	sil_wrw_mem((void *)SDIR1_w, 0x00000001);	/* SDRAM������쥸����1 */
				/* DINIRQ  ������������󥹳��� */

	/* SDRAM�������λ�Ԥ� */
	while( (sil_rew_mem((void *)SDIR1_w) & 0x00010000) != 0 );

	/* SDRAM���ơ������쥸�����γ�ǧ */
	while( sil_rew_mem((void *)SDSTR_w) != 0);

	sil_wrw_mem((void *)SD0MOD_w, 0x00000020);
				/* SDRAM0�⡼�ɥ쥸���� */
				/* A9   �饤�ȥС�����Ĺ(0=Burst) */
				/* A8-7 �ƥ��ȥ⡼��(00=Mode Reister Set) */
				/* A6-4 CAS�쥤�ƥ�(010=2��������) */
				/* A3   �С����ȥ�����(0=Sequential) */
				/* A2-1 �С�����Ĺ(000=1) */

	sil_wrw_mem((void *)SD0TR_w, 0x00021302);	/* SDRAM0�����ߥ󥰥쥸���� */
				/* DRAS �������ƥ��ִ���(010=3��������) */
				/* DRCD �������쥤�ƥ󥷴���(01=2��������) */
				/* DPCG ���ץ���㡼������(001=2��������) */
				/* DWR  �饤�ȥꥫ�Х����(1=2��������) */
				/* DCL  CAS�쥤�ƥ�(010=2��������) */

	sil_wrw_mem((void *)SD0ADR_w, 0x00000203);
				/* SDRAM0���ɥ쥹�쥸���� */
				/* DDBW SDRAM�ǡ����Х���(10=32�ӥå�) */
				/* DSZ  ����ͥ륵����(011=32M�Х���) */

	sil_wrw_mem((void *)SDRFCNT1_w, 0x00014208);
				/* SDRAM��ե�å�������쥸����1 */
				/* DRFEN �����ȥ�ե�å���ư��(1=ͭ��) */
				/* DREFW �����ȥ�ե�å��奵�������(0100=5��������) */
				/* DRFC  �����ȥ�ե�å����׵�ֳ� */
				/* 64mS/4096=1.56us */

	sil_wrw_mem((void *)SDC0CNT_w, 0x00110000);
				/* SDRAMC0����쥸���� */
				/* BSIZE �����Х���(01=32�ӥåȥХ�) */
				/* EXENB ư�����(1=ư�����) */
#endif /* ROM_BOOT */
}


/*
 *  str_ker() �μ¹����˥ޥ����ץ��å��Τ߼¹Ԥ������������
 */
void
target_mprc_initialize(void)
{
	prc_mprc_initialize();

	/*
	 *	��������ϥ⡼�ɤ�����
	 */
		/*
		 *	CPU0��sleep̿��μ¹Ԥǡ�CPU0�����꡼�ץ⡼�ɤ�����
		 *	�������꡼�ץ��顼�ػ�
		 *	���������ǥ����ѿ徽ȯ���Ҥ�̵��
		 */
	sil_wrb_mem((void *)STBCR1_b, STBCR1_AXTALE);

		/*
		 *	����H-UDI��ư��
		 *	����FPU0,FPU1��ư��
		 *	����UBC0,UBC1��ư��
		 *	��
		 *	������
		 *	����JTAG���ߥ�졼������Ѥ�����ϡ�
		 *	����H-UDI��FPU��UBC����ߤ��ƤϤ����ʤ���
		 */
	sil_wrb_mem((void *)STBCR2_b, 0x00U);

		/*
		 *	����ATAPI�����
		 *	����MTU2�����
		 *	����ADC�����
		 *	����DAC�����
		 *	����RTC�����
		 */
	sil_wrb_mem((void *)STBCR3_b, 0xffU);

		/*
		 *	����SCFI0��ư��
		 *	����SCFI1��ư��
		 *	����SCFI2�����
		 *	����SCFI3�����
		 *	����SCFI4�����
		 *	����SCFI5�����
		 */
	sil_wrb_mem((void *)STBCR4_b, (uint8_t)~(STBCR4_SCIF0 | STBCR4_SCIF1));

		/*
		 *	����IIC3_0�����
		 *	����IIC3_1�����
		 *	����IIC3_2�����
		 *	����IIC3_3�����
		 *	����RCAN0�����
		 *	����RCAN1�����
		 */
	sil_wrb_mem((void *)STBCR5_b, 0xffU);

		/*
		 *	����SSIF0�����
		 *	����SSIF1�����
		 *	����SSIF2�����
		 *	����SSIF3�����
		 *	����SSIF4�����
		 *	����SSIF5�����
		 */
	sil_wrb_mem((void *)STBCR6_b, 0xffU);

		/*
		 *	����CMT01��ư��
		 *	����CMT23�����
		 *	����FLCTL�����
		 *	����SSU0�����
		 *	����SSU1�����
		 *	����2DG�����
		 *	����USB�����
		 */
	sil_wrb_mem((void *)STBCR7_b, (uint8_t)~STBCR7_CMT01);

	/*
	 *	SCIF��I/O�ݡ��Ȥ�����	 �׸�Ƥ:PE4/SCK0ü�Ҥ������ɬ�ס�
	 */
	sil_wrh_mem((void *)PECRL1_h, 0x1111U);/* SCIF0:RTS0 CTS0 TxD0 RxD0 */
#if TNUM_PORT > 1
	sil_wrh_mem((void *)PECRL2_h, 0x0110U);/* SCIF1:TxD1 RxD1 */
#endif /* TNUM_PORT > 1 */
	
	/*
	 * �С��ʡ������ѤΥ��ꥢ�륳��ȥ���ν����
	 */
	sh_scif_init(1);
#if TNUM_PORT > 1
	sh_scif_init(2);
#endif /* TNUM_PORT > 1 */
}

/*
 *	�������åȰ�¸�ν����
 */
void
target_initialize(void)
{
	/*
	 *	�ץ��å���¸�ν����
	 */
	prc_initialize();
}

/*
 *	�������åȰ�¸�ν�λ����
 */
void
target_exit(void)
{
	/*
	 *	�ץ��å���¸�ν�λ����
	 */
	prc_exit();

	/*
	 *	��ȯ�Ķ���¸�ν�λ����
	 */
	apsh2ad_exit();

	/*
	 * �����ˤ���ʤ�
	 */
	while(true);
}

/*
 *	�����ƥ�������٥���ϤΤ����ʸ������
 */
void
target_fput_log(char_t c)
{
#if TNUM_PORT == 1
	ID siopid = TARGET_PUTC_PORTID;
#else	/* TNUM_PORT == 1 */
	ID siopid = sil_get_pindex() + 1;
#endif	/* TNUM_PORT == 1 */

	if (c == '\n') {
		sh_scif_pol_putc('\r', siopid);
	}
	sh_scif_pol_putc(c, siopid);
}


/*
 *	�����������μ��Ի��μ¹����ǽ�����T.B.D��
 */
void
TOPPERS_assert_abort(void)
{
	uint_t index = sil_get_pindex();
	
	syslog(LOG_EMERG, "prcindex = %d" ,index);
	while(true);
}

