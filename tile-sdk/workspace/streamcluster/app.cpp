
/**
 * TOPPERS/FMP Kernel
 *
 * Copyright (C) 2016 by Yixiao Li (liyixiao@ertl.jp)
 *
 *  The above copyright holders grant permission gratis to use,
 *  duplicate, modify, or redistribute (hereafter called use) this
 *  software (including the one made by modifying this software),
 *  provided that the following four conditions (1) through (4) are
 *  satisfied.
 *
 *  (1) When this software is used in the form of source code, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be retained in the source code without modification.
 *
 *  (2) When this software is redistributed in the forms usable for the
 *      development of other software, such as in library form, the above
 *      copyright notice, this use conditions, and the disclaimer shown
 *      below must be shown without modification in the document provided
 *      with the redistributed software, such as the user manual.
 *
 *  (3) When this software is redistributed in the forms unusable for the
 *      development of other software, such as the case when the software
 *      is embedded in a piece of equipment, either of the following two
 *      conditions must be satisfied:
 *
 *    (a) The above copyright notice, this use conditions, and the
 *        disclaimer shown below must be shown without modification in
 *        the document provided with the redistributed software, such as
 *        the user manual.
 *
 *    (b) How the software is to be redistributed must be reported to the
 *        TOPPERS Project according to the procedure described
 *        separately.
 *
 *  (4) The above copyright holders and the TOPPERS Project are exempt
 *      from responsibility for any type of damage directly or indirectly
 *      caused from the use of this software and are indemnified by any
 *      users or end users of this software from any and all causes of
 *      action whatsoever.
 *
 *  THIS SOFTWARE IS PROVIDED "AS IS." THE ABOVE COPYRIGHT HOLDERS AND
 *  THE TOPPERS PROJECT DISCLAIM ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, ITS APPLICABILITY TO A PARTICULAR
 *  PURPOSE. IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS AND THE
 *  TOPPERS PROJECT BE LIABLE FOR ANY TYPE OF DAMAGE DIRECTLY OR
 *  INDIRECTLY CAUSED FROM THE USE OF THIS SOFTWARE.
 */

extern "C" {
#include "app.h"
#include "parsec-helper.h"
#include <stdio.h>
#include <string.h>
}

void main_task(intptr_t exinf) {
	// Prepare arguments
	char nthreads[10];
    char *argv[] = { "streamcluster",
#if defined(TEST_RUNCONF)  // test.runconf
    		"2", "5", "1", "10", "10", "5",
#elif defined(SIMSMALL_RUNCONF) // simsmall.runconf
    		"10", "20", "32", "4096", "4096", "1000",
#elif defined(SIMMEDIUM_RUNCONF) // simmedium.runconf
    		"10", "20", "64", "8192", "8192", "1000",
#elif defined(SIMLARGE_RUNCONF) // simlarge.runconf
    		"10", "20", "128", "16384", "16384", "1000",
#elif defined(NATIVE_RUNCONF) || 1 // native.runconf
    		"10", "20", "128", "1000000", "200000", "5000",
#else
#error Must specify runconf!
#endif
    		"none", "output.txt", nthreads };

    int argc = sizeof(argv) / sizeof(argv[0]);

    // Run PARSEC application
    run_parsec_app(argc, argv, nthreads);
}

#if 0 // Legacy code

extern "C" {
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include <sil.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "app.h"

extern void my_ramfs_init();
extern void my_pthread_reset();
extern void debug_loop();
extern void raise_int();
extern void TOPPERS_assert_abort();
extern void hv_power_off();
}

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

static uint_t counter;

/*
 *  グローバル初期化ルーチン
 */
void
global_inirtn(intptr_t exinf)
{
	counter = 1;
}

/*
 *  グローバル終了ルーチン
 */
void
global_terrtn(intptr_t exinf)
{
	syslog(LOG_EMERG, "global_terrtn exinf = %d, counter = %d", exinf, counter++);
}

/*
 *  ローカル初期化ルーチン
 */
void
local_inirtn(intptr_t exinf)
{
	extern void raise_int();
	syslog(LOG_NOTICE, "local_inirtn exinf = %d, counter = %d", exinf, counter++);
	raise_int();
}

/*
 *  ローカル終了ルーチン
 */
