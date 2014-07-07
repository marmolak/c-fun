#include <stdio.h>

int main ()
{
    int id = 1;
    int p;
    for (p = 0; p < 32; ++p) {
        id <<= 1;
    }

    printf ("%d\n", id);

    id = 1;
    id <<= 32;
    printf ("%d\n", id);

    printf ("%d\n", 1<<32);
}
