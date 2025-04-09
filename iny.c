// inpavail_raw.c
#include <stdint.h>

#define SYS_poll 7

struct pollfd {
    int fd;
    short events;
    short revents;
};

long syscall(long n, ...);

void _start(void) {
    struct pollfd pfd = { .fd = 0, .events = 1 };
    long ret = syscall(SYS_poll, &pfd, 1, 0);

    long code = (ret > 0 && (pfd.revents & 1)) ? 0 : 1;

    // exit(code)
    __asm__ volatile (
        "mov $60, %%rax\n"  // syscall: exit
        "mov %0, %%rdi\n"
        "syscall\n"
        : : "r"(code) : "%rax", "%rdi"
    );
}
