/**
 *  Referring to types
 *  ==================
 *
 *  Generic macros by using statement expressions, __auto_type/typeof().
 *
 *  Note: Compile with -std=c11.
 */

#include <stdio.h>

#define max(a, b) \
({ \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b; \
})

#define max1(a, b) \
({ \
    __auto_type _a = (a); \
    __auto_type _b = (b); \
    _a > _b ? _a : _b; \
})

int
main(int argc, const char *argv[])
{
    printf("%d, %d\n", max(1, 2), max1(3, 4));
    return 0;
}
