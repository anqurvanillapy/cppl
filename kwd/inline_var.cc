/**
 *  Inline variables
 *  ================
 *
 *  Use inline keyword to define an external linkage const namespace scope
 *  variable, or any static class data member, in a header file, so that
 *  the multiple definitions that result when that header is included in
 *  multiple translation units are okay with the linker - it just chooses
 *  *one* of them.
 *
 *  Note: Compile with -std=c++17.
 *
 *  XXX: This seems not compilable on my g++ 5.4.0.
 */

#include <iostream>

/// Until C++17, it can be done via this trick with template.
template<class Dummy>
struct _Foo {
    static std::string hi;
};

/// Static member variable should be initialized outside the class.
template<class Dummy>
std::string _Foo<Dummy>::hi = "Hi! I'm Foo.";

/// Type alias via using was introduced since C++11.
using Foo = _Foo<void>; // `Foo::hi' is now allowed

/// Use the inline variable outside the class.
struct Bar {
    static std::string const hi = "Hi! I'm Bar.";
};

inline std::string Bar::hi = "Hi! I'm Bar.";

/// It can also be defined in the class definition.
struct Baz {
    static inline std::string hi = "Hi! I'm Baz.";
};

int
main(int argc, const char *argv[])
{
    std::cout << Foo::hi << std::endl;
    std::cout << Bar::hi << std::endl;
    std::cout << Baz::hi << std::endl;

    return 0;
}