void
local_terrtn(intptr_t exinf)
{
	syslog(LOG_NOTICE, "local_terrtn exinf = %d, counter = %d", exinf, counter++);
}

int pthread_mutexattr_init(void *attr) {
	syslog(LOG_EMERG, "DUMMY: %s() called.", __FUNCTION__);
    //debug_loop();
}

#include "stdio.h"
#include <stdarg.h>

int
printf(const char *format, ...)
{
	SYSLOG	syslog;
	va_list	ap;
	uint_t	i;
	char	c;
	bool_t	lflag;

	syslog.logtype = LOG_TYPE_COMMENT;
	syslog.loginfo[0] = (intptr_t) format;
	i = 1U;
	va_start(ap, format);

	while ((c = *format++) != '\0' && i < TMAX_LOGINFO) {
		if (c != '%') {
			continue;
		}

		lflag = false;
		c = *format++;
		while ('0' <= c && c <= '9') {
			c = *format++;
		}
		if (c == 'l') {
			lflag = true;
			c = *format++;
		}
		switch (c) {
		case 'd':
			syslog.loginfo[i++] = lflag ? (intptr_t) va_arg(ap, long_t)
										: (intptr_t) va_arg(ap, int_t);
			break;
		case 'u':
		case 'x':
		case 'X':
			syslog.loginfo[i++] = lflag ? (intptr_t) va_arg(ap, ulong_t)
										: (intptr_t) va_arg(ap, uint_t);
			break;
		case 'p':
			syslog.loginfo[i++] = (intptr_t) va_arg(ap, void *);
			break;
		case 'c':
			syslog.loginfo[i++] = (intptr_t) va_arg(ap, int);
			break;
		case 's':
			syslog.loginfo[i++] = (intptr_t) va_arg(ap, const char *);
			break;
		case '\0':
			format--;
			break;
		default:
			break;
		}
	}
	va_end(ap);
    int prio = LOG_NOTICE;
	(void) syslog_wri_log(prio, &syslog);
}

extern "C" {extern void posix_initialize();}

void rr_task(intptr_t unused) {

}

#include "hv/hypervisor.h"
#include "hv/pagesize.h"

/*
 *  メインタスク
 */

void main_task(intptr_t exinf)
{
	syslog(LOG_NOTICE, "HV_L0_ENTRIES=%d, HV_L1_ENTRIES=%d", HV_L0_ENTRIES, HV_L1_ENTRIES);

	posix_initialize();
	my_ramfs_init();
    extern int main (int argc, char **argv);
    int argc = 10;
    char cores_str[3] = "01";
    char *argv[] = { "streamcluster",
#if defined(TEST_RUNCONF)   // test.runconf
    		"2", "5", "1", "10", "10", "5",
#elif defined(SIMSMALL_RUNCONF) // simsmall.runconf
    		"10", "20", "32", "4096", "4096", "1000",
#elif defined(SIMMEDIUM_RUNCONF) // simmedium.runconf
    		"10", "20", "64", "8192", "8192", "1000",
#elif defined(SIMLARGE_RUNCONF) // simlarge.runconf
    		"10", "20", "128", "16384", "16384", "1000",
#elif defined(NATIVE_RUNCONF) || 1 // native.runconf
    		"10", "20", "128", "1000000", "200000", "5000",
#else
#error Must specify runconf!
#endif
    		"none", "output.txt", cores_str };
#define TMIN_THREADS (36)  // TODO: only one setup is allowed, to make sure DATA is clean!
#define TMAX_THREADS (36)
//#define TMIN_THREADS 1
//#define TMAX_THREADS TNUM_PRCID
    for (int threads = TMIN_THREADS; threads <= TMAX_THREADS; ++threads) {
    	cores_str[0] = '0' + (threads / 10);
    	cores_str[1] = '0' + (threads % 10);
    	syslog(LOG_EMERG, "Application start, %d threads used.", threads);
    	uint64_t cycle_counter = __insn_mfspr(SPR_CYCLE);
    	main(argc, argv);
    	cycle_counter = __insn_mfspr(SPR_CYCLE) - cycle_counter;
    	syslog(LOG_EMERG, "Application terminated, %d threads used, %lu cycles, %d ms.", threads, cycle_counter, cycle_counter / 1200000 /* hv_sysconf(HV_SYSCONF_CPU_SPEED) */);
    }
	//syslog(LOG_NOTICE, "Call write().");
    //read(0x1234, 0x5678, 0xabcd);
#if 1
    {
        const char *filename = "output.txt";
        syslog(LOG_EMERG, "====== DUMP %s ======", filename);
        char buf[1024];
        FILE *file = fopen(filename, "r");
        while (fgets(buf, sizeof(buf), file) != NULL) {
            syslog(LOG_EMERG, "%s", buf);
        }
        fclose(file);
    }
#endif
	syslog(LOG_EMERG, "Sample program ends.");
	SVC_PERROR(ext_ker());
	//assert(0);
}

