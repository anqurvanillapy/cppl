/**
 *  Tuple as return value
 *  =====================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <tuple>

// Good abstraction like a coordinate system should be retained, instead of
// returning a tuple.
struct good_abstracion_t {
	int a;
	int b;
};

std::tuple<int, int>
foo()
{
	// return std::make_tuple(42, 42);
	return {42, 69};
}

good_abstracion_t
bar()
{
	return {42, 69};
}

int
main()
{
	int a1, b1;
	auto[a2, b2]            = foo();
	std::tie(a1, b1)        = foo();
	good_abstracion_t x     = bar();

	std::cout
		<< "a1=" << a1 << ",\tb1=" << b1 << std::endl
		<< "a2=" << a2 << ",\tb2=" << b2 << std::endl
		<< "x.a=" << x.a << ",\tx.b=" << x.b << std::endl;

	return 0;
}
