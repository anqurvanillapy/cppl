/**
 *  Memory laundering
 *  =================
 *
 *  Perhaps for non-UB type punning.
 *
 *  Note: Compile with -std=c++17.
 */
#include <iostream>

struct foo {
	const int n;
};

union bar {
	foo x;
	double y;
};

int
main()
{
	bar a = {{42}};
	foo* p0 = new (&a.x) foo{69};
	// foo.n is const, so there could be unexpected optimizations.
	// std::cout << p->n << std::endl;
	std::cout << *std::launder(&p0->n) << std::endl;

	std::aligned_storage_t<sizeof(int), alignof(int)> i;
	new (&i) int{42};
	// The compiler is prevented to trace the original object.
	// int* p1 = (int*)(&i);
	int* p1 = std::launder(reinterpret_cast<int*>(&i));
	std::cout << *p1 << std::endl;
	return 0;
}
