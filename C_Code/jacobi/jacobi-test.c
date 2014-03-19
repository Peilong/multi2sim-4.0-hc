#include "jacobi.h"
#include "jacobi_data.h"
#include "stdlib.h"
#include "stdio.h"

int main ()
{
	int   nrot;
	float v[N][N];
	unsigned long loop;

	//accPrintCycle();

	for (loop = 1; 1 ; ++loop)
	{
		//jacob (a, d, v, &nrot);
		printf("Jacobi Loop: %lu\n", loop);
	}

	//accPrintCycle();

	printf( "\nnumber of Jacobi applied: %i\n", nrot);
	return 1;
}
