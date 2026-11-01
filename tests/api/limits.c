#include <limits.h>
#include <stdint.h>
#include <assert.h>

static_assert(SCHAR_MIN < 0 && SCHAR_MAX > 0);
static_assert(SHRT_MIN  < 0 && SHRT_MAX  > 0);
static_assert(INT_MIN   < 0 && INT_MAX   > 0);
static_assert(LONG_MIN  < 0 && LONG_MAX  > 0);
static_assert(LLONG_MIN < 0 && LLONG_MAX > 0);

static_assert(UCHAR_MAX  > 0);
static_assert(USHRT_MAX  > 0);
static_assert(UINT_MAX   > 0);
static_assert(ULONG_MAX  > 0);
static_assert(ULLONG_MAX > 0);

static_assert(USHRT_MAX <= UINT_MAX);
static_assert(UINT_MAX  <= ULONG_MAX);
static_assert(ULONG_MAX <= ULLONG_MAX);

static_assert(SHRT_MAX  <= INT_MAX);
static_assert(INT_MAX   <= LONG_MAX);
static_assert(LONG_MAX  <= LLONG_MAX);
