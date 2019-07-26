/**
 *  Minimal VM
 *  ==========
 *
 *  A minimal VM that simulates GHC to evaluate `(\x -> x) 42`.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

typedef enum {
    TypeInt,
    TypeFun,
} type_t;

typedef void(*entry_t)();

typedef struct {
    type_t type;
    entry_t entry;
} infotbl_t;

typedef struct {
    infotbl_t* info_ptr;
    void *payload;
} heap_obj_t;

// VM

uintptr_t R1;
uintptr_t R2;
uintptr_t R3;
uintptr_t R4;

#define STACK_SIZ 8192

uintptr_t stk;

uintptr_t push(uintptr_t *s, heap_obj_t *v)
{
    uintptr_t obj = (uintptr_t)v;
    *(uintptr_t *)*s = obj;
    *s += sizeof(void *);
    return obj;
}

void pop(uintptr_t *s)
{
    *s -= sizeof(void *);
}

// Source

void v_entry() {}

infotbl_t v_info = {
    .type = TypeInt,
    .entry = v_entry,
};

void fn_entry() {
    R1 = R2;
}

infotbl_t fn_info = {
    .type = TypeFun,
    .entry = fn_entry,
};

int main() {
    stk = (uintptr_t)malloc(STACK_SIZ);

    heap_obj_t *v = (heap_obj_t *)malloc(sizeof(heap_obj_t));
    v->info_ptr = &v_info;
    v->payload = (void *)42;

    heap_obj_t *fn = (heap_obj_t *)malloc(sizeof(heap_obj_t));
    fn->info_ptr = &fn_info;
    fn->payload = NULL;

    R1 = push(&stk, fn);

    R2 = (uintptr_t)v->payload;
    R1 = (uintptr_t)((heap_obj_t *)R1)->info_ptr->entry;
    ((entry_t)R1)();

    printf("R1=%d\n", (int)R1);

    pop(&stk);

    free(v);
    free(fn);
    free((void *)stk);

    return 0;
}
