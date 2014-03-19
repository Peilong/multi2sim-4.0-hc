//============== jacobi-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include "jacobi.h"
#include "smithwaterman.h"

//----------- V a r a i a b l e s ---------------------//
pthread_barrier_t barrier;

//----------- Random float number generator -----------//
#define RANMAX 10000.0
float random_number_gen ()
{
	float random_number;
	return random_number = rand() / (float)RANMAX;
}

//------------- Random char generator -----------------//
unsigned char random_char_gen()
{
	unsigned char a = (unsigned char) (rand() & 0x00ff);
	return a;	
}

//------------- Jacobi thread -------------------------//
void *jacobithread (void *arg)
{
	int i, j, nrot;
	float a[N][N], d[N], v[N][N];
	//Init a[i][j], d[i]
	for (i = 0; i <= N; i++)
		for (j = 0; j < N; j++)
			a[i][j] = 1.2 * random_number_gen ();
	for (i = 0; i <= N; i++)
		d[i] = random_number_gen ();

	pthread_barrier_wait(&barrier);
	jacob (a,d,v,&nrot);
	return NULL;
}

//------------ Smithe-Waterman thread ------------------//
void *smithwatermanthread(void *arg) 
{
	int i;
    char aa [21];
	char q[STRLEN];
	//Init aa[i], q[i]
	for (i=0; i<21; i++)
		aa[i] = random_number_gen();
	for (i=0; i<STRLEN; i++)
		q[i] = random_number_gen();

	pthread_barrier_wait(&barrier);	
	SmithWaterman(aa, q);
	return NULL;
}


int main(int argc, char *argv[]) 
{
	pthread_t threads[2];
	pthread_barrier_init(&barrier, NULL, 2);


	//Create two threads
	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, jacobithread, NULL);
	pthread_create(&threads[1], NULL, smithwatermanthread, NULL);

	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);

	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


