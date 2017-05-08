/**
 *  myatoi
 *  ======
 *
 *  A re-implementation of atoi, without using libraries.
 */

#include <stdio.h>

int
myatoi(const char *s)
{
    long i, d;
    int sign;
    // Array-based LIFO.
    int si = 0, sa[10];

    sign = (*s == '-') ? (++s, -1) : 1;

    for (; *s != '\0' && si < 10; ++s) {
        // NOTE: Standard atoi will break when there are words.
        // if (*s < 48 || *s > 57) goto error;
        if (*s < 48 || *s > 57) break;
        sa[si++] = *s % 48;
    }

    for (i = 0, d = 1, --si; si >= 0; d *= 10, --si) i += sa[si] * d;

    // 2 ** 31 - 1 == 2147483647.
    // NOTE: Standard atoi can overflow without errors.
    // if (i > 2147483647 || i < -2147483648) goto error;

    return i * sign;   // converts to int
// If necessary.
// error:
//    return -1;
}


int
main(int argc, const char *arv[])
{
    char unsi[] = "123";
    char si[] = "-123";
    char sl[] = "4444444444";
    char unsl[] = "-4444444444";
    char toolong[] = "4444444444444444";

    printf("signed int=%d\n", myatoi(si));
    printf("unsigned int=%d\n", myatoi(unsi));
    printf("unsigned long=%d\n", myatoi(sl));
    printf("unsigned long=%d\n", myatoi(unsl));
    printf("string too long=%d\n", myatoi(toolong));
    printf("invalid string=%d\n", myatoi("+"));

    return 0;
}
