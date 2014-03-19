//============== 3des-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
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
	jacobiansPoseComposition(X, U, df_dx, out_X_oplus_U);

	printf ("SLAM jacobians ACC Done. \n");
	return NULL;
}

//-------------- SLAM Coordinates thread ---------------//
void *CoordinatesThread(void *arg) 
{
	CPose3DQuat cpose;
	TPoint3D point;
	kftype out_jacob_dryp_dpoint[3][3];
	kftype out_jacob_dryp_dpose[3][7];
	unsigned int i,j;

	cpose = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	point = (TPoint3D) {
		random_number_gen(), 
		random_number_gen(),
		random_number_gen()
	};

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			out_jacob_dryp_dpoint[i][j] = random_number_gen();

	for (i=0; i<3; i++)
		for (j=0; j<7; j++)
			out_jacob_dryp_dpose[i][j] = random_number_gen();

	pthread_barrier_wait(&barrier);	
	sphericalCoordinates(cpose,point,
		out_jacob_dryp_dpoint,
		out_jacob_dryp_dpose
	);

	printf ("SLAM Sperical Coords ACC Done. \n");
	return NULL;
}


int main(int argc, char *argv[]) 
{
	pthread_t threads[2];
	pthread_barrier_init(&barrier, NULL, 2);


	//Create two threads
	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, JacobiansThread, NULL);
	pthread_create(&threads[1], NULL, CoordinatesThread, NULL);

	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);

	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


