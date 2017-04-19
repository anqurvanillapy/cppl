/**
 *  Universal reference
 *  ===================
 *
 *  An example of the ambiguity of T&&, reference collapsing rule, and
 *  a little case of overload resolution.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

template <typename T>
class foo {
public:
    foo(T&) { std::cout << "foo got a lvalue" << std::endl; }
    foo(T&&) { std::cout << "foo got a rvalue" << std::endl; }
};

template <typename T>
void
f(const T&)
{
    std::cout << "f got a lvalue" << std::endl;
}

template <typename T>
void
f(T&&)
{
    std::cout << "f got a rvalue" << std::endl;
}

template <typename T>
void
bar(T&& t)
{
    f(t);
}

int
main(int argc, const char *argv[])
{
    int n = 42;
    // i, j here are all treated as int&.  The reference parts of types
    // of i and j are stripped off, yielding type int, and then becaouse
    // each is an lvalue (due to their names), the deduced type for both
    // i and j is int&.
    int& i = n;
    int&& j = 42;

    foo<int> a(i);
    foo<int> b(j);
    foo<int> c(42); // rvalue

    // They all got rvalue because the const T& candidate is not prior to
    // the T&& due to overload resolution.
    //
    // Note that there is type deduction.
    bar(i);
    bar(j);
    bar(42);

    return 0;
}
