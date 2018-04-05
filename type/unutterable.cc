/**
 *  Unutterable
 *  ===========
 *
 *  Lambda expression is unutterable.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

int
main()
{
	auto a = [] {};
	auto b = [] {};

	std::cout
		<< std::boolalpha
		<< std::is_same<decltype(a), decltype(b)>()
		<< std::endl;

	return 0;
}