extern "C" {



void *mem_uncached;
void *mem_cache_no_l3;
void *mem_cache_hash_l3;
void *mem_cache_tile_l3;

void* uma_gen_l1_page_table(int l0index) {
	static HV_PTE l1_page_table[HV_L1_ENTRIES] __attribute__((aligned(HV_PAGE_TABLE_ALIGN)));
#if 1
	HV_PTE l1_pte = hv_pte(0
			|HV_PTE_PRESENT
			|HV_PTE_PAGE
			|HV_PTE_GLOBAL
			//|HV_PTE_USER
//			|HV_PTE_ACCESSED // TODO: check this
//			|HV_PTE_DIRTY
			//|HV_PTE_CLIENT0
			//|HV_PTE_CLIENT1
			//|HV_PTE_CLIENT2
			//|HV_PTE_NC
			//|HV_PTE_NO_ALLOC_L1
			//|HV_PTE_NO_ALLOC_L2
			//|HV_PTE_CACHED_PRIORITY // TODO: check this
			|HV_PTE_READABLE
			|HV_PTE_WRITABLE
			|HV_PTE_EXECUTABLE
			);

	mem_uncached = (void*)(HV_L1_SPAN * l0index + HV_PAGE_SIZE_LARGE * 0);
	l1_pte = hv_pte_set_mode(l1_pte, HV_PTE_MODE_UNCACHED);
	l1_pte = hv_pte_set_pa(l1_pte, (HV_PhysAddr)mem_uncached);
	l1_page_table[0] = l1_pte;

	mem_cache_no_l3 = (void*)(HV_L1_SPAN * l0index + HV_PAGE_SIZE_LARGE * 1);
	l1_pte = hv_pte_set_mode(l1_pte, HV_PTE_MODE_CACHE_NO_L3);
	l1_pte = hv_pte_set_pa(l1_pte, (HV_PhysAddr)mem_cache_no_l3);
	l1_page_table[1] = l1_pte;

	mem_cache_hash_l3 = (void*)(HV_L1_SPAN * l0index + HV_PAGE_SIZE_LARGE * 2);
//	l1_pte = hv_pte_set_mode(l1_pte, HV_PTE_MODE_CACHE_HASH_L3);
	l1_pte = hv_pte_set_mode(l1_pte,
//			HV_PTE_MODE_UNCACHED
//			HV_PTE_MODE_CACHE_NO_L3
			HV_PTE_MODE_CACHE_TILE_L3
			//HV_PTE_MODE_CACHE_HASH_L3
			//HV_PTE_MODE_MMIO
			);
	l1_pte = hv_pte_set_lotar(l1_pte, HV_XY_TO_LOTAR(0, 0));
	l1_pte = hv_pte_set_pa(l1_pte, (HV_PhysAddr)mem_cache_hash_l3);
	l1_page_table[2] = l1_pte;

	mem_cache_tile_l3 = (void*)(HV_L1_SPAN * l0index + HV_PAGE_SIZE_LARGE * 3);
	l1_pte = hv_pte_set_mode(l1_pte,
//			HV_PTE_MODE_UNCACHED
//			HV_PTE_MODE_CACHE_NO_L3
			HV_PTE_MODE_CACHE_TILE_L3
			//HV_PTE_MODE_CACHE_HASH_L3
			//HV_PTE_MODE_MMIO
			);
	l1_pte = hv_pte_set_lotar(l1_pte, HV_XY_TO_LOTAR(TILEGX_CLIENT_WD - 1, TILEGX_CLIENT_HT - 1));
	l1_pte = hv_pte_set_pa(l1_pte, (HV_PhysAddr)mem_cache_tile_l3);

	l1_page_table[3] = l1_pte;
#endif
	return l1_page_table;
}

}

#endif

