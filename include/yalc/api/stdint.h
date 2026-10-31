#ifndef __YALC_API_STDINT_H
#define __YALC_API_STDINT_H

#include <yalc/config.h>
#include __YALC_INC(cstd.h)

#if __YALC_CSTD >= __YALC_C23
#   define __STDC_VERSION_STDINT_H__ 202311U
#endif

// TODO: don't rely on gcc predefined __*_TYPE__ macros
//       and/or implement custom detection logic like:
//
//       #ifndef __INT8_TYPE__
//       #  define __INT8_TYPE__ ...
//       #endif

#define __M(MAX) (-(MAX) - 1)

/////////////// 8-bit ///////////////
typedef __INT8_TYPE__ int8_t;
typedef __UINT8_TYPE__ uint8_t;
typedef __INT_FAST8_TYPE__ int_fast8_t;
typedef __UINT_FAST8_TYPE__ uint_fast8_t;
typedef __INT_LEAST8_TYPE__ int_least8_t;
typedef __UINT_LEAST8_TYPE__ uint_least8_t;

#define INT8_MIN __M(__INT8_MAX__)
#define INT8_MAX __INT8_MAX__
#define UINT8_MAX __UINT8_MAX__

#define INT_FAST8_MIN __M(__INT_FAST8_MAX__)
#define INT_FAST8_MAX __INT_FAST8_MAX__
#define UINT_FAST8_MAX __UINT_FAST8_MAX__

#define INT_LEAST8_MIN __M(__INT_LEAST8_MAX__)
#define INT_LEAST8_MAX __INT_LEAST8_MAX__
#define UINT_LEAST8_MAX __UINT_LEAST8_MAX__

#define INT8_C(c) __INT8_C(c)
#define UINT8_C(c) __UINT8_C(c)

#if __YALC_CSTD >= __YALC_C23
#   define INT8_WIDTH 8
#   define UINT8_WIDTH 8
#   define INT_FAST8_WIDTH __INT_FAST8_WIDTH__
#   define UINT_FAST8_WIDTH __INT_FAST8_WIDTH__
#   define INT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#   define UINT_LEAST8_WIDTH __INT_LEAST8_WIDTH__
#endif

/////////////// 16-bit //////////////
typedef __INT16_TYPE__ int16_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __INT_FAST16_TYPE__ int_fast16_t;
typedef __UINT_FAST16_TYPE__ uint_fast16_t;
typedef __INT_LEAST16_TYPE__ int_least16_t;
typedef __UINT_LEAST16_TYPE__ uint_least16_t;

#define INT16_MIN __M(__INT16_MAX__)
#define INT16_MAX __INT16_MAX__
#define UINT16_MAX __UINT16_MAX__

#define INT_FAST16_MIN __M(__INT_FAST16_MAX__)
#define INT_FAST16_MAX __INT_FAST16_MAX__
#define UINT_FAST16_MAX __UINT_FAST16_MAX__

#define INT_LEAST16_MIN __M(__INT_LEAST16_MAX__)
#define INT_LEAST16_MAX __INT_LEAST16_MAX__
#define UINT_LEAST16_MAX __UINT_LEAST16_MAX__

#define INT16_C(c) __INT16_C(c)
#define UINT16_C(c) __UINT16_C(c)

#if __YALC_CSTD >= __YALC_C23
#   define INT16_WIDTH 16
#   define UINT16_WIDTH 16
#   define INT_FAST16_WIDTH __INT_FAST16_WIDTH__
#   define UINT_FAST16_WIDTH __INT_FAST16_WIDTH__
#   define INT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#   define UINT_LEAST16_WIDTH __INT_LEAST16_WIDTH__
#endif

/////////////// 32-bit //////////////
typedef __INT32_TYPE__ int32_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __INT_FAST32_TYPE__ int_fast32_t;
typedef __UINT_FAST32_TYPE__ uint_fast32_t;
typedef __INT_LEAST32_TYPE__ int_least32_t;
typedef __UINT_LEAST32_TYPE__ uint_least32_t;

#define INT32_MIN __M(__INT32_MAX__)
#define INT32_MAX __INT32_MAX__
#define UINT32_MAX __UINT32_MAX__

#define INT_FAST32_MIN __M(__INT_FAST32_MAX__)
#define INT_FAST32_MAX __INT_FAST32_MAX__
#define UINT_FAST32_MAX __UINT_FAST32_MAX__

#define INT_LEAST32_MIN __M(__INT_LEAST32_MAX__)
#define INT_LEAST32_MAX __INT_LEAST32_MAX__
#define UINT_LEAST32_MAX __UINT_LEAST32_MAX__

#define INT32_C(c) __INT32_C(c)
#define UINT32_C(c) __UINT32_C(c)

