/*
 * loadbalancer.h
 *
 *  Created on: Apr 15, 2016
 *      Author: liyixiao
 */

#pragma once

/*
 *  ロードバランス
 */
extern ER get_rtsk(ID prcid, PRI tskpri, uint_t *p_rtsk);
extern ER iget_rtsk(ID prcid, PRI tskpri, uint_t *p_rtsk);
extern ER get_prd(PRI tskpri, uint_t prd, ID *p_tskid);
extern ER iget_prd(PRI tskpri, uint_t prd, ID *p_tskid);

/*
 *  ロードバランス
 */
#define TPRD_LOWEST		0			/* 最低優先順位指定 */

#include "lb.h"

