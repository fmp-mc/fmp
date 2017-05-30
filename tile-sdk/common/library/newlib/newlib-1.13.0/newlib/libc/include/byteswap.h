#ifndef _BYTESWAP_H
#define _BYTESWAP_H

/* Return a value with all bytes in the 16 bit argument swapped.  */
#define bswap_16(x) \
  ({ unsigned short __x = x; ((__x & 0xff) << 8) | ((__x >> 8) & 0xff); })

/* Return a value with all bytes in the 32 bit argument swapped.  */
/* FIXME: we're not allowing for constant values here */
#define bswap_32(x) __insn_bytex(x)

/* Return a value with all bytes in the 64 bit argument swapped.  */
/* FIXME: we're not allowing for constant values here */
#define bswap_64(x) \
  ({ unsigned long long __x = x; \
     bswap_32((unsigned int)(x >> 32)) | (bswap_32((unsigned int)x) << 32); })

#endif
