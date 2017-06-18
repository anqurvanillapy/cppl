/**
 *  Generic Vector
 *  ==============
 *
 *  A generic vector written in C, inspired by this blog post:
 *
 *      https://tiehuis.github.io/generic-data-structures-in-c
 *
 *  TODO: RAII.
 *
 *  Note: Compile with -std=c11 -fplan9-extensions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

/* Helpers. */

/// Avoids macro naming errors.
typedef char* string;

/// Like a compile-time switch statement on types.
#define GET_FMT_SPEC(x) _Generic((x), int: "%d", float: "%f", char*: "\"%s\"")

/// Get the length of initializer list.
#define ARR_LEN(a) (sizeof(a) / sizeof(*a))

/* Definitions. */

/// Type-independent header of gvec.
typedef struct {
    size_t cap, siz;
} _gvec_header;

/// The data[] as the last member of struct is a flexible array member from C99.
#define gvec(T) \
    struct gvec_##T { \
        _gvec_header; \
        T data[]; \
    }

/// Allocation by using statement expression, which returns a pointer.
#define gvec_new(T, args...) \
({ \
    const size_t n = 16; \
    const T _args[] = {args}; \
    assert(("initialize too many elements", ARR_LEN(_args) <= n)); \
    struct gvec_##T *v = malloc(sizeof(_gvec_header) + sizeof(T) * n); \
    v->cap = n; \
    v->siz = ARR_LEN(_args); \
    for (size_t i = 0; i < v->siz; ++i) v->data[i] = _args[i]; \
    v; \
})

#define gvec_pop(v) (v->data[--v->siz])

/// Returns an lvalue that can be used with a pointer dereference.
#define gvec_ref(v, i) (&v->data[i])
#define gvec_at(v, i) (*(gvec_ref(v, i)))

/// A lot of struct assignments here...
#define gvec_push(v, args...) \
({ \
    const __typeof__(*v->data) _args[] = {args}; \
    if (v->siz + ARR_LEN(_args) >= v->cap) { \
        while (v->cap <= v->siz + ARR_LEN(_args)) v->cap *= 2; \
        v = realloc(v, sizeof(_gvec_header) + v->cap * sizeof(*v->data)); \
    } \
    for (int i = 0; i < ARR_LEN(_args); ++i) v->data[v->len++] = _args[i]; \
    v; \
})

#define gvec_free(v) free(v)

#define gvec_repr(v) \
({ \
    printf("["); \
    for (size_t i = 0; i < v->siz; ++i) { \
        printf(GET_FMT_SPEC(v->data[i]), v->data[i]); \
        if (i + 1 < v->siz) printf(", "); \
    } \
    printf("]\n"); \
})

/* Have some fun now. */

typedef struct {
    int x, y;
} tuple;

int
main(int argc, const char *argv[])
{
    gvec(string) *sv = gvec_new(string, "hello", "world", "crazy", "tho");
    gvec_repr(sv);
    gvec_free(sv);

    gvec(tuple) *tv = gvec_new(tuple, { .x = 1, .y = 2 }, {3, 4}, {5, 6});
    printf("gvec<tuple>[1].x=%d\n", gvec_at(tv, 1).x);
    gvec_free(tv);

    // Assertion error.
    gvec(int) *iv = gvec_new(int, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);
    gvec_repr(iv);
    gvec_free(iv);

    return 0;
}
