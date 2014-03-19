#include "Jacobians.h"
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
	CPose3DQuat X, U;
	kftype df_dx[7][4];
	CPose3DQuat out_X_oplus_U[1];
	unsigned int i,j;

	X = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	U = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	for (i=0; i<7; i++)
		for (j=0; j<4; j++)
			df_dx[i][j] = random_number_gen();


	jacobiansPoseComposition(X, U, df_dx, out_X_oplus_U);

	printf ("SLAM jacobians ACC Done. \n");
	return 0;
}

