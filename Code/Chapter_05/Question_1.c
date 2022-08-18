#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	printf("hello world (pid:%d)\n", (int) getpid());
	int x = 100; //Test variable 
	int rc = fork();
	if (rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		x = 60; 
		printf("hello, I am child (pid:%d). The value of x is:%d\n", (int) getpid(), x);
	} else {
		int rc_wait = wait(NULL); 
		x = 50;
		printf("hello, I am parent of %d (pid:%d). The value of x is:%d\n", rc, (int) getpid(), x); 
	} 
	return 0; 
}