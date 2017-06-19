/**
 *  Unsafe printf
 *  =============
 *
 *  Malicious usage of printf.  Using non-literals of string in printf is simply
 *  dangerous, so just do not ignore any warnings unless determined.
 */

#include <stdio.h>

void
foo(const char *s)
{
    int a = 0, b = 42;

    // A last newline in the string literal might leave an undefined behavior.
    printf("%p %p", &a, &b);

    // According to the generated assembly code, the printf system call actually
    // looks for the `&a' and `&b' due to the `%n' format specifier and for most
    // of the time the OS will not retain the values from stack for security
    // purposes, and finally yields a SIGSEGV.
    //
    // Solve the boundary error?  Just use `s' as an argument printed with `%s'
    // specifier.
    printf(s);

    // Their values are modified, or the program is terminated.
    printf("%d %d\n", a, b);
}

int
main(int argc, const char *argv[])
{
    char s[] = "lol %n oops %n";
    foo(s);

    return 0;
}
