/**
 *  Sign for int32_t
 *  ================
 *
 *  If an int32_t variable is positive, returns 1, else if it is negative,
 *  returns -1, else returns 0.
 */

#include <assert.h>

int
i32sign(int n)
{
	int tmp = n >> 31;
	return ~(tmp & 1) + (!(tmp ^ 0) & !!n) + 1;
}

int
main()
{
	assert(i32sign(42) == 1);
	assert(i32sign(0) == 0);
	assert(i32sign(-42) == -1);
	return 0;
}
