/**
 *  Destructor That Throws
 *  ======================
 *
 *  Throwing exceptions in destructor might be propagated which is really
 *  dangerous for potential memory leak. Due to the stack unwinding, the
 *  destructor of an object would be guaranteed to run if an exception in
 *  the same scope is thrown. In such scenerio, the exception thrown by
 *  the destructor might be impossible to catch from the outside.
 *
 *  Better to get it in the dtor and do nothing in the `catch' block for
 *  a safer catching.
 */

#include <iostream>

class Foo {
public:
    Foo() { /* nop */ }

     // ~Foo()
     // {
     //     i_will_throw();
     //     std::cout << "It can't log!" << std::endl;
     // }

     // ~Foo()
     // {
     //     try {
     //         i_will_throw();
     //     } catch (...) {
     //         std::cout << "It's not safe, actually!" << std::endl;
     //         throw std::runtime_error("Say you will never ever catche me no!");
     //     }
     // }

    ~Foo()
    {
       try {
           i_will_throw();
       } catch (...) { /* nop */ }
       // Safe now!
    }
private:
    void
    i_will_throw()
    {
        throw std::runtime_error("don't throw me out of the dtor!");
    }
};

void
func()
{
    Foo foo;
    throw std::runtime_error("catch me please!");   // triggers the dtor of foo!
}

int
main(int argc, const char *argv[])
{
    try {
        func(); // gotcha!
    } catch (...) { /* but cannot catch the dtor exception! */ }

    return 0;
}
