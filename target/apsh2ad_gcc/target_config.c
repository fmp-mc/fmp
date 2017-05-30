/*
 *	TOPPERS/FMP Kernel
 *		Toyohashi Open Platform for Embedded Real-Time Systems/
 *		Advanced Standard Profile Kernel
 *	
 *	Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *				Graduate School of Information Science, Nagoya Univ., JAPAN
 *	Copyright (C) 2009-2011 by Industrial Technology Institute,
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
 *  $Id: target_config.c 877 2011-08-18 07:28:32Z mit-kimai $
 */

/*
 *	ターゲット依存モジュール（APSH2AD用）
 */

#include "kernel_impl.h"
#include <sil.h>
#include "pdic/sh/sh_scif.h"
#include "apsh2ad.h"
#include "target_syssvc.h"		/*  TNUM_PORT, target_fput_log()  */

/*
 *  バス・ステート・コントローラとピン・ファンクション・コントローラの初期化
 *  
 *  　この関数は、CPU0がhardware_init_hook()から以下の条件で
 *  　呼び出すことを想定している。
 *  　　・スタックポインタが内蔵RAMを指している。
 *  　　・他方のプロセッサ（CPU1）が外部バスにアクセスしていない。
 *  
 *  　この関数は、スタートアップルーチンの「bss/dataセクションの初期化」より
 *  　前に実行される必要があるため、target_mprc_initialize()とは別関数としている。
 */
extern void target_bsc_pfc_initialize(void);

