#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

//Function that executes when program receives SIGCONT signal from OS
void sig_cont_handler(int signum) {
	printf("goodbye\n");
	exit(0);
}

int main(int argc, char *argv[]) {
	pid_t parent_pid = getpid();
	int rc = fork();
	if (rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		printf("hello\n");
		kill(parent_pid,SIGCONT); //Send SIGCONT signal to parent process;
	} else {
		signal(SIGCONT,sig_cont_handler); //Assign function that says what to do when receive SIGCONT signal
		pause(); //Pause process until process receives SIGCONT signal and sig_cont_handler is invoked
	} 
	return 0; 
}

