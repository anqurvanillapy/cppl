/**
 *  Macro evaluation
 *  ================
 *
 *  The preprocessor will just do the replacing job, so be careful of the
 *  presence of something like parentheses.
 */

#include <iostream>

#define A 3 + 5
#define B A * A

int
main(int argc, const char *argv[])
{
    // Identical to 3 + 5 * 3 + 5 * 2, hence 28.
    std::cout << B * 2 << std::endl;

    return 0;
}
