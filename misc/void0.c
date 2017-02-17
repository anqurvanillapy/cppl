/**
 *  void 0
 *  ======
 *
 *  void 0 in ternary operator for concise use.
 */

#include <stdio.h>

#define DO_NOTHING ((void) 0)

void foo();

int
main(int argc, const char *args[])
{
    0 ? foo() : DO_NOTHING;
    return 0;
}

void
foo()
{
    printf("foo!\n");
}
