//============== 3des-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "SURF.h"
#include "IDSI.h"

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

//--------------------- SURF thread ------------------//
void *SURFThread(void *arg) 
{
	SURFPoint keypoint;
	keypoint = (SURFPoint){10, 10, 100, 0.77};

	float descriptor[DESC_SIZE];	
	unsigned char img[IMGH][IMGW];
	unsigned int sum[IMGH+1][IMGW+1];
	unsigned int i,j;

	for (i=0; i<DESC_SIZE; i++)
		descriptor[i] = random_number_gen();
	for (i=0; i<IMGH; i++)
		for (j=0; j< IMGW; j++)
			img[i][j] = random_char_gen();

	pthread_barrier_wait(&barrier);	
	SURFdescriptor(&keypoint, descriptor, img, sum);

	printf ("SURFdescriptor ACC Done. \n");

	return NULL;
}

//------------------------ IDSI thread ---------------//
void *IDSIThread(void *arg) 
{
	unsigned char img[IMGH][IMGW];
	int x, y;
	float idsi[DIM_DIST][DIM_INTEN];
	unsigned int i,j;


	for (i=0; i<IMGH; i++)
		for (j=0; j< IMGW; j++)
			img[i][j] = random_char_gen();

	x = random_char_gen();
	y = random_char_gen();

	pthread_barrier_wait(&barrier);	
	computeIDSI(img, x, y, idsi);

	printf ("IDSI ACC Done. \n");

	return NULL;
}


int main(int argc, char *argv[]) 
{
	pthread_t threads[2];
	pthread_barrier_init(&barrier, NULL, 2);


	//Create two threads
	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, SURFThread, NULL);
	pthread_create(&threads[1], NULL, IDSIThread, NULL);

	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);

	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


