/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2007-2011 by Embedded and Real-Time Systems Laboratory
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
 * ターゲット依存モジュール（CT11MPCORE用）
 */
#include "kernel_impl.h"
#include <sil.h>

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
#define SDRAM_ADDR 0x00000000
#define SRAM_ADDR  0x48000000

#define SDRAM_SIZE 0x08000000 /* 128MB */
#define SRAM_SIZE  0x00200000 /*   1MB */

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
	m_attribute.ns   = 0;		  /* Secure       */    
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
	 *  Enable caching for the SDRAM
	 */
	m_attribute.pa   = SDRAM_ADDR;
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SDRAM_SIZE;
	m_attribute.s    = 1;		  /* 共有		 */
	m_attribute.ap   = 3;		  /* フルアクセス */
	m_attribute.tex  = 1;		  /* Outer and Inner */
	m_attribute.c    = 1;		  /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);

	/*
	 *  Enable caching for the SRAM
	 */
	m_attribute.pa   = SRAM_ADDR;	 /* pa is started from 0x48000000 (SRAM) */
	m_attribute.va   = m_attribute.pa;
	m_attribute.size = SRAM_SIZE;	 /* 2MB */
	m_attribute.ap   = 3;			 /* フルアクセス */
	m_attribute.tex  = 1;			 /* Outer and Inner */
	m_attribute.c    = 1;			 /* Inner Write-Back, Write Allocate */ 
	m_attribute.b    = 1;

	mmu_map_memory(&m_attribute);
}

/*
 *  ターゲット依存の初期化
 */
void
target_initialize(void)
{
	/*
	 * EBとの接続を初期化
	 */
	if (x_sense_mprc()) {
		eb_init_int_mode();
	}

	/*
	 * チップ依存の初期化
	 */
	chip_initialize();
        
	/*
	 *  UARTを初期化
	 */
	ct11mpcore_uart_init();
}

/*
 *  ターゲット依存の終了処理
 */
void
target_exit(void)
{
#ifndef TOPPERS_ENABLE_SEMIHOSTING
	/*
	 *  チップ依存の終了処理
	 */
	chip_exit();

	/*
	 *  開発環境依存の終了処理
	 */
	ct11mpcore_exit();

	while(1);

#else /* TOPPERS_ENABLE_SEMIHOSTING */
	extern void exit(int);
	if (x_sense_mprc()) {
		exit(0);
	}
	else {
		while(1);
	}
#endif /* TOPPERS_ENABLE_SEMIHOSTING */
}

/*
 *  システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char_t c)
{
	if (c == '\n') {
		ct11mpcore_putc('\r');
	}
	ct11mpcore_putc(c);
}

/*
 *  実行時間分布集計モジュールで用いる測定用タイマの初期化関数
 */
void
perf_timer_initialize(intptr_t exinf)
{
	scu_counter_init();
}

/*
 *  実行時間分布集計モジュール用のカウンタによる計測
 */
void
perf_timer_get(uint32_t *p_time)
{
	*p_time = scu_counter_get_current();
}

/*
 *  実行時間分布集計モジュール用のカウンタによる測定結果の単位変換
 *  nsecに変換 
 */
uint32_t
perf_timer_conv_tim(uint32_t time)
{
	return (time * 1000) / CT11MPCORE_CORE_CLK;
}

#ifdef TOPPERS_ENABLE_SEMIHOSTING
extern void start_master(void);

/*
 *  コンパイラのスタートアップルーチンから呼び出される．
 *  sta_ker()を呼び出してカーネルをスタートさせる． 
 */
int
main(void)
{
	start_master();
	return 1;
}
#endif /* TOPPERS_ENABLE_SEMIHOSTING */
