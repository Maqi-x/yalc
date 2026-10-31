#ifndef __YALC_INTL_UNIMPL_H
#define __YALC_INTL_UNIMPL_H

#include <yalc/config.h>
#include __YALC_API_INC(assert.h)

#define __YALC_UNIMPLEMENTED(MSG) \
    assert(0 && (MSG))

#endif // __YALC_INTL_UNIMPL_H
