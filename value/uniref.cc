/**
 *  Universal reference
 *  ===================
 *
 *  An example of the ambiguity of T&&, using overloading.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

template <typename T>
void
pick(T&)
{
    std::cout << "lvalue" << std::endl;
}

template <typename T>
void
pick(T&&)
{
    std::cout << "rvalue" << std::endl;
}

template <typename T>
void
pick_from_two(T&& t)
{
    pick(t);
}

int
main(int argc, const char *argv[])
{
    int i = 42;

    // Type deduction here! 42 treated as a lvalue.
    pick_from_two(42);
    pick_from_two(i);

    return 0;
}
