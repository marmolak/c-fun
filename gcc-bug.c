/* Compile this with -ftrapv on gcc < 4.10 or clang */

/* 
GCC will produce:
gcc version 4.8.3 20140624 (Red Hat 4.8.3-1) (GCC)

gcc -ggdb3 -o gcc-bug -ftrapv gcc-bug.c

main:
...
   0x00000000004005e2 <+34>:	cltq   
   0x00000000004005e4 <+36>:	mov    $0x7fffffff,%esi
   0x00000000004005e9 <+41>:	mov    %rax,%rdi
   0x00000000004005ec <+44>:	callq  0x400620 <__mulvdi3>
...

__mulvdi3:
...
   0x0000000000400620 <+0>:	mov    %rdi,%rax
   0x0000000000400623 <+3>:	imul   %rsi
   0x0000000000400626 <+6>:	mov    %rax,%rsi
   0x0000000000400629 <+9>:	sar    $0x3f,%rsi
   0x000000000040062d <+13>:	cmp    %rdx,%rsi
   0x0000000000400630 <+16>:	jne    0x400634 <__mulvdi3+20>
   0x0000000000400632 <+18>:	repz retq 
   0x0000000000400634 <+20>:	push   %rax
   0x0000000000400635 <+21>:	callq  0x400480 <abort@plt>
...
32-bit signed integer is promoted to signed long. Then overflow can happen.

clang on fedora 20:
clang version 3.4 (tags/RELEASE_34/final)
Target: x86_64-redhat-linux-gnu

clang -ggdb3 -o gcc-bug -ftrapv gcc-bug.c

main:
...
   0x00000000004005a3 <+35>:	mov    $0x7fffffff,%ecx
   0x00000000004005a8 <+40>:	imul   %eax,%ecx
   0x00000000004005ab <+43>:	seto   %dl
   0x00000000004005ae <+46>:	xor    $0x1,%dl
   0x00000000004005b1 <+49>:	test   $0x1,%dl
   0x00000000004005b4 <+52>:	mov    %ecx,-0x18(%rbp)
   0x00000000004005b7 <+55>:	jne    0x4005bf <main+63>
   0x00000000004005bd <+61>:	ud2    
   0x00000000004005bf <+63>:	lea    0x400690,%rdi
...

Clang uses 32-bit signet arithmetics

NOTE (from wiki):
UD2 Undefined Instruction
Generates an invalid opcode. This instruction is provided for software testing
to explicitly generate an invalid opcode. The opcode for this instruction is
reserved for this purpose.

This will be patched in gcc 4.10
https://gcc.gnu.org/ml/gcc-patches/2014-07/msg01626.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv)
{
    signed int x = INT_MAX * atoi(argv[1]);
    printf ("%d\nsizeof int: %lu\n sizeof long: %lu\n", x, sizeof(int), sizeof(long));

    return 0;
}