void target_bsc_pfc_initialize(void)
{
#ifdef ROM_BOOT
	/* バスコントローラの設定 */
	sil_wrw_mem((void *)CSMOD0_w, 0x00000000);
				/* CS0モードレジスタ */
				/* PRMOD  0 =ノーマルアクセス互換モード */
				/* PWENB  0 =ページライトアクセス禁止 */
				/* PRENB  0 =ページリードアクセス禁止 */
				/* EWENB  0 =外部ウェイト禁止 */
				/* WRMOD  0 =バイトライトストローブモード */

	sil_wrw_mem((void *)CS1WCNT0_w, 0x07070000);	
				/* CS1ウェイト制御レジスタ1 */
				/* CSRWAIT  00110=6ウェイトサイクル */
				/* CSWWAIT  00110=6ウェイトサイクル */
				/* CSPRWAIT   000=0ウェイトサイクル */
				/* CSPWWAIT   000=0ウェイトサイクル */

	sil_wrw_mem((void *)CS2WCNT0_w, 0x12210011);	
				/* CS2ウェイト制御レジスタ1 */
				/* CSON   001=1ウェイトサイクル */
				/* WDON   010=2ウェイトサイクル */
				/* WRON   010=2ウェイトサイクル */
				/* RDON   001=1ウェイトサイクル */
				/* WDOOFF 000=0ウェイトサイクル */
				/* CSWOFF 001=1ウェイトサイクル */
				/* CSROFF 001=1ウェイトサイクル */

#endif /* ROM_BOOT */

	/* I/Oの設定 */
	sil_wrh_mem((void *)PACRL4_h, 0x1111);		/* D31~16 */
	sil_wrh_mem((void *)PACRL3_h, 0x1111);
	sil_wrh_mem((void *)PACRL2_h, 0x1111);
	sil_wrh_mem((void *)PACRL1_h, 0x1111);

	sil_wrh_mem((void *)PBCRH2_h, 0x0001);		/* WDTOVF */
	sil_wrh_mem((void *)PBCRH1_h, 0x0001);		/* PB17 SDWE */
	sil_wrh_mem((void *)PBCRL4_h, 0x1111);		/* CKE CAS RAS WE3 */
	sil_wrh_mem((void *)PBCRL3_h, 0x1111);		/* WE2 WE1 WE0 CS5 */
	sil_wrh_mem((void *)PBCRL2_h, 0x2111);		/* SDCS0 CS3 CS2 CS1 */
	sil_wrh_mem((void *)PBCRL1_h, 0x1111);		/* A22 A21 A1 A0 */

	sil_wrh_mem((void *)PCCRL3_h, 0x0000);		/* PC10~0 */
	sil_wrh_mem((void *)PCCRL2_h, 0x0000);
	sil_wrh_mem((void *)PCCRL1_h, 0x0000);

	sil_wrh_mem((void *)PCIORL_h, 0x07FF);		/* OUT : PC10~0 */

	sil_wrh_mem((void *)PDCRL1_h, 0x0222);		/* A25 A24 A23 */

	sil_wrh_mem((void *)PECRL1_h, 0x1111);		/* RTS0 CTS0 TxD0 RxD0 */

	sil_wrh_mem((void *)PFCRL2_h, 0x0000);		/* LED2 */
	sil_wrh_mem((void *)PFCRL1_h, 0x0330);		/* LED1 CTx0 CRx0 PF0 */

	sil_wrh_mem((void *)PFIORL_h, 0x0019);
						/* OUT : LED2(PF4) LED1(PF3) PF0 */

	sil_wrh_mem((void *)PHIORL_h, 0x0280);
						/* PH7,PH8:USBHOST0 PH9,PH10:USBHOST1 PH6:WP*/

	sil_wrh_mem((void *)PJCRL4_h, 0x0000);		/* PJ12~0 */
	sil_wrh_mem((void *)PJCRL3_h, 0x0000);
	sil_wrh_mem((void *)PJCRL2_h, 0x0000);
	sil_wrh_mem((void *)PJCRL1_h, 0x0000);

	sil_wrh_mem((void *)PJIORL_h, 0x1FFF);		/* OUT : PJ12~0 */

#ifdef ROM_BOOT

	sil_wrw_mem((void *)SDIR0_w, 0x00000082);	/* SDRAM初期化レジスタ0 */
				/* DPC   初期化プリチャージサイクル(000=3サイクル) */
				/* DARFC 初期化オートリフレッシュ回数(1000=8回) */
				/* DARFI 初期化オートリフレッシュ間隔(0010=5サイクル) */

	sil_wrw_mem((void *)SDIR1_w, 0x00000001);	/* SDRAM初期化レジスタ1 */
				/* DINIRQ  初期化シーケンス開始 */

	/* SDRAM初期化終了待ち */
	while( (sil_rew_mem((void *)SDIR1_w) & 0x00010000) != 0 );

	/* SDRAMステータスレジスタの確認 */
	while( sil_rew_mem((void *)SDSTR_w) != 0);

	sil_wrw_mem((void *)SD0MOD_w, 0x00000020);
				/* SDRAM0モードレジスタ */
				/* A9   ライトバースト長(0=Burst) */
				/* A8-7 テストモード(00=Mode Reister Set) */
				/* A6-4 CASレイテンシ(010=2サイクル) */
				/* A3   バーストタイプ(0=Sequential) */
				/* A2-1 バースト長(000=1) */

	sil_wrw_mem((void *)SD0TR_w, 0x00021302);	/* SDRAM0タイミングレジスタ */
				/* DRAS ロウアクティブ期間(010=3サイクル) */
				/* DRCD ロウカラムレイテンシ期間(01=2サイクル) */
				/* DPCG ロウプリチャージ期間(001=2サイクル) */
				/* DWR  ライトリカバリ期間(1=2サイクル) */
				/* DCL  CASレイテンシ(010=2サイクル) */

	sil_wrw_mem((void *)SD0ADR_w, 0x00000203);
				/* SDRAM0アドレスレジスタ */
				/* DDBW SDRAMデータバス幅(10=32ビット) */
				/* DSZ  チャネルサイズ(011=32Mバイト) */

	sil_wrw_mem((void *)SDRFCNT1_w, 0x00014208);
				/* SDRAMリフレッシュ制御レジスタ1 */
				/* DRFEN オートリフレッシュ動作(1=有効) */
				/* DREFW オートリフレッシュサイクル数(0100=5サイクル) */
				/* DRFC  オートリフレッシュ要求間隔 */
				/* 64mS/4096=1.56us */

	sil_wrw_mem((void *)SDC0CNT_w, 0x00110000);
				/* SDRAMC0制御レジスタ */
				/* BSIZE 外部バス幅(01=32ビットバス) */
				/* EXENB 動作許可(1=動作許可) */
#endif /* ROM_BOOT */
}


/*
 *  str_ker() の実行前にマスタプロセッサのみ実行される初期化処理
 */
