#ifndef __YALC_CONFIG_H
#define __YALC_CONFIG_H

#ifndef __YALC_INC_BASE
#define __YALC_INC_BASE
#endif

#define __YALC_STRINGIFY_(x) #x
#define __YALC_STRINGIFY(x) __YALC_STRINGIFY_(x)

#define __YALC_CONCAT_(p, q) p##q
#define __YALC_CONCAT(p, q) __YALC_CONCAT_(p, q)

#define __YALC_QUOTE_(x) x
#define __YALC_QUOTE(x) __YALC_QUOTE_(x)

#define __YALC_INC(PATH) __YALC_STRINGIFY(__YALC_QUOTE(__YALC_INC_BASE)__YALC_QUOTE(PATH))

#endif // __YALC_CONFIG_H
