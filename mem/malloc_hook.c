/**
 *  malloc hook
 *  ===========
 */

#include <stdio.h>
#include <stdlib.h>

extern void* __libc_malloc(size_t size);

void*
malloc(size_t size)
{
	void* caller = __builtin_return_address(0);
	printf("caller: %p\n", caller);
	return __libc_malloc(size);
}

int
main()
{
	int* p = (int*)malloc(sizeof(int));
	free(p);
	p = NULL;
	return 0;
}
