/*
 *	TOPPERS Software
 *		Toyohashi Open Platform for Embedded Real-Time Systems
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
 *  $Id: prc_sil.h 873 2011-08-18 06:50:17Z mit-kimai $
 */

/*
 *	sil.hのプロセッサ依存部（SH2A-DUAL用）
 */

#ifndef TOPPERS_PRC_SIL_H
#define TOPPERS_PRC_SIL_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  エンディアンの反転
 */
Inline uint16_t
toppers_sil_rev_endian_uint16(uint16_t src)
{
	uint16_t dst;
	Asm("swap.b %1, %0" : "=r"(dst) : "r"(src) );
	return dst;
}

#define	TOPPERS_SIL_REV_ENDIAN_UINT16(data) \
		toppers_sil_rev_endian_uint16(data)

Inline uint32_t
toppers_sil_rev_endian_uint32(uint32_t src)
{
	uint32_t dst;
	Asm("swap.b %1, %0 \n"		/*  0x1234→0x1243  */
		"swap.w %0, %0 \n" 		/*  0x1243→0x4312  */
		"swap.b %0, %0"			/*  0x4312→0x4321  */
		: "=r"(dst) : "r"(src) );
	return dst;
}

#define	TOPPERS_SIL_REV_ENDIAN_UINT32(data) \
		toppers_sil_rev_endian_uint32(data)


/*
 *	レジスタ・アクセス関数
 *	　sil_re?_mem,sil_wr?_memをこのファイル内で使用したいが、
 *	　この時点で定義されていないため、同等の関数を用意する。
 */

/*
 *	8ビット・レジスタの読出し／書込み
 */
Inline uint8_t
sil_reb_reg(uint8_t *p_reg)
{
	uint8_t	data;

	data = *((volatile uint8_t *)p_reg);
	return(data);
}

Inline void
sil_wrb_reg(uint8_t *p_reg, uint8_t data)
{
	*((volatile uint8_t *)p_reg) = data;
}

/*
 *	16ビット・レジスタの読出し／書込み
 */
Inline uint16_t
sil_reh_reg(uint16_t *p_reg)
{
	uint16_t	data;

	data = *((volatile uint16_t *)p_reg);
	return(data);
}

Inline void
sil_wrh_reg(uint16_t *p_reg, uint16_t data)
{
	*((volatile uint16_t *)p_reg) = data;
}

/*
 *	32ビット・レジスタの読出し／書込み
 */
Inline uint32_t
sil_rew_reg(uint32_t *p_reg)
{
	uint32_t	data;

	data = *((volatile uint32_t *)p_reg);
	return(data);
}

Inline void
sil_wrw_reg(uint32_t *p_reg, uint32_t data)
{
	*((volatile uint32_t *)p_reg) = data;
}

/*
 *	レジスタに対する論理演算
 */

/*
 *	8ビット・レジスタのOR演算
 */
Inline void
sil_orb_reg(uint8_t *p_reg, uint_t bitptn)
{
	uint8_t reg_val = sil_reb_reg(p_reg);

	reg_val |= (uint8_t)bitptn;
	sil_wrb_reg(p_reg, reg_val);
}

/*
 *	8ビット・レジスタのAND演算
 */
Inline void
sil_anb_reg(uint8_t *p_reg, uint_t bitptn)
{
	uint8_t reg_val = sil_reb_reg(p_reg);

	reg_val &= (uint8_t)bitptn;
	sil_wrb_reg(p_reg, reg_val);
}

/*
 *	16ビット・レジスタのOR演算
 */
Inline void
sil_orh_reg(uint16_t *p_reg, uint_t bitptn)
{
	uint16_t reg_val = sil_reh_reg(p_reg);

	reg_val |= (uint16_t)bitptn;
	sil_wrh_reg(p_reg, reg_val);
}


/*
 *	16ビット・レジスタのAND演算
 */
Inline void
sil_anh_reg(uint16_t *p_reg, uint_t bitptn)
{
	uint16_t reg_val = sil_reh_reg(p_reg);

	reg_val &= (uint16_t)bitptn;
	sil_wrh_reg(p_reg, reg_val);
}


/*
 *	16ビット・レジスタのビット・セット／クリア
 */
