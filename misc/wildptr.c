/**
 *  Wild pointers
 *  =============
 *
 *  Some examples of wild pointers, perhaps mixed with something about dangling
 *  pointers.
 */

#include <stdio.h>

int
main(int argc, const char *argv[])
{
    /* Example 0 */

    int *p; // uninited

    {
        int a = 42;
        p = &a;
    }   // a does not exist now, p becomes invalid

    // Dead pointer usage.  It might print the right value in memory though but
    // remember this is an undefined behavior.
    printf("%d\n", *p);

    return 0;
}
