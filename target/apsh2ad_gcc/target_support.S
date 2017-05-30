/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *								Toyohashi Univ. of Technology, JAPAN
 *	Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2007-2010 by Industrial Technology Institute,
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
 *  $Id: target_support.S 765 2011-01-13 07:18:55Z mit-kimai $
 */

/*
 *	ターゲット依存モジュール アセンブリ言語部（APSH2AD）
 */

#define  TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#include "kernel_impl.h"

/*
 *	ROM化時に，DATAセクションのサイズが0だと，BSSがTXTの直下に配置され
 *	るため，DATAセクションのサイズを0にしないためのダミー変数を定義．
 *	コンパイラの最適化により削除されるのを防ぐため、アセンブラで記述し
 *	ている。
 */
	.data
_dummy:
	.long 0x00000000

/*
 *	低レベルのターゲット依存の初期化
 *
 *	スタートアップモジュールの中で，メモリの初期化の前に呼び出される．
 *	以下の状態でここに分岐する。
 *	　r4:プロセッサINDEX
 *	　r5:テーブルのインデックス=プロセッサINDEX*4
 */

/*
 *	初期化時のシーケンス
 *	
 *	以下のシーケンスでプロセッサ間の同期を取る。
 *	
 *	　　　　　　　　　CPU0　　　　　　　　CPU1
 *	ターゲット依存（target_support.S）
 *	　　　　　　　　セマフォ制御レジスタSEM0をロック
 *	
 *	　　　　　　　　クロック設定		クロック設定
 *	　　　　　　　　FRQCR1以外　　　　　FRQCR1のみ
 *	
 *	　　　　　　　　高速内蔵RAM0へのアクセス設定（SYSCRn）
 *	
 *	　　　　　　　　　　　　　　　　　　高速内蔵RAM1へのアクセス設定（SYSCRn）
 *	　　　　　　　　　　　　　　　　　　高速内蔵RAM1上の変数cpu1_flag←0
 *	　　　　　　　　　　　　　　　　　　高速内蔵RAM1上に命令コードをコピー
 *	　　　　　　　　　　　　　　　　　　コピーした命令コードに分岐
 *	　　　　　　　　SEM0を待つ		←	SEM0をリリース...(1)
 *	
 *	　　　　　　　　外部メモリへのアクセス設定
 *	　　　　　　　　（バスステートコンローラの初期化）
 *										　
 *	アーキテクチャ依存（start.S）
 *	　　　　　　　　bss/dataセクションの初期化
 *	　　　　　　　　software_init_hook()の呼び出し
 *	　　　　　　　　target_mprc_initialize()の呼び出し
 *	
 *	　　　　　　　　cpu1_flag←1	→	cpu1_flag=1となるまで待つ...(2)
 *	
 *	　　　　　　　　　　　（CPU0とCPU1はここで合流する。）
 *	　　　　　　　　　　　キャッシュの初期化（各CPU）
 *	　　　　　　　　　　　カーネル起動
 *	　　　　　　　　　　　（sta_ker()の呼び出し）
 *	
 *	
 *  　他プロセッサと同期を取るには、
 *  　　・sleep命令＋プロセッサ間割込み
 *  　　・セマフォレジスタを使った排他制御
 *  　　・内部RAMへのtest & set命令
 *  　の３つが考えられる。
 *  　
 *  　処理内容や使用状況により、以下の制限事項がある。
 *  　
 *  　・全割込みロック状態
 *  　　　プロセッサ間割込みは使用できない。
 *  　
 *  　・クロック周波数の設定
 *  　　　FRQCR1レジスタはCPU1からのみ設定可能
 *  　
 *  　・高速内蔵RAMへのアクセス設定（SYSCRnの初期化）
 *  　　　他プロセッサは高速内蔵メモリへのアクセス不可
 *  　　　（高速内蔵メモリに配置された命令への命令フェッチも不可）
 *  　
 *  　・外部メモリへのアクセス設定
 *  　　（バスステートコントローラの初期化）
 *  　　　他プロセッサは外部メモリへのアクセス不可
 *  　　　（外部メモリに配置された命令への命令フェッチも不可）
 *  　
 *  　ここでは、
 *	　　・CPU0が待つ場合：セマフォ制御レジスタ
 *	　　・CPU1が待つ場合：高速内蔵RAM1上のフラグ変数
 *  　を用いている。
 *	　フラグを用いるのは、
 *	　　・CPU1をCPUバスだけで動作させるため
 *	　　・target_mprc_initialize()と干渉しないため
 *	　　　　（内部でセマフォ制御レジスタを初期化している。）
 */
	.text
	.align 4
	.globl _hardware_init_hook
