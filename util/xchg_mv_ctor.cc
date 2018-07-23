/**
 *  mv ctor with std::exchange
 *  ==========================
 *
 *  A more convenient way for std::move semantics.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <iomanip>
#include <utility>

struct foo {
	int a;
	std::string b;

	foo(int a_, std::string b_)
		: a{a_}
		, b{b_}
	{
		/* nop */
	} 

	foo(foo&& rhs)
		: a{std::exchange(rhs.a, 0)}
		, b{std::exchange(rhs.b, "")}
	{
		/* nop */
	}

	foo&
	operator=(foo&& rhs)
	{
		a = std::exchange(rhs.a, 0);
		b = std::exchange(rhs.b, "");
		return *this;
	}
};

int
main()
{
	foo a = {42, "Hello, world"};
	foo b = std::move(a);
	std::cout
		<< a.a              << std::endl
		<< std::quoted(a.b) << std::endl
		<< b.a              << std::endl
		<< std::quoted(b.b) << std::endl;
	return 0;
}
