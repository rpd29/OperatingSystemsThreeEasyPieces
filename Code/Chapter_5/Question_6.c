#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int rc = fork();
	if (rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("child process id: %d\n", (int) getpid());
	} else {
		int rc_wait_parent = waitpid(rc, NULL, 0);
		printf("return value of parent waitpid call: %d\n", rc_wait_parent); 
	} 
	return 0; 
}

