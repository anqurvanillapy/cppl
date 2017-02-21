/**
 *  Deleted functions
 *  =================
 *
 *  A function could be defined as deleted using `= delete;' syntax, which
 *  will not be compiled and is ill-formed of any use. If the function is
 *  overloaded, overload resolution takes place first and the program is
 *  only ill-formed if the deleted function was selected.
 */

#include <iostream>

class Foo {
public:
    void* operator new(std::size_t) = delete;
    void* operator new[](std::size_t) = delete;
};

int
main(int argc, const char *argv[])
{
    // Using new will raise use of deleted function error.
    Foo *foo = new Foo;

    // Using new[] is also illegal.
    Foo *bar = new Foo[10];
    return 0;
}
