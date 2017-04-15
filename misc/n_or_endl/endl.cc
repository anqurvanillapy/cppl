/**
 *  endl
 *  ====
 *
 *  See comments on Makefile.
 */

#include <iostream>

int
main(int argc, const char *argv[])
{
    for (int i = 0; i < 100000000; ++i) std::cout << std::endl;
    return 0;
}
