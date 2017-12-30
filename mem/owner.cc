/**
 *  Ownership
 *  =========
 *
 *  Case study of ownership, mainly based on CppCoreGuidelines.
 *
 *  Note: Compile with -std=c++14.
 */

#include <iostream>
#include <type_traits>

// Annotate in the header that the return value of the function is probably
// a pointer that will not be deleted on the heap, passing the ownership to the
// caller.
template <class T, class =std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;

class foo {
	foo()
	{
		std::cout << "foo ctor" << std::endl;
	}

	friend owner<foo*> get_foo();
};

owner<foo*>
get_foo()
{
	return new foo;
}

int
main()
{
	auto p = get_foo();
	delete p;
	return 0;
}
