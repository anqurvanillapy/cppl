/**
 *  Most vexing parse
 *  =================
 *
 *  A specific form of syntactic ambiguity resolution.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>

class Foo {
public:
    Foo() { /* nop */ }
    // Or overloads the operator().
    // void operator()();
};

class Bar {
public:
    Bar(const Foo &f) { /* nop */ }

    void sayhi()
    {
        std::cout << "Hi!" << std::endl;
    }
};

int
main(int argc, const char *argv[])
{
    // It's seemingly ambiguous, since it could be interpreted either as
    // 1. a variable definition or
    // 2. a function declaration.
    Bar bar(Foo());

    // To resolve the ambiguity, use the uniform initialization syntax, and
    // the following statement is unambiguously a variable definition now.
    // Bar bar{Foo()};

    // This will raise the error since bar is a function (if compiled by
    // g++).
    bar.sayhi();

    return 0;
}
