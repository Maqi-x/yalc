#include <stdint.h>
#include <assert.h>

static_assert(sizeof(int8_t)  && sizeof(uint8_t)  == 1);
static_assert(sizeof(int16_t) && sizeof(uint16_t) == 2);
static_assert(sizeof(int32_t) && sizeof(uint32_t) == 4);
static_assert(sizeof(int64_t) && sizeof(uint64_t) == 8);

static_assert(sizeof(intmax_t)  >= sizeof(int64_t));
static_assert(sizeof(uintmax_t) >= sizeof(uint64_t));
static_assert(sizeof(intptr_t)  == sizeof(void *));
static_assert(sizeof(uintptr_t) == sizeof(void *));
static_assert(sizeof(intptr_t)  == sizeof(uintptr_t));

static_assert(sizeof(int_least8_t)  >= 1 && sizeof(uint_least8_t)  >= 1);
static_assert(sizeof(int_least16_t) >= 2 && sizeof(uint_least16_t) >= 2);
static_assert(sizeof(int_least32_t) >= 4 && sizeof(uint_least32_t) >= 4);
static_assert(sizeof(int_least64_t) >= 8 && sizeof(uint_least64_t) >= 8);

static_assert(sizeof(int_fast8_t)  >= 1 && sizeof(uint_fast8_t)  >= 1);
static_assert(sizeof(int_fast16_t) >= 2 && sizeof(uint_fast16_t) >= 2);
static_assert(sizeof(int_fast32_t) >= 4 && sizeof(uint_fast32_t) >= 4);
static_assert(sizeof(int_fast64_t) >= 8 && sizeof(uint_fast64_t) >= 8);

static_assert(sizeof(intmax_t)  >= sizeof( int64_t));
static_assert(sizeof(uintmax_t) >= sizeof(uint64_t));
static_assert((intmax_t)-1  < 0);
static_assert((uintmax_t)-1 > 0);

static_assert(INTMAX_MAX  >= INT64_MAX);
static_assert(UINTMAX_MAX >= UINT64_MAX);

int main() {
    return sizeof(uint64_t) - 8;
}
