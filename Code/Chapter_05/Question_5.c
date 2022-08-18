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
		int rc_wait_child = wait(NULL);
		printf("child process id: %d\nreturn value of child wait call: %d\n", (int) getpid(), rc_wait_child);
	} else {
		int rc_wait_parent = wait(NULL);
		printf("return value of parent wait call: %d\n", rc_wait_parent); 
	} 
	return 0; 
}

