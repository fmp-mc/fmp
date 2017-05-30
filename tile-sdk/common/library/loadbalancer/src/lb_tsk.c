/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2009-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: sample1.c 374 2008-03-22 01:32:57Z honda $
 */

#include <kernel.h>
#include <t_syslog.h>
#include <log_output.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "loadbalancer.h"
#include "lb_tsk.h"
#include "lb.h"
#include "kernel_cfg.h"

#define DEBUG

/*
 *  サービスコールのエラーのログ出力
 */
Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

/*
 *  データキューID
 */
ID const load_dtqid[TNUM_PRCID] = {
/* [[[cog
import cog, pass0
for i in range(1, pass0.core_number + 1):
	cog.outl('LOAD_DTQ{0},'.format(i))
]]] */
LOAD_DTQ1,
LOAD_DTQ2,
LOAD_DTQ3,
LOAD_DTQ4,
LOAD_DTQ5,
LOAD_DTQ6,
LOAD_DTQ7,
LOAD_DTQ8,
LOAD_DTQ9,
LOAD_DTQ10,
LOAD_DTQ11,
LOAD_DTQ12,
LOAD_DTQ13,
LOAD_DTQ14,
LOAD_DTQ15,
LOAD_DTQ16,
LOAD_DTQ17,
LOAD_DTQ18,
LOAD_DTQ19,
LOAD_DTQ20,
LOAD_DTQ21,
LOAD_DTQ22,
LOAD_DTQ23,
LOAD_DTQ24,
LOAD_DTQ25,
LOAD_DTQ26,
LOAD_DTQ27,
LOAD_DTQ28,
LOAD_DTQ29,
LOAD_DTQ30,
LOAD_DTQ31,
LOAD_DTQ32,
LOAD_DTQ33,
LOAD_DTQ34,
LOAD_DTQ35,
LOAD_DTQ36,
LOAD_DTQ37,
LOAD_DTQ38,
LOAD_DTQ39,
LOAD_DTQ40,
LOAD_DTQ41,
LOAD_DTQ42,
LOAD_DTQ43,
LOAD_DTQ44,
LOAD_DTQ45,
LOAD_DTQ46,
LOAD_DTQ47,
LOAD_DTQ48,
LOAD_DTQ49,
LOAD_DTQ50,
LOAD_DTQ51,
LOAD_DTQ52,
LOAD_DTQ53,
LOAD_DTQ54,
LOAD_DTQ55,
LOAD_DTQ56,
LOAD_DTQ57,
LOAD_DTQ58,
LOAD_DTQ59,
LOAD_DTQ60,
LOAD_DTQ61,
LOAD_DTQ62,
LOAD_DTQ63,
LOAD_DTQ64,
LOAD_DTQ65,
LOAD_DTQ66,
LOAD_DTQ67,
LOAD_DTQ68,
LOAD_DTQ69,
LOAD_DTQ70,
LOAD_DTQ71,
LOAD_DTQ72,
/* [[[end]]] */
};

/*
 *  周期ハンドラID
 */
