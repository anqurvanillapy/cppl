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
#include <cassert>

// Annotate in the header that the return value of the function is probably
// a pointer that will not be deleted on the heap, passing the ownership to the
// caller.
template <class T, class = std::enable_if_t<std::is_pointer<T>::value>>
using owner = T;

class foo {
public:
	static owner<foo*>
	get()
	{
		if (!i_) i_ = new foo;
		return i_;
	}

	static void
	do_something()
	{
		assert(i_ != nullptr && "singleton is not alive");
	}
private:
	foo() = default;

	static foo* i_;
};

foo* foo::i_{};

int
main()
{
	auto p = foo::get();
	p->do_something();
	delete p;

	return 0;
}
