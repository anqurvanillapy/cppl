/**
 *  Minimal VM
 *  ==========
 *
 *  A minimal VM that simulates GHC to evaluate the following Haskell code:
 *
 *  ```hs
 *  fn :: Int -> Int -> Int
 *  fn = \x y -> x
 *
 *  fnPartial :: Int -> Int
 *  fnPartial = fn 42
 *
 *  main :: IO ()
 *  main = print $ fnPartial 69
 *  ```
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum ObjType {
  ObjCtor, /**< Constructor */
  ObjThunk,
  ObjInd, /**< Indirection */
} obj_type_t;

typedef enum Type {
  TypeInt,
  TypeFun,
} type_t;

typedef void (*entry_t)();

typedef struct {
  type_t type;
  entry_t entry;
} infotbl_t;

typedef struct {
  obj_type_t obj_type;
  infotbl_t *info_ptr;
  void *payload;
} closure_t;

// VM

#define STACK_SIZ 8192

uintptr_t R1;
uintptr_t R2;
uintptr_t R3;
uintptr_t R4;

uintptr_t stk;

#define NOT_EVAL &(-8)
#define EVAL_1st +1

uintptr_t push(uintptr_t *s, closure_t *v) {
  uintptr_t obj = (uintptr_t)v;
  *(uintptr_t *)*s = obj;
  *s += sizeof(void *);
  return obj;
}

void pop(uintptr_t *s) { *s -= sizeof(void *); }

// Source

void v_entry() {}

infotbl_t v_info = {
    .type = TypeInt,
    .entry = v_entry,
};

closure_t v = {
    .obj_type = ObjCtor,
    .info_ptr = &v_info,
    .payload = (void *)42,
};

void fn_entry() {
  uintptr_t arg0 = R2;
  uintptr_t arg1 = R3;
  (void)arg1;
  R1 = arg0;
}

infotbl_t fn_info = {
    .type = TypeFun,
    .entry = fn_entry,
};

void fnPartial_entry() {
  uintptr_t arg0 = R2;

  R3 = arg0;
  R2 = (uintptr_t)v.payload;

  fn_info.entry();
}

infotbl_t fnPartial_info = {
    .type = TypeFun,
    .entry = fnPartial_entry,
};

int main() {
  stk = (uintptr_t)malloc(STACK_SIZ);

  closure_t *fn = (closure_t *)malloc(sizeof(closure_t));
  fn->obj_type = ObjThunk;
  fn->info_ptr = &fn_info;
  fn->payload = NULL;

  closure_t *fnPartial = (closure_t *)malloc(sizeof(closure_t));
  fnPartial->obj_type = ObjThunk;
  fnPartial->info_ptr = &fnPartial_info;
  fnPartial->payload = NULL;

  R1 = push(&stk, fnPartial);

  R2 = 69;
  R1 = (uintptr_t)((closure_t *)R1)->info_ptr->entry;
  ((entry_t)R1)();

  printf("R1=%d\n", (int)R1);

  pop(&stk);

  free(fn);
  free(fnPartial);
  free((void *)stk);

  return 0;
}
