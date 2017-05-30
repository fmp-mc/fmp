/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2007-2011 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: sh7205_config.h 800 2011-05-02 08:08:34Z mit-kimai $
 */

/*
 *		プロセッサ依存モジュール（SH7205用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_SH7205_CONFIG_H
#define TOPPERS_SH7205_CONFIG_H

#ifndef TOPPERS_TARGET_CONFIG_H
#error  target_config.h is not included!
#endif	/*  TOPPERS_TARGET_CONFIG_H  */

/*
 * CPU例外番号に関する定義
 */
#define TMIN_EXCNO		UINT_C(4)		/*  GENERAL_ILLEGAL_INSTRUCTION_VECTOR  */
#define TMAX_EXCNO		UINT_C(63)		/*  TRAPA_INST_VECTOR  */
#define TNUM_EXC		(TMAX_EXCNO - TMIN_EXCNO + 1U)

/*
 * 割込みハンドラ番号に関する定義
 */
#define TMIN_INHNO		UINT_C(64)
#define TMAX_INHNO		UINT_C(235)
#define TNUM_INH		(TMAX_INHNO - TMIN_INHNO + 1U)

/*
 * 割込み番号に関する定義
 */
#define TMIN_INTNO				UINT_C(64)
#define TMAX_INTNO				UINT_C(258)
#define TNUM_INT				(TMAX_INTNO - TMIN_INTNO + 1U)

/*  IRQ割込み  */
#define TMIN_INTNO_IRQ 			IRQ0_VECTOR
#define TMAX_INTNO_IRQ			IRQ7_VECTOR

/*  PINT割込み  */
#define TMIN_INTNO_PINT			PINT0_VECTOR
#define TMAX_INTNO_PINT			PINT7_VECTOR

/*  内蔵周辺モジュール（IDCNTレジスタアクセス用インデックス）  */
#define TMIN_INTNO_PERIPHERAL	DMAC0_DMINT0_VECTOR
#define TMAX_INTNO_PERIPHERAL	RCAN1_SLE1_VECTOR
/*  IDCNTレジスタアクセス用インデックス  */
#define TMIN_INTNO_IDCNT		DMAC0_DMINT0_VECTOR
/*  スパースな部分もカウントする  */
#define TNUM_IDCNT				(139U - 6U + 1U)

/*  プロセッサ間割込み  */
#define TMIN_INTNO_IPI			IPI15_VECTOR
#define TMAX_INTNO_IPI			IPI08_VECTOR


/*
 *  CnIPRxレジスタの数
 *  　スパースな部分はカウントしない。
 */
#define TNUM_IPR			19U


/*
 *  割込み要求ライン毎の優先レベル設定レジスタの設定情報
 *  　
 *  　テーブルには、CPU0のC0IPRxのアドレスだけを格納する。
 *  　CPU1のC1IPRxのアドレスは、CPU0のC0IPRxのアドレスに
 *  　0x100を加えることで求められる。
 *  　　要検討：プロセッサ間割込みについては、割込み優先レベルが固定されている。
 */
#define IPR_INFO_TBL_DATA   \
	{C0IPR01_h, 12U}, /*  64 IRQ0 */ \
	{C0IPR01_h,  8U}, /*  65 IRQ1 */ \
	{C0IPR01_h,  4U}, /*  66 IRQ2 */ \
	{C0IPR01_h,  0U}, /*  67 IRQ3 */ \
	{C0IPR02_h, 12U}, /*  68 IRQ4 */ \
	{C0IPR02_h,  8U}, /*  69 IRQ5 */ \
	{C0IPR02_h,  4U}, /*  70 IRQ6 */ \
	{C0IPR02_h,  0U}, /*  71 IRQ7 */ \
