/**
 * Enum to string
 * ==============
 *
 * Static reflection of `enum`s/`enum class`es.
 *
 * Note: Compile with clang++ -std=c++17.
 */

#include <iostream>

enum class Level { A, B, C };

template <typename E, E V>
[[nodiscard]] constexpr auto enum_to_string() noexcept {
    std::string_view sv = __PRETTY_FUNCTION__;
    sv.remove_prefix(38);
    sv.remove_suffix(1);
    std::cout << sv << std::endl;
}

int main()
{
    enum_to_string<Level, Level::A>();
    return 0;
}
