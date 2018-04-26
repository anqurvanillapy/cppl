/**
 *  std::variant
 *  ============
 *
 *  Type-safe union.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <variant>

int
main()
{
	std::variant<int, std::string> a, b;
	a = 42;
	b = "Hello, world!";
	std::cout << std::get<int>(a) << std::endl;
	try {
		std::cout << std::get<int>(b) << std::endl;
	} catch (const std::bad_variant_access&) {
		/* nop */
	}
	std::cout << std::get<std::string>(b) << std::endl;
	return 0;
}
