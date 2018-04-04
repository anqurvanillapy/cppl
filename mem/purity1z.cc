/**
 *  Purity in C++17
 *  ===============
 *
 *  Very naive attempt.
 *
 *  Note: Compile with -std=c++17.
 */

#include <tuple>
#include <cassert>

int i = 0;


template <typename T, typename ...Args>
class pure_io {
public:
	template <T F(const Args&...)>
	static constexpr T
	apply(const Args&... args) noexcept
	{
		static_assert(noexcept(F(args...)), "constant function required");
		constexpr auto ret = F(args...);
		return ret;
	}

	template <typename F, typename G>
	static constexpr T
	lapply(F f, G g) noexcept
	{
		constexpr auto ret = f(g());
		return ret;
	}
};

template <auto X, auto Y>
constexpr auto
foo()
{
	return X + Y;
}

int
main()
{
	static_assert(pure_io<int>::apply<foo<0, 42>>() == 42, "function oops");

	auto f_vals = [] {
		return std::make_tuple(0, 42);
	};
	auto f_swap = [](std::tuple<int, int> args) {
		return std::make_tuple(std::get<1>(args),
							   std::get<0>(args));
	};
	constexpr auto res = pure_io<std::tuple<int, int>>::lapply(f_swap, f_vals);
	static_assert(std::get<0>(res) == 42 && std::get<1>(res) == 0,
				  "lambda oops");

	return 0;
}
