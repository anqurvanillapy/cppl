/**
 *  Implementation-specific overloading
 *  ===================================
 *
 *  If a function and a callable object share a same name, the invocation of
 *  one of it might be implementation-specific.
 */

#include <iostream>

class Foo {
public:
    void
    operator()()
    {
        std::cout << "invocation of the object of Foo" << std::endl;
    }
};

void
foo()
{
    std::cout << "invocation of function foo()" << std::endl;
}

int
main(int argc, const char *argv[])
{
    Foo foo;
    // On G++ 5.4.0, this will invocate the object foo.
    foo();
    return 0;
}
