/**
 *  Struct inheritance
 *  ==================
 *
 *  Members in struct are by default public. Inheritance of struct and its
 *  pointers can be sometimes weird like the following scenario.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

struct Foo {
    int a = 1;
    // Non-C++11 struct init:
    // int a;
    // Foo() : a(1) { /* nop */ };
};

struct Bar : Foo {
    int b = 2;
    // Non-C++11 struct init:
    // int b;
    // Bar() : b(2) { /* nop */ };
};

int
main(int argc, const char *argv[])
{
    Foo* foo = new Bar;

    std::cout << foo->a << std::endl;
    // Accessing b is illegal.
    // std::cout << foo->b << std::endl;

    // It indicates that foo points to a Bar-sized object.
    std::cout << sizeof(foo) << std::endl;

    return 0;
}
