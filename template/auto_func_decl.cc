/**
 *  `auto` function declarations
 *  ============================
 *
 *  Some syntaxes for function declarations that deduce the return type.
 *
 *  Note: Compile with -std=c++14.
 */

#include <iostream>
#include <typeinfo>

/// decltype ahead of the argument declarations would simply raise the
/// compilation error, because a and b are undeclared.  The workaround is using
/// declval with template parameters that are already declared.
// decltype(a + b) compose(T1 a, T2 b)
template <typename T1, typename T2>
decltype(std::declval<T1>() + std::declval<T2>())
foo(T1 a, T2 b)
{
    return a + b;
}

/// auto here doesn't mean type checking, just a part of the syntax.  Now a and
/// b are declared before the return type deduction.
template <typename T1, typename T2>
auto
bar(T1 a, T2 b)
    -> decltype(a + b)
{
    return a + b;
}

/// In C++14 the `->' syntax could be omitted.  But `->' remains useful when the
/// body of source file can be hidden and some return type information can be
/// left in the header file by this.
template <typename T1, typename T2>
auto
baz(T1 a, T2 b)
{
    return a + b;
}

int
main(int argc, const char *argv[])
{
    // Check the return types of the function calls.
    std::cout << typeid(foo<int, long>(42, 420)).name() << std::endl;
    std::cout << typeid(bar<int, long>(42, 420)).name() << std::endl;
    std::cout << typeid(baz<int, long>(42, 420)).name() << std::endl;

    return 0;
}
