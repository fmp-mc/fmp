/*
 *  R-Car H1用ドライバ定義
 */

#ifndef TOPPERS_R_CAR_H1_H
#define TOPPERS_R_CAR_H1_H

/*
 *  MPCore Private Memory Regin Base Address
 */
#define MPCORE_PMR_BASE  0xf0000000

/*
 * 割込み数
 */
#define DIC_TMIN_INTNO    0U
#define DIC_TMAX_INTNO  255U
#define DIC_TNUM_INT    256U

/*
 *  R-Car H1 registers
 */
/* pfc */
#define	PMMR		0xfffc0000
#define	GPSR0		0xfffc0004
#define	GPSR1		0xfffc0008
#define	GPSR2		0xfffc000c
#define	GPSR3		0xfffc0010
#define	GPSR4		0xfffc0014
#define	GPSR5		0xfffc0018
#define	GPSR6		0xfffc001c
#define	IPSR0		0xfffc0020
#define	IPSR1		0xfffc0024
#define	IPSR2		0xfffc0028
#define	IPSR3		0xfffc002c
#define	IPSR4		0xfffc0030
#define	IPSR5		0xfffc0034
#define	IPSR6		0xfffc0038
#define	IPSR7		0xfffc003c
#define	IPSR8		0xfffc0040
#define	IPSR9		0xfffc0044
#define	IPSR10		0xfffc0048
#define	IPSR11		0xfffc004c
#define	IPSR12		0xfffc0050
#define	IOCTRL0		0xfffc0060
#define	IOCTRL1		0xfffc0064
#define	IOCTRL2		0xfffc0068
#define	IOCTRL3		0xfffc006c
#define	MOD_SEL		0xfffc0090
#define	MOD_SEL2	0xfffc0094
#define	PUPR0		0xfffc0100
#define	PUPR1		0xfffc0104
#define	PUPR2		0xfffc0108
#define	PUPR3		0xfffc010c
#define	PUPR4		0xfffc0110
#define	PUPR5		0xfffc0114
#define	PUPR6		0xfffc0118
#define	ARMTREN		0xfffc0200
#define	RGWD0		0xfffc0210
#define	RGWD1		0xfffc0214
#define	RGWD2		0xfffc0218
#define	RGWD3		0xfffc021c
#define	RGWD4		0xfffc0220
#define	RGWD5		0xfffc0224
#define	RGRD0		0xfffc0230
#define	RGRD1		0xfffc0234
#define	RGRD2		0xfffc0238

/* reset/wdt */
#define	MODEMR	0xffcc0020
#define		MD1	(1 << 1)
#define		MD2	(1 << 2)

/*
 *  UARTの定義
 */
/* ベースアドレス */
#define SCIF2_BASE		0xffe42000
#define SCIF4_BASE		0xffe44000

/* 割込み番号 */
#define IRQNO_SCIF2   0x7a  
#define IRQNO_SCIF4   0x7c

/*
 *  タイマの定義
 */
/* ベースアドレス */
#define TMU012_BASE		0xffd80000
#define TMU0_BASE		0xffd80008
#define TMU1_BASE		0xffd80014
#define TMU2_BASE		0xffd80020
#define TMU345_BASE		0xffd81000
#define TMU3_BASE		0xffd81008
#define TMU4_BASE		0xffd81014
#define TMU5_BASE		0xffd81020
#define TMU678_BASE		0xffd82000
#define TMU6_BASE		0xffd82008
#define TMU7_BASE		0xffd82014
#define TMU8_BASE		0xffd82020

/* レジスタのオフセット */ 
#define TMU_TSTR 0x04
#define TMU_TCOR 0x00
#define TMU_TCNT 0x04
#define TMU_TCR  0x08


/* 割込み番号 */
#define IRQNO_TMU3  0x44
#define IRQNO_TMU4  0x45
#define IRQNO_TMU5  0x46
#define IRQNO_TMU6  0x48
#define IRQNO_TMU7  0x49
#define IRQNO_TMU8  0x4a


#ifndef TOPPERS_MACRO_ONLY

Inline void
set_guard_reg(uint32_t addr, uint32_t mask, uint32_t val) {
	uint32_t tmp;

	tmp = sil_rew_mem((void*)addr);
	tmp = (tmp & ~mask) | val;
	sil_wrw_mem((void*)PMMR, ~tmp);
	sil_wrw_mem((void*)addr, tmp);
}

#endif /* TOPPERS_MACRO_ONLY */



#endif /* TOPPERS_R_CAR_H1_H */
