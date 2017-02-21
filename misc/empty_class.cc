/**
 *  Empty class
 *  ===========
 *
 *  An empty class exactly exists and has the size of 1 byte, since its objects
 *  shoud be different and "new" always returns pointers to distinct objects. An
 *  object that has actual size can exist and be sure to have unique identity.
 *
 *  But if a class/struct derived from the empty class has some members, a good
 *  optimizer can avoid the overhead to make the members locate at the start.
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

class Empty { };

struct X : Empty {  // private derivation
    int a;          // first in struct X
};

bool
is_optimized(X *p)
{
    void *p1 = p;       // points to X
    void *p2 = &p->a;   // points to the member a in X
    return p1 == p2;    // points to the same place?
}

int
main(int argc, const char *argv[])
{
    Empty a, b;
    Empty *p1 = new Empty;
    Empty *p2 = new Empty;
    struct X *c;

    c = (X *)malloc(sizeof(X));
    c->a = 255;   // struct member assignment (meaningless)

    cout << "Size of an empty class is " << sizeof(Empty) << endl;
    cout << "Sizes of the empty objects a, b are " << sizeof(a) << ", "
        << sizeof(b) << endl;

    cout << "Are addresses of a, b the same? " << (&a == &b) << endl;
    cout << "Are pointers p1, p2 the same? " << (p1 == p2) << endl;

    cout << "Value of struct X c.a is " << c->a << endl;
    cout << "Is the struct derived from the empty class optimized? "
        << is_optimized(c) << endl;

    return 0;
}
