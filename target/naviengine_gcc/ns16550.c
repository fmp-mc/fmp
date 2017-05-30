/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel    
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: ns16550.c 884 2012-01-11 06:43:38Z ertl-honda $
 */

/*
 *     ST16C2550 �� �ʰ�SIO�ɥ饤��
 */

#include <sil.h>
#include "target_syssvc.h"
#include "ns16550.h"

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_RDY_SND	1U		/* ������ǽ������Хå� */
#define SIO_RDY_RCV	2U		/* �������Υ�����Хå� */

/*
 * �ƥ쥸�����Υ��ե��å�
 */
#define NS16550_RHR   0x00   /* B  LCR bit7=0 Read  */
#define NS16550_THR   0x00   /* B  LCR bit7=0 Write */
#define NS16550_DLL   0x00   /* B  LCR bit7=1       */
#define NS16550_IER   0x04   /* B  LCR bit7=0       */
#define NS16550_DLM   0x04   /* B  LCR bit7=1       */
#define NS16550_IIR   0x08   /* B  Read  */
#define	NS16550_LCR   0x0c   /* B  */
#define NS16550_MCR   0x10   /* B  */
#define NS16550_LSR   0x14   /* B  Read */
#define NS16550_MSR   0x18   /* B  Read */
#define NS16550_SCR   0x1c   /* B  */
#define NS16550_FCR   0x20   /* B  Write */

#define IIR_TX            0x02       /* ����������ȯ�� */
#define IER_TX            0x02       /* ���������ߵ��� */
#define IIR_RX            0x01       /* ����������ȯ�� */
#define IER_RX            0x01       /* ���������ߵ��� */


#define LCR_DL_MODE       0x80       /* Divisor Enable */
#define LCR_VAL           0x03       /* 8bit,1stop,Noparity,No break */
#define FCR_FIFO_DISABLE  0x00
#define FCR_FIFO_ENABLE   0x01

#define LSR_RX_DATA_READY 0x01
#define LSR_TX_EMPTY      0x20


/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
    uint32_t reg_base;    /* �쥸�����Υ١������ɥ쥹 */
    uint8_t  lcr_val;     /* �⡼�ɥ쥸������������   */
    uint8_t  dlm_val;     /* �ܡ��졼�Ⱦ�̤�������   */
    uint8_t  dll_val;     /* �ܡ��졼�Ȳ��̤�������   */
    uint8_t intno;        /* ������ֹ� */
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
    const SIOPINIB  *p_siopinib; /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
    intptr_t         exinf;      /* ��ĥ���� */
    bool_t             openflag;   /* �����ץ�Ѥߥե饰 */
    bool_t             sendflag;   /* ��������ߥ��͡��֥�ե饰 */
    bool_t             getready;   /* ʸ��������������� */
    bool_t             putready;   /* ʸ���������Ǥ������ */
};


/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {
    {UART0_BASE, UART0_LCR_VAL, UART0_DLM_VAL, UART0_DLL_VAL, DIC_IRQNO_UART0},
#if TNUM_SIOP > 2
    {UART1_BASE, UART1_LCR_VAL, UART1_DLM_VAL, UART1_DLL_VAL, DIC_IRQNO_UART1},
#endif /* TNUM_SIOP > 2 */
#if TNUM_SIOP > 3
    {UART2_BASE, UART1_LCR_VAL, UART1_DLM_VAL, UART1_DLL_VAL, DIC_IRQNO_UART2},
#endif /* TNUM_SIOP > 3 */
#if TNUM_SIOP > 4
    {UART3_BASE, UART1_LCR_VAL, UART1_DLM_VAL, UART1_DLL_VAL, DIC_IRQNO_UART3},
#endif /* TNUM_SIOP > 4 */
};

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å��μ�Ф�
 */
#define INDEX_SIOPINIB(siopid)  ((uint_t)((siopid) - 1))
#define get_siopinib(siopid)  (&(siopinib_table[INDEX_SIOPINIB(siopid)]))

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB  siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((uint_t)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))

Inline void
ns16550_write(uint32_t addr, uint32_t offset, uint8_t val)
{
    sil_wrb_mem((void*)(addr + offset),val);
}

Inline uint8_t
ns16550_read(uint32_t addr, uint32_t offset)
{
    return(sil_reb_mem((void*)(addr + offset)));
}

/*
 * ʸ�������������?
 */ 
Inline bool_t
ns16550_getready(SIOPCB *p_siopcb)
{
    uint16_t status;

    status = ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_LSR);
    
    return((status & LSR_RX_DATA_READY));
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline bool_t
ns16550_putready(SIOPCB *p_siopcb)
{
    uint16_t status;

    status = ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_LSR);
    
    return (status & LSR_TX_EMPTY);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline uint8_t
ns16550_getchar(SIOPCB *p_siopcb)
{
    return(ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_RHR));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
ns16550_putchar(SIOPCB *p_siopcb, uint8_t c)
{
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_THR, c);
}

/*
 *  ��������ߵ���
 */
Inline void
ns16550_enable_send(SIOPCB *p_siopcb)
{
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_IER,
                (ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_IER) | IER_TX));
}

/*
 *  ��������߶ػ�
 */
