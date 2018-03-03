/**
 *  Swap 2 vars w/ -O3
 *  ==================
 *
 *  -O3 well optimizes swapping of 2 variables.  Use -S to read the assembly
 *  code.
 */
#include <stdio.h>

int
main()
{
	int a, b, temp;

	a = 42;
	b = 69;

	temp = a;
	a = b;
	b = temp;

	printf("a=%d, b=%d w/ temp\n", a, b);

	a = 42;
	b = 69;

	a += b;
	b = a - b;
	a -= b;

	printf("a=%d, b=%d w/o temp\n", a, b);

	return 0;
}
