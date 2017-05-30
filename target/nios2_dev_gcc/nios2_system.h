/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2009 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: nios2_system.h 451 2009-10-19 08:50:43Z ertl-honda $
 */

/*
 *  NIOS2�����ƥ�����
 *
 *  �ڥ�ե����Υ��ɥ쥹�������ֹ���������
 */

#ifndef TOPPERS_NIOS2_SYSTEM_H
#define TOPPERS_NIOS2_SYSTEM_H

#ifdef TOPPERS_NIOS2_DEV_1S40

/*
 *  �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif  /* TNUM_PRCID */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK     50000U

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    230
#define SIL_DLY_TIM2     70

/*
 *  �󥿥�������ƥ������ѤΥ����å������������
 */
#define DEFAULT_PRC1_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC2_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC3_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC4_ISTKSZ    (0x1000U)  /* 4Kbyte */

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN   4

/*
 *  �ǡ������������ν������Ԥʤ�ʤ�
 */
#define NIOS2_OMIT_DATA_INIT

/*
 *  Interrupt Vector Instruction ̿������
 */
#define NIOS2_USE_INT_VEC_INST       /* Interrupt Vector Instruction ��Ȥ� */
#define NIOS2_INT_VEC_INST_NO    0   /* ̿���ֹ�                            */

/*
 *  ����å��奵����
 */
#define NIOS2_ICACHE_SIZE       0x1000  /* 4kbyte */
#define NIOS2_ICACHE_LINE_SIZE  0x0010  /* 32byte */
#define NIOS2_DCACHE_SIZE       0x0000
#define NIOS2_DCACHE_LINE_SIZE 

/*
 *  �ڥ�ե����Υ١������ɥ쥹
 */
#define CPU_1_PERI_BASEADDR  0x01000000
#define CPU_2_PERI_BASEADDR  0x02000000
#define CPU_3_PERI_BASEADDR  0x03000000
#define CPU_4_PERI_BASEADDR  0x04000000

/*
 *  Interval Timer
 */
#define SYS_CLK_TIMER_1_BASE (0x00000840 + CPU_1_PERI_BASEADDR)
#define SYS_CLK_TIMER_2_BASE (0x00000840 + CPU_2_PERI_BASEADDR)
#define SYS_CLK_TIMER_3_BASE (0x00000840 + CPU_3_PERI_BASEADDR)
#define SYS_CLK_TIMER_4_BASE (0x00000840 + CPU_4_PERI_BASEADDR)

#define SYS_CLK_TIMER_1_INT   0U
#define SYS_CLK_TIMER_2_INT   0U
#define SYS_CLK_TIMER_3_INT   0U
#define SYS_CLK_TIMER_4_INT   0U

/*
 *  JTAG UART
 */
#define JTAG_UART_1_BASE (0x00000860 + CPU_1_PERI_BASEADDR)
#define JTAG_UART_2_BASE (0x00000860 + CPU_2_PERI_BASEADDR)
#define JTAG_UART_3_BASE (0x00000860 + CPU_3_PERI_BASEADDR)
#define JTAG_UART_4_BASE (0x00000860 + CPU_4_PERI_BASEADDR)

#define JTAG_UART_1_INT   1U
#define JTAG_UART_2_INT   1U
#define JTAG_UART_3_INT   1U
#define JTAG_UART_4_INT   1U

/*
 *  Mutex
 */ 
#define TSK_MUTEX_1_BASE   (0x00000810 + CPU_1_PERI_BASEADDR)
#define OBJ_MUTEX_1_BASE   (0x00000820 + CPU_1_PERI_BASEADDR)
#define TSK_MUTEX_2_BASE   (0x00000810 + CPU_2_PERI_BASEADDR)
#define OBJ_MUTEX_2_BASE   (0x00000820 + CPU_2_PERI_BASEADDR)
#define TSK_MUTEX_3_BASE   (0x00000810 + CPU_3_PERI_BASEADDR)
#define OBJ_MUTEX_3_BASE   (0x00000820 + CPU_3_PERI_BASEADDR)
#define TSK_MUTEX_4_BASE   (0x00000810 + CPU_4_PERI_BASEADDR)
#define OBJ_MUTEX_4_BASE   (0x00000820 + CPU_4_PERI_BASEADDR)

/*
 * �ץ��å��ֳ�����HW
 */
#define PRC_INT_1_BASE  (0x00000800 + CPU_1_PERI_BASEADDR)
#define PRC_INT_2_BASE  (0x00000800 + CPU_2_PERI_BASEADDR)
#define PRC_INT_3_BASE  (0x00000800 + CPU_3_PERI_BASEADDR)
#define PRC_INT_4_BASE  (0x00000800 + CPU_4_PERI_BASEADDR)

