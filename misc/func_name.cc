/**
 *  Function names
 *  ==============
 *
 *  GCC provides three magic constants that hold the name of the current
 *  function as a string. __func__ is the first of these. __FUNCTION__ is
 *  provided for backward compatibility. __PRETTY_FUNCTION__ contains the
 *  signature of the function as well as its bare name.
 */

#include <iostream>

class Foo {
public:
    void
    func_name()
    {
        std::cout << __func__ << std::endl;
        std::cout << __FUNCTION__ << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int
main(int argc, const char *argv[])
{
    Foo foo;
    foo.func_name();

    return 0;
}
