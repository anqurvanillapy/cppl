/**
 *  Fold expression
 *  ===============
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

using namespace std::literals;

template <typename... Args>
void
vprintln(Args&&... args)
{
	(std::cout << ... << (args + ", "s)) << std::endl;
}

int
main()
{
	vprintln("foo", "bar", "Hello, world!");
	return 0;
}
