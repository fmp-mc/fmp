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
memmove (void *dest, const void *src, size_t n)
{
  if ((const char *) src >= (char *) dest + n
      || (char *) dest >= (const char *) src + n)
    {
      /* We found no overlap, so let memcpy do all the heavy lifting.  */
      return memcpy (dest, src, n);
    }

  if (n != 0)
    {
      const uint8_t *in;
      uint8_t x;
      uint8_t *out;
      int stride;

      if (src < dest)
	{
	  /* copy backwards */
	  in = (const uint8_t *) src + n - 1;
	  out = (uint8_t *) dest + n - 1;
	  stride = -1;
	}
      else
	{
	  /* copy forwards */
	  in = (const uint8_t *) src;
	  out = (uint8_t *) dest;
	  stride = 1;
	}

      /* Manually software-pipeline this loop. */
      x = *in;
      in += stride;

      while (--n != 0)
	{
	  *out = x;
	  out += stride;
	  x = *in;
	  in += stride;
	}

      *out = x;
    }

  return dest;
}
