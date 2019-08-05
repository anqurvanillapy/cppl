/**
 *  std::move WYW
 *  =============
 *
 *  Move whatever you want.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

class X {
public:
    X() {std::cout << "ctor\n"; }
    ~X() { std::cout << "dtor\n"; }
};

class Y {
public:
    Y(X x) : x_{std::move(x)} {}
    ~Y() = default;
private:
    X x_;
};

int main()
{
    X x;
    Y y0{x}; // copy
    Y y1{std::move(x)}; // move
    return 0;
}
