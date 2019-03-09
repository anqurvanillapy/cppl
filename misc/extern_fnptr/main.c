/*
 *  extern function pointer
 *  =======================
 *
 *  Testing "extern" linkage, it seems unnecessary.
 */

#include "foo.h"

typedef void (*fnptr)();

int
main()
{
    fnptr fn = foo;
    foo();
    return 0;
}
