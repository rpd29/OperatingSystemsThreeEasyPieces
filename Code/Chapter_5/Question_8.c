#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
	int pipefds[2];
	pipe(pipefds);
	int rc1 = fork();
	if (rc1<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc1 == 0) {
		char message_sent[100] = "message passed through pipe";
		write(STDOUT_FILENO, message_sent, 100);
	} else {
		int rc_wait_parent = wait(NULL);
		int rc2 = fork(); 
		if (rc2<0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		} else if (rc2 == 0) { 
			char message_received[100];
			read(STDIN_FILENO, message_received, 100);
			printf("%s\n", message_received);
		} 
	} 
	return 0; 
}

