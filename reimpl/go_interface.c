/**
 * Go interface in C
 * =================
 *
 * Disclaimer: May not be correct.
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_M,
} Type; 

// type I interface {
//     Func()
// }

typedef struct {
    void(*Func)(void *data);
} IfaceI;

typedef struct {
    Type CurType;
    IfaceI Face;
    void *Data;
} I;

// type M struct {
//     Data int
// }
//
// func (m M) Func() {
//     fmt.Println(m.Data)
// }

typedef struct {
    int Value;
} M;

void Func(void *data)
{
    printf("%d\n", ((M *)data)->Value);
}

int main()
{
    // var i I = M{42}
    M m = { 42 };
    I *i = malloc(sizeof(I));
    i->Data = &m;
    i->CurType = TYPE_M;
    i->Face.Func = Func;

    // i.Func()
    i->Face.Func(i->Data);

    return 0;
}
