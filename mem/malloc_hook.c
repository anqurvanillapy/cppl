/**
 *  malloc hook
 *  ===========
 *
 *  - Notes:
 *      + __builtin_return_address only works with gcc
 *      + __libc_malloc only works with glibc
 */

#include <stdio.h>
#include <stdlib.h>

#ifdef __GNUC__

extern void* __libc_malloc(size_t size);
int is_malloc_hook_enabled = 1;

void*
malloc_hook(size_t size, void* caller)
{
	void* p;

	is_malloc_hook_enabled = 0;
	p = malloc(size);

	// User-defined behavior.
	printf("caller=%p, size=%lu\n", caller, size);

	is_malloc_hook_enabled = 1;

	return p;
}

void*
malloc(size_t size)
{
	void* caller = __builtin_return_address(0);

	if (is_malloc_hook_enabled) {
		return malloc_hook(size, caller);
	}

	return __libc_malloc(size);
}
int
main()
{
	int* p = (int*)malloc(sizeof(int));
	*p = 42;
	printf("%d\n", *p);
	free(p);
	p = NULL;
	return 0;
}

#else

int
main()
{
	fprintf(stderr, "snippet not workable for your compiler\n");
	return 1;
}

#endif /* __GNUC__ */
