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
 *  @(#) $Id: sh7786.h 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *  SH7786�Υϡ��ɥ������񸻤����
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
#define    TMU2_INTEVT         UINT_C(0x00000|0x7A0)
#define    TMU3_INTEVT         UINT_C(0x00000|0x7C0)
#define    TMU4_INTEVT         UINT_C(0x00000|0x480)/* SH7786�Ǥ�������ǧ*/
#define    TMU5_INTEVT         UINT_C(0x00000|0x4A0)/* SH7786�Ǥ�������ǧ*/

#define    SCIF0_RXI_INTEVT    UINT_C(0x00000|0x720)
#define    SCIF0_TXI_INTEVT    UINT_C(0x00000|0x760)

#define    SCIF1_RXI_INTEVT    UINT_C(0x00000|0x780)
#define    SCIF1_TXI_INTEVT    UINT_C(0x00000|0x780)

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
#define C0INTMSK1    UINT_C(0xFE410040)
#define C1INTMSK1    UINT_C(0xFE410044)
#define C0INTMSKCLR0 UINT_C(0xFE410050)
#define C1INTMSKCLR0 UINT_C(0xFE410054)
#define C0INTMSKCLR1 UINT_C(0xFE410060)
#define C1INTMSKCLR1 UINT_C(0xFE410064)

#define NMIFCR       UINT_C(0xFE4100C0)
#define NMISET 	     UINT_C(0xFE4100C4)
#define USERIMASK    UINT_C(0xFE411000)

#define INT2PRI00     UINT_C(0xFE410800)
#define INT2PRI01     UINT_C(0xFE410804)
#define INT2PRI02     UINT_C(0xFE410808)
#define INT2PRI03     UINT_C(0xFE41080C)
#define INT2PRI04     UINT_C(0xFE410810)
#define INT2PRI05     UINT_C(0xFE410814)
#define INT2PRI06     UINT_C(0xFE410818)
#define INT2PRI07     UINT_C(0xFE41081C)
#define INT2PRI08     UINT_C(0xFE410820)

#define C0INT2MSK0   UINT_C(0xFE410A20)
#define C0INT2MSK1   UINT_C(0xFE410A24)
#define C0INT2MSK2   UINT_C(0xFE410A28)
#define C0INT2MSK3   UINT_C(0xFE410A2C)

#define C0INT2MSKCLR0 UINT_C(0xFE410A30)
#define C0INT2MSKCLR1 UINT_C(0xFE410A34)
#define C0INT2MSKCLR2 UINT_C(0xFE410A38)
#define C0INT2MSKCLR3 UINT_C(0xFE410A3C)

#define C1INT2MSK0   UINT_C(0xFE410B20)
#define C1INT2MSK1   UINT_C(0xFE410B24)
#define C1INT2MSK2   UINT_C(0xFE410B28)
#define C1INT2MSK3   UINT_C(0xFE410B2C)

#define C1INT2MSKCLR0 UINT_C(0xFE410B30)
#define C1INT2MSKCLR1 UINT_C(0xFE410B34)
#define C1INT2MSKCLR2 UINT_C(0xFE410B38)
#define C1INT2MSKCLR3 UINT_C(0xFE410B3C)

#define INT2B08       UINT_C(0xFE410C20)

#define C0INTICI      UINT_C(0xFE410070)
#define C1INTICI      UINT_C(0xFE410074)

#define C0INTICICLR   UINT_C(0xFE410080)
#define C1INTICICLR   UINT_C(0xFE410084)

#define C0ICIPRI      UINT_C(0xFE410090)
#define C1ICIPRI      UINT_C(0xFE410094)

#define C0ICIPRICLR   UINT_C(0xFE4100A0)
#define C1ICIPRICLR   UINT_C(0xFE4100A4)

#define IRQ_LOWLEVEL    UINT_C(0x02)
#define IRQ_POSEDGE     UINT_C(0x01)
#define IRQ_NEGEDGE     UINT_C(0x00)

/*
 * �ޥ������ꥢ�쥸�����Υޥ����ѥ�����
 */
#define INT2MSK0 UINT_C(0x00000001)
#define INT2MSK1 UINT_C(0xFFFFFFFF)
#define INT2MSK2 UINT_C(0x3F0001FF)
#define INT2MSK3 UINT_C(0xFFFFFF00)

//TMU�ޥ����ѥ�����
#define TMU_0_MASK UINT_C(0x80000000)
#define TMU_1_MASK UINT_C(0x40000000)


//SCIF�ޥ����ѥ�����
#define SCIF_0_RXI_MASK UINT_C(0x00000040)
#define SCIF_0_TXI_MASK UINT_C(0x00000010)
#define SCIF_1_RXI_MASK UINT_C(0x00000008)
#define SCIF_1_TXI_MASK UINT_C(0x00000008)


/*
 * �����ޡ��쥸����
 */
#define TIM0_BASE UINT_C(0xFFD80008)
#define TIM1_BASE UINT_C(0xFFD80014)
#define TIM2_BASE UINT_C(0xFFD80020)
#define TIM3_BASE UINT_C(0xFFDA0008)
#define TIM4_BASE UINT_C(0xFFDA0014)
#define TIM5_BASE UINT_C(0xFFDA0020)

/*
 * �ƥ쥸�����Υ��ե��å�
 */
#define TIM_TCOR   0x0000U  /* W */
#define TIM_TCNT   0x0004U  /* W */
#define TIM_TCR    0x0008U  /* H */

#define TMU_TSTR0   UINT_C(0xffd80004)  /* B */

#define TMU_TCOR0  UINT_C(0xffd80008)  /* W */
#define TMU_TCNT0  UINT_C(0xffd8000c)  /* W */
#define TMU_TCR0   UINT_C(0xffd80010)  /* H */

#define TMU_TCOR1  UINT_C(0xffd80014)  /* W */
#define TMU_TCNT1  UINT_C(0xffd80018)  /* W */
#define TMU_TCR1   UINT_C(0xffd8001c)  /* H */

#define TMU_TCOR2  UINT_C(0xffd80020)  /* W */
#define TMU_TCNT2  UINT_C(0xffd80024)  /* W */
#define TMU_TCR2   UINT_C(0xffd80028)  /* H */

#define TMU_TSTR1  UINT_C(0xffda0004)  /* B */

#define TMU_TCOR3  UINT_C(0xffda0008)  /* W */
#define TMU_TCNT3  UINT_C(0xffda000c)  /* W */
#define TMU_TCR3   UINT_C(0xffda0010)  /* H */

#define TMU_TCOR4  UINT_C(0xffda0014)  /* W */
#define TMU_TCNT4  UINT_C(0xffda0018)  /* W */
#define TMU_TCR4   UINT_C(0xffda001c)  /* H */

#define TMU_TCOR5  UINT_C(0xffda0020)  /* W */
#define TMU_TCNT5  UINT_C(0xffda0024)  /* W */
#define TMU_TCR5   UINT_C(0xffda0028)  /* H */

#define TMU_STR0   UINT_C(0x01)
#define TMU_STR1   UINT_C(0x02)
#define TMU_STR2   UINT_C(0x04)
#define TCR_UNF    UINT_C(0x0100)
#define TCR_UNIE   UINT_C(0x20)


/*
 *  FIFO�դ����ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCIF)�쥸����
 */
#define SH_SCIF0_BASE UINT_C(0xFFEA0000)
#define SH_SCIF1_BASE UINT_C(0xFFEB0000)
#define SH_SCIF2_BASE UINT_C(0xFFEC0000)
#define SH_SCIF3_BASE UINT_C(0xFFED0000)

#define SH_INT2B08    UINT_C(0xFE410C20)
/*
 *�����ճ���߾ܺ��װ�ɽ���쥸����
 */
#define SCIF1_RXI1    UINT_C(0x00000002)
#define SCIF1_TXI1    UINT_C(0x00000008)

/*
 *  GPIO��Ϣ�쥸����
 */
#define GPIO_PDCR  UINT_C(0xFFCC0006) /* D */
#define GPIO_PHCR  UINT_C(0xFFCC000E) /* H */
#define GPIO_PDCR_SCIF1_ENABLE (~UINT_C(0x3F00))
#define GPIO_PHCR_SCIF0_ENABLE (~UINT_C(0x003F))

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
#define CSTBCR_LIGHT_SLEEP  UINT_C(0x80000000)

#endif /* TOPPERS_RPROTO1_H */
