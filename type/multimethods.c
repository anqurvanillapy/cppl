/**
 *  Multimethods
 *  ============
 *
 *  Simulate multimethods (multiple dispatch) in C.
 */

#include <stdio.h>

typedef void (*fn_case_t)(void);

void fn_AA(void) { printf("A=>A\n"); }
void fn_AB(void) { printf("A=>B\n"); }
void fn_BA(void) { printf("B=>A\n"); }
void fn_BB(void) { printf("B=>B\n"); }

typedef enum {
  A,
  B,
  TYPE_NUM,
} Type;

fn_case_t fn_cases[TYPE_NUM][TYPE_NUM] = {
    {&fn_AA, &fn_AB},
    {&fn_BA, &fn_BB},
};

void run(Type m, Type n)
{
    (*fn_cases[m][n])();
}

int main()
{
    run(A, B);
    return 0;
}
