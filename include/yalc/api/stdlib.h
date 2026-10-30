#ifndef __YALC_API_STDLIB_H
#define __YALC_API_STDLIB_H

#include <yalc/config.h>
#include __YALC_INC(cstd.h)

#define NULL ((void*)0)

__YALC_NO_RETURN__
void exit(int __ec);

#endif // __YALC_API_STDLIB_H
