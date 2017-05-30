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
 *  @(#) $Id: rproto1_config.h 512 2010-02-01 05:33:27Z ertl-honda $
 */

/*
 *     �ץ��å���¸�⥸�塼���RPROTO1�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS__RPROTO1_CONFIG_H
#define TOPPERS__RPROTO1_CONFIG_H

/*
 *  ����ߥϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_INHNO 0x1C0U
#define TMAX_INHNO 0xFE0U
#define TNUM_INH   0x080U

/*
 *  ������ֹ�˴ؤ������
 */ 
#define TMIN_INTNO 0x1C0U
#define TMAX_INTNO 0xFE0U
#define TNUM_INT   0x080U

/*
 *  ����ߥޥ����쥸�������ܿ�
 */
#define TNUM_MST_INFO_TBL 12

/*
 *  ����ߥޥ����쥸�������ܿ�
 */
#define TNUM_MAK_INFO_DATA 3

#ifndef TOPPERS_MACRO_ONLY

/*
 * ������׵�饤�����ͥ��������쥸�������������
 */
#define IPR_INFO_TBL_DATA \
    {0U, 0},        /* 0x000(0x000) */ \
    {0U, 0},        /* 0x020(0x001) */ \
    {0U, 0},        /* 0x040(0x002) */ \
    {0U, 0},        /* 0x060(0x003) */ \
    {0U, 0},        /* 0x080(0x004) */ \
    {0U, 0},        /* 0x0A0(0x005) */ \
    {0U, 0},        /* 0x0C0(0x006) */ \
    {0U, 0},        /* 0x100(0x007) */ \
    {0U, 0},        /* 0x100(0x008) */ \
    {0U, 0},        /* 0x120(0x009) */ \
    {0U, 0},        /* 0x140(0x00A) */ \
    {0U, 0},        /* 0x160(0x00B) */ \
    {0U, 0},        /* 0x180(0x00C) */ \
    {0U, 0},        /* 0x1A0(0x00D) */ \
\
    {0U, 0},        /* 0x1C0(0x00E) NMI */ \
\
    {0U, 0},        /* 0x1E0(0x00F) */ \
\
    {0U, 0},        /* 0x200(0x010) IRL 0000 */ \
    {0U, 0},        /* 0x220(0x011) IRL 0001 */ \
    {0U, 0},        /* 0x240(0x012) IRL 0010 */ \
    {0U, 0},        /* 0x260(0x013) IRL 0011 */ \
    {0U, 0},        /* 0x280(0x014) IRL 0100 */ \
    {0U, 0},        /* 0x2A0(0x015) IRL 0101 */ \
    {0U, 0},        /* 0x2C0(0x016) IRL 0110 */ \
    {0U, 0},        /* 0x2E0(0x017) IRL 0111 */ \
    {0U, 0},        /* 0x300(0x018) IRL 1000 */ \
    {0U, 0},        /* 0x320(0x019) IRL 1001 */ \
    {0U, 0},        /* 0x340(0x01A) IRL 1010 */ \
    {0U, 0},        /* 0x360(0x01B) IRL 1011 */ \
    {0U, 0},        /* 0x380(0x01C) IRL 1100 */ \
    {0U, 0},        /* 0x3A0(0x01D) IRL 1101 */ \
    {0U, 0},        /* 0x3C0(0x01E) IRL 1110 */ \
    {0U, 0},        /* 0x3E0(0x01F) */ \
\
    {INT2PRI0, 0},  /* 0x400(0x020) TMU_0 */ \
    {INT2PRI0, 4},  /* 0x420(0x021) TMU_1  */ \
    {INT2PRI0, 8},  /* 0x440(0x022) TMU_2  */ \
    {INT2PRI0, 12}, /* 0x460(0x023) TMU_3  */ \
    {INT2PRI0, 16}, /* 0x480(0x024) TMU_4  */ \
    {INT2PRI0, 20}, /* 0x4A0(0x025) TMU_5  */ \
\
    {0U,  0},       /* 0x4C0(0x026) */ \
    {0U, 0},        /* 0x4E0(0x027) */ \
\
    {INT2PRI2, 0},  /* 0x500(0x028) PCII_0*/ \
    {INT2PRI2, 4},  /* 0x520(0x029) PCII_1*/ \
    {INT2PRI2, 8},  /* 0x540(0x02A) PCII_2*/ \
    {INT2PRI2, 12}, /* 0x560(0x02B) PCII_3 */ \
    {INT2PRI2, 16}, /* 0x580(0x02C) PCII_4 */ \
    {INT2PRI2, 20}, /* 0x5A0(0x02D) PCII_5 */ \
    {INT2PRI2, 20}, /* 0x5C0(0x02E) PCII_6 */ \
    {INT2PRI2, 20}, /* 0x5E0(0x02F) PCII_7 */ \
    {INT2PRI2, 20}, /* 0x600(0x030) PCII_8 */ \
    {INT2PRI2, 20}, /* 0x620(0x031) PCII_9 */ \
\
    {0U, 0},        /* 0x640(0x032)  */ \
    {0U, 0},        /* 0x660(0x033)  */ \
    {0U, 0},        /* 0x680(0x034)  */ \
    {0U, 0},        /* 0x6A0(0x035)  */ \
    {0U, 0},        /* 0x6C0(0x036)  */ \
    {0U, 0},        /* 0x6E0(0x037)  */ \
\
    {INT2PRI1, 0}, /* 0x700(0x038) SCIF-ch0 ERI0 */ \
    {INT2PRI1, 0}, /* 0x720(0x039)          RXI0 */ \
    {INT2PRI1, 0}, /* 0x740(0x03A)          BRI0 */ \
    {INT2PRI1, 0}, /* 0x760(0x03B)          TXI0 */ \
\
    {INT2PRI1, 4}, /* 0x780(0x03C) SCIF-ch1 ERI1 */ \
    {INT2PRI1, 4}, /* 0x7A0(0x03D)         RXI1 */ \
    {INT2PRI1, 4}, /* 0x7C0(0x03E)         BRI1 */ \
    {INT2PRI1, 4}, /* 0x7E0(0x03F)         TXI1 */ \
\
    {INT2PRI1, 8}, /* 0x800(0x040) SCIF-ch2 ERI2 */ \
    {INT2PRI1, 8}, /* 0x820(0x041)          RXI2 */ \
    {INT2PRI1, 8}, /* 0x840(0x042)          BRI2 */ \
    {INT2PRI1, 8}, /* 0x860(0x043)          TXI2 */ \
\
    {INT2PRI1, 12}, /* 0x880(0x044) SCIF-ch3 ERI3 */ \
    {INT2PRI1, 12}, /* 0x8A0(0x045)          RXI3*/ \
    {INT2PRI1, 12}, /* 0x8C0(0x046)          BRI3*/ \
    {INT2PRI1, 12}, /* 0x8E0(0x047)          TXI3*/ \
\
    {INT2PRI2, 24}, /* 0x900(0x048) DMINT0  DMINT0 */ \
    {INT2PRI2, 24}, /* 0x920(0x049)  DMINT1 */ \
    {INT2PRI2, 24}, /* 0x940(0x04A)  DMINT2 */ \
    {INT2PRI2, 24}, /* 0x960(0x04B)  DMINT3 */ \
    {INT2PRI2, 24}, /* 0x980(0x04C)  DMINT4  */ \
    {INT2PRI2, 24}, /* 0x9A0(0x04D)  DMINT5 */ \
    {INT2PRI2, 24}, /* 0x9C0(0x04E)  DMAE0 */ \
\
    {INT2PRI3, 0},  /* 0x9E0(0x04F) */ \
\
    {INT2PRI2, 28}, /* 0xA00(0x050) DMIN6 */ \
    {INT2PRI2, 28}, /* 0xA20(0x051) DMIN7 */ \
    {INT2PRI2, 28}, /* 0xA40(0x052) DMIN8 */ \
    {INT2PRI2, 28}, /* 0xA60(0x053) DMIN9 */ \
    {INT2PRI2, 28}, /* 0xA80(0x054) DMIN10 */ \
    {INT2PRI2, 28}, /* 0xAA0(0x055) DMIN11  */ \
    {INT2PRI2, 28}, /* 0xAC0(0x056) DMAE1 */ \
\
    {INT2PRI3, 4},  /* 0xAE0(0x057) IIC */ \
\
    {INT2PRI3, 8},  /* 0xB00(0x058) VIN_0 */ \
    {INT2PRI3, 12}, /* 0xB20(0x059) VIN_1 */ \
\
    {INT2PRI3, 16}, /* 0xB40(0x05A) IMP*/ \
\
    {INT2PRI3, 20}, /* 0xB60(0x05B) ATA*/ \
\
    {0U, 0},        /* 0xB80(0x05C)  */ \
    {0U, 0},        /* 0xBA0(0x05D)  */ \
    {0U, 0},        /* 0xBC0(0x05E)  */ \
    {0U, 0},        /* 0xBE0(0x05F)  */ \
\
    {INT2PRI1, 16}, /* 0xC00(0x060) TEND */ \
    {INT2PRI1, 16}, /* 0xC20(0x061) AE  */ \
    {INT2PRI1, 16}, /* 0xC40(0x062) TMISS */ \
\
    {INT2PRI1, 20}, /* 0xC60(0x063) TEND */ \
    {INT2PRI1, 20}, /* 0xC80(0x064) AE */ \
    {INT2PRI1, 20}, /* 0xCA0(0x065) TMISS */ \
\
    {INT2PRI1, 24}, /* 0xCC0(0x066) TEND*/ \
    {INT2PRI1, 24}, /* 0xCE0(0x067) AE*/ \
    {INT2PRI1, 24}, /* 0xC00(0x068) TMISS */ \
\
    {INT2PRI1, 16}, /* 0xD20(0x069)       TEND  */ \
    {INT2PRI1, 16}, /* 0xD40(0x06A)       AE   */ \
    {INT2PRI1, 16}, /* 0xD60(0x06B)       TMISS  */ \
\
    {0U, 0},        /* 0xD80(0x06C)  */ \
    {0U, 0},        /* 0xDA0(0x06D) */ \
    {0U, 0},        /* 0xDC0(0x06E)   */ \
    {0U, 0},        /* 0xDE0(0x06F)   */ \
\
    {INT2PRI3, 24}, /* 0xE00(0x070) FE_0 */ \
\
    {INT2PRI3, 28}, /* 0xE20(0x071) FE_1 */ \
\
    {INT2PRI4,  4}, /* 0xE40(0x072) GPIO_0 */ \
\
    {INT2PRI4, 8},  /* 0xE60(0x073) GPIO_1*/ \
\
    {INT2PRI4, 12}, /* 0xE80(0x074) GPIO_2 */ \
\
    {INT2PRI4, 16}, /* 0xEA0(0x075) GPIO_3 */ \
    {INT2PRI4, 20}, /* 0xEC0(0x076) PAM*/ \
\
    {0U, 0},        /* 0xEE0(0x077) */ \
\
    {C0ICIPRI, 0},        /* 0xF00(0x078) */ \
    {C1ICIPRI, 4},        /* 0xF20(0x079) */ \
    {C2ICIPRI, 8},        /* 0xF40(0x07A) */ \
    {C3ICIPRI, 12},        /* 0xF60(0x07B) */ \
\
    {0U, 0},        /* 0xF80(0x07C) */ \
    {0U, 0},        /* 0xFA0(0x07D) */ \
    {0U, 0},        /* 0xFC0(0x07E) */ \
    {0U, 0},        /* 0xFE0(0x07F) */ \


/*
 * ������׵�饤����Υޥ������ꥢ�쥸�������������
 */
#define MSKCLR_INFO_TBL_DATA \
    {0U, 0},        /* 0x000(0x000) */ \
    {0U, 0},        /* 0x020(0x001) */ \
    {0U, 0},        /* 0x040(0x002) */ \
    {0U, 0},        /* 0x060(0x003) */ \
    {0U, 0},        /* 0x080(0x004) */ \
    {0U, 0},        /* 0x0A0(0x005) */ \
    {0U, 0},        /* 0x0C0(0x006) */ \
    {0U, 0},        /* 0x100(0x007) */ \
    {0U, 0},        /* 0x100(0x008) */ \
    {0U, 0},        /* 0x120(0x009) */ \
    {0U, 0},        /* 0x140(0x00A) */ \
    {0U, 0},        /* 0x160(0x00B) */ \
    {0U, 0},        /* 0x180(0x00C) */ \
    {0U, 0},        /* 0x1A0(0x00D) */ \
\
    {0U, 0},        /* 0x1C0(0x00E) NMI */ \
\
    {0U, 0},        /* 0x1E0(0x00F) */ \
\
    {0U, 0},        /* 0x200(0x010) IRL 0000 */ \
    {0U, 0},        /* 0x220(0x011) IRL 0001 */ \
    {0U, 0},        /* 0x240(0x012) IRL 0010 */ \
    {0U, 0},        /* 0x260(0x013) IRL 0011 */ \
    {0U, 0},        /* 0x280(0x014) IRL 0100 */ \
    {0U, 0},        /* 0x2A0(0x015) IRL 0101 */ \
    {0U, 0},        /* 0x2C0(0x016) IRL 0110 */ \
    {0U, 0},        /* 0x2E0(0x017) IRL 0111 */ \
    {0U, 0},        /* 0x300(0x018) IRL 1000 */ \
    {0U, 0},        /* 0x320(0x019) IRL 1001 */ \
    {0U, 0},        /* 0x340(0x01A) IRL 1010 */ \
    {0U, 0},        /* 0x360(0x01B) IRL 1011 */ \
    {0U, 0},        /* 0x380(0x01C) IRL 1100 */ \
    {0U, 0},        /* 0x3A0(0x01D) IRL 1101 */ \
    {0U, 0},        /* 0x3C0(0x01E) IRL 1110 */ \
    {0U, 0},        /* 0x3E0(0x01F) */ \
\
    {C0INT2MSKCLR0, TMU_0_MASK},  /* 0x400(0x020) TMU_0 */ \
    {C0INT2MSKCLR0, TMU_1_MASK},  /* 0x420(0x021) TMU_1  */ \
    {C0INT2MSKCLR0, TMU_2_MASK},  /* 0x440(0x022) TMU_2  */ \
    {C0INT2MSKCLR0, TMU_3_MASK},  /* 0x460(0x023) TMU_3  */ \
    {C0INT2MSKCLR0, TMU_4_MASK},  /* 0x480(0x024) TMU_4  */ \
    {C0INT2MSKCLR0, TMU_5_MASK},  /* 0x4A0(0x025) TMU_5  */ \
\
    {0U, 0},       /* 0x4C0(0x026) */ \
    {0U, 0},        /* 0x4E0(0x027) */ \
\
    {C0INT2MSKCLR1, PCII_0_MASK},  /* 0x500(0x028) PCII_0*/ \
    {C0INT2MSKCLR1, PCII_1_MASK},  /* 0x520(0x029) PCII_1*/ \
    {C0INT2MSKCLR1, PCII_2_MASK},  /* 0x540(0x02A) PCII_2*/ \
    {C0INT2MSKCLR1, PCII_3_MASK}, /* 0x560(0x02B) PCII_3 */ \
    {C0INT2MSKCLR1, PCII_4_MASK}, /* 0x580(0x02C) PCII_4 */ \
    {C0INT2MSKCLR1, PCII_5_MASK}, /* 0x5A0(0x02D) PCII_5 */ \
    {C0INT2MSKCLR1, PCII_6_MASK}, /* 0x5C0(0x02E) PCII_6 */ \
    {C0INT2MSKCLR1, PCII_7_MASK}, /* 0x5E0(0x02F) PCII_7 */ \
    {C0INT2MSKCLR1, PCII_8_MASK}, /* 0x600(0x030) PCII_8 */ \
    {C0INT2MSKCLR1, PCII_9_MASK}, /* 0x620(0x031) PCII_9 */ \
\
    {0U, 0},        /* 0x640(0x032)  */ \
    {0U, 0},        /* 0x660(0x033)  */ \
    {0U, 0},        /* 0x680(0x034)  */ \
    {0U, 0},        /* 0x6A0(0x035)  */ \
    {0U, 0},        /* 0x6C0(0x036)  */ \
    {0U, 0},        /* 0x6E0(0x037)  */ \
\
    {C0INT2MSKCLR2, SCIF_0_ERI_MASK}, /* 0x700(0x038) SCIF-ch0 ERI0 */ \
    {C0INT2MSKCLR2, SCIF_0_RXI_MASK}, /* 0x720(0x039)          RXI0 */ \
    {C0INT2MSKCLR2, SCIF_0_BRI_MASK}, /* 0x740(0x03A)          BRI0 */ \
    {C0INT2MSKCLR2, SCIF_0_TXI_MASK}, /* 0x760(0x03B)          TXI0 */ \
\
    {C0INT2MSKCLR2, SCIF_1_ERI_MASK}, /* 0x780(0x03C) SCIF-ch1 ERI1 */ \
    {C0INT2MSKCLR2, SCIF_1_RXI_MASK}, /* 0x7A0(0x03D)         RXI1 */ \
    {C0INT2MSKCLR2, SCIF_1_BRI_MASK}, /* 0x7C0(0x03E)         BRI1 */ \
    {C0INT2MSKCLR2, SCIF_1_TXI_MASK}, /* 0x7E0(0x03F)         TXI1 */ \
\
    {C0INT2MSKCLR2, SCIF_2_ERI_MASK}, /* 0x800(0x040) SCIF-ch2 ERI2 */ \
    {C0INT2MSKCLR2, SCIF_2_RXI_MASK}, /* 0x820(0x041)          RXI2 */ \
    {C0INT2MSKCLR2, SCIF_2_BRI_MASK}, /* 0x840(0x042)          BRI2 */ \
    {C0INT2MSKCLR2, SCIF_2_TXI_MASK}, /* 0x860(0x043)          TXI2 */ \
\
    {C0INT2MSKCLR2, SCIF_3_ERI_MASK}, /* 0x880(0x044) SCIF-ch3 ERI3 */ \
    {C0INT2MSKCLR2, SCIF_3_RXI_MASK}, /* 0x8A0(0x045)          RXI3*/ \
    {C0INT2MSKCLR2, SCIF_3_BRI_MASK}, /* 0x8C0(0x046)          BRI3*/ \
    {C0INT2MSKCLR2, SCIF_3_TXI_MASK}, /* 0x8E0(0x047)          TXI3*/ \
\
    {C0INT2MSKCLR1, DMAC_0_0_MASK}, /* 0x900(0x048) DMINT0  DMINT0 */ \
    {C0INT2MSKCLR1, DMAC_0_1_MASK}, /* 0x920(0x049)  DMINT1 */ \
    {C0INT2MSKCLR1, DMAC_0_2_MASK}, /* 0x940(0x04A)  DMINT2 */ \
    {C0INT2MSKCLR1, DMAC_0_3_MASK}, /* 0x960(0x04B)  DMINT3 */ \
    {C0INT2MSKCLR1, DMAC_0_4_MASK}, /* 0x980(0x04C)  DMINT4  */ \
    {C0INT2MSKCLR1, DMAC_0_5_MASK}, /* 0x9A0(0x04D)  DMINT5 */ \
    {C0INT2MSKCLR1, DMAC_0_05_MASK}, /* 0x9C0(0x04E)  DMAE0 */ \
\
    {C0INT2MSKCLR0, DU_MASK},  /* 0x9E0(0x04F) DU*/ \
\
    {C0INT2MSKCLR1, DMAC_1_6_MASK}, /* 0xA00(0x050) DMIN6 */ \
    {C0INT2MSKCLR1, DMAC_1_7_MASK}, /* 0xA20(0x051) DMIN7 */ \
    {C0INT2MSKCLR1, DMAC_1_8_MASK}, /* 0xA40(0x052) DMIN8 */ \
    {C0INT2MSKCLR1, DMAC_1_9_MASK}, /* 0xA60(0x053) DMIN9 */ \
    {C0INT2MSKCLR1, DMAC_1_10_MASK}, /* 0xA80(0x054) DMIN10 */ \
    {C0INT2MSKCLR1, DMAC_1_11_MASK}, /* 0xAA0(0x055) DMIN11  */ \
    {C0INT2MSKCLR1, DMAC_1_611_MASK}, /* 0xAC0(0x056) DMAE1 */ \
\
    {C0INT2MSKCLR0, IIC_MASK},  /* 0xAE0(0x057) IIC */ \
\
    {C0INT2MSKCLR0, VIN_0_MASK},  /* 0xB00(0x058) VIN_0 */ \
    {C0INT2MSKCLR0, VIN_1_MASK}, /* 0xB20(0x059) VIN_1 */ \
\
    {C0INT2MSKCLR0, IMP_MASK}, /* 0xB40(0x05A) IMP*/ \
\
    {C0INT2MSKCLR0, ATA_MASK}, /* 0xB60(0x05B) ATA*/ \
\
    {0U, 0},        /* 0xB80(0x05C)  */ \
    {0U, 0},        /* 0xBA0(0x05D)  */ \
    {0U, 0},        /* 0xBC0(0x05E)  */ \
    {0U, 0},        /* 0xBE0(0x05F)  */ \
\
    {C0INT2MSKCLR1, DTU0_MASK}, /* 0xC00(0x060) TEND */ \
    {C0INT2MSKCLR1, DTU0_MASK}, /* 0xC20(0x061) AE  */ \
    {C0INT2MSKCLR1, DTU0_MASK}, /* 0xC40(0x062) TMISS */ \
\
    {C0INT2MSKCLR1, DTU1_MASK}, /* 0xC60(0x063) TEND */ \
    {C0INT2MSKCLR1, DTU1_MASK}, /* 0xC80(0x064) AE */ \
    {C0INT2MSKCLR1, DTU1_MASK}, /* 0xCA0(0x065) TMISS */ \
\
    {C0INT2MSKCLR1, DTU2_MASK}, /* 0xCC0(0x066) TEND*/ \
    {C0INT2MSKCLR1, DTU2_MASK}, /* 0xCE0(0x067) AE*/ \
    {C0INT2MSKCLR1, DTU2_MASK}, /* 0xC00(0x068) TMISS */ \
\
    {C0INT2MSKCLR1, DTU3_MASK}, /* 0xD20(0x069)       TEND  */ \
    {C0INT2MSKCLR1, DTU3_MASK}, /* 0xD40(0x06A)       AE   */ \
    {C0INT2MSKCLR1, DTU3_MASK}, /* 0xD60(0x06B)       TMISS  */ \
\
    {0U, 0},        /* 0xD80(0x06C)  */ \
    {0U, 0},        /* 0xDA0(0x06D) */ \
    {0U, 0},        /* 0xDC0(0x06E)   */ \
    {0U, 0},        /* 0xDE0(0x06F)   */ \
\
    {C0INT2MSKCLR0, FE0_MASK}, /* 0xE00(0x070) FE_0 */ \
\
    {C0INT2MSKCLR0, FE1_MASK}, /* 0xE20(0x071) FE_1 */ \
\
    {C0INT2MSKCLR0, GPIO_0_MASK}, /* 0xE40(0x072) GPIO_0 */ \
\
    {C0INT2MSKCLR0, GPIO_1_MASK},  /* 0xE60(0x073) GPIO_1*/ \
\
    {C0INT2MSKCLR0, GPIO_2_MASK}, /* 0xE80(0x074) GPIO_2 */ \
\
    {C0INT2MSKCLR0, GPIO_3_MASK}, /* 0xEA0(0x075) GPIO_3 */ \
    {C0INT2MSKCLR0, PAM_MASK}, /* 0xEC0(0x076) PAM*/ \
\
    {0U, 0},        /* 0xEE0(0x077) */ \
\
    {0U, 0},        /* 0xF00(0x078) */ \
    {0U, 0},        /* 0xF20(0x079) */ \
    {0U, 0},        /* 0xF40(0x07A) */ \
    {0U, 0},        /* 0xF60(0x07B) */ \
\
    {0U, 0},        /* 0xF80(0x07C) */ \
    {0U, 0},        /* 0xFA0(0x07D) */ \
    {0U, 0},        /* 0xFC0(0x07E) */ \
    {0U, 0},        /* 0xFE0(0x07F) */ \


#define CALC_CPU_MSKCLR_OFFSET(cpuindex) (cpuindex * 4);

/*
 *  �����ͥ���٥쥸�����ν����
 */
Inline void
init_int2pri(void) 
{
	sil_wrw_mem((void*)INT2PRI0, 0x00000000U);
	sil_wrw_mem((void*)INT2PRI1, 0x00000000U);
	sil_wrw_mem((void*)INT2PRI2, 0x00000000U);
	sil_wrw_mem((void*)INT2PRI3, 0x00000000U);
	sil_wrw_mem((void*)INT2PRI4, 0x00000000U);
}

/*
 *  ����ߥޥ����쥸�����ν����
 */
Inline void
init_int2msk(void)
{
	sil_wrw_mem((void *)C0INT2MSK0, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C1INT2MSK0, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C2INT2MSK0, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C3INT2MSK0, 0xFFFFFFFFU);

	sil_wrw_mem((void *)C0INT2MSK1, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C1INT2MSK1, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C2INT2MSK1, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C3INT2MSK1, 0xFFFFFFFFU);

	sil_wrw_mem((void *)C0INT2MSK2, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C1INT2MSK2, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C2INT2MSK2, 0xFFFFFFFFU);
	sil_wrw_mem((void *)C3INT2MSK2, 0xFFFFFFFFU);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �ץ��å���¸�⥸�塼���SH34�ѡ�
 */
#include "sh4a_gcc/prc_config.h"

#endif /* TOPPERS_RPROTO1_CONFIG_H */
