/**
 *  Indirect function
 *  =================
 */

#include <stdio.h>

int func (void) __attribute__((ifunc("func_resolver")));

int impl_switch = 1;

int func_impl()
{
    printf("impl\n");
}

int func_impl_alter()
{
    printf("impl_alter\n");
}

void* func_resolver()
{
    return impl_switch == 1 ? func_impl : func_impl_alter;
}

int main()
{
    func();
    return 0;
}