\
	{0U, 0U},         /*  72 */ \
	{0U, 0U},         /*  73 */ \
	{0U, 0U},         /*  74 */ \
	{0U, 0U},         /*  75 */ \
	{0U, 0U},         /*  76 */ \
	{0U, 0U},         /*  77 */ \
	{0U, 0U},         /*  78 */ \
	{0U, 0U},         /*  79 */ \
\
	{C0IPR05_h, 12U}, /*  80 PINT0 */ \
	{C0IPR05_h, 12U}, /*  81 PINT1 */ \
	{C0IPR05_h, 12U}, /*  82 PINT2 */ \
	{C0IPR05_h, 12U}, /*  83 PINT3 */ \
	{C0IPR05_h, 12U}, /*  84 PINT4 */ \
	{C0IPR05_h, 12U}, /*  85 PINT5 */ \
	{C0IPR05_h, 12U}, /*  86 PINT6 */ \
	{C0IPR05_h, 12U}, /*  87 PINT7 */ \
\
	{0U, 0U},         /*  88 */ \
	{0U, 0U},         /*  89 */ \
	{0U, 0U},         /*  90 */ \
	{0U, 0U},         /*  91 */ \
	{0U, 0U},         /*  92 */ \
	{0U, 0U},         /*  93 */ \
	{0U, 0U},         /*  94 */ \
	{0U, 0U},         /*  95 */ \
	{0U, 0U},         /*  96 */ \
	{0U, 0U},         /*  97 */ \
	{0U, 0U},         /*  98 */ \
	{0U, 0U},         /*  99 */ \
	{0U, 0U},         /* 100 */ \
	{0U, 0U},         /* 101 */ \
\
	{C0IPR06_h,12U}, /*  102 DMAC0 */ \
	{C0IPR06_h, 8U}, /*  103 DMAC1 */ \
	{C0IPR06_h, 4U}, /*  104 DMAC2 */ \
	{C0IPR06_h, 0U}, /*  105 DMAC3 */ \
	{C0IPR07_h,12U}, /*  106 DMAC4 */ \
	{C0IPR07_h, 8U}, /*  107 DMAC5 */ \
	{C0IPR07_h, 4U}, /*  108 DMAC6 */ \
	{C0IPR07_h, 0U}, /*  109 DMAC7 */ \
	{C0IPR08_h,12U}, /*  110 DMAC8 */ \
	{C0IPR08_h, 8U}, /*  111 DMAC9 */ \
	{C0IPR08_h, 4U}, /*  112 DMAC10 */ \
	{C0IPR08_h, 0U}, /*  113 DMAC11 */ \
	{C0IPR09_h,12U}, /*  114 DMAC12 */ \
	{C0IPR09_h, 8U}, /*  115 DMAC13 */ \
	{C0IPR09_h, 4U}, /*  116 DMINTA */ \
	{C0IPR09_h, 0U}, /*  117 USB */ \
	{C0IPR10_h,12U}, /*  118 CMI0 要確認 */ \
	{C0IPR10_h, 8U}, /*  119 CMI1 要確認 */ \
	{C0IPR10_h, 4U}, /*  120 CMI2 要確認 */ \
	{C0IPR10_h, 0U}, /*  121 CMI3 要確認 */ \
	{C0IPR11_h,12U}, /*  122 WDT0 */ \
	{C0IPR11_h, 8U}, /*  123 WDT1 */ \
	{C0IPR11_h, 4U}, /*  124 TGI0A */ \
	{C0IPR11_h, 4U}, /*  125 TGI0B */ \
	{C0IPR11_h, 4U}, /*  126 TGI0C */ \
	{C0IPR11_h, 4U}, /*  127 TGI0D */ \
	{C0IPR11_h, 0U}, /*  128 TGI0V */ \
	{C0IPR11_h, 0U}, /*  129 TGI0E */ \
	{C0IPR11_h, 0U}, /*  130 TGI0F */ \
	{C0IPR12_h,12U}, /*  131 TGI1A */ \
	{C0IPR12_h,12U}, /*  132 TGI1B */ \
	{C0IPR12_h, 8U}, /*  133 TGI1V */ \
	{C0IPR12_h, 8U}, /*  134 TGI1U */ \
	{C0IPR12_h, 4U}, /*  135 TGI2A */ \
	{C0IPR12_h, 4U}, /*  136 TGI2B */ \
	{C0IPR12_h, 0U}, /*  137 TGI2V */ \
	{C0IPR12_h, 0U}, /*  138 TGI2U */ \
	{C0IPR13_h,12U}, /*  139 TGI3A */ \
	{C0IPR13_h,12U}, /*  140 TGI3B */ \
	{C0IPR13_h,12U}, /*  141 TGI3C */ \
	{C0IPR13_h,12U}, /*  142 TGI3D */ \
	{C0IPR13_h, 8U}, /*  143 TGI3V */ \
	{C0IPR13_h, 4U}, /*  144 TGI4A */ \
	{C0IPR13_h, 4U}, /*  145 TGI4B */ \
	{C0IPR13_h, 4U}, /*  146 TGI4C */ \
	{C0IPR13_h, 4U}, /*  147 TGI4D */ \
	{C0IPR13_h, 0U}, /*  148 TGI4V */ \
	{C0IPR14_h,12U}, /*  149 SSII0 */ \
	{C0IPR14_h,12U}, /*  150 SSIRTI0 */ \
	{C0IPR14_h, 8U}, /*  151 SSII1 */ \
	{C0IPR14_h, 8U}, /*  152 SSIRTI1 */ \
	{C0IPR14_h, 4U}, /*  153 SSII2 */ \
	{C0IPR14_h, 4U}, /*  154 SSIRTI2 */ \
	{C0IPR14_h, 0U}, /*  155 SSII3 */ \
	{C0IPR14_h, 0U}, /*  156 SSIRTI3 */ \
	{C0IPR15_h,12U}, /*  157 SSII4 */ \
	{C0IPR15_h,12U}, /*  158 SSIRTI4 */ \
	{C0IPR15_h, 8U}, /*  159 SSII5 */ \
	{C0IPR15_h, 8U}, /*  160 SSIRTI5 */ \
