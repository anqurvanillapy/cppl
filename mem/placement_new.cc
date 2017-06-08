/**
 *  Placement new
 *  =============
 *
 *  ::new(placement_params) (type) initializer
 *  ::new(placement_params) type initializer    // if type cannot include parens
 *
 *  If placement_params are provided, they are passed to the allocation function
 *  as additional arguments.  Such allocation functions are known as "placement
 *  new", after the standard allocation function
 *
 *      void* operator new(std::size_t, void*)
 *
 *  which simply returns its second argument unchagned.  This is used to
 *  construct objects in allocated storage.
 */

#include <iostream>

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

int
main(int argc, const char *argv[])
{
    placement_construct_obj<foo>();
    return 0;
}
