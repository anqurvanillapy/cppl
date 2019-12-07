/**
 * Static reflection of POD
 * ========================
 *
 * Note: Compile with -std=c++17, with gcc9.x.
 */
#include <iostream>
#include <functional>
#include <tuple>
#include <type_traits>
#include <utility>

namespace detail {

template <typename T>
struct AlwaysFalse : std::false_type {};

template <typename T>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto always_false_v = AlwaysFalse<T>::value;

template <typename T, typename... Args>
decltype(void(T{{std::declval<Args>()}...}), std::true_type{}) TestIsAggregateInitializable(int);

template <typename, typename...>
std::false_type TestIsAggregateInitializable(...);

template <typename T, typename... TArgs>
using IsAggregateInitializable = decltype(TestIsAggregateInitializable<T, TArgs...>(0));

struct AnyType {
    template <typename T>
    constexpr operator T &() const noexcept;
};

template <typename T>
auto StructToTuple(T &&data) noexcept
{
    using Type = std::decay_t<T>;

    static_assert(std::is_standard_layout_v<Type> && std::is_trivial_v<Type>, "T should be a POD type");

    /* } else */ if constexpr (IsAggregateInitializable<Type, AnyType, AnyType, AnyType, AnyType, AnyType, AnyType>{}) {
        auto &&[p1, p2, p3, p4, p5, p6] = data;
        return std::make_tuple(p1, p2, p3, p4, p5, p6);
    } else if constexpr (IsAggregateInitializable<Type, AnyType, AnyType, AnyType, AnyType, AnyType>{}) {
        auto &&[p1, p2, p3, p4, p5] = data;
        return std::make_tuple(p1, p2, p3, p4, p5);
    } else if constexpr (IsAggregateInitializable<Type, AnyType, AnyType, AnyType, AnyType>{}) {
        auto &&[p1, p2, p3, p4] = data;
        return std::make_tuple(p1, p2, p3, p4);
    } else if constexpr (IsAggregateInitializable<Type, AnyType, AnyType, AnyType>{}) {
        auto &&[p1, p2, p3] = data;
        return std::make_tuple(p1, p2, p3);
    } else if constexpr (IsAggregateInitializable<Type, AnyType, AnyType>{}) {
        auto &&[p1, p2] = data;
        return std::make_tuple(p1, p2);
    } else if constexpr (IsAggregateInitializable<Type, AnyType>{}) {
        auto &&[p1] = data;
        return std::make_tuple(p1);
    } else {
        static_assert(always_false_v<Type>, "Data type is empty or contains too many fields");
    }
}

template <size_t I = 0, typename T, size_t Size = std::tuple_size_v<std::remove_reference_t<T>>, typename Fn,
          typename... Args>
void PodForEachHelper(T &&tuple, Fn &&fn, Args &&... args)
{
    if constexpr (I < Size) {
        std::invoke(fn, args..., std::get<I>(tuple));

        if constexpr (I + 1 < Size) {
            PodForEachHelper<I + 1>(std::forward<T>(tuple), std::forward<Fn>(fn), std::forward<Args>(args)...);
        }
    }
}

} /* namespace detail */

template <typename T, typename Fn, typename... Args>
void PodForEach(T &&data, Fn &&fn, Args &&... args)
{
    detail::PodForEachHelper(detail::StructToTuple(data), fn, args...);
}

template <typename T, typename = std::enable_if_t<std::is_standard_layout_v<T> && std::is_trivial_v<T>>>
// NOLINTNEXTLINE(readability-identifier-naming)
inline constexpr auto fields_size_v = std::tuple_size_v<std::invoke_result_t<decltype(detail::StructToTuple<T>), T>>;

struct Data {
    int a;
    char b[2];
    bool c;
};

int main()
{
    std::cout << "fields size: " << fields_size_v<Data> << std::endl;

    PodForEach(Data{1, "a", true},
        [](const auto& v) { std::cout << std::boolalpha << v << std::endl; });

    return 0;
}