\
	{0U, 0U},        /* 161 */ \
\
	{C0IPR16_h,12U}, /*  162 IIC3_0_STPI0 */ \
	{C0IPR16_h,12U}, /*  163 IIC3_0_NAKI0 */ \
	{C0IPR16_h,12U}, /*  164 IIC3_0_RXI0 */ \
	{C0IPR16_h,12U}, /*  165 IIC3_0_TXI0 */ \
	{C0IPR16_h,12U}, /*  166 IIC3_0_TEI0 */ \
	{C0IPR16_h, 8U}, /*  167 IIC3_0_STPI1 */ \
	{C0IPR16_h, 8U}, /*  168 IIC3_0_NAKI1 */ \
	{C0IPR16_h, 8U}, /*  169 IIC3_0_RXI1 */ \
	{C0IPR16_h, 8U}, /*  170 IIC3_0_TXI1 */ \
	{C0IPR16_h, 8U}, /*  171 IIC3_0_TEI1 */ \
	{C0IPR16_h, 4U}, /*  172 IIC3_0_STPI2 */ \
	{C0IPR16_h, 4U}, /*  173 IIC3_0_NAKI2 */ \
	{C0IPR16_h, 4U}, /*  174 IIC3_0_RXI2 */ \
	{C0IPR16_h, 4U}, /*  175 IIC3_0_TXI2 */ \
	{C0IPR16_h, 4U}, /*  176 IIC3_0_TEI2 */ \
	{C0IPR16_h, 0U}, /*  177 IIC3_0_STPI3 */ \
	{C0IPR16_h, 0U}, /*  178 IIC3_0_NAKI3 */ \
	{C0IPR16_h, 0U}, /*  179 IIC3_0_RXI3 */ \
	{C0IPR16_h, 0U}, /*  180 IIC3_0_TXI3 */ \
	{C0IPR16_h, 0U}, /*  181 IIC3_0_TEI3 */ \
	{C0IPR17_h,12U}, /*  182 SCIF0_BRI */ \
	{C0IPR17_h,12U}, /*  183 SCIF0_ERI */ \
	{C0IPR17_h,12U}, /*  184 SCIF0_RXI */ \
	{C0IPR17_h,12U}, /*  185 SCIF0_TXI */ \
	{C0IPR17_h, 8U}, /*  186 SCIF1_BRI */ \
	{C0IPR17_h, 8U}, /*  187 SCIF1_ERI */ \
	{C0IPR17_h, 8U}, /*  188 SCIF1_RXI */ \
	{C0IPR17_h, 8U}, /*  189 SCIF1_TXI */ \
	{C0IPR17_h, 4U}, /*  190 SCIF2_BRI */ \
	{C0IPR17_h, 4U}, /*  191 SCIF2_ERI */ \
	{C0IPR17_h, 4U}, /*  192 SCIF2_RXI */ \
	{C0IPR17_h, 4U}, /*  193 SCIF2_TXI */ \
	{C0IPR17_h, 0U}, /*  194 SCIF3_BRI */ \
	{C0IPR17_h, 0U}, /*  195 SCIF3_ERI */ \
	{C0IPR17_h, 0U}, /*  196 SCIF3_RXI */ \
	{C0IPR17_h, 0U}, /*  197 SCIF3_TXI */ \
	{C0IPR18_h,12U}, /*  198 SCIF4_BRI */ \
	{C0IPR18_h,12U}, /*  199 SCIF4_ERI */ \
	{C0IPR18_h,12U}, /*  200 SCIF4_RXI */ \
	{C0IPR18_h,12U}, /*  201 SCIF4_TXI */ \
	{C0IPR18_h, 8U}, /*  202 SCIF5_BRI */ \
	{C0IPR18_h, 8U}, /*  203 SCIF5_ERI */ \
	{C0IPR18_h, 8U}, /*  204 SCIF5_RXI */ \
	{C0IPR18_h, 8U}, /*  205 SCIF5_TXI */ \
	{C0IPR19_h,12U}, /*  206 SSU0_SSERI0 */ \
	{C0IPR19_h,12U}, /*  207 SSU0_SSRXI0 */ \
	{C0IPR19_h,12U}, /*  208 SSU0_SSTXI0 */ \
	{C0IPR19_h, 8U}, /*  209 SSU1_SSERI1 */ \
	{C0IPR19_h, 8U}, /*  210 SSU1_SSRXI1 */ \
	{C0IPR19_h, 8U}, /*  211 SSU1_SSTXI1 */ \
	{C0IPR19_h, 4U}, /*  212 ADC */ \
	{C0IPR19_h, 0U}, /*  213 2DG_BLT */ \
	{C0IPR19_h, 0U}, /*  214 2DG_OUT */ \
	{C0IPR20_h,12U}, /*  215 ATAPII */ \
	{C0IPR20_h, 8U}, /*  216 FLSTEI */ \
	{C0IPR20_h, 8U}, /*  217 FLTENDI */ \
	{C0IPR20_h, 8U}, /*  218 FLTREQ0I */ \
	{C0IPR20_h, 8U}, /*  219 FLTREQ1I */ \
	{C0IPR20_h, 4U}, /*  220 RTC_ARM */ \
	{C0IPR20_h, 4U}, /*  221 RTC_PRD */ \
	{C0IPR20_h, 4U}, /*  222 RTC_CUP */ \
