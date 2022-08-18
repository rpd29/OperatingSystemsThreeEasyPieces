//allocate memory and don't free before end of program to see what happens when using debugging tools gdb and valgrind

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 int *x = malloc(sizeof(int));
}