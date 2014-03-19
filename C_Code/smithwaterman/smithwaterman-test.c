//============== jacobi-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "smithwaterman.h"

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


int main(int argc, char *argv[]) 
{

	int i;
    char aa [21];
	char q[STRLEN];
	//Init aa[i], q[i]
	for (i=0; i<21; i++)
		aa[i] = random_number_gen();
	for (i=0; i<STRLEN; i++)
		q[i] = random_number_gen();

	accPrintCycle();
	SmithWaterman(aa, q);
	accPrintCycle();	
	
	printf("Smithwaterman finished\n");
	return 1;
}


