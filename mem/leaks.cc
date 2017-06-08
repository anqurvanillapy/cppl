/**
 *  Memory leaks
 *  ============
 *
 *  Some examples of memory leaks.
 *
 *  Note: Use `valgrind <executable> --leak-check=full -v' to check the leak
 *  summary.  Here there will be 12 bytes (3 ints) leaked.
 */

#include <stdexcept>

void
lost_pointer()
{
    int *p = new int(42);
    p = nullptr;
}

void
no_delete_or_dtor()
{
    int *p = new int(42);
}

void
i_will_throw()
{
    throw std::runtime_error("idk");
}

void
exception_thrown()
{
    int *p = new int(42);
    i_will_throw();
    delete p;
}

int
main(int argc, const char *argv[])
{
    lost_pointer();
    no_delete_or_dtor();

    try {
        exception_thrown();
    } catch (...) { /* nop */ }

    return 0;
}
