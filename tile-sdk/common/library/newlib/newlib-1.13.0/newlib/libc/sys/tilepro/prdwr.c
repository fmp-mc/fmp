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

#include <unistd.h>
#include <stdarg.h>
#include <endian.h>
#include <sys/types.h>
#include <sys/syscall.h>

#ifdef __LP64__
#define SIGNEXT(off) off
#else
/* Pad out to make the register pair line up to match the kernel API. */
#define SIGNEXT(off) 0, off, off >> 31
#endif

ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset)
{
  return syscall(SYS_pread64, fd, buf, nbytes, SIGNEXT(offset));
}

ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset)
{
  return syscall(SYS_pwrite64, fd, buf, nbytes, SIGNEXT(offset));
}