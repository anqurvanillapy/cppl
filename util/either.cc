/**
 * Either
 * ======
 *
 * A pointer-tagged Either type.
 *
 * Note: Compile with -std=c++17.
 */

#include <iostream>
#include <cstdint>

template <
    typename L,
    typename R,
    typename = std::enable_if_t<
        std::is_pointer_v<L> &&
        std::is_pointer_v<R>
    >
>
class Either final {
public:
    using left_type = L;
    using right_type = R;

    constexpr Either() noexcept
        : value_{}
    { }

    constexpr Either(L left) noexcept
        : value_{reinterpret_cast<uintptr_t>(left) | TAG_LEFT}
    { }

    constexpr Either(R right) noexcept
        : value_{reinterpret_cast<uintptr_t>(right) | TAG_RIGHT}
    { }

    [[nodiscard]] constexpr bool is_left() const noexcept
    {
        return static_cast<bool>(value_ & TAG_LEFT);
    }

    [[nodiscard]] constexpr bool is_right() const noexcept
    {
        return static_cast<bool>(value_ & TAG_RIGHT);
    }

    [[nodiscard]] constexpr L left() const noexcept
    {
        return reinterpret_cast<L>(value_ & RESET);
    }

    [[nodiscard]] constexpr R right() const noexcept
    {
        return reinterpret_cast<R>(value_ & RESET);
    }

private:
    static constexpr uintptr_t TAG_LEFT = 1U << 0U;
    static constexpr uintptr_t TAG_RIGHT = 1U << 1U;
    static constexpr uintptr_t RESET = 0xFFFFFFFFFFFFFFF8;

    uintptr_t value_;
};

int main()
{
    std::cout << std::boolalpha;

    // Must be heap-allocated.
    int *n = new int{42};
    std::string s = "hello";

    Either<int *, const char *> a{n};
    std::cout << "a is_left: " << a.is_left() << std::endl;
    std::cout << "a is_right: " << a.is_right() << std::endl;
    std::cout << "a value: " << *a.left() << std::endl;

    Either<int *, const char *> b{s.data()};
    std::cout << "b is_left: " << b.is_left() << std::endl;
    std::cout << "b is_right: " << b.is_right() << std::endl;
    std::cout << "b value: " << b.right() << std::endl;

    delete n;
}
