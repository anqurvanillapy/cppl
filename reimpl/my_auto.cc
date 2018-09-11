/**
 *  Homemade auto
 *  =============
 *
 *  Some homebrews of simulating `auto` keyword.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

template <typename T>
constexpr T
def_auto(T v)
{
	return v;
}

template <typename T>
inline void
def_auto_ref(T& v)
{
	// Function body for the use of referent.
	++v;
}

template <typename T>
struct auto_ref
{
	constexpr explicit auto_ref(T& v)
		: referent{v}
	{
		/* nop */
	}

	inline T&
	operator++()
	{
		return ++referent;
	}

	T& referent;
};

int
main()
{
	// auto a = 42;
	// std::cout << a << std::endl;
	std::cout << def_auto(42) << std::endl;

	int b = 42;
	// auto& r = b;
	// r++;
	def_auto_ref(b);
	std::cout << b << std::endl;

	int c = 69;
	auto_ref r(c);
	++r;
	std::cout << c << std::endl;

	return 0;
}
