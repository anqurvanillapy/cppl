/**
 *  Using definitions
 *  =================
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

struct Color {
    using ColorType = enum class ColorType : int {
        Red,
        Green,
        Blue,
    };

    int ColorValue;
};

using X = struct {
    int A;
};

int main()
{
    Color c;
    c.ColorValue = static_cast<int>(Color::ColorType::Blue);
    std::cout << c.ColorValue << std::endl;

    X x;
    x.A = 42;
    std::cout << x.A << std::endl;

    return 0;
}
