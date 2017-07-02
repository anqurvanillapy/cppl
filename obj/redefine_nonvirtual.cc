/**
 *  Redefine non-virtual members
 *  ============================
 *
 *  effcpp: "Never redefine a non-virutal function in C++.
 */

#include <iostream>

class base {
public:
    base() = default;
    ~base() = default;
    void foo() { std::cout << "base" << std::endl; }
};

class derived : public base {
public:
    derived() = default;
    ~derived() = default;
    void foo() { std::cout << "derived" << std::endl; }
};

void
i_take_a_base_ptr(base* b)
{
    // It will run the base member function.
    b->foo();
}

int
main(int argc, const char *argv[])
{
    derived *d = new derived();
    i_take_a_base_ptr(d);

    return 0;
}
