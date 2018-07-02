/**
 *  C11 pointer unsoundness
 *  =======================
 *
 *  In C11, comparing 2 pointers derived from the same array object where at
 *  least one pointer points one element past of the array is *undefined*.
 *
 *  Note: Check out the following post
 *  https://stefansf.de/post/pointers-are-more-abstract-than-you-might-expect/.
 *  Compiling with -std=c11 -Wall -Wextra -pedantic spits nothing.
 */

#include <stdio.h>

const int NUM = 8;

int
main()
{
	int i;
	int* p;
	int x[NUM];

	for (i = 0; i < NUM; ++i) x[i] = i;
	// Comparing the pointer points to the 9th element is UB.
	for (p = x; p < &x[NUM]; ++p) printf("%d\n", *p);

	return 0;
}
