/**
 *  Macro multi-expressions
 *  =======================
 *
 *  2 ways of containing multiple expressions in macros
 */

#include <stdio.h>

#define foo() \
    do { \
        printf("Hello, "); \
        printf("world!\n"); \
    } while(0)
#define bar() \
    ({ \
        printf("Aloha, "); \
        printf("jerk!\n"); \
    })

int
main(int argc, const char *argv[])
{
    foo();
    bar();

    return 0;
}
