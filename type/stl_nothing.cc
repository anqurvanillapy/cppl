/**
 *  Nothing type in STL
 *  ===================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>
#include <tuple>

using nothing_t = std::tuple<>;

int main()
{
    auto nothing = nothing_t{};
    (void)nothing;
    std::cout << sizeof(nothing_t) << std::endl;
    return 0;
}
