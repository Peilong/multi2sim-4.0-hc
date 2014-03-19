//============== 3des-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "seg_bus.h"
#include "sample_image1.h"
#include "Jacobians.h"
#include "des.h"
#include "IDSI.h"
#include "jacobi.h"
#include "segmentation_acc.h"
#include "smithwaterman.h"
#include "SURF.h"


//---------------- C o n s t a n t s -------------------//
#define ARRAY_SIZE (512*512)
#define TOTALTHREADS 7

// Comment out the corresponding macros if you want to 
// turn off the accelerator
#if 0
#define ACC3DES
#define ACCIDSI
#define ACCSEG
#define ACCSLAMJ
#define ACCSLAMC
#define ACCSW
#define ACCSURF
#endif
//-------------- V a r a i a b l e s -------------------//
pthread_barrier_t barrier;


//================ F U N C T I O N S ===================//

//-------------- Random char generator -----------------//
// Purpose:
// Generate a character. Range from 0 ~ 255
// Input: Void
// Output: the character
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
	unsigned long loop = 0;


	X = (CPose3DQuat) {rand(), rand(),
		rand(), rand(),	rand(), rand(),	rand()};

	U = (CPose3DQuat) {rand(), rand(),
		rand(), rand(),	rand(), rand(),	rand()};

	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 41456 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		#ifdef ACCSLAMJ
		printf("SLAM-J Loop: %lu\n", loop);
		if (accSLAMJConfigReq())
		{
			if(accSLAMJConfigPrepared())
			{
				accSLAMJ();
			}
			else {jacobiansPoseComposition(X, U, df_dx, out_X_oplus_U);}
		}		
		else
		#endif
		jacobiansPoseComposition(X, U, df_dx, out_X_oplus_U);
	}
	//printf ("SLAM jacobians ACC Done. \n");
	return NULL;
}

//-------------- SLAM Coordinates thread ---------------//
void *CoordinatesThread(void *arg) 
{
	CPose3DQuat cpose;
	TPoint3D point;
	kftype out_jacob_dryp_dpoint[3][3];
	kftype out_jacob_dryp_dpose[3][7];
	unsigned long loop = 0;

	cpose = (CPose3DQuat) {rand(), rand(),
		rand(), rand(),	rand(), rand(), rand()};

	point = (TPoint3D) {
		rand(), rand(),	rand()
	};

	pthread_barrier_wait(&barrier);	

	for (loop = 0; loop < 41647 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		printf("SLAM-C Loop: %lu\n", loop);
		#ifdef ACCSLAMC
		if (accSLAMCConfigReq())
		{
			if(accSLAMCConfigPrepared())
			{
				accSLAMC();
			}
			else
			{	sphericalCoordinates(cpose,point,
		                     out_jacob_dryp_dpoint,
		                     out_jacob_dryp_dpose
	                        );
			}		
		}
		else
		#endif
			sphericalCoordinates(cpose,point,
		                     out_jacob_dryp_dpoint,
		                     out_jacob_dryp_dpose
	                        );
	}

	return NULL;
}

//------------------ 3 DES thread -------------------//
void *DESThread(void *arg) 
{
	int i, j, u, v;
	des_context ctx;
	des3_context ctx3;
	int iter;
	unsigned char buf[8 * 1024];
	unsigned long loop=0;

	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 5528 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		printf("3DES Loop: %lu\n", loop);
		#ifdef ACC3DES
		if (acc3DESConfigReq())
		{
			if(acc3DESConfigPrepared())
			{
				acc3DES();
			}
			else
			{
				for( i = 0; i < 2; i++ )
				{
					u = 0;
					v = i & 1;

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
				}		
			}
		}

		else
		
			#endif
			for( i = 0; i < 2; i++ )
			{
				u = 0;
				v = i & 1;

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
			}
	}
	return NULL;
}


//---------------------- IDSI thread -------------------------//
void *IDSIThread(void *arg) 
{
	unsigned char img[IMGH][IMGW];
	int x, y;
	float idsi[DIM_DIST][DIM_INTEN];
	unsigned int i,j;
	const unsigned char * arraypointer = sample_image1;
	unsigned long loop=0;

	arraypointer = sample_image1;
	for (i=0; i<IMGH; i++)
	{	
		for (j=0; j< IMGW; j++)
		{			
			img[i][j] = *arraypointer++;
		}
	}

	x = random_char_gen() % IMGW;
	y = random_char_gen() % IMGH;

	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 36793 ; loop ++)
	//for (loop = 0; 1; loop ++)
	{
		printf("IDSI Loop: %lu\n", loop);
		#ifdef ACCIDSI
		if (accIDSIConfigReq())
		{
			if(accIDSIConfigPrepared())
			{
				accIDSI();
			}
			else 
			{	
				computeIDSI(img, x, y, idsi);
			}
		}
		else
		#endif
			computeIDSI(img, x, y, idsi);
	}
	return NULL;
}


