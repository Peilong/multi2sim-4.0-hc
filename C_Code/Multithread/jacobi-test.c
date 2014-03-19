#include "jacobi.h"
#include "jacobi_data.h"
#include "stdlib.h"
#include "stdio.h"

int main ()
{
	int  i, nrot;
	float v[N][N];
	long loop = 0;
	//float (* matrix_a)[N], (* matrix_v)[N], * array_d;

	//matrix_a = a;
	//array_d  = d;
	//matrix_v = v;

	accPrintCycle();
	//while (1)
	for (i=0;i<1;i++)
	{
		jacob (a, d, v, &nrot);
		printf("Loop: %lu\n", loop++);
	}	
	accPrintCycle();

	printf( "\nnumber of Jacobi applied: %i\n", nrot);
	return 1;
}