\
	{0U, 0U},        /* 223 */ \
	{0U, 0U},        /* 224 */ \
	{0U, 0U},        /* 225 */ \
\
	{C0IPR21_h,12U}, /*  226 RCAN0_ERS0 */ \
	{C0IPR21_h,12U}, /*  227 RCAN0_OVR0 */ \
	{C0IPR21_h,12U}, /*  228 RCAN0_RM00 */ \
	{C0IPR21_h,12U}, /*  229 RCAN0_RM10 */ \
	{C0IPR21_h,12U}, /*  230 RCAN0_SLE0 */ \
	{C0IPR21_h, 8U}, /*  231 RCAN1_ERS1 */ \
	{C0IPR21_h, 8U}, /*  232 RCAN1_OVR1 */ \
	{C0IPR21_h, 8U}, /*  233 RCAN1_RM01 */ \
	{C0IPR21_h, 8U}, /*  234 RCAN1_RM11 */ \
	{C0IPR21_h, 8U}  /*  235 RCAN1_SLE1 */


#ifndef TOPPERS_MACRO_ONLY

#include <sil.h>

/*
 *  割込みコントローラのレジスタ定義
 *  　　・1コア分
 * 　ペリファラルの数によって、割込みコントローラのレジスタ構成が
 * 　異なるため、チップ依存部で定義する。
 */
