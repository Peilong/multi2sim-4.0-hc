#include "SURF.h"
#include "stdlib.h"
#include "stdio.h"

#define RANMAX 10000.0

float random_number_gen ()
{
	float random_number;
	return random_number = rand() / (float)RANMAX;
}

unsigned char random_char_gen()
{
	unsigned char a = (unsigned char) (rand() & 0x00ff);
	return a;
}

int main ()
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

	SURFdescriptor(&keypoint, descriptor, img, sum);

	printf ("SURFdescriptor ACC Done. \n");
	return 0;
}
