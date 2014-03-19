#include "IDSI.h"
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
	unsigned char img[IMGH][IMGW];
	int x, y;
	float idsi[DIM_DIST][DIM_INTEN];
	unsigned int i,j;


	for (i=0; i<IMGH; i++)
		for (j=0; j< IMGW; j++)
			img[i][j] = random_char_gen();

	x = random_char_gen();
	y = random_char_gen();

	computeIDSI(img, x, y, idsi);

	printf ("IDSI ACC Done. \n");
	return 0;
}

