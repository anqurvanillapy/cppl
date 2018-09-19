/**
 *  Lambda init
 *  ===========
 *
 *  Lambda expression with initialization in the capturings.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

struct foo_t {
	void
	foo() const /* const is required */
	{
		std::cout << "foo" << std::endl;
	}
};

auto f = [a = foo_t{}]() {
	a.foo();
};

int
main()
{
	f();
	return 0;
}
