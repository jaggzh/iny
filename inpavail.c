#include <poll.h>
/* #include <stdio.h> */
/* #include <unistd.h> */

int main(void) {
    //struct pollfd pfd = { .fd = STDIN_FILENO, .events = POLLIN };
    struct pollfd pfd = { .fd = 0, .events = POLLIN };

    int ret = poll(&pfd, 1, 0);  // timeout = 0 for non-blocking check

    if (ret > 0 && (pfd.revents & POLLIN))
        return 0;  // data is available
    else
        return 1;  // no data
}
