/**
 *  Type deduction
 *  ==============
 *
 *  Some examples of template functions' type deduction.
 */

#include <iostream>

template <typename T>
void
foo(T n)
{
    std::cout << n << std::endl;
}

template <typename T1, typename T2>
void
bar(T1 i)
{
    T2 j = 0;
    std::cout << i + j << std::endl;
}

int
main(int argc, const char *argv[])
{
    foo(42);
    // The following cannot be deduced.
    // bar(42);

    return 0;
}
