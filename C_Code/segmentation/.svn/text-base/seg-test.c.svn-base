#include "segmentation_acc.h"
#include "seg_bus.h"
#include "stdlib.h"
#include "stdio.h"

#define ARRAY_SIZE (512*512)

int main ()
{
	//float * A_bus;
	//float * B_bus;

	float C[ARRAY_SIZE];
	int c[2];
	long loop = 0;

	c[0] = -2;
	c[1] = 2;

	//accPrintCycle();
	while (1)
	{
		segmentation_acc(Bus_A, Bus_B, C, c);
		printf("Loop: %lu\n", loop++);
	}	
	//accPrintCycle();	

	printf ("Segmentation ACC Done. \n");
	return 0;
}
