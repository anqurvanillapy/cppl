/**
 *  Lambda calculus in C
 *  ====================
 *
 *  I mean the abstract syntax.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct lambda {
    struct lambda *(*fp)(struct lambda *, ...);
} *lambda_t;

lambda_t ftrue(lambda_t x, ...) { return x; }
lambda_t vtrue = &(struct lambda){.fp = ftrue};

lambda_t ffalse(lambda_t x, ...) { va_list args; va_start(args, x); lambda_t  y = va_arg(args, lambda_t); va_end(args); return y; }
lambda_t vfalse = &(struct lambda){.fp = ffalse};

lambda_t fnot(lambda_t b, ...) { return b->fp(vfalse, vtrue); }
lambda_t vnot = &(struct lambda){.fp = fnot};

typedef struct { lambda_t lp; char* name; } symtbl_t;
symtbl_t *symtbl;

void
init_symtbl()
{
    symtbl = (symtbl_t *)malloc(sizeof(symtbl_t) *3);
    symtbl[0].lp = vtrue; symtbl[0].name = "true";
    symtbl[1].lp = vfalse; symtbl[1].name = "false";
    symtbl[2].lp = vnot; symtbl[2].name = "not";
}

char*
lookup(lambda_t  lp)
{
    size_t i;
    for (i = 0; i < sizeof(symtbl_t) * 3; ++i) {
        if (lp == symtbl[i].lp) {
            return symtbl[i].name;
        }
    }
    return "<nil>";
}

int main() {
    init_symtbl();
    lambda_t p1 = vnot->fp(vtrue);
    lambda_t p2 = vnot->fp(vfalse);
    printf("p1=%s,p2=%s\n", lookup(p1), lookup(p2));
    return 0;
}