Inline void
ns16550_disable_send(SIOPCB *p_siopcb)
{
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_IER,
                (ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_IER) & ~IER_TX));
                
}

/*
 *  ��������ߵ���
 */
Inline void
ns16550_enable_rcv(SIOPCB *p_siopcb)
{
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_IER,
                (ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_IER) | IER_RX));
}

/*
 *  ��������߶ػ�
 */
Inline void
ns16550_disable_rcv(SIOPCB *p_siopcb)
{
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_IER,
                (ns16550_read(p_siopcb->p_siopinib->reg_base, NS16550_IER) & ~IER_RX));
                
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
ns16550_initialize()
{
    SIOPCB  *p_siopcb;
    uint_t  i;

    /*
     *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
     */
    for (p_siopcb = siopcb_table, i = 0; i < TNUM_SIOP; p_siopcb++, i++) {
        p_siopcb->p_siopinib = &(siopinib_table[i]);
        p_siopcb->openflag = false;
        p_siopcb->sendflag = false;
    }    
}

    
/*
 * SIOPINIB�ν����
 */
void
ns16550_init_siopinib(const SIOPINIB *p_siopinib)
{
    /*
     *  ʬ���������
     */
    /* Divisor Enable */
    ns16550_write(p_siopinib->reg_base, NS16550_LCR,
                (ns16550_read(p_siopinib->reg_base, NS16550_LCR) | LCR_DL_MODE));
    ns16550_write(p_siopinib->reg_base, NS16550_DLL, p_siopinib->dll_val);
    ns16550_write(p_siopinib->reg_base, NS16550_DLM, p_siopinib->dlm_val);

    /* Divisor Disable */
    ns16550_write(p_siopinib->reg_base, NS16550_LCR,
                (ns16550_read(p_siopinib->reg_base, NS16550_LCR) & ~LCR_DL_MODE));

    /* �⡼������ */
    ns16550_write(p_siopinib->reg_base, NS16550_LCR, p_siopinib->lcr_val);

    /* FIFO Disable */
    ns16550_write(p_siopinib->reg_base, NS16550_FCR, FCR_FIFO_DISABLE);

    /* ����߶ػ� */
    ns16550_write(p_siopinib->reg_base, NS16550_IER, 0x00);
}


/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫?
 */
bool_t
ns16550_openflag(ID siopid)
{
	SIOPCB          *p_siopcb;

	p_siopcb = get_siopcb(siopid);

	return(p_siopcb->openflag);
}


/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
ns16550_opn_por(ID siopid, intptr_t exinf)
{
    SIOPCB      *p_siopcb;

    p_siopcb = get_siopcb(siopid);
    
    /*
     * �����
     */
    ns16550_init_siopinib(p_siopcb->p_siopinib);
    
    /* ��������߶ػ� */
    ns16550_enable_rcv(p_siopcb);
    /* ��������߶ػ� */
    ns16550_disable_rcv(p_siopcb);
    
    p_siopcb->exinf = exinf;
    p_siopcb->getready = p_siopcb->putready = false;
    p_siopcb->openflag = true;

    return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
ns16550_cls_por(SIOPCB *p_siopcb)
{
    /* ����߶ػ� */
    ns16550_write(p_siopcb->p_siopinib->reg_base, NS16550_IER, 0x00);   
    p_siopcb->openflag = false;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
ns16550_snd_chr(SIOPCB *p_siopcb, char_t c)
{
    if (ns16550_putready(p_siopcb)){
        ns16550_putchar(p_siopcb, c);
        return(true);
    }
    return(false);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int
ns16550_rcv_chr(SIOPCB *p_siopcb)
{
    if (ns16550_getready(p_siopcb)) {
        return((int)(uint8_t)ns16550_getchar(p_siopcb));
    }
    return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
ns16550_ena_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
    switch (cbrtn) {
        case SIO_RDY_SND:
            ns16550_enable_send(p_siopcb);
            break;
        case SIO_RDY_RCV:
            ns16550_enable_rcv(p_siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
ns16550_dis_cbr(SIOPCB *p_siopcb, uint_t cbrtn)
{
    switch (cbrtn) {
        case SIO_RDY_SND:
            ns16550_disable_send(p_siopcb);
            break;
        case SIO_RDY_RCV:
            ns16550_disable_rcv(p_siopcb);
            break;
    }
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
ns16550_isr_siop(SIOPCB *p_siopcb)
{
    if (ns16550_getready(p_siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        ns16550_irdy_rcv(p_siopcb->exinf);
    }
    if (ns16550_putready(p_siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        ns16550_irdy_snd(p_siopcb->exinf);
    }
}

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
ns16550_isr(intptr_t exinf)
{
    ns16550_isr_siop(get_siopcb(exinf));
}

/*
 *  SIOPCB�ؤΥݥ��󥿤���ݡ����ֹ���֤�
 */
ID
ns16550_get_siopid(SIOPCB *p_siopcb)
{
	return (ID)((p_siopcb - siopcb_table) + 1);
}

/*
 *  ������ֹ���֤�
 */
uint8_t
ns16550_get_intno(SIOPCB *p_siopcb)
{
	return p_siopcb->p_siopinib->intno;
}