Inline void
sil_seth_bit(uint16_t *p_reg, uint_t bit)
{
	uint32_t reg_val = sil_reh_reg(p_reg);

	/*
	 *	bitが7以下の定数であれば、
	 *	bset命令に展開されることを期待
	 */
	reg_val |= (1U << bit);
	sil_wrh_reg(p_reg, reg_val);
}

Inline void
sil_clrh_bit(uint16_t *p_reg, uint_t bit)
{
	uint32_t reg_val = sil_reh_reg(p_reg);

	/*
	 *	bitが7以下の定数であれば、
	 *	bclr命令に展開されることを期待
	 */
	reg_val &= ~(1U << bit);
	sil_wrh_reg(p_reg, reg_val);
}


/*
 *	プロセッサINDEX（0オリジン）の取得
 *	　戻り値
 *	　　CPU0：0
 *	　　CPU1：1
 */
Inline uint_t
sil_get_pindex(void)
{
	uint_t index;
	uint32_t cpuidr = sil_rew_reg((uint32_t *)CPUIDR_w);
	
	if ((cpuidr & CPUIDR_ID_BIT) == 0U) {
		index = 0U;
	} else {
		index = 1U;
	}
	return index;
}

/*
 *	プロセッサIDの取得
 *	　戻り値
 *	　　CPU0：1
 *	　　CPU1：2
 */
Inline void
sil_get_pid(ID *p_id)
{
	*p_id = sil_get_pindex() + 1U;
}


/*
 *	NMIを除くすべての割込みの禁止
 */
Inline uint32_t
TOPPERS_disint(void)
{
	uint32_t  TOPPERS_sr, TOPPERS_iimp;

	Asm("stc  sr,%0" : "=r"(TOPPERS_sr));
	TOPPERS_iimp = TOPPERS_sr & 0x000000f0U;
	Asm("ldc %0, sr" : : "r"(TOPPERS_sr | 0x000000f0U) : "memory", "t");
	return(TOPPERS_iimp);
}

/*
 *	割込み優先度マスク（内部表現）の現在値の設定
 */
Inline void
TOPPERS_set_iipm(uint32_t TOPPERS_iipm)
{
	uint32_t  TOPPERS_sr;

	Asm("stc  sr,%0" : "=r"(TOPPERS_sr));
	TOPPERS_sr = (TOPPERS_sr & ~0x000000f0U) | TOPPERS_iipm;
	Asm("ldc %0, sr" : : "r"(TOPPERS_sr) : "memory", "t");
}

#ifdef ENABLE_CACHE
Inline void
TOPPERS_set_iipm_with_nop(uint32_t TOPPERS_iipm)
{
	uint32_t  TOPPERS_sr;

	Asm("stc  sr,%0" : "=r"(TOPPERS_sr));
	TOPPERS_sr = (TOPPERS_sr & ~0x000000f0U) | TOPPERS_iipm;
	Asm("ldc %0, sr;"
		"nop; nop"		/*  CPUからINTCに伝達されるまでの遅延  */
	 	: : "r"(TOPPERS_sr) : "memory", "t");
}
#else	/*  ENABLE_CACHE  */
#define TOPPERS_set_iipm_with_nop(TOPPERS_iipm)	TOPPERS_set_iipm(TOPPERS_iipm)
#endif	/*  ENABLE_CACHE  */

/*
 *	全割込みロック状態の制御
 *	
 *	途中でマイグレーションし、元のプロセッサと異なるプロセッサの
 *	SRレジスタへの書き込みが起こる場合の考察
 *	
 *	マイグレーションが発生するのは、マイグレーション元プロセッサ／
 *	先プロセッサ共に
 *	　　・全割込みロック解除状態　かつ
 *	　　・割込み優先度マスク全解除状態
 *	の場合に限られるので、マイグレーション先で実行再開される際には、
 *	上記の状態になっており、SRレジスタを上書きしても問題ない。
 */
#define SIL_PRE_LOC 	 uint32_t TOPPERS_saved_iipm
#define SIL_LOC_INT()	 ((void)(TOPPERS_saved_iipm = TOPPERS_disint()))
#define SIL_UNL_INT()	 (TOPPERS_set_iipm_with_nop(TOPPERS_saved_iipm))