_hardware_init_hook:
	tst    r4, r4
	bt     _cpu0
	bra    _cpu1
	nop

    /*******************************
     *  マスタプロセッサの場合の処理
     ********************************/
_cpu0:
    /*
     *  セマフォレジスタSEMR0の初期化（ロック相当）
     *  　SEMR0を読み出すことにより、ビット0が0（資源使用中）に
     *  　初期化される。
     */
	mov.l  _semr0_addr_b, r1
	mov.b  @r1, r2

	/* クロック発信器(CPG)設定 */
	/* I0Φ=200MHz,BΦ=66.666MHz,PΦ=33.333MHz */
	/*	　備考：CPU1の内部クロックI1ΦはFRQCR1で設定	*/
	mov.l _frqcr0_addr_h, r1
	movi20 #0x0104, r2
	mov.w r2, @r1

	/*
	 *	内部RAM0を有効にする
	 *
	 *	システムコントロールレジスタの設定の注意事項
	 *　　・高速内蔵RAM空間以外にプログラムを配置する。
	 *　　・SYSCRnへのライト命令の直後にリード命令を配置する。
	 */
	mov.l _sys_cr1_addr_b, r1	 /*  CPU0から高速内蔵RAM0へのアクセス有効  */
	mov   #0xff, r0
	mov.b r0, @r1
	mov.b @r1, r3
							/*  CPU0から高速内蔵RAM0へのライト有効  */
	mov.b r0, @(SYSCR2_b - SYSCR1_b, r1)
	mov.b @(SYSCR2_b - SYSCR1_b, r1), r3
							/*  CPU1から高速内蔵RAM0へのアクセス有効  */
	mov.b r0, @(SYSCR3_b - SYSCR1_b, r1)
	mov.b @(SYSCR3_b - SYSCR1_b, r1), r3
							/*  CPU1から高速内蔵RAM0へのライト有効  */
	mov.b r0, @(SYSCR4_b - SYSCR1_b, r1)
	mov.b @(SYSCR4_b - SYSCR1_b, r1), r0

	/*
	 *	CPU1との同期ポイント(1)
	 *　　CPU1が高速内部RAM1に分岐するまで待つ。
	 */
	mov.l  _semr0_addr_b, r1
_wait_cpu1:
	mov.b  @r1, r2
			/*
			 *  SEMR0のSEMFビット（ビット0）以外は常に0が読み出されるので、
			 *  符号拡張の結果、上位バイトも0に設定される。
			 */
	tst    r2, r2
	bt     _wait_cpu1	/*  SEMR0が0の間、待つ  */
	
	/*
	 *	バス・ステート・コントローラとピン・ファンクション・コントローラの初期化
	 */
	sts.l  pr, @-r15	/*  pr保存  */
	mov.l  _target_bsc_pfc_initialize_p, r1
	jsr/n  @r1
	lds.l  @r15+, pr	/*  pr復元  */

	rts/n

    /************************************
     *  マスタプロセッサでない場合の処理
     ************************************/
