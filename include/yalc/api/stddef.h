#ifndef __YALC_API_STDDEF_H
#define __YALC_API_STDDEF_H

#include <yalc/config.h>
#include __YALC_INC(cstd.h)

// NULL is a part of the stddef.h's public interface
#include __YALC_INTL_INC(null.h)

// TODO: more portable version
#define offsetof(P, D) \
    __builtin_offsetof(P, D)

#if __YALC_CSTD >= __YALC_C11
    typedef struct {
        long long __ll;
        long double __ld;
    } max_align_t;
#endif

typedef __PTRDIFF_TYPE__ ptrdiff_t;
typedef __WCHAR_TYPE__ wchar_t;
typedef __SIZE_TYPE__ size_t;

// TODO: again, more portable version
#define __yalc_unreachable() \
    __builtin_unreachable()

#if __YALC_CSTD >= __YALC_C23
    #define __STDC_VERSION_STDDEF_H__ 202311L
    typedef typeof(nullptr) nullptr_t;

    #define unreachable() __yalc_unreachable()
#endif

#endif // __YALC_API_STDDEF_H
