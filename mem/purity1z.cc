/**
 *  Purity in C++17
 *  ===============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <tuple>

class pure_io {
public:
	template <auto F()>
	static constexpr auto
	fapply() noexcept
	{
		static_assert(noexcept(F()), "constant function required");
		constexpr auto ret = F();
		return ret;
	}

	template <typename F, typename G>
	static constexpr auto
	lapply(F f, G g) noexcept
	{
		static_assert(noexcept(g()), "no-param lambda required at arg#1");
		constexpr auto ret = f(g());
		return ret;
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

int
main()
{
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

	return 0;
}
