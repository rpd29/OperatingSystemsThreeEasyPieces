//Program that uses an arbitrary amount of system memory specified by command line argument (in kilobytes)

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int process_id = getpid();
	printf("process id is: %d\n", process_id); //Print process id to use with pmap command 
	int memory_block_size = 1000*atoi(argv[1]); //Size of memory_block to allocate in bytes
	int *a;
	a = malloc(memory_block_size);
	int i = 1;
	int j;
	while (i>0) { 
		for(j=0; j<(memory_block_size); j++) {
			*(a+j) = j;
			// printf("%d\n", process_id);
		}
	}
	return 0; 
}