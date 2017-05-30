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
 *
 * Create a new context.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ucontext.h>

void
makecontext (ucontext_t *ucp, void (*func) (void), int argc, ...)
{
  extern void __startcontext (void);
  unsigned long *sp;
  va_list ap;
  int i;

  /* Initialize the top of stack. */
  sp = (unsigned long *) ((((unsigned long) ucp->uc_stack.ss_sp
                            + ucp->uc_stack.ss_size) & -16L) - 16);
  sp[0] = sp[1] = 0;

  if (argc > 10) {
    fprintf(stderr, "makecontext: too many parameters\n");
    exit(-1);
  }

  /* Set register parameters.  */
  va_start(ap, argc);
  for (i = 0; i < argc; i++)
    ucp->uc_mcontext.gregs[i] = va_arg(ap, long);
  va_end(ap);

  /* Pass (*func) to __startcontext in pc.  */
  ucp->uc_mcontext.pc = (long) func;

  /* Set stack pointer.  */
  ucp->uc_mcontext.sp = (long) sp;

  /* Set the return address to trampoline.  */
  ucp->uc_mcontext.lr = (long) __startcontext;

  /* Pass ucp->uc_link to __start_context in r30.  */
  ucp->uc_mcontext.gregs[30] = (long) ucp->uc_link;
}
