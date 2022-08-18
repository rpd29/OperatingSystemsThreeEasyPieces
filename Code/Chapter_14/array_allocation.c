//allocate memory for an array of 100 integers and set array[100] equal to a value to see what happens when using debugging tools gdb and valgrind

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 int *data = (int *) malloc(100*sizeof(int));
	 data[100] = 0; 
}