#include "segmentation_acc.h"
#include "stdlib.h"
#include "stdio.h"

#define RANMAX 10000.0
#define ARRAY_SIZE 262000

float random_number_gen ()
{
	float random_number;
	return random_number = rand() / (float)RANMAX;
}

int main ()
{
	float * A_bus;
	float * B_bus;
	float * C_bus;
	float A[ARRAY_SIZE], B[ARRAY_SIZE], C[ARRAY_SIZE];
	int c[2];
	long i;
	for (i=0; i<ARRAY_SIZE; i++)
		A[i] = random_number_gen();
	for (i=0; i<ARRAY_SIZE; i++)
		B[i] = random_number_gen();

	A_bus = A;
	B_bus = B;
	C_bus = C;

	c[0] = -2;
	c[1] = 2;

	segmentation_acc(A_bus, B_bus, C_bus, c);

	printf ("Segmentation ACC Done. \n");
	return 0;
}