uint_t const loadbalance_cycid[TNUM_PRCID][3] = {
/* [[[cog
import cog, pass0
for i in range(1, pass0.core_number + 1):
	cog.outl('{{CYC_LOADSEV{0},CYC_REBALANCE{0},CYC_RR{0}}},'.format(i))
]]] */
{CYC_LOADSEV1,CYC_REBALANCE1,CYC_RR1},
{CYC_LOADSEV2,CYC_REBALANCE2,CYC_RR2},
{CYC_LOADSEV3,CYC_REBALANCE3,CYC_RR3},
{CYC_LOADSEV4,CYC_REBALANCE4,CYC_RR4},
{CYC_LOADSEV5,CYC_REBALANCE5,CYC_RR5},
{CYC_LOADSEV6,CYC_REBALANCE6,CYC_RR6},
{CYC_LOADSEV7,CYC_REBALANCE7,CYC_RR7},
{CYC_LOADSEV8,CYC_REBALANCE8,CYC_RR8},
{CYC_LOADSEV9,CYC_REBALANCE9,CYC_RR9},
{CYC_LOADSEV10,CYC_REBALANCE10,CYC_RR10},
{CYC_LOADSEV11,CYC_REBALANCE11,CYC_RR11},
{CYC_LOADSEV12,CYC_REBALANCE12,CYC_RR12},
{CYC_LOADSEV13,CYC_REBALANCE13,CYC_RR13},
{CYC_LOADSEV14,CYC_REBALANCE14,CYC_RR14},
{CYC_LOADSEV15,CYC_REBALANCE15,CYC_RR15},
{CYC_LOADSEV16,CYC_REBALANCE16,CYC_RR16},
{CYC_LOADSEV17,CYC_REBALANCE17,CYC_RR17},
{CYC_LOADSEV18,CYC_REBALANCE18,CYC_RR18},
{CYC_LOADSEV19,CYC_REBALANCE19,CYC_RR19},
{CYC_LOADSEV20,CYC_REBALANCE20,CYC_RR20},
{CYC_LOADSEV21,CYC_REBALANCE21,CYC_RR21},
{CYC_LOADSEV22,CYC_REBALANCE22,CYC_RR22},
{CYC_LOADSEV23,CYC_REBALANCE23,CYC_RR23},
{CYC_LOADSEV24,CYC_REBALANCE24,CYC_RR24},
{CYC_LOADSEV25,CYC_REBALANCE25,CYC_RR25},
{CYC_LOADSEV26,CYC_REBALANCE26,CYC_RR26},
{CYC_LOADSEV27,CYC_REBALANCE27,CYC_RR27},
{CYC_LOADSEV28,CYC_REBALANCE28,CYC_RR28},
{CYC_LOADSEV29,CYC_REBALANCE29,CYC_RR29},
{CYC_LOADSEV30,CYC_REBALANCE30,CYC_RR30},
{CYC_LOADSEV31,CYC_REBALANCE31,CYC_RR31},
{CYC_LOADSEV32,CYC_REBALANCE32,CYC_RR32},
{CYC_LOADSEV33,CYC_REBALANCE33,CYC_RR33},
{CYC_LOADSEV34,CYC_REBALANCE34,CYC_RR34},
{CYC_LOADSEV35,CYC_REBALANCE35,CYC_RR35},
{CYC_LOADSEV36,CYC_REBALANCE36,CYC_RR36},
{CYC_LOADSEV37,CYC_REBALANCE37,CYC_RR37},
{CYC_LOADSEV38,CYC_REBALANCE38,CYC_RR38},
{CYC_LOADSEV39,CYC_REBALANCE39,CYC_RR39},
{CYC_LOADSEV40,CYC_REBALANCE40,CYC_RR40},
{CYC_LOADSEV41,CYC_REBALANCE41,CYC_RR41},
{CYC_LOADSEV42,CYC_REBALANCE42,CYC_RR42},
{CYC_LOADSEV43,CYC_REBALANCE43,CYC_RR43},
{CYC_LOADSEV44,CYC_REBALANCE44,CYC_RR44},
{CYC_LOADSEV45,CYC_REBALANCE45,CYC_RR45},
{CYC_LOADSEV46,CYC_REBALANCE46,CYC_RR46},
{CYC_LOADSEV47,CYC_REBALANCE47,CYC_RR47},
{CYC_LOADSEV48,CYC_REBALANCE48,CYC_RR48},
{CYC_LOADSEV49,CYC_REBALANCE49,CYC_RR49},
{CYC_LOADSEV50,CYC_REBALANCE50,CYC_RR50},
{CYC_LOADSEV51,CYC_REBALANCE51,CYC_RR51},
{CYC_LOADSEV52,CYC_REBALANCE52,CYC_RR52},
{CYC_LOADSEV53,CYC_REBALANCE53,CYC_RR53},
{CYC_LOADSEV54,CYC_REBALANCE54,CYC_RR54},
{CYC_LOADSEV55,CYC_REBALANCE55,CYC_RR55},
{CYC_LOADSEV56,CYC_REBALANCE56,CYC_RR56},
{CYC_LOADSEV57,CYC_REBALANCE57,CYC_RR57},
{CYC_LOADSEV58,CYC_REBALANCE58,CYC_RR58},
{CYC_LOADSEV59,CYC_REBALANCE59,CYC_RR59},
{CYC_LOADSEV60,CYC_REBALANCE60,CYC_RR60},
{CYC_LOADSEV61,CYC_REBALANCE61,CYC_RR61},
{CYC_LOADSEV62,CYC_REBALANCE62,CYC_RR62},
{CYC_LOADSEV63,CYC_REBALANCE63,CYC_RR63},
{CYC_LOADSEV64,CYC_REBALANCE64,CYC_RR64},
{CYC_LOADSEV65,CYC_REBALANCE65,CYC_RR65},
{CYC_LOADSEV66,CYC_REBALANCE66,CYC_RR66},
{CYC_LOADSEV67,CYC_REBALANCE67,CYC_RR67},
{CYC_LOADSEV68,CYC_REBALANCE68,CYC_RR68},
{CYC_LOADSEV69,CYC_REBALANCE69,CYC_RR69},
{CYC_LOADSEV70,CYC_REBALANCE70,CYC_RR70},
{CYC_LOADSEV71,CYC_REBALANCE71,CYC_RR71},
{CYC_LOADSEV72,CYC_REBALANCE72,CYC_RR72},
/* [[[end]]] */
};

/*
 * load_average(負荷指標)管理用配列
 */
int_t mp_load_average[TNUM_PRCID];

/*
 *  戻り値：最低負荷のCPUID
 *  OUT(imbalance)：移動するタスク数
 */
