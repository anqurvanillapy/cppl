/**
 *  Return initializer list
 *  =======================
 *
 *  An example of returning initializer list mechanism.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <array>

/// There are no performance penalties involved between foo and bar.  The return
/// value is constructed equivalent to c, and there is not even a single copy or
/// move of an std::array instance involved.
std::array<int, 3>
foo()
{
	return { 1, 2, 3 };
}

std::array<int, 3>
bar()
{
	return std::array<int, 3>{ 1, 2, 3 };
}

int
main()
{
	auto a = foo();
	auto b = bar();
	std::array<int, 3> c = { 1, 2, 3 };

	std::cout << a.size() << std::endl;
	std::cout << b.size() << std::endl;
	std::cout << c.size() << std::endl;

	return 0;
}
