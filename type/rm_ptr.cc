/**
 *  Remove pointer
 *  ==============
 *
 *  Remove the pointer from type T, useful when tracking information of a
 *  function, instead of its pointer.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <functional>

long (*foo)(long);

int
main()
{
	std::function<std::remove_pointer_t<decltype(foo)>>::result_type i = 42;
	std::cout << sizeof i << std::endl;
	return 0;
}
