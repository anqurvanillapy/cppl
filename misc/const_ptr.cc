/**
 *  Const pointer
 *  =============
 *
 *  `const char *` is a pointer to a `const char`, while `char *const` is
 *  a constant pointer to a `char`.
 *
 *  The first, the value being pointed to cannot be changed but the
 *  pointer can be. The second, the value being pointed at can change but
 *  the pointer can't.
 *
 *  Note: Why SIGSEGV? Because when writting `char *c = "abc"`, it is
 *  similar to the following code:
 *
 *      // __unnamed is magic because modifying it gives UB.
 *      static char __unnamed[] = "abc";
 *      char *c = __unnamed;
 *
 *  The implicit cast from `char[]` to `char *` is always legal. So when
 *  modifying c[0], it would modify `__unnamed` which is UB. In other
 *  words, string literals are stored in read-only memory when the
 *  program is run. "abc" is stored in read-only memory and `*c` points
 *  to the first character. And the segfault happens when trying to
 *  change it.
 */

#include <iostream>

int
main(int argc, const char *argv[])
{
    const char *str1 = "foo";
    // FIXME: ISO C++11 does not allow conversion from string literal to
    // the following type.
    char *const str2 = "bar";

    // Legal.
    str1++;

    // XXX: Read-only variable is not assignable.
    // str1[1] = 'o';

    // XXX: No compilation error, but gets SIGSEGV. Why? See above.
    // str2[2] = 'z';

    // XXX: Cannot assign to variable with const-qualified type.
    // str2++;

    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;

    return 0;
}