_cpu1:
	/*
	 *	CPU1の内部クロックI1Φの分周率：×１倍
	 *	（FRQCR1には、CPU1からでないとアクセスできない。）
	 */
	mov.l _frqcr1_addr_h, r1
	mov    #00, r2
	mov.w  r2, @r1

	/*
	 *	内部RAM1を有効にする
	 *
	 *	システムコントロールレジスタの設定の注意事項
	 *　　・高速内蔵RAM空間以外にプログラムを配置する。
	 *　　・SYSCRnへのライト命令の直後にリード命令を配置する。
	 */
	mov.l _sys_cr7_addr_b, r1	 /*  CPU0から高速内蔵RAM1へのアクセス有効  */
	mov   #0xff, r0
	mov.b r0, @r1
	mov.b @r1, r3				/*  ダミーリード  */
							/*  CPU0から高速内蔵RAM1へのライト有効  */
	mov.b r0, @(SYSCR8_b - SYSCR7_b, r1)
	mov.b @(SYSCR8_b - SYSCR7_b, r1), r3	/*  ダミーリード  */
							/*  CPU1から高速内蔵RAM1へのアクセス有効  */
	mov.b r0, @(SYSCR9_b - SYSCR7_b, r1)
	mov.b @(SYSCR9_b - SYSCR7_b, r1), r3	/*  ダミーリード  */
							/*  CPU1から高速内蔵RAM1へのライト有効  */
	mov.b r0, @(SYSCR10_b - SYSCR7_b, r1)
	mov.b @(SYSCR10_b - SYSCR7_b, r1), r0	/*  ダミーリード  */

	/*
	 *	高速内蔵RAM1上に命令コードをコピー
	 */
	mov.l  _ram1_routine_start_p, r1
	mov.l  _ram1_routine_end_p, r2
	mov.l  _ram1_routine_dst, r3
_copy_ram1:
	mov.l  @r1+, r0
	cmp/hi r1, r2
	mov.l  r0, @r3
	add    #4, r3
	bt	   _copy_ram1
	/*
	 *	高速内蔵RAM1上にコピーした命令コードに分岐
	 */
	mov.l  _ram1_routine_dst, r1
	add    #4, r1		/*  cpu1_flagの分、4バイトスキップする  */
	jmp    @r1
	 nop

	/*
	 *	高速内蔵RAM1上に配置する変数と命令コード
	 */
	.align 2
_ram1_routine_start:	/*  RAM1にコピーする領域：ここから  */

_cpu1_flag:				/*  同期用のフラグ変数cpu1_flag  */
	.long 0x00			/*  　初期値：0  */

	/*
	 *	CPU0との同期ポイント(1)
	 *	　CPU0への通知
	 */
	mov.l  _semr0_addr_b, r1
	mov    #SEMR_SEMF_BIT, r2
	mov.b  r2, @r1

	/*
	 *	CPU0との同期ポイント(2)
	 *	　cpu1_flag=1となるまで待つ。
	 */
	mov.l  _cpu1_flag_addr, r1
_wait_cpu0:
	mov.l  @r1, r0
	cmp/eq #1, r0
	bf     _wait_cpu0

	rts/n	/*  start.Sへリターン  */


	.align 2
_semr0_addr_b:
	.long SEMR0_b
_cpu1_flag_addr:
	.long INNER_RAM1_PAGE0_ADDRESS_START
_ram1_routine_end:	/*  RAM1にコピーする領域：ここまで  */


_frqcr0_addr_h:
	.long FRQCR0_h
_frqcr1_addr_h:
	.long FRQCR1_h

_sys_cr1_addr_b:
	.long SYSCR1_b
_sys_cr7_addr_b:
	.long SYSCR7_b
_target_bsc_pfc_initialize_p:
	.long _target_bsc_pfc_initialize


_ram1_routine_start_p:
	.long _ram1_routine_start
_ram1_routine_end_p:
	.long _ram1_routine_end
_ram1_routine_dst:
	.long INNER_RAM1_PAGE0_ADDRESS_START

