/**
 *  Nope
 *  ====
 *
 *  A fast yes, but no.
 *
 *  Note: The benchmarks are machine-specific.  Use `pv >/dev/null' to monitor
 *  the process.
 */

#include <stdio.h>
#include <unistd.h>

int
main(int argc, const char *argv[])
{
    if (argc > 1) {
        printf("Usage: nope\n");
        return 1;
    }

    char str[] = "n\n";

    // About 5MiB/s.
    // for (;;) write(1, str, sizeof(str));

    // About 50MiB/s.
    // for (;;) printf("%s", str);

    // About 110MiB/s.
    // for (;;) puts("n");

    // About 120MiB/s.
    // for (;;) fprintf(stdout, "%s", str);

    // About 7.4GiB/s without flags, geez.
    // Have a try: -O2 -pipe -march=native -mtune=native
    char buf[BUFSIZ];
    int i;

    for (i = 0; i < BUFSIZ; ++i) buf[i] = str[i%2];
    for (;;) write(1, buf, BUFSIZ);

    return 0;
}
