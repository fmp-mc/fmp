/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2007-2011 by Industrial Technology Institute,
 *								Miyagi Prefectural Government, JAPAN
 *	
 *	上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *	ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *	変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *	(1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *		権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *		スコード中に含まれていること．
 *	(2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *		用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *		者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *		の無保証規定を掲載すること．
 *	(3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *		用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *		と．
 *	  (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *		  作権表示，この利用条件および下記の無保証規定を掲載すること．
 *	  (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *		  報告すること．
 *	(4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *		害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *		また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *		由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *		免責すること．
 *	
 *	本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *	よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *	に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *	アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *	の責任を負わない．
 * 
 *  $Id: sh7205.h 800 2011-05-02 08:08:34Z mit-kimai $
 */

/*
 *	SH7205のハードウェア資源の定義
 */

#ifndef TOPPERS_SH7205_H
#define TOPPERS_SH7205_H

/*
 *	例外ベクタ
 */
#define POWER_ON_RESET_VECTOR				0
#define MANUAL_RESET_VECTOR					2
#define GENERAL_ILLEGAL_INSTRUCTION_VECTOR	4
#define SLOT_ILLEGAL_INSTRUCTION_VECTOR		6
#define CPU_ADDRESS_ERROR_VECTOR			9
#define NMI_VECTOR							11
#define USER_BREAK_VECTOR					12
#define FPU_VECTOR							13
#define H_UDI_VECTOR						14
#define BANK_OVER_FLOW_VECTOR				15
#define BANK_UNDER_FLOW_VECTOR				16
#define DIVIDE_BY_ZERO_VECTOR				17
#define OVER_FLOW_VECTOR					18
#define SLEEP_ERROR_VECTOR					19

/*
 *	割込みベクタ
 */
#define IPI15_VECTOR				21
#define IPI14_VECTOR				22
#define IPI13_VECTOR				23
#define IPI12_VECTOR				24
#define IPI11_VECTOR				25
#define IPI10_VECTOR				26
#define IPI09_VECTOR				27
#define IPI08_VECTOR				28

#define IRQ0_VECTOR 	   			64
#define IRQ1_VECTOR 	   			65
#define IRQ2_VECTOR 	   			66
#define IRQ3_VECTOR 	   			67
#define IRQ4_VECTOR 	   			68
#define IRQ5_VECTOR 	   			69
#define IRQ6_VECTOR 	   			70
#define IRQ7_VECTOR    				71

#define PINT0_VECTOR   				80
#define PINT1_VECTOR   				81
#define PINT2_VECTOR   				82
#define PINT3_VECTOR   				83
#define PINT4_VECTOR   				84
#define PINT5_VECTOR   				85
#define PINT6_VECTOR   				86
#define PINT7_VECTOR   				87

#define DMAC0_DMINT0_VECTOR 	 	102
#define DMAC1_DMINT1_VECTOR 	 	103
#define DMAC2_DMINT2_VECTOR 	 	104
#define DMAC3_DMINT3_VECTOR 	 	105
#define DMAC4_DMINT4_VECTOR 	 	106
#define DMAC5_DMINT5_VECTOR 	 	107
#define DMAC6_DMINT6_VECTOR 	 	108
#define DMAC7_DMINT7_VECTOR 	 	109
#define DMAC8_DMINT8_VECTOR 	 	110
#define DMAC9_DMINT9_VECTOR 	 	111
#define DMAC10_DMINT10_VECTOR	   	112
#define DMAC11_DMINT11_VECTOR	   	113
#define DMAC12_DMINT12_VECTOR	   	114
#define DMAC13_DMINT13_VECTOR	   	115
#define DMINTA_VECTOR	   			116

#define USBI_VECTOR 	 			117

#define CMI0_VECTOR 	   			118
#define CMI1_VECTOR 	   			119
#define CMI2_VECTOR 	   			120
#define CMI3_VECTOR 	   			121

#define ITI0_VECTOR 	   			122
#define ITI1_VECTOR 	   			123

#define MTU0_TGI0A_VECTOR		 	124
#define MTU0_TGI0B_VECTOR		 	125
#define MTU0_TGI0C_VECTOR		 	126
#define MTU0_TGI0D_VECTOR		 	127
#define MTU0_TGI0V_VECTOR		 	128
#define MTU0_TGI0E_VECTOR		 	129
#define MTU0_TGI0F_VECTOR		 	130

#define MTU1_TGI1A_VECTOR		 	131
#define MTU1_TGI1B_VECTOR		 	132
#define MTU1_TGI1V_VECTOR		 	133
#define MTU1_TGI1U_VECTOR		 	134

#define MTU2_TGI2A_VECTOR		 	135
#define MTU2_TGI2B_VECTOR		 	136
#define MTU2_TGI2V_VECTOR		 	137
#define MTU2_TGI2U_VECTOR		 	138

#define MTU3_TGI3A_VECTOR		 	139
#define MTU3_TGI3B_VECTOR		 	140
#define MTU3_TGI3C_VECTOR		 	141
#define MTU3_TGI3D_VECTOR		 	142
#define MTU3_TGI3V_VECTOR		 	143

#define MTU4_TGI4A_VECTOR		 	144
#define MTU4_TGI4B_VECTOR		 	145
#define MTU4_TGI4C_VECTOR		 	146
#define MTU4_TGI4D_VECTOR		 	147
#define MTU4_TGI4V_VECTOR		 	148

#define SSIF0_SSII0_VECTOR		  	149
#define SSIF0_SSIRTI0_VECTOR	  	150
#define SSIF1_SSII1_VECTOR		  	151
#define SSIF1_SSIRTI1_VECTOR	  	152
#define SSIF2_SSII2_VECTOR		  	153
#define SSIF2_SSIRTI2_VECTOR	  	154
#define SSIF3_SSII3_VECTOR		  	155
#define SSIF3_SSIRTI3_VECTOR	  	156
#define SSIF4_SSII4_VECTOR		  	157
#define SSIF4_SSIRTI4_VECTOR	  	158
#define SSIF5_SSII5_VECTOR		  	159
#define SSIF5_SSIRTI5_VECTOR	  	160
/*	161は欠番  */
#define IIC3_0_STPI0_VECTOR    		162
#define IIC3_0_NAKI0_VECTOR    		163
#define IIC3_0_RXI0_VECTOR	  		164
#define IIC3_0_TXI0_VECTOR	  		165
#define IIC3_0_TEI0_VECTOR	  		166
#define IIC3_1_STPI1_VECTOR    		167
#define IIC3_1_NAKI1_VECTOR    		168
#define IIC3_1_RXI1_VECTOR	  		169
#define IIC3_1_TXI1_VECTOR	  		170
#define IIC3_1_TEI1_VECTOR	  		171
#define IIC3_2_STPI2_VECTOR    		172
#define IIC3_2_NAKI2_VECTOR    		173
#define IIC3_2_RXI2_VECTOR	  		174
#define IIC3_2_TXI2_VECTOR	  		175
#define IIC3_2_TEI2_VECTOR	  		176
#define IIC3_3_STPI3_VECTOR    		177
#define IIC3_3_NAKI3_VECTOR    		178
#define IIC3_3_RXI3_VECTOR	  		179
#define IIC3_3_TXI3_VECTOR	  		180
#define IIC3_3_TEI3_VECTOR	  		181

#define SCIF0_BRI_VECTOR   			182
#define SCIF0_ERI_VECTOR   			183
#define SCIF0_RXI_VECTOR   			184
#define SCIF0_TXI_VECTOR   			185

#define SCIF1_BRI_VECTOR   			186
#define SCIF1_ERI_VECTOR   			187
#define SCIF1_RXI_VECTOR   			188
#define SCIF1_TXI_VECTOR   			189

#define SCIF2_BRI_VECTOR   			190
#define SCIF2_ERI_VECTOR   			191
#define SCIF2_RXI_VECTOR   			192
#define SCIF2_TXI_VECTOR   			193

#define SCIF3_BRI_VECTOR   			194
#define SCIF3_ERI_VECTOR   			195
#define SCIF3_RXI_VECTOR   			196
#define SCIF3_TXI_VECTOR   			197

#define SCIF4_BRI_VECTOR   			198
#define SCIF4_ERI_VECTOR   			199
#define SCIF4_RXI_VECTOR   			200
#define SCIF4_TXI_VECTOR   			201

#define SCIF5_BRI_VECTOR   			202
#define SCIF5_ERI_VECTOR   			203
#define SCIF5_RXI_VECTOR   			204
#define SCIF5_TXI_VECTOR   			205

#define SSU0_SSERI0_VECTOR	 		206
#define SSU0_SSRXI0_VECTOR	 		207
#define SSU0_SSTXI0_VECTOR	 		208
#define SSU1_SSERI1_VECTOR	 		209
#define SSU1_SSRXI1_VECTOR	 		210
#define SSU1_SSTXI1_VECTOR	 		211

#define ADI_VECTOR	 				212

#define I2DG_BLT_VECTOR				213	/*	マクロ名の先頭は数字にできない	*/
#define I2DG_OUT_VECTOR   			214	/*	同上  */

#define ATAPII_VECTOR				215

#define FLSTEI_VECTOR				216
#define FLTENDI_VECTOR	 			217
#define FLTREQ0I_VECTOR   			218
#define FLTREQ1I_VECTOR   			219

#define RTC_ARM_VECTOR	 			220
#define RTC_PRD_VECTOR	 			221
#define RTC_CUP_VECTOR	 			222
/*	223〜225は欠番	*/
#define RCAN0_ERS0_VECTOR			226
#define RCAN0_OVR0_VECTOR			227
#define RCAN0_RM00_VECTOR			228
#define RCAN0_RM10_VECTOR			229
#define RCAN0_SLE0_VECTOR			230
#define RCAN1_ERS1_VECTOR			231
#define RCAN1_OVR1_VECTOR			232
#define RCAN1_RM01_VECTOR			233
#define RCAN1_RM11_VECTOR			234
#define RCAN1_SLE1_VECTOR			235

/*
 * レジスタ定義
 */

/*
 * マルチプロセッサ
 */
#define CPUIDR_w		UINT_C(0xfffc1404)
 #define CPUIDR_ID_BIT	UINT_C(0x40000000)

 #define SEMR_SEMF_BIT	UINT_C(0x00000001)
#define SEMR0_b			UINT_C(0xfffc1e00)
#define SEMR1_b			UINT_C(0xfffc1e04)
#define SEMR2_b			UINT_C(0xfffc1e08)
#define SEMR3_b			UINT_C(0xfffc1e0c)
#define SEMR4_b			UINT_C(0xfffc1e10)
#define SEMR5_b			UINT_C(0xfffc1e14)
#define SEMR6_b			UINT_C(0xfffc1e18)
#define SEMR7_b			UINT_C(0xfffc1e1c)
#define SEMR8_b			UINT_C(0xfffc1e20)
#define SEMR9_b			UINT_C(0xfffc1e24)
#define SEMR10_b		UINT_C(0xfffc1e28)
#define SEMR11_b		UINT_C(0xfffc1e2c)
#define SEMR12_b		UINT_C(0xfffc1e30)
#define SEMR13_b		UINT_C(0xfffc1e34)
#define SEMR14_b		UINT_C(0xfffc1e38)
#define SEMR15_b		UINT_C(0xfffc1e3c)
#define SEMR16_b		UINT_C(0xfffc1e40)
#define SEMR17_b		UINT_C(0xfffc1e44)
#define SEMR18_b		UINT_C(0xfffc1e48)
#define SEMR19_b		UINT_C(0xfffc1e4c)
#define SEMR20_b		UINT_C(0xfffc1e50)
#define SEMR21_b		UINT_C(0xfffc1e54)
#define SEMR22_b		UINT_C(0xfffc1e58)
#define SEMR23_b		UINT_C(0xfffc1e5c)
#define SEMR24_b		UINT_C(0xfffc1e60)
#define SEMR25_b		UINT_C(0xfffc1e64)
#define SEMR26_b		UINT_C(0xfffc1e68)
#define SEMR27_b		UINT_C(0xfffc1e6c)
#define SEMR28_b		UINT_C(0xfffc1e70)
#define SEMR29_b		UINT_C(0xfffc1e74)
#define SEMR30_b		UINT_C(0xfffc1e78)
#define SEMR31_b		UINT_C(0xfffc1e7c)


/*
 * 割込みコントローラレジスタ（INTC）
 */

/*
 * CPU0対象レジスタ
 */
#define C0ICR0_h		UINT_C(0xfffd9400)
#define C0ICR1_h		UINT_C(0xfffd9402)
#define C0ICR2_h		UINT_C(0xfffd9404)
#define C0IRQRR_h		UINT_C(0xfffd9406)
#define C0PINTER_h		UINT_C(0xfffd9408)
#define C0PIRR_h		UINT_C(0xfffd940a)
#define C0IBCR_h		UINT_C(0xfffd940a)
#define C0IBNR_h		UINT_C(0xfffd940e)
 #define IBNR_BE0	 	UINT_C(0x4000)
 #define IBNR_BOVE	 	UINT_C(0x2000)

#define C0IPR01_h		UINT_C(0xfffd9418)
#define C0IPR02_h		UINT_C(0xfffd941a)
#define C0IPR05_h		UINT_C(0xfffd9420)

#define C0INTER_h		UINT_C(0xfffd9428)
#define C0IRQER_h		UINT_C(0xfffd942a)

#define C0IPCR15_h		UINT_C(0xfffc1c00)
#define C0IPCR14_h		UINT_C(0xfffc1c02)
#define C0IPCR13_h		UINT_C(0xfffc1c04)
#define C0IPCR12_h		UINT_C(0xfffc1c06)
#define C0IPCR11_h		UINT_C(0xfffc1c08)
#define C0IPCR10_h		UINT_C(0xfffc1c0a)
#define C0IPCR09_h		UINT_C(0xfffc1c0c)
#define C0IPCR08_h		UINT_C(0xfffc1c0e)
 #define IPCR_CI		UINT_C(0x1)

#define C0IPER_h		UINT_C(0xfffc1c10)

#define C0IPR06_h		UINT_C(0xfffd9800)
#define C0IPR07_h		UINT_C(0xfffd9802)
#define C0IPR08_h		UINT_C(0xfffd9804)
#define C0IPR09_h		UINT_C(0xfffd9806)
#define C0IPR10_h		UINT_C(0xfffd9808)
#define C0IPR11_h		UINT_C(0xfffd980a)
#define C0IPR12_h		UINT_C(0xfffd980c)
#define C0IPR13_h		UINT_C(0xfffd980e)
#define C0IPR14_h		UINT_C(0xfffd9810)
#define C0IPR15_h		UINT_C(0xfffd9812)
#define C0IPR16_h		UINT_C(0xfffd9814)
#define C0IPR17_h		UINT_C(0xfffd9816)
#define C0IPR18_h		UINT_C(0xfffd9818)
#define C0IPR19_h		UINT_C(0xfffd981a)
#define C0IPR20_h		UINT_C(0xfffd981c)
#define C0IPR21_h		UINT_C(0xfffd981e)

/*
 * CPU1対象レジスタ
 */
#define C1ICR0_h		UINT_C(0xfffd9500)
#define C1ICR1_h		UINT_C(0xfffd9502)
#define C1ICR2_h		UINT_C(0xfffd9504)
#define C1IRQRR_h		UINT_C(0xfffd9506)
#define C1PINTER_h		UINT_C(0xfffd9508)
#define C1PIRR_h		UINT_C(0xfffd950a)
#define C1IBCR_h		UINT_C(0xfffd950a)
#define C1IBNR_h		UINT_C(0xfffd950e)

#define C1IPR01_h		UINT_C(0xfffd9518)
#define C1IPR02_h		UINT_C(0xfffd951a)
#define C1IPR05_h		UINT_C(0xfffd9520)

#define C1INTER_h		UINT_C(0xfffd9528)
#define C1IRQER_h		UINT_C(0xfffd952a)

#define C1IPCR15_h		UINT_C(0xfffc1c20)
#define C1IPCR14_h		UINT_C(0xfffc1c22)
#define C1IPCR13_h		UINT_C(0xfffc1c24)
#define C1IPCR12_h		UINT_C(0xfffc1c26)
#define C1IPCR11_h		UINT_C(0xfffc1c28)
#define C1IPCR10_h		UINT_C(0xfffc1c2a)
#define C1IPCR09_h		UINT_C(0xfffc1c2c)
#define C1IPCR08_h		UINT_C(0xfffc1c2e)

#define C1IPER_h		UINT_C(0xfffc1c30)

#define C1IPR06_h		UINT_C(0xfffd9900)
#define C1IPR07_h		UINT_C(0xfffd9902)
#define C1IPR08_h		UINT_C(0xfffd9904)
#define C1IPR09_h		UINT_C(0xfffd9906)
#define C1IPR10_h		UINT_C(0xfffd9908)
#define C1IPR11_h		UINT_C(0xfffd990a)
#define C1IPR12_h		UINT_C(0xfffd990c)
#define C1IPR13_h		UINT_C(0xfffd990e)
#define C1IPR14_h		UINT_C(0xfffd9910)
#define C1IPR15_h		UINT_C(0xfffd9912)
#define C1IPR16_h		UINT_C(0xfffd9914)
#define C1IPR17_h		UINT_C(0xfffd9916)
#define C1IPR18_h		UINT_C(0xfffd9918)
#define C1IPR19_h		UINT_C(0xfffd991a)
#define C1IPR20_h		UINT_C(0xfffd991c)
#define C1IPR21_h		UINT_C(0xfffd991e)

/*
 * CPU0,CPU1共通レジスタ
 */
#define IDCNT6_h		UINT_C(0xfffd9c0c)
#define IDCNT7_h		UINT_C(0xfffd9c0e)
#define IDCNT8_h		UINT_C(0xfffd9c10)
#define IDCNT9_h		UINT_C(0xfffd9c12)
#define IDCNT10_h		UINT_C(0xfffd9c14)
#define IDCNT11_h		UINT_C(0xfffd9c16)
#define IDCNT12_h		UINT_C(0xfffd9c18)
#define IDCNT13_h		UINT_C(0xfffd9c1a)
#define IDCNT14_h		UINT_C(0xfffd9c1c)
#define IDCNT15_h		UINT_C(0xfffd9c1e)
#define IDCNT16_h		UINT_C(0xfffd9c20)
#define IDCNT17_h		UINT_C(0xfffd9c22)
#define IDCNT18_h		UINT_C(0xfffd9c24)
#define IDCNT19_h		UINT_C(0xfffd9c26)
#define IDCNT20_h		UINT_C(0xfffd9c28)
#define IDCNT21_h		UINT_C(0xfffd9c2a)
#define IDCNT22_h		UINT_C(0xfffd9c2c)
#define IDCNT23_h		UINT_C(0xfffd9c2e)
#define IDCNT24_h		UINT_C(0xfffd9c30)
#define IDCNT25_h		UINT_C(0xfffd9c32)
#define IDCNT26_h		UINT_C(0xfffd9c34)
#define IDCNT27_h		UINT_C(0xfffd9c36)
#define IDCNT28_h		UINT_C(0xfffd9c38)
#define IDCNT29_h		UINT_C(0xfffd9c3a)
#define IDCNT30_h		UINT_C(0xfffd9c3c)
#define IDCNT31_h		UINT_C(0xfffd9c3e)
#define IDCNT32_h		UINT_C(0xfffd9c40)
#define IDCNT33_h		UINT_C(0xfffd9c42)
#define IDCNT34_h		UINT_C(0xfffd9c44)
#define IDCNT35_h		UINT_C(0xfffd9c46)
#define IDCNT36_h		UINT_C(0xfffd9c48)
#define IDCNT37_h		UINT_C(0xfffd9c4a)
#define IDCNT38_h		UINT_C(0xfffd9c4c)
#define IDCNT39_h		UINT_C(0xfffd9c4e)
#define IDCNT40_h		UINT_C(0xfffd9c50)
#define IDCNT41_h		UINT_C(0xfffd9c52)
#define IDCNT42_h		UINT_C(0xfffd9c54)
#define IDCNT43_h		UINT_C(0xfffd9c56)
#define IDCNT44_h		UINT_C(0xfffd9c58)
#define IDCNT45_h		UINT_C(0xfffd9c5a)
#define IDCNT46_h		UINT_C(0xfffd9c5c)
#define IDCNT47_h		UINT_C(0xfffd9c5e)
#define IDCNT48_h		UINT_C(0xfffd9c60)
#define IDCNT49_h		UINT_C(0xfffd9c62)
#define IDCNT50_h		UINT_C(0xfffd9c64)
#define IDCNT51_h		UINT_C(0xfffd9c66)
#define IDCNT52_h		UINT_C(0xfffd9c68)
#define IDCNT53_h		UINT_C(0xfffd9c6a)
#define IDCNT54_h		UINT_C(0xfffd9c6c)
#define IDCNT55_h		UINT_C(0xfffd9c6e)
#define IDCNT56_h		UINT_C(0xfffd9c70)
#define IDCNT57_h		UINT_C(0xfffd9c72)
#define IDCNT58_h		UINT_C(0xfffd9c74)
#define IDCNT59_h		UINT_C(0xfffd9c76)
#define IDCNT60_h		UINT_C(0xfffd9c78)
#define IDCNT61_h		UINT_C(0xfffd9c7a)
#define IDCNT62_h		UINT_C(0xfffd9c7c)
#define IDCNT63_h		UINT_C(0xfffd9c7e)
#define IDCNT64_h		UINT_C(0xfffd9c80)
/*	65は欠番  */
#define IDCNT66_h		UINT_C(0xfffd9c84)
#define IDCNT67_h		UINT_C(0xfffd9c86)
#define IDCNT68_h		UINT_C(0xfffd9c88)
#define IDCNT69_h		UINT_C(0xfffd9c8a)
#define IDCNT70_h		UINT_C(0xfffd9c8c)
#define IDCNT71_h		UINT_C(0xfffd9c8e)
#define IDCNT72_h		UINT_C(0xfffd9c90)
#define IDCNT73_h		UINT_C(0xfffd9c92)
#define IDCNT74_h		UINT_C(0xfffd9c94)
#define IDCNT75_h		UINT_C(0xfffd9c96)
#define IDCNT76_h		UINT_C(0xfffd9c98)
#define IDCNT77_h		UINT_C(0xfffd9c9a)
#define IDCNT78_h		UINT_C(0xfffd9c9c)
#define IDCNT79_h		UINT_C(0xfffd9c9e)
#define IDCNT80_h		UINT_C(0xfffd9ca0)
#define IDCNT81_h		UINT_C(0xfffd9ca2)
#define IDCNT82_h		UINT_C(0xfffd9ca4)
#define IDCNT83_h		UINT_C(0xfffd9ca6)
#define IDCNT84_h		UINT_C(0xfffd9ca8)
#define IDCNT85_h		UINT_C(0xfffd9caa)
#define IDCNT86_h		UINT_C(0xfffd9cac)
#define IDCNT87_h		UINT_C(0xfffd9cae)
#define IDCNT88_h		UINT_C(0xfffd9cb0)
#define IDCNT89_h		UINT_C(0xfffd9cb2)
#define IDCNT90_h		UINT_C(0xfffd9cb4)
#define IDCNT91_h		UINT_C(0xfffd9cb6)
#define IDCNT92_h		UINT_C(0xfffd9cb8)
#define IDCNT93_h		UINT_C(0xfffd9cba)
#define IDCNT94_h		UINT_C(0xfffd9cbc)
#define IDCNT95_h		UINT_C(0xfffd9cbe)
#define IDCNT96_h		UINT_C(0xfffd9cc0)
#define IDCNT97_h		UINT_C(0xfffd9cc2)
#define IDCNT98_h		UINT_C(0xfffd9cc4)
#define IDCNT99_h		UINT_C(0xfffd9cc6)
#define IDCNT100_h		UINT_C(0xfffd9cc8)
#define IDCNT101_h		UINT_C(0xfffd9cca)
#define IDCNT102_h		UINT_C(0xfffd9ccc)
#define IDCNT103_h		UINT_C(0xfffd9cce)
#define IDCNT104_h		UINT_C(0xfffd9cd0)
#define IDCNT105_h		UINT_C(0xfffd9cd2)
#define IDCNT106_h		UINT_C(0xfffd9cd4)
#define IDCNT107_h		UINT_C(0xfffd9cd6)
#define IDCNT108_h		UINT_C(0xfffd9cd8)
#define IDCNT109_h		UINT_C(0xfffd9cda)
#define IDCNT110_h		UINT_C(0xfffd9cdc)
#define IDCNT111_h		UINT_C(0xfffd9cde)
#define IDCNT112_h		UINT_C(0xfffd9ce0)
#define IDCNT113_h		UINT_C(0xfffd9ce2)
#define IDCNT114_h		UINT_C(0xfffd9ce4)
#define IDCNT115_h		UINT_C(0xfffd9ce6)
#define IDCNT116_h		UINT_C(0xfffd9ce8)
#define IDCNT117_h		UINT_C(0xfffd9cea)
#define IDCNT118_h		UINT_C(0xfffd9cec)
#define IDCNT119_h		UINT_C(0xfffd9cee)
#define IDCNT120_h		UINT_C(0xfffd9cf0)
#define IDCNT121_h		UINT_C(0xfffd9cf2)
#define IDCNT122_h		UINT_C(0xfffd9cf4)
#define IDCNT123_h		UINT_C(0xfffd9cf6)
#define IDCNT124_h		UINT_C(0xfffd9cf8)
#define IDCNT125_h		UINT_C(0xfffd9cfa)
#define IDCNT126_h		UINT_C(0xfffd9cfc)
/*	127〜129は欠番	*/
#define IDCNT130_h		UINT_C(0xfffd9d04)
#define IDCNT131_h		UINT_C(0xfffd9d06)
#define IDCNT132_h		UINT_C(0xfffd9d08)
#define IDCNT133_h		UINT_C(0xfffd9d0a)
#define IDCNT134_h		UINT_C(0xfffd9d0c)
#define IDCNT135_h		UINT_C(0xfffd9d0e)
#define IDCNT136_h		UINT_C(0xfffd9d10)
#define IDCNT137_h		UINT_C(0xfffd9d12)
#define IDCNT138_h		UINT_C(0xfffd9d14)
#define IDCNT139_h		UINT_C(0xfffd9d16)
 #define IDCNT_RSV		UINT_C(0x4000)
 #define IDCNT_CPUN		UINT_C( 0x200)
 #define IDCNT_INTEN	UINT_C( 0x100)
 #define IDCNT_INTEN_BIT UINT_C( 0x8)
 #define IDCNT_MON		UINT_C(  0x10)

#define DREQER0_b		UINT_C(0xfffe0800)
#define DREQER1_b		UINT_C(0xfffe0801)
#define DREQER2_b		UINT_C(0xfffe0802)
#define DREQER3_b		UINT_C(0xfffe0803)
#define DREQER4_b		UINT_C(0xfffe0804)
#define DREQER5_b		UINT_C(0xfffe0805)
#define DREQER6_b		UINT_C(0xfffe0806)
#define DREQER7_b		UINT_C(0xfffe0807)
#define DREQER8_b		UINT_C(0xfffe0808)

#define IRQ_POSEDGE   UINT_C(0x02)
#define IRQ_NEGEDGE   UINT_C(0x01)

/*	ベースアドレス	*/ 
#define INTC_BASE0	 	C0ICR0_h
#define INTC_BASE1	 	C1ICR0_h


/*
 *	コンペアマッチ・タイマ（CMT） 
 */
/*	0/1ch共通  */
#define CMSTR_01_h   	UINT_C(0xfffe3000)

/*	0ch  */
#define CMCSR_0_h   	UINT_C(0xfffe3002)
#define CMCNT_0_h   	UINT_C(0xfffe3004)
#define CMCOR_0_h   	UINT_C(0xfffe3006)

/*	1ch  */
#define CMCSR_1_h   	UINT_C(0xfffe3008)
#define CMCNT_1_h   	UINT_C(0xfffe300a)
#define CMCOR_1_h   	UINT_C(0xfffe300c)

/*	2/3ch共通  */
#define CMSTR_23_h   	UINT_C(0xfffe3400)

/*	2ch  */
#define CMCSR_2_h   	UINT_C(0xfffe3402)
#define CMCNT_2_h   	UINT_C(0xfffe3404)
#define CMCOR_2_h   	UINT_C(0xfffe3406)

/*	3ch  */
#define CMCSR_3_h   	UINT_C(0xfffe3408)
#define CMCNT_3_h   	UINT_C(0xfffe340a)
#define CMCOR_3_h   	UINT_C(0xfffe340c)

#define CMSTR_STR0		UINT_C(0x0001)
#define CMSTR_STR1		UINT_C(0x0002)
#define CMSTR_STR2		UINT_C(0x0001)
#define CMSTR_STR3		UINT_C(0x0002)
#define CMCSR_CMF		UINT_C(0x0080)
#define CMCSR_CMIE		UINT_C(0x0040)

#define CMT_BASE	 CMSTR_01_h	/*	ベースアドレス	*/ 

/*
 *	FIFO付きシリアルコミュニケーションインターフェース(SCIF)レジスタ
 */
#define SH_SCIF0_BASE	UINT_C(0xFFFE8000)	 /*  ベースアドレス  */
#define SH_SCIF1_BASE	UINT_C(0xFFFE8800)
#define SH_SCIF2_BASE	UINT_C(0xFFFE9000)
#define SH_SCIF3_BASE	UINT_C(0xFFFE9800)
#define SH_SCIF4_BASE	UINT_C(0xFFFEa000)
#define SH_SCIF5_BASE	UINT_C(0xFFFEa800)

/*
 *	ピンファンクションコントローラ（PFC）
 */
#define PAIORL_h	 UINT_C(0xfffe3802)
#define PACRL4_h	 UINT_C(0xfffe380c)
#define PACRL3_h	 UINT_C(0xfffe380e)
#define PACRL2_h	 UINT_C(0xfffe3810)
#define PACRL1_h	 UINT_C(0xfffe3812)

#define PBIORH_h	 UINT_C(0xfffe3820)
#define PBIORL_h	 UINT_C(0xfffe3822)
#define PBCRH2_h	 UINT_C(0xfffe3828)
#define PBCRH1_h	 UINT_C(0xfffe382a)
#define PBCRL4_h	 UINT_C(0xfffe382c)
#define PBCRL3_h	 UINT_C(0xfffe382e)
#define PBCRL2_h	 UINT_C(0xfffe3830)
#define PBCRL1_h	 UINT_C(0xfffe3832)

#define PCIORL_h	 UINT_C(0xfffe3842)
#define PCCRL3_h	 UINT_C(0xfffe384e)
#define PCCRL2_h	 UINT_C(0xfffe3850)
#define PCCRL1_h	 UINT_C(0xfffe3852)

#define PDIORL_h	 UINT_C(0xfffe3862)
#define PDCRL1_h	 UINT_C(0xfffe3872)

#define PEIORL_h	 UINT_C(0xfffe3882)
#define PECRL4_h	 UINT_C(0xfffe388c)
#define PECRL3_h	 UINT_C(0xfffe388e)
#define PECRL2_h	 UINT_C(0xfffe3890)
#define PECRL1_h	 UINT_C(0xfffe3892)

#define PFIORL_h	 UINT_C(0xfffe38a2)
#define PFCRL2_h	 UINT_C(0xfffe38b0)
#define PFCRL1_h	 UINT_C(0xfffe38b2)

#define PGCRL2_h	 UINT_C(0xfffe38d0)
#define PGCRL1_h	 UINT_C(0xfffe38d2)

#define PHIORL_h	 UINT_C(0xfffe38e2)
#define PHCRL4_h	 UINT_C(0xfffe38ec)
#define PHCRL3_h	 UINT_C(0xfffe38ee)
#define PHCRL2_h	 UINT_C(0xfffe38f0)
#define PHCRL1_h	 UINT_C(0xfffe38f2)

#define PJIORL_h	 UINT_C(0xfffe3902)
#define PJCRL4_h	 UINT_C(0xfffe390c)
#define PJCRL3_h	 UINT_C(0xfffe390e)
#define PJCRL2_h	 UINT_C(0xfffe3910)
#define PJCRL1_h	 UINT_C(0xfffe3912)

#define PKIORL_h	 UINT_C(0xfffe3922)
#define PKCRL1_h	 UINT_C(0xfffe3932)

#define PFC_BASE 	 PAIORL_h				/*	ベースアドレス	*/ 

/*
 *	クロックパルス発振器（CPG）
 */
#define FRQCR0_h	 UINT_C(0xfffe0010)
#define FRQCR1_h	 UINT_C(0xfffe0012)


/*
 *	バスステートコントローラ（BSC）
 */
#define CS0CNT_w	 UINT_C(0xff420000)
#define CS0REC_w	 UINT_C(0xff420008)
#define CS1CNT_w	 UINT_C(0xff420010)
#define CS1REC_w	 UINT_C(0xff420018)
#define CS2CNT_w	 UINT_C(0xff420020)
#define CS2REC_w	 UINT_C(0xff420028)
#define CS3CNT_w	 UINT_C(0xff420030)
#define CS3REC_w	 UINT_C(0xff420038)
#define CS4CNT_w	 UINT_C(0xff420040)
#define CS4REC_w	 UINT_C(0xff420048)
#define CS5CNT_w	 UINT_C(0xff420050)
#define CS5REC_w	 UINT_C(0xff420058)

#define SDC0CNT_w 	 UINT_C(0xff420100)
#define SDC1CNT_w 	 UINT_C(0xff420110)

#define CSMOD0_w	 UINT_C(0xff421000)
#define CS1WCNT0_w	 UINT_C(0xff421004)
#define CS2WCNT0_w	 UINT_C(0xff421008)
#define CSMOD1_w	 UINT_C(0xff421010)
#define CS1WCNT1_w	 UINT_C(0xff421014)
#define CS2WCNT1_w	 UINT_C(0xff421018)
#define CSMOD2_w	 UINT_C(0xff421020)
#define CS1WCNT2_w	 UINT_C(0xff421024)
#define CS2WCNT2_w	 UINT_C(0xff421028)
#define CSMOD3_w	 UINT_C(0xff421030)
#define CS1WCNT3_w	 UINT_C(0xff421034)
#define CS2WCNT3_w	 UINT_C(0xff421038)
#define CSMOD4_w	 UINT_C(0xff421040)
#define CS1WCNT4_w	 UINT_C(0xff421044)
#define CS2WCNT4_w	 UINT_C(0xff421048)
#define CSMOD5_w	 UINT_C(0xff421050)
#define CS1WCNT5_w	 UINT_C(0xff421054)
#define CS2WCNT5_w	 UINT_C(0xff421058)

#define SDRFCNT0_w	 UINT_C(0xff422000)
#define SDRFCNT1_w	 UINT_C(0xff422004)
#define SDIR0_w		 UINT_C(0xff422008)
#define SDIR1_w		 UINT_C(0xff42200c)
#define SDPWDCNT_w	 UINT_C(0xff422010)
#define SDPWDDCNT_w	 UINT_C(0xff422014)
#define SD0ADR_w	 UINT_C(0xff422020)
#define SD0TR_w		 UINT_C(0xff422024)
#define SD0MOD_w	 UINT_C(0xff422028)
#define SD1ADR_w	 UINT_C(0xff422040)
#define SD1TR_w		 UINT_C(0xff422044)
#define SD1MOD_w	 UINT_C(0xff422048)
#define SDSTR_w		 UINT_C(0xff4220e4)
#define SDCKSCNT_w	 UINT_C(0xff4220e8)
#define ACSWR_w		 UINT_C(0xfffe1404)

#define BSC_BASE 	 CS0CNT_w				/*	ベースアドレス	*/ 


/*
 *	キャッシュ
 */
#define CCR1_w	 UINT_C(0xfffc1000)
 #define CCR1_ICF	UINT_C(0x0800)
 #define CCR1_ICE	UINT_C(0x0100)
 #define CCR1_OCF	UINT_C(0x0008)
 #define CCR1_WT	UINT_C(0x0002)
 #define CCR1_OCE	UINT_C(0x0001)
#define CCR2_w	 UINT_C(0xfffc1004)

/*
 *	低消費電力モード関連（PDM：Power-Down Modes）
 */
#define STBCR1_b	UINT_C(0xfffe0014)
 #define STBCR1_STBY   UINT_C(0x80)
 #define STBCR1_DEEP   UINT_C(0x40)
 #define STBCR1_SLPERE UINT_C(0x20)
 #define STBCR1_AXTALE UINT_C(0x10)
#define STBCR2_b	UINT_C(0xfffe0018)
#define STBCR3_b	UINT_C(0xfffe0400)
 #define STBCR3_ATAPI  UINT_C(0x80)
 #define STBCR3_MTU2   UINT_C(0x20)
 #define STBCR3_ADC    UINT_C(0x04)
 #define STBCR3_DAC    UINT_C(0x02)
 #define STBCR3_RTC    UINT_C(0x01)
#define STBCR4_b	UINT_C(0xfffe0402)
 #define STBCR4_SCIF0  UINT_C(0x80)
 #define STBCR4_SCIF1  UINT_C(0x40)
 #define STBCR4_SCIF2  UINT_C(0x20)
 #define STBCR4_SCIF3  UINT_C(0x10)
 #define STBCR4_SCIF4  UINT_C(0x08)
 #define STBCR4_SCIF5  UINT_C(0x04)
#define STBCR5_b	UINT_C(0xfffe0404)
#define STBCR6_b	UINT_C(0xfffe0406)
#define STBCR7_b	UINT_C(0xfffe0408)
 #define STBCR7_CMT01  UINT_C(0x80)
 #define STBCR7_CMT23  UINT_C(0x40)
 #define STBCR7_FLCTL  UINT_C(0x10)
 #define STBCR7_SSU0   UINT_C(0x08)
 #define STBCR7_SSU1   UINT_C(0x04)
 #define STBCR7_2DG    UINT_C(0x02)
 #define STBCR7_USB    UINT_C(0x01)

#define SYSCR1_b	UINT_C(0xfffe0480)
#define SYSCR2_b	UINT_C(0xfffe0482)
#define SYSCR3_b	UINT_C(0xfffe0484)
#define SYSCR4_b	UINT_C(0xfffe0486)
#define SYSCR5_b	UINT_C(0xfffe0488)
#define SYSCR6_b	UINT_C(0xfffe048a)
#define SYSCR7_b	UINT_C(0xfffe04a0)
#define SYSCR8_b	UINT_C(0xfffe04a2)
#define SYSCR9_b	UINT_C(0xfffe04a4)
#define SYSCR10_b 	UINT_C(0xfffe04a6)
#define SYSCR11_b 	UINT_C(0xfffe04a8)
#define SYSCR12_b 	UINT_C(0xfffe04aa)

#define SWRSTCR_b 	UINT_C(0xfffe0440)
#define HIZCR_b		UINT_C(0xfffe0442)

#define C0MSR_b		UINT_C(0xfffe0040)
#define C1MSR_b		UINT_C(0xfffe0042)

#define RRAMKP_b	UINT_C(0xfffe0c00)
#define DSCTR_b		UINT_C(0xfffe0c02)
#define DSSSR_h		UINT_C(0xfffe0c04)
#define DSFR_h		UINT_C(0xfffe0c08)

#define PDM_BASE 	STBCR1				/*	ベースアドレス	*/


/*
 *	高速内蔵RAM
 */
/*  アドレス空間（CPU固有領域用：CPUバスを利用）  */
#define INNER_RAM0_PAGE0_ADDRESS_START		UINT_C(0xfff80000)
#define INNER_RAM0_PAGE1_ADDRESS_START		UINT_C(0xfff84000)
#define INNER_RAM0_PAGE2_ADDRESS_START		UINT_C(0xfff88000)
#define INNER_RAM0_PAGE3_ADDRESS_START		UINT_C(0xfff8c000)
#define INNER_RAM1_PAGE0_ADDRESS_START		UINT_C(0xfffa0000)
#define INNER_RAM1_PAGE1_ADDRESS_START		UINT_C(0xfffa4000)

/*  シャドー空間（共有領域用：高速内蔵RAMアクセスバスを利用）  */
#define INNER_RAM0_PAGE0_SHADOW_START		UINT_C(0xffd80000)
#define INNER_RAM0_PAGE1_SHADOW_START		UINT_C(0xffd84000)
#define INNER_RAM0_PAGE2_SHADOW_START		UINT_C(0xffd88000)
#define INNER_RAM0_PAGE3_SHADOW_START		UINT_C(0xffd8c000)
#define INNER_RAM1_PAGE0_SHADOW_START		UINT_C(0xffda0000)
#define INNER_RAM1_PAGE1_SHADOW_START		UINT_C(0xffda4000)

#define INNER_RAM_PAGE_SIZE					UINT_C(0x00004000)


/*
 *  マルチファンクションタイマパルスユニットMTU2
 */
/*
 *  共通
 */
#define TSTR_b		0xfffe2280U
#define TSTR_CST0	0x01U
#define TSTR_CST1	0x02U
#define TSTR_CST2	0x04U
#define TSTR_CST3	0x40U
#define TSTR_CST4	0x80U


/*
 *  チャネル0
 */
#define TCR_0_b		0xfffe2300U
#define TIER_0_b	0xfffe2304U
#define TSR_0_b		0xfffe2305U
#define TCNT_0_h	0xfffe2306U

/*
 *  チャネル1
 */
#define TCR_1_b		0xfffe2380U
#define TIER_1_b	0xfffe2384U
#define TSR_1_b		0xfffe2385U
#define TCNT_1_h	0xfffe2386U

/*
 *  チャネル2
 */
#define TCR_2_b		0xfffe2000U
#define TIER_2_b	0xfffe2004U
#define TSR_2_b		0xfffe2005U
#define TCNT_2_h	0xfffe2006U

/*
 *  チャネル3
 */
#define TCR_3_b		0xfffe2200U
#define TIER_3_b	0xfffe2208U
#define TSR_3_b		0xfffe222cU
#define TCNT_3_h	0xfffe2210U

/*
 *  チャネル4
 */
#define TCR_4_b		0xfffe2201U
#define TIER_4_b	0xfffe2209U
#define TSR_4_b		0xfffe222dU
#define TCNT_4_h	0xfffe2212U

/*  タイマステータスレジスタ（TSR）  */
#define TCR_TCFV	0x10U	/*  オーバフローフラグ  */

/*  タイマインタラプトイネーブルレジスタ（TIER）  */
#define TIER_TCIEV	0x10U	/*  オーバフローインタラプトイネーブル  */



#endif /* TOPPERS_SH7205_H */
