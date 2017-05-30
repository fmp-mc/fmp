
#ifndef	_FCNTL_
#ifdef __cplusplus
extern "C" {
#endif
#define	_FCNTL_
#include <_ansi.h>
#define	_FOPEN		(-1)	/* from sys/file.h, kernel use only */
#define	_FREAD		000001	/* read enabled */
#define	_FWRITE		000002	/* write enabled */
#define	_FCREAT		000100	/* open with file create */
#define	_FEXCL		000200	/* error on open if file exists */
#define	_FNOCTTY	000400	/* don't assign a ctty on this open */
#define	_FTRUNC		001000	/* open with truncation */
#define	_FAPPEND	002000	/* append (writes guaranteed at the end) */
#define	_FNONBLOCK	004000	/* non blocking I/O (POSIX style) */
#define	_FSYNC		010000	/* do all writes synchronously */
#define	_FASYNC		020000	/* signal pgrp when data ready */
#define	_FNDELAY	_FNONBLOCK	/* non blocking I/O (4.2 style) */
#define	_FNBIO		_FNONBLOCK	/* non blocking I/O (sys5 style) */

#define	O_ACCMODE	(O_RDONLY|O_WRONLY|O_RDWR)

/*
 * Flag values for open(2) and fcntl(2)
 * The kernel adds 1 to the open modes to turn it into some
 * combination of FREAD and FWRITE.
 */
#define	O_RDONLY	0		/* +1 == FREAD */
#define	O_WRONLY	1		/* +1 == FWRITE */
#define	O_RDWR		2		/* +1 == FREAD|FWRITE */
#define	O_APPEND	_FAPPEND
#define	O_CREAT		_FCREAT
#define	O_TRUNC		_FTRUNC
#define	O_EXCL		_FEXCL
/*	O_SYNC		_FSYNC		not posix, defined below */
/*	O_NDELAY	_FNDELAY 	set in include/fcntl.h */
/*	O_NDELAY	_FNBIO 		set in 5include/fcntl.h */
#define	O_NONBLOCK	_FNONBLOCK
#define	O_NOCTTY	_FNOCTTY
/* For machines which care - */
#if defined (_WIN32) || defined (__CYGWIN__)
#define _FBINARY        0x10000
#define _FTEXT          0x20000
#define _FNOINHERIT	0x40000

#define O_BINARY	_FBINARY
#define O_TEXT		_FTEXT
#define O_NOINHERIT	_FNOINHERIT

/* The windows header files define versions with a leading underscore.  */
#define _O_RDONLY	O_RDONLY
#define _O_WRONLY	O_WRONLY
#define _O_RDWR		O_RDWR
#define _O_APPEND	O_APPEND
#define _O_CREAT	O_CREAT
#define _O_TRUNC	O_TRUNC
#define _O_EXCL		O_EXCL
#define _O_TEXT		O_TEXT
#define _O_BINARY	O_BINARY
#define _O_RAW		O_BINARY
#define _O_NOINHERIT	O_NOINHERIT
#endif

#ifndef	_POSIX_SOURCE

#define	O_SYNC		_FSYNC

/*
 * Flags that work for fcntl(fd, F_SETFL, FXXXX)
 */
#define	FAPPEND		_FAPPEND
#define	FSYNC		_FSYNC
#define	FASYNC		_FASYNC
#define	FNBIO		_FNBIO
#define	FNONBIO		_FNONBLOCK	/* XXX fix to be NONBLOCK everywhere */
#define	FNDELAY		_FNDELAY

/*
 * Flags that are disallowed for fcntl's (FCNTLCANT);
 * used for opens, internal state, or locking.
 */
#define	FREAD		_FREAD
#define	FWRITE		_FWRITE

/*
 * The rest of the flags, used only for opens
 */
#define	FOPEN		_FOPEN
#define	FCREAT		_FCREAT
#define	FTRUNC		_FTRUNC
#define	FEXCL		_FEXCL
#define	FNOCTTY		_FNOCTTY

/* Required for the new *at() family of syscalls. */
#define AT_FDCWD		-100    /* Special value used to indicate
                                           openat should use the current
                                           working directory. */
#define AT_SYMLINK_NOFOLLOW	0x100   /* Do not follow symbolic links.  */
#define AT_REMOVEDIR		0x200   /* Remove directory instead of
                                           unlinking file.  */
#define AT_SYMLINK_FOLLOW	0x400   /* Follow symbolic links.  */

#endif	/* !_POSIX_SOURCE */

/* XXX close on exec request; must match UF_EXCLOSE in user.h */
#define	FD_CLOEXEC	1	/* posix */

/* fcntl(2) requests */
#define	F_DUPFD		0	/* Duplicate fildes */
#define	F_GETFD		1	/* Get fildes flags (close on exec) */
#define	F_SETFD		2	/* Set fildes flags (close on exec) */
#define	F_GETFL		3	/* Get file flags */
#define	F_SETFL		4	/* Set file flags */
#define	F_GETLK  	5	/* Get record-locking information */
#define	F_SETLK  	6	/* Set or Clear a record-lock (Non-Blocking) */
#define	F_SETLKW 	7	/* Set or Clear a record-lock (Blocking) */
#ifndef	_POSIX_SOURCE
#define	F_SETOWN 	8	/* Set owner - for ASYNC */
#define	F_GETOWN 	9	/* Get owner - for ASYNC */
#endif	/* !_POSIX_SOURCE */

/* fcntl(2) flags (l_type field of flock structure) */
#define	F_RDLCK		0	/* read lock */
#define	F_WRLCK		1	/* write lock */
#define	F_UNLCK		2	/* remove lock(s) */

/*#include <sys/stdtypes.h>*/

#ifndef __ASSEMBLER__

#ifndef __CYGWIN__
/* file segment locking set data type - information passed to system by user */
struct flock {
	short	l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
	short	l_whence;	/* flag to choose starting offset */
	long	l_start;	/* relative offset, in bytes */
	long	l_len;		/* length, in bytes; 0 means lock to EOF */
	int	l_pid;		/* returned with F_GETLK */
};
#endif /* __CYGWIN__ */

#include <sys/types.h>
#include <sys/stat.h>		/* sigh. for the mode bits for open/creat */

extern int open _PARAMS ((const char *, int, ...));
extern int creat _PARAMS ((const char *, mode_t));
extern int fcntl _PARAMS ((int, int, ...));

/* Provide _<systemcall> prototypes for functions provided by some versions
   of newlib.  */
#ifdef _COMPILING_NEWLIB
extern int _open _PARAMS ((const char *, int, ...));
extern int _fcntl _PARAMS ((int, int, ...));
#ifdef __LARGE64_FILES
extern int _open64 _PARAMS ((const char *, int, ...));
#endif
#endif

#endif

#ifdef __cplusplus
}
#endif
#endif	/* !_FCNTL_ */
