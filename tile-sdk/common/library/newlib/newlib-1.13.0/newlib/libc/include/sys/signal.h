/* sys/signal.h */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"
#include <sys/features.h>
#include <sys/types.h>

/* #ifndef __STRICT_ANSI__*/

#ifdef __tile__
#include <asm/sigcontext.h>
#define _NSIG		64
#define _NSIG_BPW	(8 * sizeof(unsigned long))
#define _NSIG_WORDS	(_NSIG / _NSIG_BPW)

typedef struct {
  unsigned long sig[_NSIG_WORDS];
} sigset_t;

#else
typedef unsigned long sigset_t;
#endif

#if defined(__rtems__)

#if defined(_POSIX_REALTIME_SIGNALS)

/* sigev_notify values
   NOTE: P1003.1c/D10, p. 34 adds SIGEV_THREAD.  */

#define SIGEV_NONE   1  /* No asynchronous notification shall be delivered */
                        /*   when the event of interest occurs. */
#define SIGEV_SIGNAL 2  /* A queued signal, with an application defined */
                        /*  value, shall be delivered when the event of */
                        /*  interest occurs. */
#define SIGEV_THREAD 3  /* A notification function shall be called to */
                        /*   perform notification. */

/*  Signal Generation and Delivery, P1003.1b-1993, p. 63
    NOTE: P1003.1c/D10, p. 34 adds sigev_notify_function and
          sigev_notify_attributes to the sigevent structure.  */

union sigval {
  int    sival_int;    /* Integer signal value */
  void  *sival_ptr;    /* Pointer signal value */
};

struct sigevent {
  int              sigev_notify;               /* Notification type */
  int              sigev_signo;                /* Signal number */
  union sigval     sigev_value;                /* Signal value */

#if defined(_POSIX_THREADS)
  void           (*sigev_notify_function)( union sigval );
                                               /* Notification function */
  pthread_attr_t  *sigev_notify_attributes;    /* Notification Attributes */
#endif
};

/* Signal Actions, P1003.1b-1993, p. 64 */
/* si_code values, p. 66 */

#define SI_USER    1    /* Sent by a user. kill(), abort(), etc */
#define SI_QUEUE   2    /* Sent by sigqueue() */
#define SI_TIMER   3    /* Sent by expiration of a timer_settime() timer */
#define SI_ASYNCIO 4    /* Indicates completion of asycnhronous IO */
#define SI_MESGQ   5    /* Indicates arrival of a message at an empty queue */

typedef struct {
  int          si_signo;    /* Signal number */
  int          si_code;     /* Cause of the signal */
  union sigval si_value;    /* Signal value */
} siginfo_t;
#endif

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76 */

#define SA_NOCLDSTOP 1   /* Do not generate SIGCHLD when children stop */
#define SA_SIGINFO   2   /* Invoke the signal catching function with */
                         /*   three arguments instead of one. */

/* struct sigaction notes from POSIX:
 *
 *  (1) Routines stored in sa_handler should take a single int as
 *      their argument although the POSIX standard does not require this.
 *  (2) The fields sa_handler and sa_sigaction may overlap, and a conforming
 *      application should not use both simultaneously.
 */

typedef void (*_sig_func_ptr)();

struct sigaction {
  int         sa_flags;       /* Special flags to affect behavior of signal */
  sigset_t    sa_mask;        /* Additional set of signals to be blocked */
                              /*   during execution of signal-catching */
                              /*   function. */
  union {
    _sig_func_ptr _handler;  /* SIG_DFL, SIG_IGN, or pointer to a function */
#if defined(_POSIX_REALTIME_SIGNALS)
    void      (*_sigaction)( int, siginfo_t *, void * );
#endif
  } _signal_handlers;
};

#define sa_handler    _signal_handlers._handler
#if defined(_POSIX_REALTIME_SIGNALS)
#define sa_sigaction  _signal_handlers._sigaction
#endif

