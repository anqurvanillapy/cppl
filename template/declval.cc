/**
 *  declval
 *  =======
 *
 *  Converts any type T to a reference type to bypass the ctors.
 *
 *  Note: Compile with -std=c++17.
 */

#include <utility>

class foo {
public:
	auto
	operator()() const
	{
		return 42;
	}
};

class bar {
public:
	bar() = delete;

	auto
	operator()() const
	{
		return 69;
	}
};

template <typename T>
void
f(T a)
{
	static_assert(std::is_same_v<decltype(a), int>);
}

int
main()
{
	decltype(foo()()) a = 1;
	// decltype(bar()()) b = 2; // call of deleted function
	decltype(std::declval<bar>()()) c = 3;
	std::invoke_result_t<decltype(std::declval<bar>())> d = 4;
	f(a); f(c); f(d);
	return 0;
}
