/**
 *  myecho
 *  ======
 *
 *  Namely the `echo` command, inspired by the OpenBSD's one.
 */

#include <stdio.h>
#include <string.h>

int
main(int argc, const char *argv[])
{
	(void)argc;
	int nl = 0;

	if (*++argv && !strcmp(*argv, "-n")) {
		++argv;
		nl = 1;
	}

	while (*argv) {
		fputs(*argv, stdout);
		if (*++argv) {
			putchar(' ');
		}
	}

	if (!nl) {
		putchar('\n');
	}

	return 0;
}