#elif defined(__tile__)
#define SA_NOCLDSTOP    1
#define SA_NOCLDWAIT	2
#define SA_SIGINFO	4
#define SA_NOPTRACE	0x02000000
#define SA_ONSTACK	0x08000000
#define SA_RESTART	0x10000000
#define SA_NODEFER	0x40000000
#define SA_RESETHAND	0x80000000
#define SA_NOMASK	SA_NODEFER
#define SA_ONESHOT	SA_RESETHAND

typedef void (*_sig_func_ptr)(int);

typedef struct siginfo {
	int si_signo;
	int si_errno;
	int si_code;
} siginfo_t;

typedef struct sigaltstack {
	void *ss_sp;
	size_t ss_size;
	int ss_flags;
} stack_t;

struct sigaction {
	union {
	  _sig_func_ptr _sa_handler;
	  void (*_sa_sigaction)(int, struct siginfo *, void *);
	} _sa_u;
	unsigned long sa_flags;
	void (*sa_restorer)(void);
	sigset_t sa_mask;
};
#define sa_handler   _sa_u._sa_handler
#define sa_sigaction _sa_u._sa_sigaction

#elif defined(__CYGWIN__)
#include <cygwin/signal.h>
#else
#define SA_NOCLDSTOP 1  /* only value supported now for sa_flags */

typedef void (*_sig_func_ptr)(int);

struct sigaction 
{
	_sig_func_ptr sa_handler;
	sigset_t sa_mask;
	int sa_flags;
};
#endif /* defined(__rtems__) */

#ifdef __tile__
int _EXFUN(kill, (int, int));
int _EXFUN(sigaction, (int, const struct sigaction *, struct sigaction *));
int _EXFUN(sigpending, (sigset_t *));
int _EXFUN(sigsuspend, (const sigset_t *));

#define sigemptyset(what) (__builtin_memset(what, 0, sizeof(sigset_t)), 0)
#define sigfillset(what) (__builtin_memset(what, -1, sizeof(sigset_t)), 0)

static __inline int sigaddset(sigset_t* what, int sig)
{
  what->sig[sig / _NSIG_BPW] |= (1UL << (sig % _NSIG_BPW));
  return 0;
}

static __inline int sigdelset(sigset_t* what, int sig)
{
  what->sig[sig / _NSIG_BPW] &= ~(1UL << (sig % _NSIG_BPW));
  return 0;
}

static __inline int sigismember(const sigset_t* what, int sig)
{
  return (what->sig[sig / _NSIG_BPW] & (1UL << (sig % _NSIG_BPW))) != 0;
}

#define SIG_BLOCK 0	/* set of signals to block */
#define SIG_UNBLOCK 1	/* set of signals to, well, unblock */
#define SIG_SETMASK 2	/* set mask with sigprocmask() */

#else

#define SIG_SETMASK 0	/* set mask with sigprocmask() */
#define SIG_BLOCK 1	/* set of signals to block */
#define SIG_UNBLOCK 2	/* set of signals to, well, unblock */

/* These depend upon the type of sigset_t, which right now 
   is always a long.. They're in the POSIX namespace, but
   are not ANSI. */
#define sigaddset(what,sig) (*(what) |= (1<<(sig)))
#define sigemptyset(what)   (*(what) = 0)

#endif

int _EXFUN(sigprocmask, (int how, const sigset_t *set, sigset_t *oset));

#if defined(_POSIX_THREADS)
int _EXFUN(pthread_sigmask, (int how, const sigset_t *set, sigset_t *oset));
#endif

/* protos for functions found in winsup sources for CYGWIN */
#if defined(__CYGWIN__) || defined(__rtems__)
#undef sigaddset
#undef sigemptyset
/* The first argument to kill should be pid_t.  Right now
   <sys/types.h> always defines pid_t to be int.  If that ever
   changes, then we will need to do something else, perhaps along the
   lines of <machine/types.h>.  */
