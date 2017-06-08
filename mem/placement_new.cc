/**
 *  Placement new
 *  =============
 *
 *  new expression
 *  --------------
 *
 *  ::new(placement_params) (type) initializer
 *  ::new(placement_params) type initializer    // if type cannot include parens
 *
 *  `::' is used to force a global scope that is explicitly the new expression,
 *  instead of anything about `operator new'.
 *
 *  If placement_params are provided, they are passed to the allocation function
 *  as additional arguments.  Such allocation functions are known as "placement
 *  new", after the standard allocation function
 *
 *      void* operator new(std::size_t, void*)
 *
 *  which simply returns its second argument unchagned.  This is used to
 *  construct objects in allocated storage.
 *
 *  operator new
 *  ------------
 *
 *  Operator new can be customized for the use of user-defined placement new.
 */

#include <iostream>

/// Use placement new for allocated storage.

class foo {
public:
    foo() : i_(42) { std::cout << "ctor: foo" << std::endl; }
    ~foo() { std::cout << "dtor: foo" << std::endl; }

    int get_answer() const { return i_; }
private:
    int i_;
};

template <typename T>
void
placement_construct_obj()
{
    char *p = new char[sizeof(T)];  // allocate memory
    T *tp = new(p) T;               // construct in the allocated storage
    std::cout << "answer=" << tp->get_answer() << std::endl;
    tp->~T();                       // destruct
    delete[] p;                     // deallocate memory
}

/// Custom placement new/delete using operator new/delete.

class bar {
public:
    bar() { throw std::runtime_error("idky"); }

    static void*
    operator new(size_t sz, int answer)
    {
        std::cout << "custom operator new, answer=" << answer << std::endl;
        return ::operator new(sz);
    }

    // When the failed placement new expression looks for the corresponding
    // placement delete function to call, it begins lookup at class scope before
    // examining the global scope, and looks for the function with the signature
    // matching the placement new.
    static void
    operator delete(void* ptr, int answer)
    {
        std::cout << "custom operator delete, answer=" << answer << std::endl;
        ::operator delete(ptr);
    }
};

int
main(int argc, const char *argv[])
{
    placement_construct_obj<foo>();

    try {
        bar *p = new (420) bar;
    } catch (...) { /* nop */ }

    return 0;
}