uint16_t
find_lowest_cpu(ID prcid, uint16_t *imbalance)
{
	//uint16_t min_load,ave_load,total_load,this_load,load;
	//uint16_t lowest_id=0;
	//uint16_t i;
	uint_t min_load,ave_load,total_load,this_load,load; // TODO: uint_16 may easily overflow -- ertl-liyixiao
	uint_t lowest_id=0;
	uint_t i;
	uint_t prcindex = prcid - 1;
  
	ave_load = this_load = total_load = 0;

	min_load = mp_load_average[prcindex];
	for (i = 1; i <= TNUM_PRCID; i++){
		load = mp_load_average[i-1];
		total_load += load;

		if (i == prcid) {
			/* 自プロセッサの場合 */
			this_load = load;
		}
		else if ( load <= min_load ){
			min_load = load;
			lowest_id = i;
		}
	}

	/* 自CPUの負荷が最低の場合は，ロードバランスを行わない */
	if (this_load <= min_load) {
		return 0;
	}

	ave_load = total_load/TNUM_PRCID;

	/* 自CPUの負荷が平均負荷以下　かつ　最高負荷が自CPU負荷の1.25倍以上のときロードバランスを行う */
	if ((this_load <= ave_load) || (100*this_load < 125*min_load)) {
		return 0;
	}

	/* ロードバランスを行う場合の，移動するタスクの数 */
	if ((ave_load - min_load) < (this_load - ave_load)) {
		*imbalance = (ave_load - min_load);
        if(*imbalance >= 100 * 128) syslog(LOG_NOTICE, "HERE1 ave:%u min:%u this:%d", ave_load, min_load, this_load); // for debug -- ertl-liyixiao
	}else{
		*imbalance = (this_load - ave_load);
        if(*imbalance >= 100 * 128) syslog(LOG_NOTICE, "HERE2"); // for debug -- ertl-liyixiao
	}
	/* 移動するタスク数の調整 */
	if (*imbalance < 128) {
		if ((this_load - min_load) >= 128*2-1) {
			*imbalance = 1;
			return lowest_id;
		}
		else{
			return 0;
		}
	}
	else{
		*imbalance /= 128;
		return lowest_id;
	}
}


void
load_balance(ID prcid)
{
	uint16_t cpu_id,imbalance=0;
	uint32_t server_req;
	uint_t prcindex = prcid - 1;
	ID dtqid;

	cpu_id = find_lowest_cpu(prcid, &imbalance);

	/*	データキュー送信
		マイグレーション先：cpuid
		cpuidが0のときは，ロードバランスを行わない*/
	if (cpu_id && (imbalance > 0)) {
		dtqid = load_dtqid[prcindex];
		server_req = (imbalance << 16) | cpu_id;
		ipsnd_dtq(dtqid, server_req);
#ifdef DEBUG
		syslog(LOG_NOTICE, "snd_dtq  server_req 0x%x  imbalancce %d  this_id %d  from %d", server_req,imbalance,prcid,cpu_id);
#endif /* DEBUG */
    }
}

/*
 * ロードバランス用周期ハンドラ
 */
void cyclic_loadserver(intptr_t exinf)
{
	load_balance((ID)exinf);
}

/*
 *  load_averageの更新
 */
void
rebalance_tick(ID prcid){
	uint_t ntsk;
	uint_t prcindex;

	prcindex = prcid - 1;

	iget_rtsk(0, LOAD_PRI, &ntsk);
	mp_load_average[prcindex] = (mp_load_average[prcindex] + ntsk * 128)/2;
}

/*
 *  load_average更新用周期ハンドラ
 */
void cyclic_rebalance(intptr_t exinf)
{
	rebalance_tick((ID)exinf);
}

/*
 *  ロードサーバータスクの本体
 */
void
loadserver_main(intptr_t exinf)
{
	uint16_t imbalance;
	ID		to_prcid;
	uint16_t j;
	ID tskid;
	ID dtqid = load_dtqid[exinf - 1];
	intptr_t req;

	sta_cyc(loadbalance_cycid[exinf - 1][0]);
	sta_cyc(loadbalance_cycid[exinf - 1][1]);
	sta_cyc(loadbalance_cycid[exinf - 1][2]);

	syslog(LOG_NOTICE, "loadserver_main start!");

	while(1){
		rcv_dtq(dtqid, &req);
#ifdef DEBUG
		syslog(LOG_NOTICE, "rcv_dtq  req 0x%x", req);
#endif /* DEBUG */
		imbalance = (req >> 16) & 0xff;
		to_prcid = req & 0xff;
		for (j = 0; j < imbalance; j++){
			if(get_prd(LOAD_PRI, 2, &tskid) == E_NOEXS) {
				continue;
			}
			syslog(LOG_NOTICE, "mig_tsk, taskid,%d,%d->%d",tskid,exinf,to_prcid);
			mig_tsk(tskid, to_prcid);
			mig_count[exinf - 1]++;
        }
	}
}

/*
 *  ロードバランス対象優先度の各優先度のレディキュー
 *  を回転させ，ラウンドロビンスケジュールを実現．
 */
void cyclic_rr(intptr_t exinf)
{
	SVC_PERROR(irot_rdq(LOAD_PRI));
}

void load_balancer_initialize(intptr_t unused) {
	for (int prcid = 1; prcid <= TNUM_PRCID; prcid++) {
		for (int i = 0; i < TNUM_TPRI; i++) {
			get_mp_p_pcb(prcid)->tsk_num[i] = 0;
		}
	}
}
