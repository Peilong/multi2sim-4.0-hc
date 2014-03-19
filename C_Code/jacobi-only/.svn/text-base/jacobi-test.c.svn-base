#include "jacobi.h"
#include "stdlib.h"
#include "stdio.h"

#define RANMAX 10000.0

float random_number_gen ()
{
	float random_number;
	return random_number = rand() / (float)RANMAX;
}

int main ()
{
	int i, j, nrot;
	float a[N][N], d[N], v[N][N];
	
	for (i = 0; i <= N; i++)
		for (j = 0; j < N; j++)
			a[i][j] = 1.2 * random_number_gen ();

	for (i = 0; i <= N; i++)
		d[i] = random_number_gen ();

	
	jacob (a, d, v, &nrot);
	

	printf( "\nnumber of Jacobi applied: %i\n", nrot);
	return 1;
}
