//create a null pointer and dereference it to see what happens

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 int *x = NULL;
	 printf("integer: %d", *x);
}