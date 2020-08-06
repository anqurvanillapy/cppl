#include <type_traits>

using Top = int;

template <typename T, T a, T b>
struct IdProp { using type = void; };

template <typename T, T a>
struct IdProp<T, a, a> { using type = Top; };

template <typename T, T a, T b>
using Id = typename IdProp<T, a, b>::type;

template <typename T, T a>
constexpr Id<T, a, a> idp{};

template <typename T, T a, T b, Id<T, a, b> p>
constexpr Id<T, b, a> sym() { return p; }

int main() {
    static_assert(sym<int, 1, 1, idp<int, 1>>() == idp<int, 1>);
}
