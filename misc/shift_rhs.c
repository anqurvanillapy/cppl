#include <assert.h>

int
main()
{
	int n = 0;

	int a = 1 << 32;
	int b = 1 << (n + 32);

	assert(a == 0);
	assert(b == 1);
	return 0;
}
