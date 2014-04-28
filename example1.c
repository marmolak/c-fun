#include <stdio.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static const int x = 10;

int main ()
{
    const long page_size = sysconf(_SC_PAGESIZE);

    unsigned long addr = (unsigned long) &x & ~(page_size - 1);
    printf ("original value of x: %d\n", x);
    printf ("address of x: %p\n", &x);
    printf ("page rounded address of x: 0x%x\n", addr);

    int *n_x = &x;
    const int ret = mprotect ((void *)addr, page_size, PROT_WRITE | PROT_READ | PROT_EXEC);
    if (ret == -1) {
        perror ("mprotect!");
        return EXIT_FAILURE;
    }

    /* write new value to x */
    *n_x = 666;

    printf ("n_x address: %p\n", n_x);
    printf ("new value of x: %d\n", x);
    printf ("new value of n_x: %d\n", *n_x);

    return EXIT_SUCCESS;
}
