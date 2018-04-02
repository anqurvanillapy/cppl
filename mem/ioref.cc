/**
 *  IORef in C++
 *  ============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <functional>
#include <cassert>

int i = 0;

void __attribute__((const))
foo()
{
	++i;
}

int
main()
{
	assert(i == 0);
	return 0;
}