#define PRC_INT_INT     2U

/*
 * SYSVER
 */
#define SYSVER_REG1 0x07110200
#define SYSVER_REG2 0x07110204
#define SYSVER_REG3 0x07110208
#define SYSVER_REG4 0x0711020C
#define SYSVER_REG5 0x07110210
#define SYSVER_REG6 0x07110214
#define SYSVER_REG7 0x07110218
#define SYSVER_REG8 0x0711021C

/*
 *  Performance Couter
 */
#define PERF_COUNTER_BASE 0x07110100

/*
 *  Performance Counter �Υ���å�
 */
#define PERF_COUNTER_CLOCK     50U

#elif defined(TOPPERS_NIOS2_DEV_3C25)

/*
 *  �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK     50000U

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    230
#define SIL_DLY_TIM2     70

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN   4

/*
 *  �󥿥�������ƥ������ѤΥ����å������������
 */
#define DEFAULT_PRC1_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC2_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC3_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC4_ISTKSZ    (0x1000U)  /* 4Kbyte */

/*
 *  �ǡ������������ν������Ԥʤ�ʤ�
 */
#define NIOS2_OMIT_DATA_INIT

/*
 *  Interrupt Vector Instruction ̿������
 */
#define NIOS2_USE_INT_VEC_INST       /* Interrupt Vector Instruction ��Ȥ� */
#define NIOS2_INT_VEC_INST_NO    0   /* ̿���ֹ�                            */

/*
 *  ����å��奵����
 */
#define NIOS2_ICACHE_SIZE       0x1000  /* 4kbyte */
#define NIOS2_ICACHE_LINE_SIZE  0x0010  /* 32byte */
#define NIOS2_DCACHE_SIZE       0x0000
#define NIOS2_DCACHE_LINE_SIZE 

/*
 *  �ڥ�ե����Υ١������ɥ쥹
 */
#define CPU_1_PERI_BASEADDR  0x02000000
#define CPU_2_PERI_BASEADDR  0x03000000

/*
 *  Interval Timer
 */
#define SYS_CLK_TIMER_1_BASE (0x00000800 + CPU_1_PERI_BASEADDR)
#define SYS_CLK_TIMER_2_BASE (0x00000800 + CPU_2_PERI_BASEADDR)

#define SYS_CLK_TIMER_1_INT   0U
#define SYS_CLK_TIMER_2_INT   0U

/*
 *  JTAG UART
 */
#define JTAG_UART_1_BASE (0x00000820 + CPU_1_PERI_BASEADDR)
#define JTAG_UART_2_BASE (0x00000820 + CPU_2_PERI_BASEADDR)

#define JTAG_UART_1_INT   1U
#define JTAG_UART_2_INT   1U

/*
 *  Mutex
 */
#define TSK_MUTEX_1_BASE   (0x00000830 + CPU_1_PERI_BASEADDR)
#define OBJ_MUTEX_1_BASE   (0x00000840 + CPU_1_PERI_BASEADDR)
#define TSK_MUTEX_2_BASE   (0x00000830 + CPU_2_PERI_BASEADDR)
#define OBJ_MUTEX_2_BASE   (0x00000840 + CPU_2_PERI_BASEADDR)

/*
 * �ץ��å��ֳ�����HW
 */
#define PRC_INT_1_BASE  (0x00000850 + CPU_1_PERI_BASEADDR)
#define PRC_INT_2_BASE  (0x00000850 + CPU_2_PERI_BASEADDR)

#define PRC_INT_1_INT   2U
#define PRC_INT_2_INT   2U

/*
 * SYSVER
 */
#define SYSVER_REG1 0x08000200
#define SYSVER_REG2 0x08000204
#define SYSVER_REG3 0x08000208
#define SYSVER_REG4 0x0800020C
#define SYSVER_REG5 0x08000210
#define SYSVER_REG6 0x08000214
#define SYSVER_REG7 0x08000218
#define SYSVER_REG8 0x0800021C

#elif defined(TOPPERS_NIOS2_DEV_3C120)

/*
 *  �ץ��å���
 */
#ifndef TNUM_PRCID
#define TNUM_PRCID  2
#endif /* TNUM_PRCID */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK     50000U

/*
 *  ���������Ԥ��Τ��������������SIL�Υ������åȰ�¸����
 */
#define SIL_DLY_TIM1    230
#define SIL_DLY_TIM2     70

/*
 *  �󥿥�������ƥ������ѤΥ����å������������
 */
#define DEFAULT_PRC1_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC2_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC3_ISTKSZ    (0x1000U)  /* 4Kbyte */
#define DEFAULT_PRC4_ISTKSZ    (0x1000U)  /* 4Kbyte */

