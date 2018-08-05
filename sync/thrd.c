/**
 *  thrd_*
 *  ======
 *
 *  A naive demo of thread support library in C11.
 *
 *  Note: It is supported in glibc version >= 2.28, which is not popular enough
 *  to run this code as soon as possible.  One can go check out musl-gcc for
 *  compling this demo.
 */

#include <stdio.h>
#include <unistd.h>
#include <threads.h>
#include <stdatomic.h>

_Atomic long i = 0;

int
foo(void* arg)
{
	long n = (long)arg;
	do {
		thrd_yield();
		printf("%ld", atomic_load(&i));
	} while (atomic_load(&i) < n);

	return thrd_success;
}

int
bar(void* arg)
{
	for (int j = 0; j < (long)arg; ++j) {
		sleep(1);
		atomic_fetch_add(&i, 1);
		++j;
	}

	return thrd_success;
}

int
main()
{
	thrd_t t1;
	thrd_t t2;
	int rc1, rc2;

	thrd_create(&t1, foo, (void*)3l);
	thrd_create(&t2, bar, (void*)10l);

	thrd_join(t1, &rc1);
	thrd_join(t2, &rc2);

	printf("\nrc=%d, %d\n", rc1, rc2);
	return 0;
}
