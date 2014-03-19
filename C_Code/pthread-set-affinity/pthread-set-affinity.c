#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>

#define CPU_NUM 3




double waste_time(long n)
{
    double res = 0;
    long i = 0;
    while (i <n * 200000) {
        i++;
        res += sqrt(i);
    }
    return res;
}

void *thread_func (void *arg)
{
	int ret = 0;
	int threadno = arg;	
	int cpu_num = CPU_NUM;
	
	cpu_set_t mask ;
	CPU_ZERO (&mask);
	CPU_SET (threadno, &mask);

	
	printf ("thread function is called, arg = %d\n", threadno);
	ret = pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask );
	if(ret < 0)
	{
		printf("pthread_setaffinity_np err \n");
		return ;
	}

	int x1 = 0;
	while(1)
	{
		if(x1 > 9) //initially, 900000000
		{
			break;
		}
		x1++;
	}

	waste_time(1);

	ret =pthread_getaffinity_np(pthread_self(), sizeof(mask), &mask );
	if(ret < 0)
	{
		printf("pthread_getaffinity_np err \n");
		return ;
	}
	
	int j;
	for( j = 0; j < cpu_num; j++)
	{
		//printf ("CPU_COUNT = %d\n", CPU_COUNT(&mask));
		if(CPU_ISSET(j,&mask))
			printf("\n======= thread[%lu]\t bind cpu[%d]\n", pthread_self(), j);
	}
}

int main(int argc, char *argv[])
{
	int ret;
	int i;
	int cpu_num = CPU_NUM;

	//printf ("pid = %d\n",getpid());

	pthread_t thread[cpu_num - 1];
	struct timeval time1,time2;

	gettimeofday (&time1, NULL);

	// Pthread Create
	for (i=0; i<cpu_num; i++)
	{
		ret = pthread_create (&thread[i], NULL, thread_func, (void *)i);
		if (ret != 0)
			printf ("pthread_create err \n");
		else
			printf ("pthread_create thread [%d] success!\n", i);
	}

	// Pthread Join
	for (i=0; i<cpu_num; i++)
	{
		ret = pthread_join (thread[i], NULL);
		if (ret != 0)
			printf ("pthread_join err \n");
		else
			printf ("pthread_join thread [%d] success!\n", i);
	}

	ret = gettimeofday (&time2, NULL);
	printf("time spend:[%ld]s [%ld]ms \n",time2.tv_sec - time1.tv_sec,(time2.tv_usec - time1.tv_usec)/1000);

	return 0;
}

