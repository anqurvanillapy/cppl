/**
 *  Patterm matching on values
 *  ==========================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <variant>
#include <iomanip>

template <int N>
using i_t = std::integral_constant<int, N>;

constexpr int
pow(int x, int y)
{
    return y == 0 ? 1 : x * pow(x, y - 1);
}

template <char...> struct int_constant_;

template <>
struct int_constant_<> {
    static const std::uint64_t value = 0;
    static const unsigned n = 0;
};

template <char C, char... Cs>
struct int_constant_<C, Cs...> {
    static const std::uint64_t value =
        (C - '0') * pow(10, int_constant_<Cs...>::n) +
        int_constant_<Cs...>::value;
    static const unsigned n = int_constant_<Cs...>::n + 1;
};

template <char... Cs>
constexpr auto
operator"" _i()
{
    constexpr auto n = int_constant_<Cs...>::value;
    return std::integral_constant<int, n>{};
}

template <typename... Ts> struct match : Ts... { using Ts::operator()...; };
template <typename... Ts> match(Ts...) -> match<Ts...>;

int
main()
{
    auto N = 42_i;
    auto S = "Hello";
    auto m = match {
        [](i_t<42> n) { std::cout << n() * 2 << std::endl; },
        [](i_t<69> n) { std::cout << n() + 2 << std::endl; },
        [](std::string& s) { std::cout << std::quoted(s) << std::endl; },
        [](auto&&) { std::cout << "not matched" << std::endl; }
    };
    std::variant<i_t<42>, i_t<69>, std::string> v0{N};
    std::variant<i_t<42>, i_t<69>, std::string> v1{S};

    std::visit(m, v0);
    std::visit(m, v1);

    return 0;
}
