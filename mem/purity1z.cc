/**
 *  Purity in C++17
 *  ===============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <type_traits>
#include <tuple>

class pure_io {
public:
	template <auto F()>
	static constexpr auto
	fapply() noexcept
	{
		static_assert(noexcept(F()), "constant function required");

		if constexpr (!std::is_same<decltype(F()), void>::value) {
			constexpr auto ret = F();
			return ret;
		}

		F();
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
			if constexpr (std::is_same<decltype(f()), void>::value) {
				f();
				return;
			} else {
				constexpr auto ret = f();
				return ret;
			}
		} else {
			if constexpr (std::is_same<decltype(f(g())), void>::value) {
				f(g());
				return;
			}

			constexpr auto ret = f(g());
			return ret;
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
};

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

	constexpr auto n0 = pure_io::fapply<bar<0, 42>>();
	static_assert(n0 == 84, "foo bar oops");
	static_assert(pure_io::fapply<baz<n0>>() == 85, "baz oops");

	auto f_vals = [] {
		return std::make_tuple(0, 42);
	};
	auto f_swap = [](auto args) {
		return std::make_tuple(std::get<1>(args),
							   std::get<0>(args));
	};
	constexpr auto n1 = pure_io::lapply(f_swap, f_vals);
	static_assert(std::get<0>(n1) == 42 && std::get<1>(n1) == 0,
				  "lambda oops");

	/**
	 *  Test functions/lambdas with return type `void'.
	 */

	pure_io::fapply<qux>();

	auto f_return_nil = [] {};
	auto f_invoke_nil = [] {};
	pure_io::lapply(f_invoke_nil, f_return_nil);

	/**
	 *  Test functions/lambdas with side-effects.
	 */

	static_assert(!pure_io::is_f_pure<quux>(), "don't touch i yo");

	auto f = [] { return 42; };
	auto f_inc_i = [](auto n) {
		++i;
		return n;
	};
	static_assert(!pure_io::is_l_pure(f_inc_i, f), "don't touch i yo");

	return 0;
}