typedef struct {
	uint16_t *icr0_h;
	uint16_t *icr1_h;
	uint16_t *icr2_h;
	uint16_t *irqrr_h;
	uint16_t *pinter_h;
	uint16_t *pirr_h;
	uint16_t *ibcr_h;
	uint16_t *ibnr_h;
	
	uint16_t *inter_h;
	uint16_t *irqer_h;
	uint16_t *ipcr15_h;
	uint16_t *ipcr14_h;
	uint16_t *ipcr13_h;
	uint16_t *ipcr12_h;
	uint16_t *ipcr11_h;
	uint16_t *ipcr10_h;
	uint16_t *ipcr9_h;
	uint16_t *ipcr8_h;
	uint16_t *iper_h;

	/*  IPRを連続した領域にまとめる  */
	uint16_t *ipr_h[TNUM_IPR];
} IRC_REG;


/*
 *  割込みコントローラのレジスタ定義
 */
#define IRC_REG_DATA   				\
	{								\
		(uint16_t *)C0ICR0_h,		\
		(uint16_t *)C0ICR1_h,		\
		(uint16_t *)C0ICR2_h,		\
		(uint16_t *)C0IRQRR_h,		\
		(uint16_t *)C0PINTER_h,		\
		(uint16_t *)C0PIRR_h,		\
		(uint16_t *)C0IBCR_h,		\
		(uint16_t *)C0IBNR_h,		\
									\
		(uint16_t *)C0INTER_h,		\
		(uint16_t *)C0IRQER_h,		\
									\
		(uint16_t *)C0IPCR15_h,		\
		(uint16_t *)C0IPCR14_h,		\
		(uint16_t *)C0IPCR13_h,		\
		(uint16_t *)C0IPCR12_h,		\
		(uint16_t *)C0IPCR11_h,		\
		(uint16_t *)C0IPCR10_h,		\
		(uint16_t *)C0IPCR09_h,		\
		(uint16_t *)C0IPCR08_h,		\
									\
		(uint16_t *)C0IPER_h,		\
									\
		{							\
			(uint16_t *)C0IPR01_h,	\
			(uint16_t *)C0IPR02_h,	\
			(uint16_t *)C0IPR05_h,	\
									\
			(uint16_t *)C0IPR06_h,	\
			(uint16_t *)C0IPR07_h,	\
			(uint16_t *)C0IPR08_h,	\
			(uint16_t *)C0IPR09_h,	\
			(uint16_t *)C0IPR10_h,	\
			(uint16_t *)C0IPR11_h,	\
			(uint16_t *)C0IPR12_h,	\
			(uint16_t *)C0IPR13_h,	\
			(uint16_t *)C0IPR14_h,	\
			(uint16_t *)C0IPR15_h,	\
			(uint16_t *)C0IPR16_h,	\
			(uint16_t *)C0IPR17_h,	\
			(uint16_t *)C0IPR18_h,	\
			(uint16_t *)C0IPR19_h,	\
			(uint16_t *)C0IPR20_h,	\
			(uint16_t *)C0IPR21_h	\
		}							\
	},{								\
		(uint16_t *)C1ICR0_h,		\
		(uint16_t *)C1ICR1_h,		\
		(uint16_t *)C1ICR2_h,		\
		(uint16_t *)C1IRQRR_h,		\
		(uint16_t *)C1PINTER_h,		\
		(uint16_t *)C1PIRR_h,		\
		(uint16_t *)C1IBCR_h,		\
		(uint16_t *)C1IBNR_h,		\
									\
		(uint16_t *)C1INTER_h,		\
		(uint16_t *)C1IRQER_h,		\
									\
		(uint16_t *)C1IPCR15_h,		\
		(uint16_t *)C1IPCR14_h,		\
		(uint16_t *)C1IPCR13_h,		\
		(uint16_t *)C1IPCR12_h,		\
		(uint16_t *)C1IPCR11_h,		\
		(uint16_t *)C1IPCR10_h,		\
		(uint16_t *)C1IPCR09_h,		\
		(uint16_t *)C1IPCR08_h,		\
									\
		(uint16_t *)C1IPER_h,		\
									\
		{							\
			(uint16_t *)C1IPR01_h,	\
			(uint16_t *)C1IPR02_h,	\
			(uint16_t *)C1IPR05_h,	\
									\
			(uint16_t *)C1IPR06_h,	\
			(uint16_t *)C1IPR07_h,	\
			(uint16_t *)C1IPR08_h,	\
			(uint16_t *)C1IPR09_h,	\
			(uint16_t *)C1IPR10_h,	\
			(uint16_t *)C1IPR11_h,	\
			(uint16_t *)C1IPR12_h,	\
			(uint16_t *)C1IPR13_h,	\
			(uint16_t *)C1IPR14_h,	\
			(uint16_t *)C1IPR15_h,	\
			(uint16_t *)C1IPR16_h,	\
			(uint16_t *)C1IPR17_h,	\
			(uint16_t *)C1IPR18_h,	\
			(uint16_t *)C1IPR19_h,	\
			(uint16_t *)C1IPR20_h,	\
			(uint16_t *)C1IPR21_h	\
		}							\
	}


