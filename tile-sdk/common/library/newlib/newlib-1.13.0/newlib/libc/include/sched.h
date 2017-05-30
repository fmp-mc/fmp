/* HACK: Primitive support for "cpu_set_t". */

#ifndef _LIBC_SCHED_H_
# define _LIBC_SCHED_H_	1

#include <_ansi.h>

#define __need_size_t
#include <stddef.h>
#include <sys/types.h>

int sched_yield(void);

typedef unsigned long int __cpu_mask;

# define __CPU_SETSIZE 1024
# define __NCPUBITS (sizeof(__cpu_mask) * 8)
# define __NCPUWORDS (__CPU_SETSIZE / __NCPUBITS)

typedef struct
{
  __cpu_mask __bits[__NCPUWORDS];
} cpu_set_t;

# define __CPU_ELT(CPU) ((CPU) / __NCPUBITS)
# define __CPU_MASK(CPU) ((__cpu_mask) 1 << ((CPU) % __NCPUBITS))

# define __CPU_ZERO(CS) \
  do { \
    cpu_set_t *__cs = (CS); \
    unsigned int __i; \
    for (__i = 0; __i < __NCPUWORDS; ++__i) \
      __cs->__bits[__i] = 0; \
  } while (0)

# define __CPU_SET(CPU, CS) \
  ((CS)->__bits[__CPU_ELT(CPU)] |= __CPU_MASK(CPU))

# define __CPU_CLR(CPU, CS) \
  ((CS)->__bits[__CPU_ELT(CPU)] &= ~__CPU_MASK(CPU))

# define __CPU_ISSET(CPU, CS) \
  (((CS)->__bits[__CPU_ELT(CPU)] & __CPU_MASK(CPU)) != 0)

/* User-visible versions (needs _GNU_SOURCE with uClibc or glibc) */
#define CPU_SETSIZE __CPU_SETSIZE
#define CPU_SET(cpu, cpusetp) __CPU_SET (cpu, cpusetp)
#define CPU_CLR(cpu, cpusetp) __CPU_CLR (cpu, cpusetp)
#define CPU_ISSET(cpu, cpusetp) __CPU_ISSET (cpu, cpusetp)
#define CPU_ZERO(cpusetp) __CPU_ZERO (cpusetp)

/* Get/set the CPU affinity for a task */
int sched_setaffinity(pid_t __pid, size_t __cpusetsize,
                      _CONST cpu_set_t *__cpuset);
int sched_getaffinity(pid_t __pid, size_t __cpusetsize,
                      cpu_set_t *__cpuset);

/* Get current CPU */
int sched_getcpu(void);

#endif
