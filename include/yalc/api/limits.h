#ifndef __YALC_API_LIMITS_H
#define __YALC_API_LIMITS_H

#include <yalc/config.h>
#include __YALC_INC(cstd.h)

#if __YALC_CSTD >= __YALC_C23
#   define __STDC_VERSION_LIMITS_H__ 202311L
#endif

#ifdef __M
#   undef __M
#endif

#define __M(MAX) (-(MAX) - 1)
#define __U(S, F) (S * 2##F + 1)

#define CHAR_BIT   __CHAR_BIT__

// completly useless macro from C23
#if __YALC_CSTD >= __YALC_C23
#   define CHAR_WIDTH CHAR_BIT
#endif

// for whatever reason gcc doesn't define
// __CHAR_MIN__ and __CHAR_MAX__ so we need
// to implement this check manually
#if '\xFF' > 0
#   define CHAR_MIN 0
#   define CHAR_MAX 255
#else
#   define CHAR_MIN (-128)
#   define CHAR_MAX 127
#endif

#if __YALC_CSTD >= __YALC_C23
#   define BOOL_WIDTH __BOOL_WIDTH__
#endif

// no idea why it's 16. copied from glibc:
//  /* Maximum length of any multibyte character in any locale.
//  We define this value here since the gcc header does not define
//  the correct value.  */
//  #define MB_LEN_MAX	16
#define MB_LEN_MAX 16

#define SCHAR_MIN __M(__SCHAR_MAX__)
#define SCHAR_MAX __SCHAR_MAX__
#define UCHAR_MAX __U(__SCHAR_MAX__,)

#define SHRT_MIN  __M(__SHRT_MAX__)
#define SHRT_MAX  __SHRT_MAX__
#define USHRT_MAX __U(__SHRT_MAX__,)

#define INT_MIN  __M(__INT_MAX__)
#define INT_MAX  __INT_MAX__
#define UINT_MAX __U(__INT_MAX__, U)

#define LONG_MIN  __M(__LONG_MAX__)
#define LONG_MAX  __LONG_MAX__
#define ULONG_MAX __U(__LONG_MAX__, UL)

#define LLONG_MIN  __M(__LONG_LONG_MAX__)
#define LLONG_MAX  __LONG_LONG_MAX__
#define ULLONG_MAX __U(__LONG_LONG_MAX__, ULL)

#if defined(__BITINT_MAXWIDTH__)
#   define BITINT_MAXWIDTH __BITINT_MAXWIDTH__
#endif

#endif // __YALC_API_LIMITS_H
