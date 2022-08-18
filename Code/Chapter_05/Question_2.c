#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int fd = open("/Users/ravi_deedwania/Documents/OSTEP/Code/Chapter_5/test_file_to_open",O_RDWR,0);
	int rc = fork();
	if (rc<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if (rc == 0) {
		char test_str1[100] = "child test string\n";
		write(fd,test_str1,100);
	} else {
		char test_str2[100] = "parent test string\n";
		write(fd,test_str2,100);
	} 
	return 0; 
}