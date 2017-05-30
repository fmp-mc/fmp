#ifndef __STDINT_H__
#define __STDINT_H__

/* ISO C99 types */

/* Provide the basic types */
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
#ifdef __GNUC__
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;
#else
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif

/* Pointer-sized types */
typedef long intptr_t;
typedef unsigned long uintptr_t;

/* Largest integer types */
typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

/* Small types (same as default) */
typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned int uint_least32_t;
typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;

/* Fast types (same as default but using 32-bit int for 16-bit types) */
typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef int int_fast16_t;
typedef unsigned int uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
typedef int64_t int_fast64_t;
typedef uint64_t uint_fast64_t;

/* We should also provide the various MAX and MIN #defines */

#endif // !__STDINT_H__