int _EXFUN(kill, (int, int));
int _EXFUN(killpg, (pid_t, int));
int _EXFUN(sigaction, (int, const struct sigaction *, struct sigaction *));
int _EXFUN(sigaddset, (sigset_t *, const int));
int _EXFUN(sigdelset, (sigset_t *, const int));
int _EXFUN(sigismember, (const sigset_t *, int));
int _EXFUN(sigfillset, (sigset_t *));
int _EXFUN(sigemptyset, (sigset_t *));
int _EXFUN(sigpending, (sigset_t *));
int _EXFUN(sigsuspend, (const sigset_t *));
int _EXFUN(sigpause, (int));

#if defined(_POSIX_THREADS)
#ifdef __CYGWIN__
#  ifndef _CYGWIN_TYPES_H
#    error You need the winsup sources or a cygwin installation to compile the cygwin version of newlib.
#  endif
#endif
int _EXFUN(pthread_kill, (pthread_t thread, int sig));
#endif

#if defined(_POSIX_REALTIME_SIGNALS)

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76
    NOTE: P1003.1c/D10, p. 39 adds sigwait().  */

int _EXFUN(sigwaitinfo, (const sigset_t *set, siginfo_t *info));
int _EXFUN(sigtimedwait,
  (const sigset_t *set, siginfo_t *info, const struct timespec  *timeout)
);
int _EXFUN(sigwait, (const sigset_t *set, int *sig));

/*  3.3.9 Queue a Signal to a Process, P1003.1b-1993, p. 78 */
int _EXFUN(sigqueue, (pid_t pid, int signo, const union sigval value));

#endif /* defined(_POSIX_REALTIME_SIGNALS) */

#endif /* defined(__CYGWIN__) || defined(__rtems__) */

/* #endif __STRICT_ANSI__ */

#if defined(__tile__)
#define SIGHUP	1
#define SIGINT	2
#define SIGQUIT	3
#define SIGILL	4
#define SIGTRAP	5
#define SIGABRT	6
#define SIGIOT	6
#define SIGBUS	7
#define SIGFPE	8
#define SIGKILL	9
#define SIGUSR1	10
#define SIGSEGV	11
#define SIGUSR2	12
#define SIGPIPE	13
#define SIGALRM	14
#define SIGTERM	15
#define SIGSTKFLT 16
#define SIGCHLD	17
#define SIGCONT	18
#define SIGSTOP	19
#define SIGTSTP	20
#define SIGTTIN	21
#define SIGTTOU	22
#define SIGURG	23
#define SIGXCPU	24
#define SIGXFSZ	25
#define SIGVTALRM 26
#define SIGPROF	27
#define SIGWINCH 28
#define SIGIO	29
#define SIGPOLL	SIGIO
#define SIGPWR	30
#define SIGSYS	31
#define SIGUNUSED 31
#define SIGRTMIN 32
#define SIGRTMAX 64
#define NSIG	64
#elif defined(___AM29K__)
/* These all need to be defined for ANSI C, but I don't think they are
   meaningful.  */
#define SIGABRT 1
#define SIGFPE 1
#define SIGILL 1
#define SIGINT 1
#define SIGSEGV 1
#define SIGTERM 1
/* These need to be defined for POSIX, and some others do too.  */
#define SIGHUP 1
#define SIGQUIT 1
#define NSIG 2
#elif defined(__GO32__)
#define SIGINT  1
#define SIGKILL 2
#define SIGPIPE 3
#define SIGFPE  4
#define SIGHUP  5
#define SIGTERM 6
#define SIGSEGV 7
#define SIGTSTP 8
#define SIGQUIT 9
#define SIGTRAP 10
#define SIGILL  11
#define SIGEMT  12
#define SIGALRM 13
#define SIGBUS  14
#define SIGLOST 15
#define SIGSTOP 16
#define SIGABRT 17
#define SIGUSR1	18
#define SIGUSR2	19
#define NSIG    20
#elif !defined(SIGTRAP)
#define	SIGHUP	1	/* hangup */
#define	SIGINT	2	/* interrupt */
#define	SIGQUIT	3	/* quit */
#define	SIGILL	4	/* illegal instruction (not reset when caught) */
#define	SIGTRAP	5	/* trace trap (not reset when caught) */
#define	SIGIOT	6	/* IOT instruction */
#define	SIGABRT 6	/* used by abort, replace SIGIOT in the future */
#define	SIGEMT	7	/* EMT instruction */
#define	SIGFPE	8	/* floating point exception */
#define	SIGKILL	9	/* kill (cannot be caught or ignored) */
#define	SIGBUS	10	/* bus error */
#define	SIGSEGV	11	/* segmentation violation */
#define	SIGSYS	12	/* bad argument to system call */
#define	SIGPIPE	13	/* write on a pipe with no one to read it */
#define	SIGALRM	14	/* alarm clock */
#define	SIGTERM	15	/* software termination signal from kill */

