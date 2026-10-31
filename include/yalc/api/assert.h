// The lack of a include guard is intentional. Inspired by musl's implementation:
// https://git.musl-libc.org/cgit/musl/tree/include/assert.h

#undef assert

#include <yalc/config.h>
#include __YALC_INC(cstd.h)

#define __YALC_ASSERT_FAIL(m) (__yalc_assert_fail(#m, __FILE__, __LINE__, __func__), 0)

#ifdef NDEBUG
#   define assert(m) (void)0
#else
#   define assert(m) ((void)((m) || __YALC_ASSERT_FAIL(m)))
#endif

#if __YALC_CSTD >= __YALC_C11
#   define static_assert _Static_assert
#endif

__YALC_NO_RETURN__
void __yalc_assert_fail(
    const char* _msg, const char* _file,
    int _line, const char* _func
);
