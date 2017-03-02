/**
 *  Static members
 *  ==============
 *
 *  - Keyword `static' has two usages:
 *      + Static storage duration with internal linkage specifier.
 *      + Declarations of class members not bound to specific instances.
 *
 *  Inside a class definition, this keyword declares members that are not
 *  bound to class instances.
 */

#include <iostream>

class Foo {
public:
    Foo() { ++no; }

    static void sayhi() { std::cout << "Hi! total: " << no << std::endl; }
private:
    static int no;
};

/// Static variables should be initialized outside the class declaration.
int Foo::no = 0;

int
main(int argc, const char *argv[])
{
    // Use qualifier :: to invoke static member function, not . qualifier.
    Foo::sayhi();

    Foo foo, bar;
    foo.sayhi();
    bar.sayhi();     // 2 instances in total

    return 0;
}
