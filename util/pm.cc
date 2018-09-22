/**
 *  Pattern matching
 *  ================
 *
 *  Use std::variant, std::visit and overloaded to have a weird taste of pattern
 *  matching in C++17.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <iomanip>
#include <variant>

template <typename... Ts> struct case_of : Ts... { using Ts::operator()...; };
template <typename... Ts> case_of(Ts...) -> case_of<Ts...>;

int
main()
{
	std::variant<int, std::string> v = 42;

	std::visit(case_of {
		[](int a) { std::cout << a << std::endl; },
		[](std::string&& a) { std::cout << std::quoted(a) << std::endl; },
		[](auto&&) { std::cout << "default" << std::endl; }
	}, v);

	return 0;
}
