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

$
$ Valid interrupt numbers and priorities
$ TODO: this is just for debugging
$
$INTNO_VALID_LOCAL = { 0,1,...,42 }$
$INTNO_VALID = { }$
$FOREACH prcid RANGE(1, TNUM_PRCID)$
    $upper_word = prcid << 16$ 
    $FOREACH intno INTNO_VALID_LOCAL$
        $INTNO_VALID = APPEND(INTNO_VALID, upper_word | intno)$
    $END$
$END$
$INTNO_CFGINT_VALID = INTNO_VALID$
$ INTNO_CFGINT_VALID = { 0,1,...,42 } 
$ INTPRI_CFGINT_VALID = { -1,-2,...,-15 }
$INTPRI_CFGINT_VALID = { -1 }$
$INHNO_DEFINH_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INTNO_CFGINT_VALID$
$INTNO_ATTISR_VALID = INTNO_CFGINT_VALID$

$
$ Functions for affinity
$

$
$ GET_AFFINITY_INI(prcid)
$ Get an AFFINITY_MASK from a processor ID
$
$FUNCTION GET_AFFINITY_INI$
    $RESULT = ""$
    $FOREACH slice RANGE(1, AFFINITY_MASK_SLICE_NUM)$
        $relative_prcid = ARGV[1] - (slice - 1) * AFFINITY_MASK_SLICE_BITS$
        $IF relative_prcid > 0 && relative_prcid <= AFFINITY_MASK_SLICE_BITS$
            $RESULT = CONCAT(RESULT, FORMAT("0x%x;", 1 << (relative_prcid - 1)))$
        $ELSE$
            $RESULT = CONCAT(RESULT, "0x0;")$
        $END$
    $END$
$END$

$
$ AFFINITY_MASK_TO_C_CODE
$ Get code of AFFINITY_MASK which can be used as an initial value
$
$FUNCTION AFFINITY_MASK_TO_C_CODE$
$ TODO: this ';' -> ',' conversion is just to ensure illegal C code be generated if not calling this function, for debug purpose
    $RESULT = REGEX_REPLACE(FORMAT("{ %s }", ARGV[1]), ";", ",")$
$END$

$
$ Generate CLASS_AFFINITY_INI and CLASS_AFFINITY_MASK
$ Only CLASS IDs for each processor are supported,
$ and CLASS_AFFINITY_MASKs mask nothing currently.
$
$FOREACH prcid RANGE(1, TNUM_PRCID)$
    $CLASS_AFFINITY_INI[prcid] = prcid$
$ TODO: CLASS_AFFINITY_MASK is just dummy currently (should generated from TNUM_PRCID)
    $CLASS_AFFINITY_MASK[prcid] = "0xFFFFFFFF;0xFFFFFFFF;"$
$END$
$NUM_CLASS = TNUM_PRCID$

$
$ Generate data structures for optimization
$

$ Optimization method 1: small page-aligned
$IF OPTIMIZE_PAGE_TABLE == 1$
$FUNCTION GENERATE_TSKSTK$
static STK_T _kernel_stack_$ARGV[1]$[COUNT_STK_T($TSK.STKSZ[ARGV[1]]$)] __attribute__ ((aligned (HV_PAGE_SIZE_SMALL)));$NL$
$END$
$FUNCTION GENERATE_PCB$
PCB _kernel_prc$ARGV[1]$_pcb __attribute__ ((aligned (HV_PAGE_SIZE_SMALL)));$NL$
$END$
$FUNCTION GENERATE_ISTACK$
static STK_T _kernel_prc$ARGV[1]$_istack[COUNT_STK_T(DEFAULT_PRC$ARGV[1]$_ISTKSZ)] __attribute__ ((aligned (HV_PAGE_SIZE_SMALL)));$NL$
$END$
$FUNCTION GENERATE_TCB$
TCB _kernel_tcb_$ARGV[1]$;$NL$
$END$
$END$

$ Optimization method 2: section merge
$IF OPTIMIZE_PAGE_TABLE == 2$
$FUNCTION GENERATE_TSKSTK$
static STK_T _kernel_stack_$ARGV[1]$[COUNT_STK_T($TSK.STKSZ[ARGV[1]]$)] __attribute__ ((section(".local_cached_prc$CLASS_AFFINITY_INI[TSK.CLASS[ARGV[1]]]$.stack")));$NL$
$END$
$FUNCTION GENERATE_PCB$
PCB _kernel_prc$ARGV[1]$_pcb __attribute__ ((section(".local_cached_prc$ARGV[1]$.bss")));$NL$
$END$
$FUNCTION GENERATE_ISTACK$
static STK_T _kernel_prc$ARGV[1]$_istack[COUNT_STK_T(DEFAULT_PRC$ARGV[1]$_ISTKSZ)] __attribute__ ((section(".local_cached_prc$ARGV[1]$.stack")));$NL$
$END$
$FUNCTION GENERATE_TCB$
$ TCB _kernel_tcb_$ARGV[1]$ __attribute__ ((section(".local_cached_prc$CLASS_AFFINITY_INI[TSK.CLASS[ARGV[1]]]$.bss")));$NL$
TCB _kernel_tcb_$ARGV[1]$;$NL$
$END$
$END$

$INCLUDE "kernel/kernel.tf"$

$ Optimization method 2: section merge
$IF OPTIMIZE_PAGE_TABLE == 2$
$FOREACH prcid RANGE(1, TNUM_PRCID)$
extern void *_local_cached_prc$prcid$_bss_start;$NL$
extern void *_local_cached_prc$prcid$_bss_end;$NL$
$END$
void *_local_cached_prc_bss_start_table[TNUM_PRCID] = {
$FOREACH prcid RANGE(1, TNUM_PRCID)$
&_local_cached_prc$prcid$_bss_start,$NL$
$END$
};
void *_local_cached_prc_bss_end_table[TNUM_PRCID] = {
$FOREACH prcid RANGE(1, TNUM_PRCID)$
&_local_cached_prc$prcid$_bss_end,$NL$
$END$
};
$END$

$
$ Generate interrupt handle table (inh_table)
$

$FOREACH prcid RANGE(1, TNUM_PRCID)$

const FP _kernel_prc$prcid$_inh_table[TNUM_INH] = {$NL$
$FOREACH inhno RANGE(0, (TNUM_INH - 1))$
    $minhno = inhno | (prcid << intno_cpu_shift)$
    $IF LENGTH(INH.INHNO[inhno]) && (CLASS_AFFINITY_INI[INH.CLASS[inhno]] == prcid)$
        $TAB$(FP)($INH.INTHDR[inhno]$),
    $ELSE$
        $IF LENGTH(INH.INHNO[minhno]) && (CLASS_AFFINITY_INI[INH.CLASS[minhno]] == prcid)$
            $TAB$(FP)($INH.INTHDR[minhno]$),
        $ELSE$
            $TAB$(FP)(_kernel_default_int_handler),
        $END$
    $END$
    $SPC$$FORMAT("/* 0x%x */", +minhno)$$NL$
$END$
};$NL$
$NL$

$END$$NL$

$ 
$ Generate interrupt handle access table (p_inh_table)
$
const FP* const _kernel_p_inh_table[TNUM_PRCID] = {$NL$
$JOINEACH prcid RANGE(1, TNUM_PRCID) ",\n"$
    $TAB$_kernel_prc$prcid$_inh_table
$END$
$NL$};$NL$
$NL$

$
$ Generate TLV resource file
$
$ $INCLUDE"arch/logtrace/tlv.tf"$

$
$ Generate hypervisor configuration file (fmp.hvc)
$
$INCLUDE "arch_hvc.tf"$
