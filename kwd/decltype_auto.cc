/**
 *  decltype(auto)
 *  =============
 *
 *  2 use cases of `decltype(auto)`.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

/* Perfectly forwards a return type. */

template <typename T, class... Args>
decltype(auto)
apply(T f, Args&&... args)
{
	return f(std::forward<Args>(args)...);
}

/* Delaying return type deduction in recursive templates. */

template <int N> struct int_v { static constexpr int value = N; };

#pragma clang diagnostic ignored "-Wundefined-inline"
constexpr auto iter(int_v<0>) -> int_v<0>;

template <int N>
constexpr decltype(auto)
iter(int_v<N>)
{
	return iter(int_v<N - 1>{});
}

int
main()
{
	auto foo = apply(
		[](int a) { return a * a; },
		42
	);
	std::cout << foo << std::endl;

	decltype(iter(int_v<3>{})) bar;
	static_assert(bar.value == 0, "expected 0 at compile time");

	return 0;
}
