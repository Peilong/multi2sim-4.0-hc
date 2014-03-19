#include "SphericalCoords.h"
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
	CPose3DQuat cpose;
	TPoint3D point;
	kftype out_jacob_dryp_dpoint[3][3];
	kftype out_jacob_dryp_dpose[3][7];
	unsigned int i,j;

	cpose = (CPose3DQuat) {random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen(), random_number_gen(),
		random_number_gen()};

	point = (TPoint3D) {
		random_number_gen(), 
		random_number_gen(),
		random_number_gen()
	};

	for (i=0; i<3; i++)
		for (j=0; j<3; j++)
			out_jacob_dryp_dpoint[i][j] = random_number_gen();

	for (i=0; i<3; i++)
		for (j=0; j<7; j++)
			out_jacob_dryp_dpose[i][j] = random_number_gen();

	sphericalCoordinates(cpose,point,
		out_jacob_dryp_dpoint,
		out_jacob_dryp_dpose
	);

	printf ("SLAM Sperical Coords ACC Done. \n");
	return 0;
}