/*
 *  割込み検出制御レジスタの定義
 */
#define IDCNT_REG_DATA   				\
		(uint16_t *)IDCNT6_h,			\
		(uint16_t *)IDCNT7_h,			\
		(uint16_t *)IDCNT8_h,			\
		(uint16_t *)IDCNT9_h,			\
		(uint16_t *)IDCNT10_h,			\
		(uint16_t *)IDCNT11_h,			\
		(uint16_t *)IDCNT12_h,			\
		(uint16_t *)IDCNT13_h,			\
		(uint16_t *)IDCNT14_h,			\
		(uint16_t *)IDCNT15_h,			\
		(uint16_t *)IDCNT16_h,			\
		(uint16_t *)IDCNT17_h,			\
		(uint16_t *)IDCNT18_h,			\
		(uint16_t *)IDCNT19_h,			\
		(uint16_t *)IDCNT20_h,			\
		(uint16_t *)IDCNT21_h,			\
		(uint16_t *)IDCNT22_h,			\
		(uint16_t *)IDCNT23_h,			\
		(uint16_t *)IDCNT24_h,			\
		(uint16_t *)IDCNT25_h,			\
		(uint16_t *)IDCNT26_h,			\
		(uint16_t *)IDCNT27_h,			\
		(uint16_t *)IDCNT28_h,			\
		(uint16_t *)IDCNT29_h,			\
		(uint16_t *)IDCNT30_h,			\
		(uint16_t *)IDCNT31_h,			\
		(uint16_t *)IDCNT32_h,			\
		(uint16_t *)IDCNT33_h,			\
		(uint16_t *)IDCNT34_h,			\
		(uint16_t *)IDCNT35_h,			\
		(uint16_t *)IDCNT36_h,			\
		(uint16_t *)IDCNT37_h,			\
		(uint16_t *)IDCNT38_h,			\
		(uint16_t *)IDCNT39_h,			\
		(uint16_t *)IDCNT40_h,			\
		(uint16_t *)IDCNT41_h,			\
		(uint16_t *)IDCNT42_h,			\
		(uint16_t *)IDCNT43_h,			\
		(uint16_t *)IDCNT44_h,			\
		(uint16_t *)IDCNT45_h,			\
		(uint16_t *)IDCNT46_h,			\
		(uint16_t *)IDCNT47_h,			\
		(uint16_t *)IDCNT48_h,			\
		(uint16_t *)IDCNT49_h,			\
		(uint16_t *)IDCNT50_h,			\
		(uint16_t *)IDCNT51_h,			\
		(uint16_t *)IDCNT52_h,			\
		(uint16_t *)IDCNT53_h,			\
		(uint16_t *)IDCNT54_h,			\
		(uint16_t *)IDCNT55_h,			\
		(uint16_t *)IDCNT56_h,			\
		(uint16_t *)IDCNT57_h,			\
		(uint16_t *)IDCNT58_h,			\
		(uint16_t *)IDCNT59_h,			\
		(uint16_t *)IDCNT60_h,			\
		(uint16_t *)IDCNT61_h,			\
		(uint16_t *)IDCNT62_h,			\
		(uint16_t *)IDCNT63_h,			\
		(uint16_t *)IDCNT64_h,			\
		(uint16_t *)NULL,/*  65は欠番  */\
		(uint16_t *)IDCNT66_h,			\
		(uint16_t *)IDCNT67_h,			\
		(uint16_t *)IDCNT68_h,			\
		(uint16_t *)IDCNT69_h,			\
		(uint16_t *)IDCNT70_h,			\
		(uint16_t *)IDCNT71_h,			\
		(uint16_t *)IDCNT72_h,			\
		(uint16_t *)IDCNT73_h,			\
		(uint16_t *)IDCNT74_h,			\
		(uint16_t *)IDCNT75_h,			\
		(uint16_t *)IDCNT76_h,			\
		(uint16_t *)IDCNT77_h,			\
		(uint16_t *)IDCNT78_h,			\
		(uint16_t *)IDCNT79_h,			\
		(uint16_t *)IDCNT80_h,			\
		(uint16_t *)IDCNT81_h,			\
		(uint16_t *)IDCNT82_h,			\
		(uint16_t *)IDCNT83_h,			\
		(uint16_t *)IDCNT84_h,			\
		(uint16_t *)IDCNT85_h,			\
		(uint16_t *)IDCNT86_h,			\
		(uint16_t *)IDCNT87_h,			\
		(uint16_t *)IDCNT88_h,			\
		(uint16_t *)IDCNT89_h,			\
		(uint16_t *)IDCNT90_h,			\
		(uint16_t *)IDCNT91_h,			\
		(uint16_t *)IDCNT92_h,			\
		(uint16_t *)IDCNT93_h,			\
		(uint16_t *)IDCNT94_h,			\
		(uint16_t *)IDCNT95_h,			\
		(uint16_t *)IDCNT96_h,			\
		(uint16_t *)IDCNT97_h,			\
		(uint16_t *)IDCNT98_h,			\
		(uint16_t *)IDCNT99_h,			\
		(uint16_t *)IDCNT100_h,			\
		(uint16_t *)IDCNT101_h,			\
		(uint16_t *)IDCNT102_h,			\
		(uint16_t *)IDCNT103_h,			\
		(uint16_t *)IDCNT104_h,			\
		(uint16_t *)IDCNT105_h,			\
		(uint16_t *)IDCNT106_h,			\
		(uint16_t *)IDCNT107_h,			\
		(uint16_t *)IDCNT108_h,			\
		(uint16_t *)IDCNT109_h,			\
		(uint16_t *)IDCNT110_h,			\
		(uint16_t *)IDCNT111_h,			\
		(uint16_t *)IDCNT112_h,			\
		(uint16_t *)IDCNT113_h,			\
		(uint16_t *)IDCNT114_h,			\
		(uint16_t *)IDCNT115_h,			\
		(uint16_t *)IDCNT116_h,			\
		(uint16_t *)IDCNT117_h,			\
		(uint16_t *)IDCNT118_h,			\
		(uint16_t *)IDCNT119_h,			\
		(uint16_t *)IDCNT120_h,			\
		(uint16_t *)IDCNT121_h,			\
		(uint16_t *)IDCNT122_h,			\
		(uint16_t *)IDCNT123_h,			\
		(uint16_t *)IDCNT124_h,			\
		(uint16_t *)IDCNT125_h,			\
		(uint16_t *)IDCNT126_h,			\
		(uint16_t *)NULL,/*  127は欠番  */\
		(uint16_t *)NULL,/*  128は欠番  */\
		(uint16_t *)NULL,/*  129は欠番  */\
		(uint16_t *)IDCNT130_h,			\
		(uint16_t *)IDCNT131_h,			\
		(uint16_t *)IDCNT132_h,			\
		(uint16_t *)IDCNT133_h,			\
		(uint16_t *)IDCNT134_h,			\
		(uint16_t *)IDCNT135_h,			\
		(uint16_t *)IDCNT136_h,			\
		(uint16_t *)IDCNT137_h,			\
		(uint16_t *)IDCNT138_h,			\
		(uint16_t *)IDCNT139_h
		