//--------------- SmithWaterman thread -------------------------//
void *SWThread(void *arg) 
{
    char aa [21];
	char q[STRLEN];
	unsigned long loop = 0;

	strcpy (aa, "acdefghiklmnpqrstvwy");
	//aa[20] = "acdefghiklmnpqrstvwy";
	/* Query Sequence = d1xpa_1 a.6.1.2 (134-210) from ASTRAL 1.67 40% */
	strcpy (q , "dkhklitkteakqeyllkdcdlekrepplkfivkknphhsqwgdmklylklqivkrslevwgsqealeeakevrqen");
/*
	for (i=0; i<21; i++)
		aa[i] = rand();
	for (i=0; i<STRLEN; i++)
		q[i] = rand();
*/
	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 1281 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		printf("SmithWaterman Loop: %lu\n", loop);
		#ifdef ACCSW
		
		if (accSWConfigReq())
		{
			if(accSWConfigPrepared())
			{
				accSW();
			}
			else 
			{SmithWaterman(aa, q);}
		}
		else
		#endif

		SmithWaterman(aa, q);
	}
	return NULL;
}


//--------------- Segmentation thread -------------------------//
void *SegThread(void *arg) 
{
	float C[ARRAY_SIZE];
	int c[2];
	unsigned long loop = 0;

	c[0] = -2;
	c[1] = 2;

	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 1 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		printf("Segmentation Loop: %lu\n", loop);
		#ifdef ACCSEG

		if (accSegConfigReq())
		{
			if(accSegConfigPrepared())
			{
				accSeg();
			}
			else segmentation_acc(Bus_A, Bus_B, C, c);
		}
		else

		#endif
		segmentation_acc(Bus_A, Bus_B, C, c);
	}
	return NULL;
}


//--------------------- SURF thread -------------------------//
void *SURFThread(void *arg) 
{
	SURFPoint keypoint;
	keypoint = (SURFPoint){6, 15, 1, 159};
	long loop = 0;

	float descriptor[DESC_SIZE];	
	unsigned char img[IMGH][IMGW];
	unsigned int sum[IMGH+1][IMGW+1];
	unsigned int i,j;
	const unsigned char * arraypointer = sample_image1;

	arraypointer = sample_image1;
	for (i=0; i<IMGH; i++)
		for (j=0; j< IMGW; j++)
			img[i][j] = *arraypointer++;

	pthread_barrier_wait(&barrier);	
	for (loop = 0; loop < 11634 ; loop ++)
	//for (loop = 0; 1; loop ++)	
	{
		printf("SURF Loop: %lu\n", loop);
		#ifdef ACCSURF

		if (accSURFConfigReq())
		{
			if(accSURFConfigPrepared())
			{
				accSURF();
			}
			else
			{SURFdescriptor(&keypoint, descriptor, img, sum);}
		}
		else

		#endif
		SURFdescriptor(&keypoint, descriptor, img, sum);
	}
	return NULL;
}

//--------------- M a i n   T h r e a d -----------------------//
int main(int argc, char *argv[]) 
{
	int i;
	pthread_t threads[TOTALTHREADS];

	//Create thread barrier
	pthread_barrier_init(&barrier, NULL, TOTALTHREADS);

	//Create two threads
	printf("Creating the threads\n");
	pthread_create(&threads[0], NULL, JacobiansThread, NULL);
	pthread_create(&threads[1], NULL, CoordinatesThread, NULL);
	pthread_create(&threads[2], NULL, DESThread, NULL);
	pthread_create(&threads[3], NULL, IDSIThread, NULL);
	pthread_create(&threads[4], NULL, SWThread, NULL);
	pthread_create(&threads[5], NULL, SURFThread, NULL);
	pthread_create(&threads[6], NULL, SegThread, NULL);

	//Pthread Join
	for (i=0; i< TOTALTHREADS; i++)
	{
		pthread_join (threads[i],NULL);
	}

	printf("end of main thread\n");

	//Destroy the thread barrier
	pthread_barrier_destroy(&barrier);

	return 1;
}


