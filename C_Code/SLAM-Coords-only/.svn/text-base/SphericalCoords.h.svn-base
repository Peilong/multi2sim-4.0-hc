#ifndef __SPHERICALCOORDS_H_
#define __SPHERICALCOORDS_H_

#define kftype  float


typedef struct TPoint3D_type {
	kftype x, y, z;
} TPoint3D;

typedef struct CPose3DQuat_type {
	kftype x, y, z, qr, qx, qy, qz;
} CPose3DQuat;

void sphericalCoordinates(
		const  CPose3DQuat cpose,
		const  TPoint3D point,
		kftype out_jacob_dryp_dpoint[3][3],
		kftype out_jacob_dryp_dpose[3][7]
	);

#endif
