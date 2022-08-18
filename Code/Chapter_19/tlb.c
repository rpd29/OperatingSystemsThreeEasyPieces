//program to help determine number and approximate size of translation lookaside buffers (TLBs) on computer running it 
//First command line argument is number of pages to touch, second command line argument is number of trials, third command line argument is number of bytes per page on computer

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	 
	 int number_of_pages, number_of_trials, integers_per_page, bytes_per_page;
	 number_of_pages = atoi(argv[1]);
	 number_of_trials = atoi(argv[2]);
	 bytes_per_page = atoi(argv[3]);
	 integers_per_page = bytes_per_page/sizeof(int) + 1; 
	 int a[(integers_per_page)*number_of_pages];

	 struct timeval start_time, finish_time; 
	 gettimeofday(&start_time,NULL); 

	 for(int i = 0; i < number_of_trials; i++) {
	 	for(int j = 0; j < number_of_pages*integers_per_page; j += integers_per_page) {
	 		a[j] += 1;
	 	}
	 }
	 
	 gettimeofday(&finish_time,NULL);
	 double time_elapsed = 1000000000 * (finish_time.tv_sec - start_time.tv_sec) + 1000*(finish_time.tv_usec - start_time.tv_usec); //In nanoseconds
	 double average_time_per_access = time_elapsed/(number_of_pages*number_of_trials); //In microseconds

	 printf("%lf",average_time_per_access);

	 return 0;
}