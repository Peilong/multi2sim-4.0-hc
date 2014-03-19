//============== 3des-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "SURF.h"
#include "Jacobians.h"

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
	for (i=0; i<4085; i++) 
	// SURF exe cycles is 41 times less than Smithwaterman
	// We execute SURF 41 times to make sure the two threads
	// end almost at the same time.
	{
		SURFdescriptor(&keypoint, descriptor, img, sum);
	}

	printf ("SURFdescriptor ACC Done. \n");

	return NULL;
}

//------------- SLAM jacobians thread ------------------//
void *JacobiansThread(void *arg) 
{
	CPose3DQuat X, U;
	kftype df_dx[7][4];
	CPose3DQuat out_X_oplus_U[1];
	unsigned int i,j;

	X = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	U = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	for (i=0; i<7; i++)
		for (j=0; j<4; j++)
			df_dx[i][j] = random_number_gen();

	pthread_barrier_wait(&barrier);	
	for (i=0; i<78572; i++)
	//SURF exe cycles are 19 times larger than SLAM-J	
	// We execute SLAM 19 times to make sure the two threads
	// end almost at the same time.
	{
		jacobiansPoseComposition(X, U, df_dx, out_X_oplus_U);
	}
	printf ("SLAM jacobians ACC Done. \n");
	return NULL;
}


int main(int argc, char *argv[]) 
{
	pthread_t threads[2];
	pthread_barrier_init(&barrier, NULL, 2);


	//Create two threads
	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, SURFThread, NULL);
	pthread_create(&threads[1], NULL, JacobiansThread, NULL);

	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);

	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


