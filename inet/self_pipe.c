/**
 *  Self-pipe trick
 *  ===============
 *
 *  This avoids race conditions while both selecting on a set of fds and also
 *  waiting for a signal.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#define log_fatal(errmsg) do \
    { \
        fprintf(stderr, errmsg "\n"); \
        _exit(1); \
    } while(0) \

static int pfd[2];  // pipe fds

static void
sighandler(int sig)
{
    int savederrno; // in case of changing `errno'

    savederrno = errno;
    if (write(pfd[1], "x", 1) < 0 && errno != EAGAIN) log_fatal("write error");
    errno = savederrno;
}

int
main(int argc, const char *argv[])
{
    long to_sec = 4;
    int selectfds[] = {0, 1, 2};

    fd_set readfds;
    int ready, nfds, flags;
    struct timeval timeout;
    struct timeval *pto;
    char ch;
    int fd, i;

    // Init timeout and nfds.
    pto = &timeout;
    timeout.tv_sec = to_sec;
    timeout.tv_usec = 0;
    nfds = 0;

    // Build the readfds.
    for (i = 0; i < 3; ++i) {
        int fd = selectfds[i];
        if (fd >= FD_SETSIZE) log_fatal("fd exceeds limit");
        if (fd >= nfds) nfds = fd + 1;
        FD_SET(fd, &readfds);
    }

    // TODO

    return 0;
}
