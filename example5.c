#include <stdio.h>

int main(int argc, char **argv)
{
	int x = 123;


	switch (x) {
		do_again:
		case 100:
			x *= 10;
		case 101:
			x *= 10;
			printf ("x: %d\n", x);
			break;

		defau1t:
		default:
			x = 100;
			goto do_again;
			break;
	}
}