/*
 *  セマフォ制御レジスタの定義
 */
#define TNUM_SEMR						32
#define SEMR_REG_DATA   				\
		(uint8_t *)SEMR0_b,				\
		(uint8_t *)SEMR1_b,				\
		(uint8_t *)SEMR2_b,				\
		(uint8_t *)SEMR3_b,				\
		(uint8_t *)SEMR4_b,				\
		(uint8_t *)SEMR5_b,				\
		(uint8_t *)SEMR6_b,				\
		(uint8_t *)SEMR7_b,				\
		(uint8_t *)SEMR8_b,				\
		(uint8_t *)SEMR9_b,				\
		(uint8_t *)SEMR10_b,			\
		(uint8_t *)SEMR11_b,			\
		(uint8_t *)SEMR12_b,			\
		(uint8_t *)SEMR13_b,			\
		(uint8_t *)SEMR14_b,			\
		(uint8_t *)SEMR15_b,			\
		(uint8_t *)SEMR16_b,			\
		(uint8_t *)SEMR17_b,			\
		(uint8_t *)SEMR18_b,			\
		(uint8_t *)SEMR19_b,			\
		(uint8_t *)SEMR20_b,			\
		(uint8_t *)SEMR21_b,			\
		(uint8_t *)SEMR22_b,			\
		(uint8_t *)SEMR23_b,			\
		(uint8_t *)SEMR24_b,			\
		(uint8_t *)SEMR25_b,			\
		(uint8_t *)SEMR26_b,			\
		(uint8_t *)SEMR27_b,			\
		(uint8_t *)SEMR28_b,			\
		(uint8_t *)SEMR29_b,			\
		(uint8_t *)SEMR30_b,			\
		(uint8_t *)SEMR31_b


#endif /* TOPPERS_MACRO_ONLY */

/*
 *  プロセッサ依存モジュール（SH2A-DUAL用）
 */
#include "sh2a_dual_config.h"

#endif /* TOPPERS_SH7205_CONFIG_H */
