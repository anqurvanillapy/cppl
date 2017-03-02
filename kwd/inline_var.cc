/**
 *  Inline variables
 *  ================
 *
 *  Use inline keyword to define an external linkage const namespace scope
 *  variable, or any static class data member, in a header file, so that
 *  the multiple definitions that result when that header is included in
 *  multiple translation units are okay with the linker - it just chooses
 *  *one* of them.
 *
 *  Note: Compile with -std=c++17.
 */

#include <iostream>

int
main(int argc, const char *argv[])
{
    // TODO
    return 0;
}
