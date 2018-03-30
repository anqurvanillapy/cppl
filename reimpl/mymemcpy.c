/**
 *  mymemcpy
 *  ========
 *
 *  A re-implementation of memcpy without using libraries functions.  Test with
 *  -DTEST_64 or -DTEST_32 for some optimizations.
 *
 *  Note: Compile with -O3 with the naive implementation `mymemcpy` will enable
 *  loop unrolling and SIMD instructions usage in GCC 8, which might be much
 *  quicker and closer to the library one `memcpy`.
 */

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#define SIZ (1024 * 1024 * 128)

void
mymemcpy(void* dst, const void* src, size_t n)
{
#if defined(TEST_64)
	unsigned char* bd = (unsigned char*)dst;
	unsigned char* bs = (unsigned char*)src;

	while (((size_t)bd & 0x7) != 0) {
		*bd++ = *bs++;
		--n;
	}

	size_t* qd = (size_t *)dst;
	size_t* qs = (size_t *)src;

	while (n >= 8) {
		*qd++ = *qs++;
		n -= 8;
	}

	if (n) {
		bd = (unsigned char*)qd;
		bs = (unsigned char*)qs;

		while (n) {
			*bd++ = *bs++;
			--n;
		}
	}
#elif defined(TEST_32)
	unsigned char* bd = (unsigned char*)dst;
	unsigned char* bs = (unsigned char*)src;

	while (((size_t)bd & 0x3) != 0) {
		*bd++ = *bs++;
		--n;
	}

	unsigned int* ld = (unsigned int*)dst;
	unsigned int* ls = (unsigned int*)src;

	while (n >= 4) {
		*ld++ = *ls++;
		n -= 4;
	}

	if (n) {
		bd = (unsigned char*)ld;
		bs = (unsigned char*)ls;

		while (n) {
			*bd++ = *bs++;
			--n;
		}
	}
#else
	size_t i;
	unsigned char* d = (unsigned char*)dst;
	unsigned char* s = (unsigned char*)src;
	for (i = 0; i < n; ++i) {
		*d++ = *s++;
	}
#endif /* TEST_64 */
}

int
main()
{
	void *a, *b;
	char *aa, *bb;

	a = malloc(SIZ);
	b = malloc(SIZ);

	aa = (char*)a;
	aa[SIZ - 1] = 'a';
	bb = (char*)b;

	mymemcpy(b, a, SIZ);
	assert(bb[SIZ - 1] == 'a');

	return 0;
}
