/**
 *  Attribute alignment
 *  ===================
 *
 *  Compiler extension for alignment, e.g. for avoiding cacheline false sharing.
 */

#include <stdlib.h>
#include <assert.h>

// Power-of-two word.
#define CACHE_ALIGNED __attribute__((__aligned__(sizeof(size_t) * 2)))

typedef struct foo_t {
	int a CACHE_ALIGNED;
	int b CACHE_ALIGNED;
} foo_t;

int
main()
{
	assert(sizeof(foo_t) == sizeof(size_t) * 4);
	return 0;
}
