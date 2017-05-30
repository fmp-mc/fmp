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
 *  @(#) $Id: rproto1.h 516 2010-02-03 05:57:37Z ertl-honda $
 */

/*
 *  RPROTO1�Υϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_RPROTO1_H
#define TOPPERS_RPROTO1_H

#include <sil.h>
#include "sh4a.h"

/*
 *   �Х����ơ��ȥ���ȥ����Ϣ
 */
#define	RFCR	    0xff800028   /* H */

#define RFCR_CLEAR  0xa400

/*
 *  �����ߤˤ�ä� INTEVT �쥸���������ꤵ�����
 */
#define    TMU0_INTEVT         UINT_C(0x00000|0x400)
#define    TMU1_INTEVT         UINT_C(0x00000|0x420)
#define    TMU2_INTEVT         UINT_C(0x00000|0x440)
#define    TMU3_INTEVT         UINT_C(0x00000|0x460)
#define    TMU4_INTEVT         UINT_C(0x00000|0x480)
#define    TMU5_INTEVT         UINT_C(0x00000|0x4A0)

#define    SCIF0_RXI_INTEVT    UINT_C(0x00000|0x720)
#define    SCIF0_TXI_INTEVT    UINT_C(0x00000|0x760)
#define    SCIF0_BRI_INTEVT    UINT_C(0x00000|0x740)

#define    SCIF1_RXI_INTEVT    UINT_C(0x00000|0x7A0)
#define    SCIF1_TXI_INTEVT    UINT_C(0x00000|0x7E0)
#define    SCIF1_BRI_INTEVT    UINT_C(0x00000|0x7C0)

#define    SCIF2_RXI_INTEVT    UINT_C(0x00000|0x820)
#define    SCIF2_TXI_INTEVT    UINT_C(0x00000|0x860)
#define    SCIF2_BRI_INTEVT    UINT_C(0x00000|0x840)

#define    SCIF3_RXI_INTEVT    UINT_C(0x00000|0x8A0)
#define    SCIF3_TXI_INTEVT    UINT_C(0x00000|0x8E0)
#define    SCIF3_BRI_INTEVT    UINT_C(0x00000|0x8C0)

//CPU�ֳ����
#define    ICI0_INTEVT      UINT_C(0x00000|0xF00)
#define    ICI1_INTEVT      UINT_C(0x00000|0xF20)
#define    ICI2_INTEVT      UINT_C(0x00000|0xF40)
#define    ICI3_INTEVT      UINT_C(0x00000|0xF60)

/*
 *  IRC��Ϣ�Υ쥸����
 */
#define ICR0 	     UINT_C(0xFE410000)
#define ICR1 	     UINT_C(0xFE41001C)
#define INTPRI0      UINT_C(0xFE410010)
#define INTREQ 	     UINT_C(0xFE410024)
#define C0INTMSK0    UINT_C(0xFE410030)
#define C1INTMSK0    UINT_C(0xFE410034)
#define C2INTMSK0    UINT_C(0xFE410038)
#define C3INTMSK0    UINT_C(0xFE41003C)
#define C0INTMSK1    UINT_C(0xFE410040)
#define C1INTMSK1    UINT_C(0xFE410044)
#define C2INTMSK1    UINT_C(0xFE410048)
#define C3INTMSK1    UINT_C(0xFE41004C)
#define C0INTMSKCLR0 UINT_C(0xFE410050)
#define C1INTMSKCLR0 UINT_C(0xFE410054)
#define C2INTMSKCLR0 UINT_C(0xFE410058)
#define C3INTMSKCLR0 UINT_C(0xFE41005C)
#define C0INTMSKCLR1 UINT_C(0xFE410060)
#define C1INTMSKCLR1 UINT_C(0xFE410064)
#define C2INTMSKCLR1 UINT_C(0xFE410068)
#define C3INTMSKCLR1 UINT_C(0xFE41006C)
#define NMIFCR       UINT_C(0xFE4100C0)
#define NMISET 	     UINT_C(0xFE4100C4)
#define USERIMASK    UINT_C(0xFE411000)
#define INT2PRI0     UINT_C(0xFE410800)
#define INT2PRI1     UINT_C(0xFE410804)
#define INT2PRI2     UINT_C(0xFE410808)
#define INT2PRI3     UINT_C(0xFE41080C)
#define INT2PRI4     UINT_C(0xFE410810)
#define C0INT2MSK0   UINT_C(0xFE410820)
#define C1INT2MSK0   UINT_C(0xFE410824)
#define C2INT2MSK0   UINT_C(0xFE410828)
#define C3INT2MSK0   UINT_C(0xFE41082C)
#define C0INT2MSK1   UINT_C(0xFE410830)
#define C1INT2MSK1   UINT_C(0xFE410834)
#define C2INT2MSK1   UINT_C(0xFE410838)
#define C3INT2MSK1   UINT_C(0xFE41083C)
#define C0INT2MSK2   UINT_C(0xFE410840)
#define C1INT2MSK2   UINT_C(0xFE410844)
#define C2INT2MSK2   UINT_C(0xFE410848)
#define C3INT2MSK2   UINT_C(0xFE41084C)
#define C0INT2MSKCLR0 UINT_C(0xFE410850)
#define C1INT2MSKCLR0 UINT_C(0xFE410854)
#define C2INT2MSKCLR0 UINT_C(0xFE410858)
#define C3INT2MSKCLR0 UINT_C(0xFE41085C)
#define C0INT2MSKCLR1 UINT_C(0xFE410860)
#define C1INT2MSKCLR1 UINT_C(0xFE410864)
#define C2INT2MSKCLR1 UINT_C(0xFE410868)
#define C3INT2MSKCLR1 UINT_C(0xFE41086C)
#define C0INT2MSKCLR2 UINT_C(0xFE410870)
#define C1INT2MSKCLR2 UINT_C(0xFE410874)
#define C2INT2MSKCLR2 UINT_C(0xFE410878)
#define C3INT2MSKCLR2 UINT_C(0xFE41087C)
#define C0INTICI      UINT_C(0xFE410070)
#define C1INTICI      UINT_C(0xFE410074)
#define C2INTICI      UINT_C(0xFE410078)
#define C3INTICI      UINT_C(0xFE41007C)
#define C0INTICICLR   UINT_C(0xFE410080)
#define C1INTICICLR   UINT_C(0xFE410084)
#define C2INTICICLR   UINT_C(0xFE410088)
#define C3INTICICLR   UINT_C(0xFE41008C)
#define C0ICIPRI      UINT_C(0xFE410090)
#define C1ICIPRI      UINT_C(0xFE410094)
#define C2ICIPRI      UINT_C(0xFE410098)
#define C3ICIPRI      UINT_C(0xFE41009C)
#define C0ICIPRICLR   UINT_C(0xFE4100A0)
#define C1ICIPRICLR   UINT_C(0xFE4100A4)
#define C2ICIPRICLR   UINT_C(0xFE4100A8)
#define C3ICIPRICLR   UINT_C(0xFE4100AC)
#define INTDISTCR0    UINT_C(0xFE4100B0)
#define INTDISTCR1    UINT_C(0xFE4100B4)
#define INT2DISTCR0   UINT_C(0xFE4108A0)
#define INT2DISTCR1   UINT_C(0xFE4108A4)
#define INT2DISTCR2   UINT_C(0xFE4108A8)
#define INTACK	      UINT_C(0xFE4100B8)
#define INTACKCLR     UINT_C(0xFE4100BC)
#define INTACKMSK0    UINT_C(0xFE4100D0)
#define INTACKMSK1    UINT_C(0xFE4100D4)
#define INT2ACKMSK0   UINT_C(0xFE4100D8)
#define INT2ACKMSK1   UINT_C(0xFE4100DC)
#define INT2ACKMSK2   UINT_C(0xFE4100E0)

#define IRQ_LOWLEVEL    UINT_C(0x02)
#define IRQ_POSEDGE     UINT_C(0x01)
#define IRQ_NEGEDGE     UINT_C(0x00)

/*
 * �ޥ������ꥢ�쥸�����Υޥ����ѥ�����
 */

//TMU�ޥ����ѥ�����
#define TMU_0_MASK UINT_C(0x00000002)
#define TMU_1_MASK UINT_C(0x00000004)
#define TMU_2_MASK UINT_C(0x00000008)
#define TMU_3_MASK UINT_C(0x00000010)
#define TMU_4_MASK UINT_C(0x00000020)
#define TMU_5_MASK UINT_C(0x00000040)

//PCII�ޥ����ѥ�����
#define PCII_0_MASK UINT_C(0x00004000)
#define PCII_1_MASK UINT_C(0x00008000)
#define PCII_2_MASK UINT_C(0x00010000)
#define PCII_3_MASK UINT_C(0x00020000)
#define PCII_4_MASK UINT_C(0x00040000)
#define PCII_5_MASK UINT_C(0x00080000)
#define PCII_6_MASK UINT_C(0x00100000)
#define PCII_7_MASK UINT_C(0x00200000)
#define PCII_8_MASK UINT_C(0x00400000)
#define PCII_9_MASK UINT_C(0x00800000)

//SCIF�ޥ����ѥ�����
#define SCIF_0_ERI_MASK UINT_C(0xFFFF0001)
#define SCIF_0_RXI_MASK UINT_C(0xFFFF0002)
#define SCIF_0_BRI_MASK UINT_C(0xFFFF0004)
#define SCIF_0_TXI_MASK UINT_C(0xFFFF0008)

#define SCIF_1_ERI_MASK UINT_C(0xFFFF0010)
#define SCIF_1_RXI_MASK UINT_C(0xFFFF0020)
#define SCIF_1_BRI_MASK UINT_C(0xFFFF0040)
#define SCIF_1_TXI_MASK UINT_C(0xFFFF0080)

#define SCIF_2_ERI_MASK UINT_C(0xFFFF0100)
#define SCIF_2_RXI_MASK UINT_C(0xFFFF0200)
#define SCIF_2_BRI_MASK UINT_C(0xFFFF0400)
#define SCIF_2_TXI_MASK UINT_C(0xFFFF0800)

#define SCIF_3_ERI_MASK UINT_C(0xFFFF1000)
#define SCIF_3_RXI_MASK UINT_C(0xFFFF2000)
#define SCIF_3_BRI_MASK UINT_C(0xFFFF4000)
#define SCIF_3_TXI_MASK UINT_C(0xFFFF8000)

//DMAC(0)�ޥ����ѥ�����
#define DMAC_0_0_MASK UINT_C(0x00000001)
#define DMAC_0_1_MASK UINT_C(0x00000002)
#define DMAC_0_2_MASK UINT_C(0x00000004)
#define DMAC_0_3_MASK UINT_C(0x00000008)
#define DMAC_0_4_MASK UINT_C(0x00000010)
#define DMAC_0_5_MASK UINT_C(0x00000020)
#define DMAC_0_05_MASK UINT_C(0x00000040)

//DU�ޥ����ѥ�����
#define DU_MASK UINT_C(0x00800000)

//DMAC(1)�ޥ����ѥ�����
#define DMAC_1_6_MASK   UINT_C(0x00000080)
#define DMAC_1_7_MASK   UINT_C(0x00000100)
#define DMAC_1_8_MASK   UINT_C(0x00000200)
#define DMAC_1_9_MASK   UINT_C(0x00000400)
#define DMAC_1_10_MASK  UINT_C(0x00000800)
#define DMAC_1_11_MASK  UINT_C(0x00001000)
#define DMAC_1_611_MASK UINT_C(0x00002000)

//IIC�ޥ����ѥ�����
#define IIC_MASK UINT_C(0x01000000)

//VIN�ޥ����ѥ�����
#define VIN_0_MASK UINT_C(0x02000000)
#define VIN_1_MASK UINT_C(0x04000000)

//IMP�ޥ����ѥ�����
#define IMP_MASK UINT_C(0x08000000)

//ATA�ޥ����ѥ�����
#define ATA_MASK UINT_C(0x10000000)

//DTU0�ޥ����ѥ�����
#define DTU0_MASK UINT_C(0x01000000)

//DTU1�ޥ����ѥ�����
#define DTU1_MASK UINT_C(0x02000000)

//DTU2�ޥ����ѥ�����
#define DTU2_MASK UINT_C(0x04000000)

//DTU3�ޥ����ѥ�����
#define DTU3_MASK UINT_C(0x08000000)

//FE_0�ޥ����ѥ�����
#define FE0_MASK UINT_C(0x40000000)

//FE_1�ޥ����ѥ�����
#define FE1_MASK UINT_C(0x80000000)

//GPIO�ޥ����ѥ�����
#define GPIO_0_MASK UINT_C(0x00080000)
#define GPIO_1_MASK UINT_C(0x00100000)
#define GPIO_2_MASK UINT_C(0x00200000)
#define GPIO_3_MASK UINT_C(0x00400000)

//PAM�ޥ����ѥ�����
#define PAM_MASK UINT_C(0x00040000)

/*
 * �����ޡ��쥸����
 */
#define TIM0_BASE UINT_C(0xFFC10008)
#define TIM1_BASE UINT_C(0xFFC10014)
#define TIM2_BASE UINT_C(0xFFC10020)
#define TIM3_BASE UINT_C(0xFFC20008)
#define TIM4_BASE UINT_C(0xFFC20014)
#define TIM5_BASE UINT_C(0xFFC20020)

/*
 * �ƥ쥸�����Υ��ե��å�
 */
#define TIM_TCOR   0x0000U  /* W */
#define TIM_TCNT   0x0004U  /* W */
#define TIM_TCR    0x0008U  /* H */

#define TMU_TSTR0   UINT_C(0xffc10004)  /* B */

#define TMU_TCOR0  UINT_C(0xffc10008)  /* W */
#define TMU_TCNT0  UINT_C(0xffc1000c)  /* W */
#define TMU_TCR0   UINT_C(0xffc10010)  /* H */

#define TMU_TCOR1  UINT_C(0xffc10014)  /* W */
#define TMU_TCNT1  UINT_C(0xffc10018)  /* W */
#define TMU_TCR1   UINT_C(0xffc1001c)  /* H */

#define TMU_TCOR2  UINT_C(0xffc10020)  /* W */
#define TMU_TCNT2  UINT_C(0xffc10024)  /* W */
#define TMU_TCR2   UINT_C(0xffc10028)  /* H */

#define TMU_TSTR1  UINT_C(0xffc20004)  /* B */

#define TMU_TCOR3  UINT_C(0xffc20008)  /* W */
#define TMU_TCNT3  UINT_C(0xffc2000c)  /* W */
#define TMU_TCR3   UINT_C(0xffc20010)  /* H */

#define TMU_TCOR4  UINT_C(0xffc20014)  /* W */
#define TMU_TCNT4  UINT_C(0xffc20018)  /* W */
#define TMU_TCR4   UINT_C(0xffc2001c)  /* H */

#define TMU_TCOR5  UINT_C(0xffc20020)  /* W */
#define TMU_TCNT5  UINT_C(0xffc20024)  /* W */
#define TMU_TCR5   UINT_C(0xffc20028)  /* H */

#define	TMU_STR0	UINT_C(0x01)
#define	TMU_STR1	UINT_C(0x02)
#define	TMU_STR2	UINT_C(0x04)
#define TCR_UNF     UINT_C(0x0100)    

/*
 *  FIFO�դ����ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCIF)�쥸����
 */
#define SH_SCIF0_BASE UINT_C(0xFFC30000)
#define SH_SCIF1_BASE UINT_C(0xFFC40000)
#define SH_SCIF2_BASE UINT_C(0xFFC50000)
#define SH_SCIF3_BASE UINT_C(0xFFC60000)

/*
 *  GPIO��Ϣ�쥸����
 */
#define GPIO_PHCP  UINT_C(0xFFC7000C) /* GH */
#define GPIO_PHCP_SCIF0_ENABLE (~UINT_C(0xFFFF0000))

/*
 *  ����å�������쥸����
 */
#define	CCR	          UINT_C(0xff00001c)   /* W */
#define CCR_DISABLE   UINT_C(0x00000808)  /* ����å���̵�� */

/*
 *  ������Х����ơ��ȥ���ȥ����Ϣ
 */
#define LBSC_MMSELR UINT_C(0xff400020) /* W */
#define LBSC_CS0BCR UINT_C(0xff802000) /* W */
#define LBSC_CS0WCR UINT_C(0xff802008) /* W */


/*
 * ������Х�����ȥ���쥸������sleep�⡼�ɤ�����
 */
#define C0STBCR UINT_C(0xfe400004)
#define C1STBCR UINT_C(0xfe401004)
#define C2STBCR UINT_C(0xfe402004)
#define C3STBCR UINT_C(0xfe403004)
#define CSTBCR_LIGHT_SLEEP  UINT_C(0x80000000)

#endif /* TOPPERS_RPROTO1_H */
