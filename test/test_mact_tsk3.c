/*
 *  TOPPERS Software
 *      Toyohashi Open Platform for Embedded Real-Time Systems
 * 
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: test_mact_tsk3.c 661 2010-07-29 10:10:12Z ertl-honda $
 */

/* 
 *		mact_tskサービスコールのテスト(3)
 *  【テストの目的】
 *    対象タスクが，起床待ちのタスクに対して，mact_tskを発行する．
 *
 *  【テスト項目】
 *
 *    (2-H) 自プロセッサに割り付けられたタスクを他プロセッサへ
 *    (2-I) 他プロセッサに割り付けられたタスクを自プロセッサへ
 */

#include <kernel.h>
#include <t_syslog.h>
#include <test_lib.h>
#include <sil.h>
#include "kernel_cfg.h"

void
task1_4(intptr_t exinf)
{
	ER		ercd;
	FLGPTN flgptn;
  
	check_point(1);
	ercd = mact_tsk(TASK1_5,2);
	check_ercd(ercd, E_OK);

	check_point(2);
	ercd = mact_tsk(TASK1_5,2);
	check_ercd(ercd, E_OK);

	//同期フラグ待ち 1回目起動待ち
	do{
		ercd = pol_flg(FLG1,1,TWF_ANDW,&flgptn);
	}while(ercd != E_OK);

	check_point(3);
	ercd = wup_tsk(TASK1_5);
	check_ercd(ercd, E_OK);

	//同期フラグ待ち 2回目起動待ち
	do{
		ercd = pol_flg(FLG1,2,TWF_ANDW,&flgptn);
		}while(ercd != E_OK);

	check_point(4);
	ercd = wup_tsk(TASK1_5);
	check_ercd(ercd, E_OK);

//ここから他プロセッサに割り付けられたタスクを自プロセッサに
	check_point(5);
	ercd = mact_tsk(TASK2_1,1);
	check_ercd(ercd, E_OK);

	check_point(7);
	ercd = mact_tsk(TASK2_1,1);
	check_ercd(ercd, E_OK);

	check_point(8);
	ercd = wup_tsk(TASK2_1);
	check_ercd(ercd, E_OK);

	check_point(11);
	ercd = wup_tsk(TASK2_1);
	check_ercd(ercd, E_OK);

	/*
	 * テスト終了
	 */
  
	check_finish(13);//CPU1
}

void
task1_5(intptr_t exinf)
{
	ER		ercd;
	static uint_t actno=0;

	actno++;
	if(actno==1){
		check_point(1);
		ercd = set_flg(FLG1,1);
		check_ercd(ercd, E_OK);    
	}else if(actno ==2){
		check_point(3);
		ercd = set_flg(FLG1,2);
		check_ercd(ercd, E_OK);    
	}

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	if(actno==1){
		check_point(2);
	}else if(actno ==2){
		check_point(4);

	/*
	 * テスト終了
	 */
		check_finish(5);
	}
  
}

void
task2_1(intptr_t exinf)
{
	ER		ercd;
	static uint_t actno=0;

	actno++;
	if(actno==1){
		check_point(6);
	}else if(actno ==2){
		check_point(10);
	}

	ercd = slp_tsk();
	check_ercd(ercd, E_OK);

	if(actno==1){
		check_point(9);
	}else if(actno ==2){
		check_point(12);
		ercd = slp_tsk();
		check_ercd(ercd, E_OK);
	}
  
}
