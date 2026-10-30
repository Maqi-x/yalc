#include <yalc/config.h>

#include __YALC_API_INC(stdlib.h)
#include __YALC_RT_INC(start.h)
#include __YALC_INC(cstd.h)

extern int main(int argc, char** argv, char** envp);

__YALC_NO_RETURN__
void _start() {
    // TODO: arguments passing
    char* argv[1] = {NULL};
    char* envp[1] = {NULL};
    int argc = 0;

    exit(main(argc, argv, envp));
}
