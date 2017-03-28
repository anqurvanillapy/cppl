/**
 *  Static storage quiz
 *  ===================
 *
 *  A simple quiz that covers static storage and scopes.
 */

#include <stdio.h>

/// Global variables won't appear in the foo() scope.
int x = 4;

void
foo()
{
    // Static storage that will not be deallocated when leaves the scope.
    static int x = 1;
    // Automatic one will vanish, and the program would print `2222'.
    // int x = 1;

    x *= x + 1;     // it gets 2, 6, 42, 1806
    printf("%d", x);
}

int
main(int argc, const char *argv[])
{
    int i;
    // It iterates 4 times.
    for (i = 0; i < x; ++i) foo();
    return 0;
}