void
target_mprc_initialize(void)
{
	prc_mprc_initialize();

	/*
	 *	低消費電力モードの設定
	 */
		/*
		 *	CPU0のsleep命令の実行で、CPU0がスリープモードへ遷移
		 *	　・スリープエラー禁止
		 *	　・オーディオ用水晶発信子が無効
		 */
	sil_wrb_mem((void *)STBCR1_b, STBCR1_AXTALE);

		/*
		 *	　・H-UDIは動作
		 *	　・FPU0,FPU1は動作
		 *	　・UBC0,UBC1は動作
		 *	　
		 *	　備考
		 *	　　JTAGエミュレータを使用する場合は、
		 *	　　H-UDI、FPU、UBCを停止してはいけない。
		 */
	sil_wrb_mem((void *)STBCR2_b, 0x00U);

		/*
		 *	　・ATAPIは停止
		 *	　・MTU2は停止
		 *	　・ADCは停止
		 *	　・DACは停止
		 *	　・RTCは停止
		 */
	sil_wrb_mem((void *)STBCR3_b, 0xffU);

		/*
		 *	　・SCFI0は動作
		 *	　・SCFI1は動作
		 *	　・SCFI2は停止
		 *	　・SCFI3は停止
		 *	　・SCFI4は停止
		 *	　・SCFI5は停止
		 */
	sil_wrb_mem((void *)STBCR4_b, (uint8_t)~(STBCR4_SCIF0 | STBCR4_SCIF1));

		/*
		 *	　・IIC3_0は停止
		 *	　・IIC3_1は停止
		 *	　・IIC3_2は停止
		 *	　・IIC3_3は停止
		 *	　・RCAN0は停止
		 *	　・RCAN1は停止
		 */
	sil_wrb_mem((void *)STBCR5_b, 0xffU);

		/*
		 *	　・SSIF0は停止
		 *	　・SSIF1は停止
		 *	　・SSIF2は停止
		 *	　・SSIF3は停止
		 *	　・SSIF4は停止
		 *	　・SSIF5は停止
		 */
	sil_wrb_mem((void *)STBCR6_b, 0xffU);

		/*
		 *	　・CMT01は動作
		 *	　・CMT23は停止
		 *	　・FLCTLは停止
		 *	　・SSU0は停止
		 *	　・SSU1は停止
		 *	　・2DGは停止
		 *	　・USBは停止
		 */
	sil_wrb_mem((void *)STBCR7_b, (uint8_t)~STBCR7_CMT01);

	/*
	 *	SCIFのI/Oポートの設定	 要検討:PE4/SCK0端子の設定も必要？
	 */
	sil_wrh_mem((void *)PECRL1_h, 0x1111U);/* SCIF0:RTS0 CTS0 TxD0 RxD0 */
#if TNUM_PORT > 1
	sil_wrh_mem((void *)PECRL2_h, 0x0110U);/* SCIF1:TxD1 RxD1 */
#endif /* TNUM_PORT > 1 */
	
	/*
	 * バーナー出力用のシリアルコントローラの初期化
	 */
	sh_scif_init(1);
#if TNUM_PORT > 1
	sh_scif_init(2);
#endif /* TNUM_PORT > 1 */
}

/*
 *	ターゲット依存の初期化
 */
void
target_initialize(void)
{
	/*
	 *	プロセッサ依存の初期化
	 */
	prc_initialize();
}

/*
 *	ターゲット依存の終了処理
 */
void
target_exit(void)
{
	/*
	 *	プロセッサ依存の終了処理
	 */
	prc_exit();

	/*
	 *	開発環境依存の終了処理
	 */
	apsh2ad_exit();

	/*
	 * ここには来ない
	 */
	while(true);
}

/*
 *	システムログの低レベル出力のための文字出力
 */
void
target_fput_log(char_t c)
{
#if TNUM_PORT == 1
	ID siopid = TARGET_PUTC_PORTID;
#else	/* TNUM_PORT == 1 */
	ID siopid = sil_get_pindex() + 1;
#endif	/* TNUM_PORT == 1 */

	if (c == '\n') {
		sh_scif_pol_putc('\r', siopid);
	}
	sh_scif_pol_putc(c, siopid);
}


/*
 *	アサーションの失敗時の実行中断処理（T.B.D）
 */
void
TOPPERS_assert_abort(void)
{
	uint_t index = sil_get_pindex();
	
	syslog(LOG_EMERG, "prcindex = %d" ,index);
	while(true);
}

