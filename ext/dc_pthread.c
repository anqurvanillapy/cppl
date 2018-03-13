/**
 *  dyncall pthread
 *  ===============
 *
 *  An example of using dyncall to call pthread_create and pthread_join, for
 *  tending to dive into its internals later.
 *
 *  Note: Compile with -lpthread -ldyncall_s, if dyncall installed.
 */

#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include <dyncall.h>

int
foo(const char* str)
{
	printf("%s\n", str);
	return 42;
}

int
main()
{
	int rc, retval;
	pthread_t t;

	DCCallVM* vm = dcNewCallVM(4096);
	dcMode(vm, DC_CALL_C_DEFAULT);

	dcReset(vm);
	dcArgPointer(vm, (DCpointer)&t);
	dcArgPointer(vm, NULL);
	dcArgPointer(vm, (DCpointer)&foo);
	dcArgPointer(vm, (DCpointer)&"Hello, world!");
	rc = dcCallInt(vm, (DCpointer)&pthread_create);
	assert(rc == 0);

	dcReset(vm);
	dcArgLong(vm, t);
	dcArgPointer(vm, (DCpointer)&retval);
	rc = dcCallInt(vm, (DCpointer)&pthread_join);
	assert(rc == 0);
	assert(retval == 42);

	return 0;
}
