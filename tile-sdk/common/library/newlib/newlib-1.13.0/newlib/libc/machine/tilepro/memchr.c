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

#include <string.h>
#include <stdint.h>

void *
memchr (const void *s, int c, size_t n)
{
  const uint32_t *last_word_ptr;
  const uint32_t *p;
  const char *last_byte_ptr;
  uintptr_t s_int;
  uint32_t goal, before_mask, v, bits;
  char *ret;

  if (__builtin_expect (n == 0, 0))
    {
      /* Don't dereference any memory if the array is empty. */
      return NULL;
    }

  /* Get an aligned pointer. */
  s_int = (uintptr_t) s;
  p = (const uint32_t *) (s_int & -4);

  /* Create four copies of the byte for which we are looking. */
  goal = 0x01010101 * (uint8_t) c;

  /* Read the first word, but munge it so that bytes before the array
     will not match goal.  Note that this shift count expression works
     because we know shift counts are taken mod 32.  */
  before_mask = (1 << (s_int << 3)) - 1;
  v = (*p | before_mask) ^ (goal & before_mask);

  /* Compute the address of the last byte. */
  last_byte_ptr = (const char *) s + n - 1;

  /* Compute the address of the word containing the last byte. */
  last_word_ptr = (const uint32_t *) ((uintptr_t) last_byte_ptr & -4);

  while ((bits = __insn_seqb (v, goal)) == 0)
    {
      if (__builtin_expect (p == last_word_ptr, 0))
        {
          /* We already read the last word in the array, so give up.  */
          return NULL;
        }
      v = *++p;
    }

  /* We found a match, but it might be in a byte past the end of the array.  */
  ret = ((char *) p) + (__insn_ctz (bits) >> 3);
  return (ret <= last_byte_ptr) ? ret : NULL;
}
