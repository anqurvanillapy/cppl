/**
 *  kill(2) ruins a day
 *  ===================
 *
 *  An example of how fork(2) and kill(2) together can cause some troubles.
 *
 *  Note: Do not ever try running this...
 */

#define _POSIX_SOURCE
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int
main(int argc, const char *argv[])
{
    pid_t p = fork();

    if (p) {    // parent
        sleep(5);
        // If fork(2) fails and the p will be -1.  kill(2) receives -1 and
        // simply sends the SIG* to all processes (excluding an unspecified set
        // of system processes) for which the process has permission to send
        // that signal.  Boom.
        kill(p, SIGKILL);
    } else {    // child
        for (;;);   // wait until killed
    }

    return 0;
}
