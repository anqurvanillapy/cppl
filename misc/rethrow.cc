/**
 *  rethrow_exception
 *  =================
 *
 *  Throws the previously captured exception object, referred to by the
 *  exception pointer p with type std::exception_ptr
 *
 *  Note: Compile with -std=c++11.
 */

#include <iostream>
#include <exception>

void
handle_eptr(std::exception_ptr eptr)    // it is ok to pass the value
{
    try {
        if (eptr) std::rethrow_exception(eptr);
    } catch (const std::exception& e) {
        std::cout << "You caught \"" << e.what() << "\" once before\n";
    }
}

int
main(int argc, const char *argv[])
{
    std::exception_ptr eptr;

    try {
        throw std::runtime_error("kinda bored now");
    } catch (...) {
        eptr = std::current_exception();
    }

    handle_eptr(eptr);

    return 0;
}
