//allocate memory for an array of integers, free them, then try to print an array value and see what happens when using valgrind

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 int *data = (int *) malloc(100*sizeof(int));
	 data[1] = 5;
	 free(data);
	 printf("integer: %d", data[1]); 
}