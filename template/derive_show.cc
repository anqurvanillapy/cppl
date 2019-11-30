/**
 * Deriving Show/Debug in C++
 * ==========================
 *
 * How to print a struct/class without declaring `operator<<` function
 * overloading, and get a bonus of structure-binding the struct/class.
 *
 * Note: Compile with -std=c++17.
 */

#include <iostream>
#include <tuple>
#include <functional>
#include <sstream>

class Data final {
public:
    template <size_t I>
    auto& get() & {
        if      constexpr(I == 0) return data;
        else if constexpr(I == 1) return data_;
    }

    template <size_t I>
    const auto& get() const& {
        if      constexpr(I == 0) return data;
        else if constexpr(I == 1) return data_;
    }

    template <size_t I>
    auto&& get() && {
        if      constexpr(I == 0) return std::move(data);
        else if constexpr(I == 1) return std::move(data_);
    }

public:
    int data{42};

private:
    int data_{69};
};

namespace std {
    template <> struct tuple_size<Data> : std::integral_constant<size_t, 2> {};

    template <> struct tuple_element<0, Data> { using type = int; };
    template <> struct tuple_element<1, Data> { using type = int; };
}

/**
 * Generic for-each for tuple-like types.
 */
template <
    size_t I = 0,
    typename TupleT,
    size_t Size = std::tuple_size_v<std::remove_reference_t<TupleT>>,
    typename Fn,
    typename... Args
>
void ForEach(TupleT&& tuple, Fn&& fn, Args&&... args)
{
    if constexpr (I < Size) {
        std::invoke(fn, args..., tuple.template get<I>());

        if constexpr (I + 1 < Size) {
            ForEach<I + 1>(
                std::forward<TupleT>(tuple),
                std::forward<Fn>(fn),
                std::forward<Args>(args)...
            );
        }
    }
}

template <typename T>
std::string Print(const T& v)
{
    std::stringstream out{};
    out << "struct{";
    ForEach(v, [&](const auto& item) { out << item << ","; });
    out.seekp(-1, out.cur);
    out << "}";
    return out.str();
}

int main()
{
    auto [a, b] = Data{};
    std::cout << "struct{" << a << ',' << b << '}' << std::endl;

    std::cout << Print(Data{}) << std::endl;
    return 0;
}
