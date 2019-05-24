/**
 *  Using definitions
 *  =================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

using Color = enum class Color : int {
    Red,
    Green,
    Blue,
};

using X = struct {
    int A;
};

int main()
{
    Color c;
    c = Color::Blue;
    std::cout << static_cast<int>(c) << std::endl;

    X x;
    x.A = 42;
    std::cout << x.A << std::endl;

    return 0;
}