#if defined(__rtems__)
#define	SIGURG	16	/* urgent condition on IO channel */
#define	SIGSTOP	17	/* sendable stop signal not from tty */
#define	SIGTSTP	18	/* stop signal from tty */
#define	SIGCONT	19	/* continue a stopped process */
#define	SIGCHLD	20	/* to parent on child stop or exit */
#define	SIGCLD	20	/* System V name for SIGCHLD */
#define	SIGTTIN	21	/* to readers pgrp upon background tty read */
#define	SIGTTOU	22	/* like TTIN for output if (tp->t_local&LTOSTOP) */
#define	SIGIO	23	/* input/output possible signal */
#define	SIGPOLL	SIGIO	/* System V name for SIGIO */
#define	SIGWINCH 24	/* window changed */
#define	SIGUSR1 25	/* user defined signal 1 */
#define	SIGUSR2 26	/* user defined signal 2 */

/* Real-Time Signals Range, P1003.1b-1993, p. 61
   NOTE: By P1003.1b-1993, this should be at least RTSIG_MAX
         (which is a minimum of 8) signals.
 */
#define SIGRTMIN 27
#define SIGRTMAX 31
#define __SIGFIRSTNOTRT SIGHUP
#define __SIGLASTNOTRT  SIGUSR2

#define NSIG	32      /* signal 0 implied */

#elif defined(__svr4__)
/* svr4 specifics. different signals above 15, and sigaction. */
#define	SIGUSR1	16
#define SIGUSR2	17
#define SIGCLD	18
#define	SIGPWR	19
#define SIGWINCH 20
#define	SIGPOLL	22	/* 20 for x.out binaries!!!! */
#define	SIGSTOP	23	/* sendable stop signal not from tty */
#define	SIGTSTP	24	/* stop signal from tty */
#define	SIGCONT	25	/* continue a stopped process */
#define	SIGTTIN	26	/* to readers pgrp upon background tty read */
#define	SIGTTOU	27	/* like TTIN for output if (tp->t_local&LTOSTOP) */
#define NSIG	28	
#else
#define	SIGURG	16	/* urgent condition on IO channel */
#define	SIGSTOP	17	/* sendable stop signal not from tty */
#define	SIGTSTP	18	/* stop signal from tty */
#define	SIGCONT	19	/* continue a stopped process */
#define	SIGCHLD	20	/* to parent on child stop or exit */
#define	SIGCLD	20	/* System V name for SIGCHLD */
#define	SIGTTIN	21	/* to readers pgrp upon background tty read */
#define	SIGTTOU	22	/* like TTIN for output if (tp->t_local&LTOSTOP) */
#define	SIGIO	23	/* input/output possible signal */
#define	SIGPOLL	SIGIO	/* System V name for SIGIO */
#define	SIGXCPU	24	/* exceeded CPU time limit */
#define	SIGXFSZ	25	/* exceeded file size limit */
#define	SIGVTALRM 26	/* virtual time alarm */
#define	SIGPROF	27	/* profiling time alarm */
#define	SIGWINCH 28	/* window changed */
#define	SIGLOST 29	/* resource lost (eg, record-lock lost) */
#define	SIGUSR1 30	/* user defined signal 1 */
#define	SIGUSR2 31	/* user defined signal 2 */
#define NSIG	32      /* signal 0 implied */
#endif
#endif

#ifdef __cplusplus
}
#endif

#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */
