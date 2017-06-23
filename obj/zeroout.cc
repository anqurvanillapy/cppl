/**
 *  Zero out
 *  ========
 *
 *  Does the default constructor (provided/synthesized by the compiler)
 *  initialize built-in types?  It depends.
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <cassert>

class foo { public: int x; };

int
main(int argc, const char *argv[])
{
    // Here compiler-synthesized default ctor is used, and a.x contains garbage.
    // Notice that `-O' and string stream concatenation might fix this issue,
    // although it is not further proved yet.
    foo a;
    std::cout << a.x << std::endl;  // probably not 0

    // Here default ctor is not used, and *value-initialization* feature is
    // utilized instead, due to the explicit `()' initializer.
    foo b = foo();
    assert(b.x == 0);

    // Ditto.
    foo *p = new foo();
    assert(p->x == 0);

    // Aggregate initializations can be trigered without involving ctors.
    foo c = {};
    assert(c.x == 0);

    // Ditto.
    foo d{};    // in C++11 style
    assert(d.x == 0);

    return 0;
}
