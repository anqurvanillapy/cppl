/**
 *  Bad function prototype
 *  ======================
 */

#include <stdio.h>

// This is a valid function prototype, but indicates that it receives abitrary
// number of arguments.
void bad();

int
main()
{
	bad();
	return 0;
}

void
bad(int x)
{
	printf("%d\n", x);
}
