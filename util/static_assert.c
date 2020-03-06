/**
 * static assertions in C
 * ======================
 *
 * N.B. Grapped from Linux kernel.
 */

#include <stdio.h>

#define STATIC_EXPECT_FALSE(e) \
    ((int)sizeof(struct{int:-!!(e);}))
#define STATIC_EXPECT_FALSE_AS_PTR(e) \
    ((void *)sizeof(struct{int:-!!(e);}))

int main()
{
    STATIC_EXPECT_FALSE(2 + 2 == 5);
    // STATIC_EXPECT_FALSE(1 + 1 == 2);
    return 0;
}
