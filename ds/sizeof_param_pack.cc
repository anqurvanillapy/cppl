/**
 *  sizeof... operator
 *  ==================
 *
 *  This operator queries the number of elements in a parameter pack.
 *
 *  Note: Compile with -std=c++14.
 */

#include <iostream>
#include <array>
#include <type_traits>

template <typename... Ts>
/// `auto' here doesn't mean type checking, just a part of auto identifier
/// function declaration syntax.
constexpr auto
/// ts here is universal reference.
make_array(Ts&&... ts)
/// Determines the common type among all types Ts..., that is the type all Ts...
/// can be implicitly converted to.  sizeof.. returns a constant of type
/// std::size_t of the parameter pack's size. Note that std::common_type_t is a
/// helper type since C++14 for common_type in C++11.
    -> std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
    // Expands the pack, forward ts as lvalue or as rvalue depending on type T.
    // Here it returns an initializer list for the array.
    return { std::forward<Ts>(ts)... };
}

int
main(int argc, const char *argv[])
{
    auto arr = make_array(1, 2, 3);

    std::cout << "size=" << arr.size() << std::endl;
    for (auto i : arr) std:: cout << i << ' ';
    std::cout << std::endl;

    return 0;
}
