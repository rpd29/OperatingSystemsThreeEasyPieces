#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sched.h>
#include <assert.h>
#include <stdbool.h>
#define _GNU_SOURCE


int main(int argc, char *argv[]) {
	
	//CODE TO MEASURE COST OF A SYSTEM CALL
	struct timeval current_time; 
	gettimeofday(&current_time,NULL); 
	printf("SYSTEM CALL COST TEST\n\n");
	printf("Start seconds: %ld\nStart micro seconds: %d\n", current_time.tv_sec, current_time.tv_usec);
	char *str;  
	int i; 
	for (i=1; i<20; i++) {
		str = (char *) malloc(15); 
	};

	gettimeofday(&current_time,NULL); 
	printf("End seconds: %ld\nEnd micro seconds: %d\n", current_time.tv_sec, current_time.tv_usec);
	printf("Total number of system calls: %d\n\n\n", i);

	
	//CODE TO MEASURE COST OF A CONTEXT SWITCH. 
	//IDEA IS TO MEASURE TIME CONSECUTIVELY WITHIN EACH PROCESS IN A LOOP, AND SEE HOW TIME DIFFERENCE BETWEEN CONSECUTIVE MEASUREMENTS WITHIN A PROCESS COMPARES TO CONSECUTIVE MEASUREMENTS ACROSS PROCESSES. 
	//NOTE HOWEVER THAT MacOS DOESN'T APPEAR TO PROVIDE AN INTERFACE FOR PINNING PROCESSES TO SPECIFIC CPUs AS OF WHEN THIS CODE WAS WRITTEN, WHICH REALLY MAKES THIS TEST MEANINGLESS SINCE BOTH PROCESSES COULD BE RUNNING CONCURRENTLY ON TWO CPUs
	//THE LOOPS BELOW ALSO APPEAR TO RUN A VARIABLE NUMBER OF TIMES ON MacOS, POSSIBLY ALSO DUE TO INABILITY TO BIND THE PROCESSES TO THE SAME CPU (SO AS A RESULT IT IS POSSIBLE THAT BOTH PROCESSES ARE STOPPED SIMULTANEOUSLY, WITH NEITHER PROCESS ABLE TO SEND CONTINUE SIGNAL TO OTHER PROCESS)

	printf("CONTEXT SWITCH COST TEST\n\n");

	int rc = fork(); //Fork to create two processes
	
	if (rc<0) { //Code to execute if fork fails
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 

	else if (rc == 0) { //Code to execute in child process
		pid_t child_pid = getpid();
		pid_t p_pid = getppid(); 
				
		//Loop for measuring cost of context switch
		for (int i = 0; i < 20; i++) {
			gettimeofday(&current_time,NULL); 
			printf("Child process first time seconds: %ld\nChild process first time micro seconds: %d\n", current_time.tv_sec, current_time.tv_usec);
			gettimeofday(&current_time,NULL); 
			printf("Child process second time seconds: %ld\nChild process second time micro seconds: %d\n\n", current_time.tv_sec, current_time.tv_usec);
			kill(p_pid,SIGCONT); //Send signal to parent process to continue 
			kill(child_pid,SIGSTOP); //Pause process and wait for parent to send SIGCONT signal
		}
	} 

	else { //Code to execute in parent process

		pid_t parent_pid = getpid();

		//THE CODE BELOW WOULD BE USED TO BIND BOTH PROCESSES TO THE SAME CPU ON A LINUX SYSTEM. BECAUSE THIS PROGRAM IS BEING RUN ON A MAC, WHICH DOESN'T SUPPORT CPU PINNING, THIS CODE HAS BEEN COMMENTED OUT 
		//cpu_set_t test_set;
		//CPU_ZERO(&test_set); 
		//CPU_SET(0, &test_set);
		//int parent_cpu_bind = sched_setaffinity(parent_pid, sizeof(cpu_set_t), &test_set);
		//int child_cpu_bind = sched_setaffinity(rc, sizeof(cpu_set_t), &test_set);
		//if (parent_cpu_bind == 1 & child_cpu_bind == 1) {
		//	printf("Parent and child bound to same CPU!");
		//}
		
		//Loop for measuring cost of context switch
		for (int i = 0; i < 20; i++) {
			gettimeofday(&current_time,NULL); 
			printf("Parent process first time seconds: %ld\nParent process first time micro seconds: %d\n", current_time.tv_sec, current_time.tv_usec);
			gettimeofday(&current_time,NULL); 
			printf("Parent process second time seconds: %ld\nParent process second time micro seconds: %d\n\n", current_time.tv_sec, current_time.tv_usec);
			kill(rc,SIGCONT); //Send SIGCONT signal to child process to allow it to continue
			kill(parent_pid,SIGSTOP); //Pause process until receiving a SIGCONT signal from child process
		}

	} 
	return 0; 
} 

