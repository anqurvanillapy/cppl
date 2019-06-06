/**
 *  Stateful metaprogramming
 *  ========================
 *
 *  This is arcane and almost the darkest corner of C++.
 *
 *  Note: Compile with -std=c++17.
 */

#include <type_traits>

template <int N>
struct flag {
    // Argument-dependent lookup.
    // warning: friend declaration ‘...’ declares a non-template function
    // [-Wnon-template-friend]
    friend constexpr int adl_flag(flag<N>);
    constexpr operator int() { return N; }
};

template <int N>
struct write {
    friend constexpr int adl_flag(flag<N>) { return N; }
    static constexpr int value = N;
};

template <int N, int = adl_flag(flag<N>{})>
constexpr int read(int, flag<N>, int R = read(0, flag<N + 1>{}))
{
    return R;
}

template <int N = 0>
constexpr int read(double, flag<N>)
{
    return N;
}

template <int N = 0>
constexpr int counter(int R = write<read(0, flag<0>{}) + N>::value)
{
    return R;
}

template <int = counter()>
struct S {};

int main()
{
    static_assert(counter() != counter(), "well done holy compiler");
    static_assert(!std::is_same_v<S<>, S<>>, "good boy");

    return 0;
}
