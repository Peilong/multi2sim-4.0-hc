//============== jacobi-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "jacobi.h"
#include "des.h"

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
	printf( "\nnumber of Jacobi applied: %i\n", nrot);
	return NULL;
}

//------------------- 3des thread --------------------//
void *desthread(void *arg) 
{
	int i, j, u, v;
	des_context ctx;
	des3_context ctx3;
	int iter;
	unsigned char buf[8 * 1024];

	pthread_barrier_wait(&barrier);	
	for( i = 0; i < 2; i++ )
	{
		u = 0;
		v = i & 1;

		printf( "  DES%c-EBC-%3d (%s): ",
		( u == 0 ) ? ' ' : '3', 64 + u * 64,
		( v == 0 ) ? "enc" : "dec" );

		for(iter=0; iter<1024; ++iter)
		memcpy( buf + iter*8, DES3_init, 8 );

		if( u == 0 )
		des_set_key( &ctx,  (unsigned char *) DES3_keys );

		if( u == 1 )
		des3_set_2keys( &ctx3, (unsigned char *) DES3_keys );

		if( u == 2 )
		des3_set_3keys( &ctx3, (unsigned char *) DES3_keys );

		for( j = 0; j < 1; j++ )
		{
			if( u == 0 )
			{
				if( v == 0 ) des_encrypt( &ctx, buf, buf );
				if( v == 1 ) des_decrypt( &ctx, buf, buf );
			}
			else
			{
				if( v == 0 ) des3_encrypt( &ctx3, buf, buf );
				if( v == 1 ) des3_decrypt( &ctx3, buf, buf );
			}
		}

		printf( "finished\n" );
	}
	return NULL;
}


int main(int argc, char *argv[]) 
{
	pthread_t threads[2];
	pthread_barrier_init(&barrier, NULL, 2);


	//Create two threads
	printf("creating the threads\n");
	pthread_create(&threads[0], NULL, jacobithread, NULL);
	pthread_create(&threads[1], NULL, desthread, NULL);

	
	pthread_join (threads[0],NULL);
	pthread_join (threads[1],NULL);

	printf("end of main thread\n");
	pthread_barrier_destroy(&barrier);

	return 1;
}


