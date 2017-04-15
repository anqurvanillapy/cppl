/**
 *  endl (no sync)
 *  =============
 *
 *  See comments on Makefile.
 */

#include <iostream>

int
main(int argc, const char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    for (int i = 0; i < 100000000; ++i) std::cout << std::endl;
    return 0;
}
