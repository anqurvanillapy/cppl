/**
 *  glibc Hashtable
 *  ===============
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <search.h>
#include <assert.h>

typedef struct unord_map_t {
	struct hsearch_data ht;
	size_t size;
} unord_map_t;

unord_map_t*
unord_map_create(size_t size)
{
	unord_map_t* self = (unord_map_t*)malloc(sizeof *self);
	assert(self);
	memset(self, 0, sizeof *self);
	hcreate_r(size, &self->ht);
	self->size = size;
	return self;
}

void
unord_map_destroy(unord_map_t** self)
{
	hdestroy_r(&(*self)->ht);
	free(*self);
	*self = NULL;
}

int
unord_map_add(unord_map_t* self, char* key, void* data)
{
	int rc;
	ENTRY e, *ep;

	e.key = key;
	e.data = data;
	rc = hsearch_r(e, ENTER, &ep, &self->ht);

	if (ep)
		++self->size;
	return rc;
}

void*
unord_map_get(unord_map_t* self, char* key)
{
	int rc;
	ENTRY e, *ep;

	e.key = key;
	rc = hsearch_r(e, FIND, &ep, &self->ht);

	if (ep) {
		assert(rc != 0);
		return ep->data;
	}
	return NULL;
}

int
main()
{
	int rc;
	size_t i;
	unord_map_t* ht = unord_map_create(8);
	void* d = NULL;

	const char* keys[] = { "foo", "bar" };
	const char* vals[] = { "42", "69" };

	for (i = 0; i < 2; ++i) {
		rc = unord_map_add(ht, (char*)keys[i], (char*)vals[i]);
		assert(rc != 0);
	}

	if ( (d = unord_map_get(ht, (char*)"foo")) != NULL)
		printf("%s\n", (char*)d);
	else
		printf("Not found\n");

	if ( (d = unord_map_get(ht, (char*)"baz")) != NULL)
		printf("%s\n", (char*)d);
	else
		printf("Not found\n");

	unord_map_destroy(&ht);
	assert(!ht);

	return 0;
}