/*
 *  �ͥ��ƥ��֥��ԥ������ξ��Υ��ԥ��å��κ����
 */
#define TMAX_NATIVE_SPN   4

/*
 *  �ǡ������������ν������Ԥʤ�ʤ�
 */
#define NIOS2_OMIT_DATA_INIT

/*
 *  Interrupt Vector Instruction ̿������
 */
#define NIOS2_USE_INT_VEC_INST       /* Interrupt Vector Instruction ��Ȥ� */
#define NIOS2_INT_VEC_INST_NO    0   /* ̿���ֹ�                            */

/*
 *  ����å��奵����
 */
#define NIOS2_ICACHE_SIZE       0x1000  /* 4kbyte */
#define NIOS2_ICACHE_LINE_SIZE  0x0010  /* 32byte */
#define NIOS2_DCACHE_SIZE       0x0000
#define NIOS2_DCACHE_LINE_SIZE 

/*
 *  �ڥ�ե����Υ١������ɥ쥹
 */
#define CPU_1_PERI_BASEADDR  0x01000000
#define CPU_2_PERI_BASEADDR  0x02000000
#define CPU_3_PERI_BASEADDR  0x03000000
#define CPU_4_PERI_BASEADDR  0x04000000

/*
 *  Interval Timer
 */
#define SYS_CLK_TIMER_1_BASE (0x00000800 + CPU_1_PERI_BASEADDR)
#define SYS_CLK_TIMER_2_BASE (0x00000800 + CPU_2_PERI_BASEADDR)
#define SYS_CLK_TIMER_3_BASE (0x00000800 + CPU_3_PERI_BASEADDR)
#define SYS_CLK_TIMER_4_BASE (0x00000800 + CPU_4_PERI_BASEADDR)

#define SYS_CLK_TIMER_1_INT   0U
#define SYS_CLK_TIMER_2_INT   0U
#define SYS_CLK_TIMER_3_INT   0U
#define SYS_CLK_TIMER_4_INT   0U

/*
 *  JTAG UART
 */
#define JTAG_UART_1_BASE (0x00000900 + CPU_1_PERI_BASEADDR)
#define JTAG_UART_2_BASE (0x00000900 + CPU_2_PERI_BASEADDR)
#define JTAG_UART_3_BASE (0x00000900 + CPU_3_PERI_BASEADDR)
#define JTAG_UART_4_BASE (0x00000900 + CPU_4_PERI_BASEADDR)

#define JTAG_UART_1_INT   1U
#define JTAG_UART_2_INT   1U
#define JTAG_UART_3_INT   1U
#define JTAG_UART_4_INT   1U

/*
 *  Mutex
 */
#define TSK_MUTEX_1_BASE   (0x00000a00 + CPU_1_PERI_BASEADDR)
#define OBJ_MUTEX_1_BASE   (0x00000b00 + CPU_1_PERI_BASEADDR)
#define TSK_MUTEX_2_BASE   (0x00000a00 + CPU_2_PERI_BASEADDR)
#define OBJ_MUTEX_2_BASE   (0x00000b00 + CPU_2_PERI_BASEADDR)
#define TSK_MUTEX_3_BASE   (0x00000a00 + CPU_3_PERI_BASEADDR)
#define OBJ_MUTEX_3_BASE   (0x00000b00 + CPU_3_PERI_BASEADDR)
#define TSK_MUTEX_4_BASE   (0x00000a00 + CPU_4_PERI_BASEADDR)
#define OBJ_MUTEX_4_BASE   (0x00000b00 + CPU_4_PERI_BASEADDR)

/*
 * �ץ��å��ֳ�����HW
 */
#define PRC_INT_1_BASE  (0x00000c00 + CPU_1_PERI_BASEADDR)
#define PRC_INT_2_BASE  (0x00000c00 + CPU_2_PERI_BASEADDR)
#define PRC_INT_3_BASE  (0x00000c00 + CPU_3_PERI_BASEADDR)
#define PRC_INT_4_BASE  (0x00000c00 + CPU_4_PERI_BASEADDR)

#define PRC_INT_1_INT   2U
#define PRC_INT_2_INT   2U
#define PRC_INT_3_INT   2U
#define PRC_INT_4_INT   2U

/*
 * SYSVER
 */
#define SYSVER_REG1 0x0c021100
#define SYSVER_REG2 0x0c021104
#define SYSVER_REG3 0x0c021108
#define SYSVER_REG4 0x0c02110c
#define SYSVER_REG5 0x0c021110
#define SYSVER_REG6 0x0c021114
#define SYSVER_REG7 0x0c021118
#define SYSVER_REG8 0x0c02111c

#endif /* TOPPERS_NIOS2_DEV_3C120 */

#endif /* TOPPERS_NIOS2_SYSTEM_H */
