#ifndef LB_H
#define LB_H

#include <kernel.h>

/*
 *  システムログタスク関連の定数のデフォルト値の定義
 */ 
#ifndef LOADTASK_PRIORITY
#define LOADTASK_PRIORITY	3		/* 初期優先度 */
#endif /* LOADTASK_PRIORITY */

#ifndef LOADTASK_STACK_SIZE
#define LOADTASK_STACK_SIZE	1024	/* スタック領域のサイズ */
#endif /* LOADTASK_STACK_SIZE */

/* ロードバランスタスク(CPU間ロードバランス実行)の起動間隔 */
/*
 *  ロードバランスタスクの起動間隔
 */
#define CYC_INTERVAL        5

/*
 *  負荷因子の更新間隔
 */
#define CYC_REBALANCE        1

/*
 *  ラウンドロビンスケジュール用周期ハンドラ起動間隔
 */
#define CYC_RDQ 1


/*
 *  タスクと周期ハンドラ
 */
extern void	loadserver_main(intptr_t exinf) throw();
extern void cyclic_loadserver(intptr_t exinf) throw();

/*
 *  ロードバランス用各種API
 */
//extern ER lb_inc_wrk(ID tskid, uint_t work);
//extern ER lb_dec_wrk(ID tskid, uint_t work);
extern ER lb_inc_wrk(ID tskid, uint_t work,bool_t *flg);
extern ER lb_dec_wrk(ID tskid, uint_t work, uint_t per_work, bool_t *flg);
extern ER lb_set_wrk(ID tskid, uint_t work);
extern void lbc_ena_lbc(void);
extern void lbc_dis_lbc(void);
extern uint16_t mig_count[TNUM_PRCID];
extern uint16_t sleep_count[4];
#endif /* LB_H */
