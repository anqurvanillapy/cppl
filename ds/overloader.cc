/**
 *  Overloader
 *  ==========
 *
 *  A class that exposes overloaded members of variadic bases without recursion,
 *  backed by a pack-expansion-based using-declaration.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <iomanip>

// `class' uncapable here.
template <typename... Ts>
struct matcher: Ts... {
	using Ts::operator()...;
};

template <typename... Ts>
matcher(Ts...) -> matcher<Ts...>;

int
main()
{
	auto m = matcher{
		[] (auto const& a) { std::cout << a << std::endl; },
		[] (const std::string& s) { std::cout << std::quoted(s) << std::endl; }
	};
	m(42);
	m("Hello, world!");
	return 0;
}