#if __YALC_CSTD >= __YALC_C23
#   define INT32_WIDTH 32
#   define UINT32_WIDTH 32
#   define INT_FAST32_WIDTH __INT_FAST32_WIDTH__
#   define UINT_FAST32_WIDTH __INT_FAST32_WIDTH__
#   define INT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#   define UINT_LEAST32_WIDTH __INT_LEAST32_WIDTH__
#endif

/////////////// 64-bit //////////////
typedef __INT64_TYPE__ int64_t;
typedef __UINT64_TYPE__ uint64_t;
typedef __INT_FAST64_TYPE__ int_fast64_t;
typedef __UINT_FAST64_TYPE__ uint_fast64_t;
typedef __INT_LEAST64_TYPE__ int_least64_t;
typedef __UINT_LEAST64_TYPE__ uint_least64_t;

#define INT64_MIN __M(__INT64_MAX__)
#define INT64_MAX __INT64_MAX__
#define UINT64_MAX __UINT64_MAX__

#define INT_FAST64_MIN __M(__INT_FAST64_MAX__)
#define INT_FAST64_MAX __INT_FAST64_MAX__
#define UINT_FAST64_MAX __UINT_FAST64_MAX__

#define INT_LEAST64_MIN __M(__INT_LEAST64_MAX__)
#define INT_LEAST64_MAX __INT_LEAST64_MAX__
#define UINT_LEAST64_MAX __UINT_LEAST64_MAX__

#define INT64_C(c) __INT64_C(c)
#define UINT64_C(c) __UINT64_C(c)

#if __YALC_CSTD >= __YALC_C23
#   define INT64_WIDTH 64
#   define UINT64_WIDTH 64
#   define INT_FAST64_WIDTH __INT_FAST64_WIDTH__
#   define UINT_FAST64_WIDTH __INT_FAST64_WIDTH__
#   define INT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#   define UINT_LEAST64_WIDTH __INT_LEAST64_WIDTH__
#endif

/////////////// intmax //////////////
typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

#define INTMAX_MIN __M(__INTMAX_MAX__)
#define INTMAX_MAX __INTMAX_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

#define INTMAX_C(c) __INTMAX_C(c)
#define UINTMAX_C(c) __UINTMAX_C(c)
#if __YALC_CSTD >= __YALC_C23
#   define INTMAX_WIDTH __INTMAX_WIDTH__
#   define UINTMAX_WIDTH __INTMAX_WIDTH__
#endif

/////////////// intptr //////////////
typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

#define INTPTR_MIN __M(__INTPTR_MAX__)
#define INTPTR_MAX __INTPTR_MAX__
#define UINTPTR_MAX __UINTPTR_MAX__
#if __YALC_CSTD >= __YALC_C23
#   define INTPTR_WIDTH __INTPTR_WIDTH__
#   define UINTPTR_WIDTH __INTPTR_WIDTH__
#endif

//////////////// size ///////////////
typedef __SIZE_TYPE__ size_t;

#define SIZE_MAX __SIZE_MAX__
#if __YALC_CSTD >= __YALC_C23
#   define SIZE_WIDTH __SIZE_WIDTH__
#endif

////////////// ptrdiff //////////////
typedef __PTRDIFF_TYPE__ ptrdiff_t;

#define PTRDIFF_MIN __M(__PTRDIFF_MAX__)
#define PTRDIFF_MAX __PTRDIFF_MAX__
#if __YALC_CSTD >= __YALC_C23
#   define PTRDIFF_WIDTH __PTRDIFF_WIDTH__
#endif

/////////////// wchar ///////////////
typedef __WCHAR_TYPE__ wchar_t;

#define WCHAR_MIN __M(__WCHAR_MAX__)
#define WCHAR_MAX __WCHAR_MAX__
#if __YALC_CSTD >= __YALC_C23
#   define WCHAR_WIDTH __WCHAR_WIDTH__
#endif

//////////////// wint ///////////////
typedef __WINT_TYPE__ wint_t;

#if __WINT_UNSIGNED__
#   define WINT_MIN 0
#else
#   define WINT_MIN __M(__WINT_MAX__)
#endif

#define WINT_MAX __WINT_MAX__
#if __YALC_CSTD >= __YALC_C23
#   define WINT_WIDTH __WINT_WIDTH__
#endif

///////////// sigatomic /////////////
// for whatever reason this macro is not always defined
#if defined(__SIG_ATOMIC_TYPE__)
    typedef __SIG_ATOMIC_TYPE__ sig_atomic_t;
#else
    typedef int sig_atomic_t;
#endif

#define SIG_ATOMIC_MIN __M(__SIG_ATOMIC_MAX__)
#define SIG_ATOMIC_MAX __SIG_ATOMIC_MAX__
#define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__

_Static_assert(SIG_ATOMIC_WIDTH == sizeof(sig_atomic_t) * 8);

#endif // __YALC_API_STDINT_H
