/**
 *  Member declaration
 *  ==================
 *
 *  A pitfall about order of member declarations and their initializer list.
 */


#include <iostream>

class foo {
public:
	explicit foo(int i = 0)
		: c{++i}
		, b{++i}
		, a{++i}
	{
		/* nop */
	}

	int a;
	int b;
	int c;
};

int
main()
{
	foo x;

	std::cout
		<< "a=" << x.a
		<< ", b=" << x.b
		<< ", c=" << x.c
		<< std::endl;

	return 0;
}
