/**
 *  Narrow cast
 *  ===========
 *
 *  Better narrowing, due to GSL.
 *
 *  Note: Compile with -std=c++17.
 */

#include <utility>
#include <cassert>

template <typename T, typename U>
constexpr T
narrow_cast(U&& u) noexcept
{
	return static_cast<T>(std::forward<U>(u));
}

int
main()
{
	constexpr int a = 42;
	static_assert(size_t{a} == 42ul); // literals are fine

	int b = 69;
	assert(narrow_cast<size_t>(b) == 42ul);
	// {...} prohibits implicit narrowing conversions here, yelling -Wnarrowing.
	// assert(size_t{b} == 69ul);

	return 0;
}
