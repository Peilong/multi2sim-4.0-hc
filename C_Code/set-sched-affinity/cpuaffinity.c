/* Short test program to test sched_setaffinity
 * (which sets the affinity of processes to processors).
 * Compile: gcc sched_setaffinity_test.c
 *              -o sched_setaffinity_test -lm
 * Usage: ./sched_setaffinity_test
 *
 * Open a "top"-window at the same time and see all the work
 * being done on CPU 0 first and after a short wait on CPU 1.
 * Repeat with different numbers to make sure, it is not a
 * coincidence.
 */

#define _GNU_SOURCE  
#include <stdio.h>
#include <math.h>
#include <sched.h>
#include <unistd.h>

double waste_time(long n)
{
	double res = 0;
	long i = 0;
	while(i <n * 200) 
	{
		i++;
		res += sqrt (i);
	}
	return res;
}


int main(int argc, char **argv)
{
	unsigned long mask = 1; /* processor 0 */
	cpu_set_t cs;
	int ret;

	//get system cpu numbers
	int cpunum=sysconf(_SC_NPROCESSORS_CONF);
	printf("Total [%d] CPU cores\n",cpunum);


	/* bind process to processor 0 */
	ret = sched_setaffinity(0, sizeof(mask), &mask);
	if (ret <0) 
	{
		perror("sched_setaffinity");
	}

	//Get the default CPU core info
	CPU_ZERO(&cs);
	if(ret=sched_getaffinity(0,sizeof(cs),&cs))
	{
		printf("Failed to get CPU cores info [%d]\n",ret);
		return 3;
	}

	char i = 0;
	for (i=0;i<cpunum;i++)
	{
		if(CPU_ISSET(i,&cs))
		printf("Initially: I am running on CPU core[%d]\n",i);
	}
	
	/* waste some time so the work is visible with "top" */
	printf ("result: %f\n", waste_time (200000));

	mask = 2; /* process switches to processor 1 now */
	ret = sched_setaffinity(0, sizeof(mask), &mask);
	if (ret <0) {
		perror("sched_setaffinity");
	}

	//Get the default CPU core info
	CPU_ZERO(&cs);
	if(ret=sched_getaffinity(0,sizeof(cs),&cs))
	{
		printf("Failed to get CPU cores info [%d]\n",ret);
		return 3;
	}

	for (i=0;i<cpunum;i++)
	{
		if(CPU_ISSET(i,&cs))
		printf("Afterwards: I am running on CPU core[%d]\n",i);
	}

	/* waste some more time to see the processor switch */
	printf ("result: %f\n", waste_time (200000));
}

