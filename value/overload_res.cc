/**
 *  Overload resolution
 *  ===================
 *
 *  Some candidates choosing due to overload resolution.
 */

#include <iostream>

template <typename T>
void
foo(const T&)
{
    std::cout << "lvalue" << std::endl;
}

template <typename T>
void
foo(T&&)
{
    std::cout << "rvalue" << std::endl;
}

int
main(int argc, const char *argv[])
{
    int n = 42;
    int& i = n;
    int&& j = 42;

    // Without template specialization, i and j are universal references
    // and will be firstly treated as lvalue (due to their names), but
    // T&& candidate is prior to the const T& candidate, according to
    // overload resolution.  So foo(T&&) is invoked.
    std::cout << "w/o specialization" << std::endl;
    foo(i);
    foo(j);

    // With specialization, i and j would not be treated as rvalue by
    // foo.  So foo(const T&) here is invoked.
    std::cout << "w/ specialization" << std::endl;
    foo<int>(i);
    foo<int>(j);

    return 0;
}
