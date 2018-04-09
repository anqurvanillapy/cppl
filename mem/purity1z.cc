/**
 *  Purity in C++17
 *  ===============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <tuple>

namespace ppio {

template <auto F()>
static constexpr auto
fapply() noexcept
{
	static_assert(noexcept(F()), "constant function required");
	return F();
}

template <auto F()>
static constexpr bool
is_f_pure() noexcept
{
	return noexcept(F());
}

template <typename F, typename G>
static constexpr auto
lapply(F f, G g) noexcept
{
	static_assert(noexcept(g()), "no-param lambda required at arg#1");

	// `else' branch cannot be omitted with `constexpr'.
	if constexpr (std::is_same<decltype(g()), void>::value) {
		return f();
	} else {
		return f(g());
	}
}

template <typename F, typename G>
static constexpr bool
is_l_pure(F f, G g) noexcept
{
	constexpr bool is_g = noexcept(g());
	if constexpr (std::is_same<decltype(g()), void>::value) {
		return noexcept(f());
	} else {
		return noexcept(f(g())) && is_g;
	}
}

} /* namespace ppio */

template <auto N>
constexpr auto
foo()
{
	return N * 2;
}

template <auto X, auto Y>
constexpr auto
bar()
{
	return foo<X + Y>();
}

template <auto N>
constexpr auto
baz()
{
	return N + 1;
}

constexpr void
qux()
{
	/* nop */
}

int i = 0;

void
quux() noexcept
{
	++i;
}

int
main()
{
	/**
	 *  Basic.
	 */

	constexpr auto n0 = ppio::fapply<bar<0, 42>>();
	static_assert(n0 == 84, "foo bar oops");
	static_assert(ppio::fapply<baz<n0>>() == 85, "baz oops");

	auto f_vals = [] {
		return std::make_tuple(0, 42);
	};
	auto f_swap = [](auto args) {
		auto [a, b] = args;
		return std::make_tuple(b, a);
	};
	constexpr auto n1 = ppio::lapply(f_swap, f_vals);
	static_assert(std::get<0>(n1) == 42 && std::get<1>(n1) == 0,
				  "lambda oops");

	/**
	 *  Test functions/lambdas with return type `void'.
	 */

	ppio::fapply<qux>();

	auto f_return_nil = [] {};
	auto f_invoke_nil = [] {};
	ppio::lapply(f_invoke_nil, f_return_nil);

	/**
	 *  Test functions/lambdas with side-effects.
	 */

	static_assert(!ppio::is_f_pure<quux>(), "don't touch i yo");

	auto f = [] { return 42; };
	auto f_inc_i = [](auto n) {
		++i;
		return n;
	};
	static_assert(!ppio::is_l_pure(f_inc_i, f), "don't touch i yo");

	return 0;
}
