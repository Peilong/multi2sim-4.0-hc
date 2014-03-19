#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	struct timeval tv;
	//struct timespec tim;
	//tim.tv_sec = 1;
	//tim.tv_nsec = 1000;
	gettimeofday(&tv, NULL);
	//nanosleep (&tim,NULL);
	return 0;
}
