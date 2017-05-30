$ ======================================================================
$  TILEGx Architecture Support Package for TOPPERS/FMP Kernel
$ 
$  Copyright (C) 2015 by Yixiao Li
$ 
$   The above copyright holders grant permission gratis to use,
$   duplicate, modify, or redistribute (hereafter called use) this
$   software (including the one made by modifying this software),
$   provided that the following four conditions (1) through (4) are
$   satisfied.
$ 
$   (1) When this software is used in the form of source code, the above
$       copyright notice, this use conditions, and the disclaimer shown
$       below must be retained in the source code without modification.
$ 
$   (2) When this software is redistributed in the forms usable for the
$       development of other software, such as in library form, the above
$       copyright notice, this use conditions, and the disclaimer shown
$       below must be shown without modification in the document provided
$       with the redistributed software, such as the user manual.
$ 
$   (3) When this software is redistributed in the forms unusable for the
$       development of other software, such as the case when the software
$       is embedded in a piece of equipment, either of the following two
$       conditions must be satisfied:
$ 
$     (a) The above copyright notice, this use conditions, and the
$         disclaimer shown below must be shown without modification in
$         the document provided with the redistributed software, such as
$         the user manual.
$ 
$     (b) How the software is to be redistributed must be reported to the
$         TOPPERS Project according to the procedure described
$         separately.
$ 
$   (4) The above copyright holders and the TOPPERS Project are exempt
$       from responsibility for any type of damage directly or indirectly
$       caused from the use of this software and are indemnified by any
$       users or end users of this software from any and all causes of
$       action whatsoever.
$ 
$   THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
$   THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
$   INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
$   PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
$   TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
$   INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
$ =====================================================================

$INCLUDE "kernel/genoffset.tf"$

$DEFINE("PCB_p_runtsk", offsetof_PCB_p_runtsk)$
$DEFINE("PCB_p_schedtsk", offsetof_PCB_p_schedtsk)$
$DEFINE("PCB_dspflg", offsetof_PCB_dspflg)$
$DEFINE("PCB_reqflg", offsetof_PCB_reqflg)$
$DEFINE("PCB_excpt_nest_count", offsetof_PCB_excpt_nest_count)$
$DEFINE("PCB_istkpt", offsetof_PCB_istkpt)$
$DEFINE("PCB_p_inh_tbl", offsetof_PCB_p_inh_tbl)$
$DEFINE("TCB_p_tinib", offsetof_TCB_p_tinib)$
$DEFINE("TCB_sp", offsetof_TCB_sp)$
$DEFINE("TCB_pc", offsetof_TCB_pc)$
$DEFINE("TCB_task_queue", offsetof_TCB_task_queue)$
$DEFINE("TINIB_exinf", offsetof_TINIB_exinf)$
$DEFINE("TINIB_task", offsetof_TINIB_task)$
