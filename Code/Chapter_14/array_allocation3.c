//allocate memory for an array of integers, then pass a funny value to free and see what happens

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 int *data = (int *) malloc(100*sizeof(int));
	 data[1] = 5;
	 free(data+50); 
}