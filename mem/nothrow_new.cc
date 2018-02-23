/*
 *  new(std::nothrow) T
 *  ===================
 *
 *  Note: Compile with -DTEST_NOTHROW.
 */

#include <iostream>
#define OVERLOAD 100000000ul

void
bad_alloc()
{
#ifdef TEST_NOTHROW
	for (;;) {
		int* p = new(std::nothrow) int[OVERLOAD];
		if (p == nullptr) {
			std::cout << "bad_alloc w/ std::nothrow" << std::endl;
			break;
		}
	}
#else
	try {
		for (;;) new int[OVERLOAD];
	} catch (const std::bad_alloc& e) {
		std::cout << e.what() << std::endl;
	}
#endif
}

int
main()
{
	bad_alloc();
	return 0;
}
