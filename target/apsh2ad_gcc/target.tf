$ 
$     パス2のターゲット依存テンプレート（APSH2AD用）
$ 

$ 
$ プロセッサに対する定義
$ 

$ グローバルタイマ時のタイムイベント用データのセクション指定
$PRC_SECTION_TEVT[0] = ""$

$ 
$ ネイティブロック方式の場合のロックの最大サポート数
$ 
$MAX_NATIVE_SPIN_LOCK = 32 - 2$
$ 
$ プロセッサ1に関する指定
$ 
$ PCBのセクション指定
$PRC_SECTION_PCB[1]  = ""$
$ 非タスクコンテキスト用スタックのセクション指定
$PRC_SECTION_ISTACK[1]  = ""$
$ タイムイベント関連データのセクション指定
$PRC_SECTION_TEVT[1] = ""$

$ ターゲット依存の定義
$PRC_SECTION_TPCB[1] = ""$


$ 
$ プロセッサ2に関する指定
$ 
$PRC_SECTION_PCB[2] = ""$
$PRC_SECTION_ISTACK[2]  = ""$
$PRC_SECTION_TEVT[2] = ""$
$PRC_SECTION_TPCB[2] = ""$



$ 
$  クラスに対する定義
$ 

$ 
$  クラス数
$ 
$NUM_CLASS = 5$

$ 
$ クラス TCL_1（クラスID 1） に関する指定
$ 　プロセッサ1が初期割付けプロセッサのクラス
$ 

$  初期所属プロセッサ(ID指定)
$CLASS_AFFINITY_INI[1] = 1$

$  マイグレーション可能なプロセッサのマスク指定
$CLASS_AFFINITY_MASK[1] = 0x00000003$

$  タスクコントロールブロックのセクション指定
$CLASS_SECTION_TSKCB[1] = ""$

$  オブジェクトコントロールブロックのセクション指定
$CLASS_SECTION_OBJCB[1] = ""$

$  タスクスタックのセクション指定
$CLASS_SECTION_TSTACK[1] = ""$


$ 
$ クラス TCL_2（クラスID 2） に関する指定
$ 　プロセッサ2が初期割付けプロセッサのクラス
$ 
$CLASS_AFFINITY_INI[2] = 2$
$CLASS_AFFINITY_MASK[2] = 0x00000003$

$CLASS_SECTION_TSKCB[2] = ""$
$CLASS_SECTION_OBJCB[2] = ""$
$CLASS_SECTION_TSTACK[2] = ""$

$ 
$ クラス TCL_1_ONLY（クラスID 3） に関する指定
$ 　割付け可能プロセッサはプロセッサ1のみのクラス
$ 
$CLASS_AFFINITY_INI[3] = 1$
$CLASS_AFFINITY_MASK[3] = 0x00000001$

$CLASS_SECTION_TSKCB[3] = ""$
$CLASS_SECTION_OBJCB[3] = ""$
$CLASS_SECTION_TSTACK[3] = ""$


$ 
$ クラス TCL_2_ONLY（クラスID 4） に関する指定
$ 　割付け可能プロセッサはプロセッサ1のみのクラス
$ 
$CLASS_AFFINITY_INI[4] = 2$
$CLASS_AFFINITY_MASK[4] = 0x00000002$

$CLASS_SECTION_TSKCB[4] = ""$
$CLASS_SECTION_OBJCB[4] = ""$
$CLASS_SECTION_TSTACK[4] = ""$

$ 
$ クラス TCL_SYSTIM_PRC（クラスID 5） に関する指定
$ 　　クローバルタイマ方式の場合のタイムイベントハンドラを登録するクラス
$ 　　（システム時刻管理プロセッサのみのクラス）
$ 
$CLASS_AFFINITY_INI[5] = TOPPERS_SYSTIM_PRCID$
$CLASS_AFFINITY_MASK[5] = 0x1 << (TOPPERS_SYSTIM_PRCID - 1)$

$CLASS_SECTION_TSKCB[5] = ""$
$CLASS_SECTION_OBJCB[5] = ""$
$CLASS_SECTION_TSTACK[5] = ""$


$ 
$ ATT_ISRのターゲット依存のチェック
$ 　（制限事項）
$ 　ハードウェア的に全プロセッサにも割り付け可能な割込み（割込み番号の上位
$ 　16ビットが0）に対するATT_ISRは，割り付け可能プロセッサが初期割付けプロ
$ 　セッサのみのクラスに割り付け可能である．
$ 
$FUNCTION TARGET_CHECK_ATT_ISR$
	$IF ((ISR.INTNO[ARGV[1]] & 0xffff0000) == 0) 
		&& ((1 << (CLASS_AFFINITY_INI[ISR.CLASS[ARGV[1]]] - 1)) != CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$
		$ERROR ISR.TEXT_LINE[order]$E_RSATR: $FORMAT(_("processor affinity of `0x%1$x\' in %2% is not match with class %3% processor affinity mask `0x%4$x\'."), +ISR.INTNO[ARGV[1]], "ATT_ISR", ISR.CLASS[ARGV[1]], +CLASS_AFFINITY_MASK[ISR.CLASS[ARGV[1]]])$$END$
	$END$
$END$


$ 
$  SH7205依存のテンプレートファイルのインクルード
$ 
$INCLUDE "sh2a_dual_gcc/sh7205.tf"$