/*
 *  SILスピンロック管理ブロックの定義
 */
typedef struct toppers_sil_spn_cb {
	/*
	 *  SILスピンロックを取得しているプロセッサID
	 *  　SILスピンロックを解放する際には0に戻すこと
 	*/
	ID spn_prcid;

	/*
	 *  SILスピンロックのネスト回数
	 *  　SILスピンロックを解放する際には0に戻すこと
	 */
	uint_t spn_nest;
} TOPPERS_SIL_SPN_CB;;


/*
 *  SILスピンロック管理ブロック（prc_config.c）
 */
extern TOPPERS_SIL_SPN_CB TOPPERS_sil_spn_cb;

/*
 *	スピンロックの取得
 */
Inline uint32_t
TOPPERS_sil_loc_spn(void)
{
	uint32_t saved_iipm;
	ID prcid;
	uint8_t semr0;
	uint8_t *p_semr0_b = (uint8_t *)SEMR0_b;

  retry:
	/* 全割込みロック状態へ*/
	saved_iipm = TOPPERS_disint();

	sil_get_pid(&prcid);
	if(TOPPERS_sil_spn_cb.spn_prcid == prcid) {
		/*  スピンロックへの操作はしない（取得済み）  */
		++TOPPERS_sil_spn_cb.spn_nest;
	} else {
		semr0 = sil_reb_reg(p_semr0_b);
			/*
			 *	SEMR0 == 0 ：使用中
			 *	SEMR0 == 1 ：空き
			 */
		if (semr0 == 0) {
			/* スピンロックが取得できなかった場合 */
			/* 全割込みロック状態を前の状態へ */
			TOPPERS_set_iipm_with_nop(saved_iipm);
			goto retry;
		} else {
			/* スピンロックが取得できた場合 */
			TOPPERS_sil_spn_cb.spn_prcid = prcid;
			TOPPERS_sil_spn_cb.spn_nest = 1;
		}
	}
	/* メモリの内容が書き換わる可能性がある */
	Asm("":::"memory");
	return saved_iipm;
}

/*
 *	スピンロックの解放
 */
Inline void
TOPPERS_sil_unl_spn(uint32_t saved_iipm)
{
	/* メモリの内容が書き換わる可能性がある */
	Asm("":::"memory");
	--TOPPERS_sil_spn_cb.spn_nest;
	if(TOPPERS_sil_spn_cb.spn_nest != 0) {
		/*
		 *  ネストしている場合
		 *  　スピンロックへの操作はしない
		 */
	} else {
		/*
		 *  ネストしていない場合
		 *  　実際にスピンロックの解放操作を行う
		 */
		TOPPERS_sil_spn_cb.spn_prcid = 0U;
		Asm("":::"memory");
		sil_wrb_reg((uint8_t *)SEMR0_b, SEMR_SEMF_BIT);

		/* 全割込みロック状態を前の状態へ */
		TOPPERS_set_iipm_with_nop(saved_iipm);
	}
}

/*
 *  スピンロックの強制解放
 *  自プロセッサがスピンロックを取得している場合に解放する． 
 */
Inline void
TOPPERS_sil_force_unl_spn(void)
{
	ID prcid;

	sil_get_pid(&prcid);

	if (TOPPERS_sil_spn_cb.spn_prcid == prcid) {
		TOPPERS_sil_spn_cb.spn_prcid = 0U;
		TOPPERS_sil_spn_cb.spn_nest = 0;
		Asm("":::"memory");
		sil_wrb_reg((uint8_t *)SEMR0_b, SEMR_SEMF_BIT);
	}
}

/*
 *	スピンロック
 */
#define SIL_LOC_SPN() ((void)(TOPPERS_saved_iipm = TOPPERS_sil_loc_spn()))
#define SIL_UNL_SPN() (TOPPERS_sil_unl_spn(TOPPERS_saved_iipm))

/*
 *	SILスピンロックをネストして取得可能であることを示すマクロ
 */
#define TOPPERS_TARGET_SUPPORT_NESTED_SIL_SPINLOC


#endif /* TOPPERS_MACRO_ONLY */

#endif /* TOPPERS_PRC_SIL_H */
