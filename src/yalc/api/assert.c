#include <yalc/config.h>
#include __YALC_API_INC(assert.h)
#include __YALC_API_INC(stdlib.h)

// TODO: portable input/output
long write(int fd, const void *buf, unsigned long count) {
    long ret;
    __asm__ volatile (
        "syscall"
        : "=a"(ret)
        : "a"(1), "D"(fd), "S"(buf), "d"(count)
        : "rcx", "r11", "memory"
    );
    return ret;
}

__YALC_NO_RETURN__
void __yalc_assert_fail(
    const char* _msg, const char* _file,
    int _line, const char* _func
) {
    (void)_msg, (void)_file;
    (void)_line, (void)_func;
    char buf[] = "Assertion failed";

    // TODO: portable input/output
    write(2, buf, sizeof buf - 1);

    //fprintf(stderr, "Assertion failed: %s (%s: %s: %d)\n", expr, file, func, line);
	//abort();
    exit(1);
}
