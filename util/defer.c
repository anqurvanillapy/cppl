/**
 *  defer in C
 *  ==========
 *
 *  `defer` in C with Blocks extension.
 *
 *  Note: Compile with clang -fblocks -lBlocksRuntime.
 */

#include <stdio.h>

static inline void __defer_cleanup(void (^*b)()) { (*b)(); }

#define __defer_merge(a, b) a##b
#define __defer_fn_name(a) __defer_merge(__defer_fn, a)
#define defer(fn) __attribute__((cleanup(__defer_cleanup))) \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-variable\"") \
    void (^__defer_fn_name(__COUNTER__))(void) = fn; \
    _Pragma("GCC diagnostic pop")

void Func1()
{
    defer(^{ printf("1\n"); });
}

void Func0()
{
    Func1();
    defer(^{ printf("2\n"); });
    defer(^{ printf("3\n"); });
    printf("4\n");
}
   
int main()
{
    Func0();
    return 0;
}
