/*
 * Copyright 2014 Tilera Corporation. All Rights Reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *   PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 *   DAMAGE. TILERA FURTHER DISCLAIMS ANY LIABILITY WHATSOEVER FOR
 *   INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHTS OF ANY THIRD PARTY.
 */

/* Version of fork() that includes __register_atfork() support. */
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <signal.h>
#include <sys/syscall.h>
 
typedef struct forkfn_t {
  void (*prepare)(void);
  void (*parent)(void);
  void (*child)(void);
} forkfn_t;

static int forkfn_slots;
static int forkfn_count;
static forkfn_t *forkfn_table;

/* This function is not prototyped in standard libc headers.
   Note: __dso_handle is unused in newlib, but included for compatibility
   with other implementations of libc.  */
int __register_atfork(void (*prepare)(void), void (*parent)(void),
                      void (*child) (void), void *__dso_handle)
{
  struct forkfn_t *ffp;

  /* If we are out of function table slots, make some more */
  if (forkfn_slots < forkfn_count + 1) {
    ffp = realloc(forkfn_table, (forkfn_slots + 20) * sizeof(forkfn_t));
    if (ffp == NULL) {
      errno = ENOMEM;
      return -1;
    }
    forkfn_table = ffp;
    forkfn_slots += 20;
  }
  ffp = &forkfn_table[forkfn_count++];
  ffp->prepare = prepare;
  ffp->parent = parent;
  ffp->child = child;
  return 0;
}

static void atfork_prepare(void)
{
  int i;
  for (i = forkfn_count; --i >= 0;)
    if (forkfn_table[i].prepare)
      forkfn_table[i].prepare();
}

static void atfork_parent(int child_pid)
{
  int i;
  for (i = 0; i < forkfn_count; ++i)
    if (forkfn_table[i].parent)
      forkfn_table[i].parent();
}

static void atfork_child(void)
{
  int i;
  for (i = 0; i < forkfn_count; ++i)
    if (forkfn_table[i].child)
      forkfn_table[i].child();
}

int _fork()
{
  int r, save_errno;

  atfork_prepare();

  r = syscall(SYS_clone, SIGCHLD, 0, NULL, NULL);

  save_errno = errno;
  if (r == 0)
    atfork_child();
  else
    atfork_parent(r);  /* also runs on error */
  errno = save_errno;

  return r;
}

#pragma weak fork = _fork
