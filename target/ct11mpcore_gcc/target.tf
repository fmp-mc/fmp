$ 
$     パス2のターゲット依存テンプレート（CT11MPCORE用）
$ 

$ 
$  有効な割込み番号，割込みハンドラ番号，CPU例外ハンドラ番号
$ 
$INTNO_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$INHNO_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,...,0x1003f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,...,0x2003f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,...,0x3003f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,...,0x4003f
}$

$ 
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$ 
$INTNO_ATTISR_VALID = { 
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$INHNO_ATTISR_VALID = {
	0x10000,0x10001,...,0x1000f;0x1001d,0x1001e,0x1001f;
	0x20000,0x20001,...,0x2000f;0x2001d,0x2001e,0x2001f;
	0x30000,0x30001,...,0x3000f;0x3001d,0x3001e,0x3001f;
	0x40000,0x40001,...,0x4000f;0x4001d,0x4001e,0x4001f;
	0x00020,0x00021,...,0x0003f
}$

$ 
$ 割込み番号，割込みハンドラ番号の長さ
$ 
$INTNO_RANGE = { 0x0000,0x0001,...,0x003f }$
$INHNO_RANGE = INTNO_RANGE$

$ 
$ プロセッサに対する定義
$ 


$ 
$  クラスに対する定義
$ 

$ 
$  クラス数
$ 
$NUM_CLASS = 9$

$ 
$ クラス1に関する指定
$ 

$  初期割付けプロセッサ(ID指定)
$CLASS_AFFINITY_INI[1] = 1$

$  マイグレーション可能なプロセッサのマスク指定
$CLASS_AFFINITY_MASK[1] = 0x0000000f$

$  オブジェクトロック
& P_LOCKの場合に使用するオブジェクトロックを持つプロセッサのIDを指定
$CLASS_OBJ_LOCK[1] = 1$

$ 
$ クラス2に関する指定
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x0000000f$
$CLASS_OBJ_LOCK[2] = 2$

$ 
$ クラス3に関する指定
$ 
$CLASS_AFFINITY_INI[3] = 3$
$CLASS_AFFINITY_MASK[3] = 0x0000000f$
$CLASS_OBJ_LOCK[3] = 3$

$ 
$ クラス4に関する指定
$ 
$CLASS_AFFINITY_INI[4] = 4$
$CLASS_AFFINITY_MASK[4] = 0x0000000f$
$CLASS_OBJ_LOCK[4] = 4$

$ 
$ クラス TCL_1_ONLY（クラスID 5）に関する指定
$ 
$CLASS_AFFINITY_INI[5] = 1$
$CLASS_AFFINITY_MASK[5] = 0x00000001$
$CLASS_OBJ_LOCK[5] = 1$

$ 
$ クラス TCL_2_ONLY（クラスID 6）に関する指定
$ 
$CLASS_AFFINITY_INI[6] = 2$
$CLASS_AFFINITY_MASK[6] = 0x00000002$
$CLASS_OBJ_LOCK[6] = 2$

$ 
$ クラス TCL_3_ONLY（クラスID 7） に関する指定
$ 
$CLASS_AFFINITY_INI[7] = 3$
$CLASS_AFFINITY_MASK[7] = 0x00000004$
$CLASS_OBJ_LOCK[7] = 3$

$ 
$ クラス TCL_4_ONLY（クラスID 8） に関する指定
$ 
$CLASS_AFFINITY_INI[8] = 4$
$CLASS_AFFINITY_MASK[8] = 0x00000008$
$CLASS_OBJ_LOCK[8] = 4$

$ 
$ クラス TCL_SYSTIM_PRC（クラスID 9） に関する指定
$ 
$CLASS_AFFINITY_INI[9] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[9] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1) $
$CLASS_OBJ_LOCK[9] = TOPPERS_SYSTIM_PRCID$

$ 
$  チップ依存テンプレートのインクルード
$ 
$INCLUDE"../../arch/arm_gcc/mpcore/arm11.tf"$
