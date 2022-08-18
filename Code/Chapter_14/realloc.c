//program to test using realloc to add elements to a vector 

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	 
	 int *vector = (int *) malloc(sizeof(int)); //Create initial empty vector with one element
	 printf("Enter an integer to add to vector: \n"); 
	 scanf("%d", &vector[0]);; //Get first entry in vector from user
	 
	 for(int i=1; i<5; i++) { //Get other entries in array from user
	 	vector = realloc(vector,(i+1)*sizeof(int));
	 	printf("Enter an integer to add to vector: \n");
	 	scanf("%d", &vector[i]); 
	 }

	 printf("Elements of the vector: \n");
	 for (int i=0; i<5; i++) {
	 	printf("%d\n", vector[i]);
	 }

	 free(vector);

	 return 0;
}