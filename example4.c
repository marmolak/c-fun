#include <stdio.h>

struct struct_with_const {
    int y;
    int x;
    int a;
    /* Interesting. When I move this on beginning of struct, clang returns zeroes. In gcc case it doesn't matter. */
    struct struct_with_const *p;
};

struct struct_with_const *construct (struct struct_with_const *x)
{
    x->y = 2;
    x->x = 222;
    x->a = 666;
    return x;
}

void fce (struct struct_with_const *h)
{
    printf ("%d\n", h->y);
    printf ("%d\n", h->x);
    printf ("%d\n", h->a);
}

int main ()
{
    struct struct_with_const x = { .p = construct(&x) };
    fce(&x);

    return 0;
}
