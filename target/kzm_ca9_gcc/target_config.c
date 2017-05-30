/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007-2012 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
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
 *  @(#) $Id: target_config.c 942 2012-10-19 07:49:03Z ertl-honda $
 */

/*
 * ターゲット依存モジュール（KZM_CA9用）
 */
#include "kernel_impl.h"
#include <sil.h>

extern void *vector_table;

#define CP15_SET_VBAR(x)    Asm("mcr p15, 0, %0, c12, c0, 0"::"r"(x))

/*
 *  str_ker() の前でマスタプロセッサで行う初期化
 */
void
target_mprc_initialize(void)
{
	/* MPCore依存部での初期化 */
	chip_mprc_initialize();
}

/*
 * メモリのベースアドレスとサイズ
 */
#define DDR_ADDR 0x00000000
#define DDR_SIZE 0x10000000 /* 256MB */


/*
 * メモリマップの初期化（chip依存部から呼び出される）
 * 同時にキャッシュも有効にする
 */
void
target_mmu_init(void)
{
	MEMORY_ATTRIBUTE m_attribute;

	/*
	 * 全セクションを物理アドレス = 仮想アドレス
	 * ノンキャッシャブル，ノンバッファブルとする 
	 */
	m_attribute.pa   = 0x00000000;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = 0x80000000;
	m_attribute.s    = 1;          /* 共有         */
	m_attribute.ap   = 3;          /* フルアクセス */
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
	m_attribute.s    = 1;		  /* 共有		 */
	m_attribute.ap   = 3;		  /* フルアクセス */
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
    //     ^ ToDo: これによりSMCバスに接続されるすべてのデバイスがアクセス禁止になる。
    //             現状は、トラスト側のシリアルポートをセキュアにするために
    //             行っているが、将来的にはトラスト側の使用するポートをUART0に変更するべき。
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

	/* 割込みを全て禁止 */
	for(i = 0; i < 32/32; i++){
		sil_wrw_mem((void *)(DIC_CE + (4 * i)), 0xffffffff);
	}

	/* ペンディングをクリア */
	for(i = 0; i < 32/32; i++){
		sil_wrw_mem((void *)(DIC_CP + (4 * i)), 0xffffffff);
	}

	/* 優先度最低に設定  */
    /* Linuxが初期化しないため代わりに初期化 */
	for(i = 0; i < 32/4; i++){
        /*
         * 本来は0xffffffffでよいが，Linuxがセカンダリコア以降の
         * コアの割込み優先度を設定しないため，ここで設定する．
         * (Linuxでは，0xa0a0a0a0ですべての割込みを初期化しているが
         *  ノンセキュア側からの優先度割込みはセキュア側から見ると
         *  1ビットシフトし，上位ビットが1となったものに見えるため
         *  0xd0d0d0d0の値になる)
         */
		sil_wrw_mem((void *)(DIC_IPR + (4 * i)), 0xd0d0d0d0);
	}
}
#endif /* TOPPERS_SAFEG_SECURE */

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	/*
	 * チップ依存の初期化
	 */
	chip_initialize();

#ifdef TOPPERS_SAFEG_SECURE
    /*
     * デバイスへのアクセス権限の設定(TrustZone)
     */
    target_tzpc_initialize();
    target_tzasc_initialize();

    /*
     * 割込みセキュリティの設定
     * (ノンセキュア側の割込み優先度に合わせて，SGI・PPIを設定)
     */
    target_gic_initialize();
#endif /* TOPPERS_SAFEG_SECURE */
        
	/*
	 *  UARTを初期化
	 */
#ifdef G_SYSLOG
	if (x_sense_mprc()) {
		kzm_ca9_uart_init();
	}
#else
	kzm_ca9_uart_init();
#endif /* G_SYSLOG */

    /*
     * 割込みベクタテーブルを VECTOR_TABLE_BASE レジスタに設定する
     */
	CP15_SET_VBAR((uint32_t) &vector_table);
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *  チップ依存の終了処理
	 */
	chip_exit();

	/*
	 *  開発環境依存の終了処理
	 */
	kzm_ca9_exit();

	while(1);
}

/*
 *  システムログの低レベル出力のための文字出力
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
 *  実行時間分布集計モジュールで用いる測定用タイマの初期化関数
 */
void
perf_timer_initialize(intptr_t exinf)
{
	timer_sp804_init();
}

/*
 *  実行時間分布集計モジュール用のカウンタによる計測
 */
void
perf_timer_get(uint32_t *p_time)
{
	*p_time = timer_sp804_get_current();
}

/*
 *  実行時間分布集計モジュール用のカウンタによる測定結果の単位変換
 *  nsecに変換 
 */
uint32_t
perf_timer_conv_tim(uint32_t time)
{
	/* 100Mhzでカウント */
	return (time * 10);
}
