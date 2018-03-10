/**
 *  dynstr
 *  ======
 *
 *  Simple dynamic string library inspired by sds.
 */

#include <stdio.h>

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <assert.h>

#define unlikely(cond)  __builtin_expect(!!(cond), 0)

typedef struct dynstr_t {
	size_t len;
	char* str;
} dynstr_t;

char*
dynstr_new(const char* s)
{
	dynstr_t* self;

	if (s != NULL) {
		size_t len   = strlen(s);
		self = (dynstr_t*)malloc(sizeof(dynstr_t) + len + 1);

		if (unlikely(!self)) {
			return NULL;
		}

		self->len = len;
		self->str = (char*)&self[1];
		memcpy(self->str, s, len + 1);
	} else {
		self = (dynstr_t*)malloc(sizeof(dynstr_t) + 1);

		if (unlikely(!self)) {
			return NULL;
		}

		self->len   = 0;
		self->str = (char*)&self[1];
		*self->str  = '\0';
	}

	return self->str;
}

size_t
dynstr_len(const char* self)
{
	return ((dynstr_t*)(self - sizeof(dynstr_t)))->len;
}

int
dynstr_delete(char* self)
{
	if (self != NULL) {
		free((dynstr_t*)(self - sizeof(dynstr_t)));
		self = NULL;
		return 1;
	}

	return 0;
}

int
main()
{
	char* s = dynstr_new("Hello, world!\n");
	assert(s);
	assert(dynstr_len(s) == 14);
	printf("%s", s);
	dynstr_delete(s);
	return 0;
}
