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
#include "string-endian.h"

#undef strchr

char *
strchr (const char *s, int c)
{
  int z, g;

  /* Get an aligned pointer. */
  const uintptr_t s_int = (uintptr_t) s;
  const uint64_t *p = (const uint64_t *) (s_int & -8);

  /* Create eight copies of the byte for which we are looking. */
  const uint64_t goal = copy_byte(c);

  /* Read the first aligned word, but force bytes before the string to
     match neither zero nor goal (we make sure the high bit of each byte
     is 1, and the low 7 bits are all the opposite of the goal byte).  */
  const uint64_t before_mask = MASK (s_int);
  uint64_t v = (*p | before_mask) ^ (goal & __insn_v1shrui (before_mask, 1));

  uint64_t zero_matches, goal_matches;
  while (1)
    {
      /* Look for a terminating '\0'. */
      zero_matches = __insn_v1cmpeqi (v, 0);

      /* Look for the goal byte. */
      goal_matches = __insn_v1cmpeq (v, goal);

      if (__builtin_expect ((zero_matches | goal_matches) != 0, 0))
        break;

      v = *++p;
    }

  z = CFZ (zero_matches);
  g = CFZ (goal_matches);

  /* If we found c before '\0' we got a match. Note that if c == '\0'
     then g == z, and we correctly return the address of the '\0'
     rather than NULL.  */
  return (g <= z) ? ((char *) p) + (g >> 3) : NULL;
}
