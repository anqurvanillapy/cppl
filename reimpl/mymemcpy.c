/**
 *  mymemcpy
 *  ========
 *
 *  A re-implementation of memcpy without using libraries functions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // for size_t in gcc, I'm sorry

void *
mymemcpy(void *dest, const void *src, size_t n)
{
    char *pd, *ps;
    // Use n directly for size_t might be 64-bit, thus unsafe for an int cast.
    for (pd = (char *)dest, ps = (char *)src; n > 0; --n, ++pd, ++ps) *pd = *ps;
    return pd;
}

typedef struct {
    int val;
} foo_t;

int
main(int argc, const char *argv[])
{
    foo_t *foo, *bar;

    foo = (foo_t *)malloc(sizeof(foo_t));
    bar = (foo_t *)malloc(sizeof(foo_t));

    foo->val = 42;
    mymemcpy(bar, foo, sizeof(bar));
    printf("bar->val=%d\n", bar->val);

    return 0;
}

