#include <yalc/config.h>

#include __YALC_API_INC(stdlib.h)

__YALC_NO_RETURN__
void exit(int __ec) {
    // TODO: make it portable
    __asm__ volatile (
        "syscall"
        :
        : "a"(60), "D"(__ec)
        : "rcx", "r11", "memory"
    );
}
