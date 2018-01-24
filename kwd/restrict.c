/**
 *  restrict
 *  ========
 *
 *  Like `register`, a dedicated keyword for optimization.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

void
foo(int n, char* restrict src, char* restrict dst)
{
	while (n-- > 0) *dst++ = *src++;
}

int
main()
{
	char s[100];

	memset(s, 42, 50);
	memset(s + 50, 69, 50);

	foo(50, s, s + 50);
	// foo(50, s + 1, s);
	assert(s[50] == 42);

	return 0;
}
