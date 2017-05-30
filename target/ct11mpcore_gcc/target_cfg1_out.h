/*
 *  @(#) $Id: target_cfg1_out.h 675 2010-09-13 06:51:40Z ertl-honda $
 */

/*
 *		cfg1_out.cをリンクするために必要なスタブの定義
 */

/*
 *  コア依存のスタブの定義
 */
#include "arm_gcc/common/core_cfg1_out.h"
#ifdef TOPPERS_ENABLE_SEMIHOSTING
int main(void){return 1;}
#endif /* TOPPERS_ENABLE_SEMIHOSTING */
