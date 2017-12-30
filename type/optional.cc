/**
 *  std::optional<T>
 *  ================
 *
 *  Optional type in C++17.  Say bye to `v8::maybe<T>`.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <optional>

std::optional<std::string>
sayhi(bool alright)
{
	if (alright) return "Hi!";
	return {};
}

int
main()
{
	std::cout << sayhi(true).value() << std::endl;
	std::cout << sayhi(false).value_or("Meh!") << std::endl;
	return 0;
}
