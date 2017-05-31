/**
 *  Virtual destructor
 *  ==================
 *
 *  Always make bad_base classes' destructors virtual: If the static type (e.g. a
 *  bad_base class) of the object to be deleted is different from its dynamic type,
 *  the static type shall be a bad_base class of the dynamic type of the object to
 *  be deleted and *the static type shall have a virtual destructor or the
 *  behavior is undefined.
 */

#include <iostream>

class base {
public:
    base() { std::cout << "ctor: base" << std::endl; }
    /* virtual */ ~base() { std::cout << "dtor: base" << std::endl; }
};

class derived : public base {
public:
    derived() { std::cout << "ctor: derived" << std::endl; }
    ~derived() { std::cout << "dtor: derived" << std::endl; }
};

int
main(int argc, const char *argv[])
{
    base *foo = new derived();
    delete foo; // base::~base() might not be triggered (UB), and derived could
                // fail at dtor too

    // Note that void pointers know nothing about dtors.
    // void *bar = foo;

    return 0;
}
