#ifndef __JACOBIANS_H_
#define __JACOBIANS_H_

#define kftype  float

typedef struct CPose3DQuat_type {
	kftype x, y, z, qr, qx, qy, qz;
} CPose3DQuat;


void jacobiansPoseComposition(
		const CPose3DQuat X,
		const CPose3DQuat U,
		kftype df_dx[7][4],
		CPose3DQuat out_X_oplus_U[1]
	);

#endif
