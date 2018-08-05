/**
 *  thrd_*
 *  ======
 *
 *  A naive demo of thread support library in C11.
 *
 *  Note: It is supported in glibc version >= 2.28, which is not popular enough
 *  to run this code as soon as possible.  One can go check out musl-gcc for
 *  compling this demo.  The use of `thrd_yield` can be indicated via re-binding
 *  threads for the process by the following command:
 *
 *      $ musl-gcc thrd.c -std=c11 -Wall -Wextra -pedantic -Ofast
 *      $ numactl --physcpubind=+1 ./a.out
 */

#include <stdio.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>

#define N 5
_Atomic long i = 0;

int
foo(void* arg)
{
	(void)arg;
	do {
		thrd_yield();
		printf("foo: %ld\n", atomic_load(&i));
	} while (atomic_load(&i) < N);

	return thrd_success;
}

int
bar(void* arg)
{
	(void)arg;
	for (int j = 0; j < N; ++j) {
		thrd_yield();
		printf("bar: inc i\n");
		atomic_fetch_add(&i, 1);
	}

	return thrd_success;
}

int
main()
{
	thrd_t t1;
	thrd_t t2;
	int rc1, rc2;

	thrd_create(&t1, foo, NULL);
	thrd_create(&t2, bar, NULL);

	thrd_join(t1, &rc1);
	thrd_join(t2, &rc2);

	printf("rc=%d, %d\n", rc1, rc2);
	return 0;
}
