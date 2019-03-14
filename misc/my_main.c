/**
 *  Custom entry
 *  ============
 *
 *  Note: Compile with -nostartfiles.
 */

#include <stdio.h>
#include <stdlib.h>

int
my_main()
{
    printf("no main function defined\n");
    return 0;
}

void
_start()
{
    int ret = my_main();
    exit(ret);
}
