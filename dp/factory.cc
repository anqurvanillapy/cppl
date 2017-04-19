/**
 *  Factory
 *  =======
 *
 *  The factory methods implemented with different fowarding methods. It
 *  could also be a case study of value categories.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <memory>

/// foo() here forwards the value directly, at the expense of creating a
/// temporary object.
template <typename T, typename Arg>
std::shared_ptr<T>
foo(Arg arg)
{
    return std::shared_ptr<T>(new T(arg));
}

/// bar() forwards the reference to optimize the speed.  However the
/// parameter could not be a lvalue, e.g. a string literal.
template <typename T, typename Arg>
std::shared_ptr<T>
bar(Arg& arg)
{
    return std::shared_ptr<T>(new T(arg));
}

/// This is nearly perfect, but it could not support std::move().
template <typename T, typename Arg>
std::shared_ptr<T>
baz(const Arg& arg)
{
    return std::shared_ptr<T>(new T(arg));
}

/// XXX: It should be provided with explicit type for the template to
/// avoid type deduction, with whom T&& could mean a lvalue.
template <typename T, typename Arg>
std::shared_ptr<T>
qux(T&& arg)
{
    return std::shared_ptr<T>(new T(std::forward<Arg>(arg)));
}

int
main(int argc, const char *argv[])
{
    int n = 42;
    std::shared_ptr<int> i;

    i = foo<int, int>(n);
    std::cout << *i << std::endl;
    // This is valid though.
    // i = foo<int, int>(42);

    i = bar<int, int>(n);
    std::cout << *i << std::endl;
    // This is invalid: no matching function call.
    // i = bar<int, int>(42);

    i = baz<int, int>(42);
    std::cout << *i << std::endl;

    i = qux<int, int>(42);
    std::cout << *i << std::endl;

    return 0;
}
