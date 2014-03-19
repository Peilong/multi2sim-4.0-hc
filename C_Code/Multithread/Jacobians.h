#ifndef __JACOBIANS_H_
#define __JACOBIANS_H_

#define kftype  float

typedef struct CPose3DQuat_type {
	kftype x, y, z, qr, qx, qy, qz;
} CPose3DQuat;

typedef struct TPoint3D_type {
	kftype x, y, z;
} TPoint3D;

float inverseSqrt(float x);

void jacobiansPoseComposition(
		const CPose3DQuat X,
		const CPose3DQuat U,
		kftype df_dx[7][4],
		CPose3DQuat out_X_oplus_U[1]
	);


void sphericalCoordinates(
		const  CPose3DQuat cpose,
		const  TPoint3D point,
		kftype out_jacob_dryp_dpoint[3][3],
		kftype out_jacob_dryp_dpose[3][7]
	);


#endif
