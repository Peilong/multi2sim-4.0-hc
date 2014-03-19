/*---------------------------------------------------------------
                     sphericalCoordinates
---------------------------------------------------------------*/

/*---------------------------------------------------------------
                         USAGE:
 sensorPoseAbs.sphericalCoordinates(
							mapEst,
							obsData[0], // range
							obsData[1], // yaw
							obsData[2],  // pitch
							&Hy,
							&Hx_sensor
							);
----------------------------------------------------------------*/

#include <math.h>
#include "SphericalCoords.h"



void inverseComposePoint(
	const kftype m_coord_x, const kftype m_coord_y, const kftype m_coord_z,
	const kftype m_quat_r, const kftype m_quat_x, const kftype m_quat_y, const kftype m_quat_z,
	const kftype gx,const kftype gy,const kftype gz,
	kftype lx[1],kftype ly[1],kftype lz[1],
	kftype out_jacobian_df_dpoint[3][3],
	kftype out_jacobian_df_dpose[3][7]
);

float inverseSqrt(float x)
{
   float xhalf = 0.5f * x;
   int i = *(int*)&x;			// store floating-point bits in integer
   i = 0x5f3759d5 - (i >> 1);	// initial guess for Newton's method
   x = *(float*)&i;				// convert new bits into float
   x = x * (1.5f - xhalf*x*x);	// One round of Newton's method
   return x;
}

void sphericalCoordinates(
		const  CPose3DQuat cpose,
		const  TPoint3D point,
		kftype out_jacob_dryp_dpoint[3][3],
		kftype out_jacob_dryp_dpose[3][7]
	)
{

	const kftype m_coord[3] = {cpose.x, cpose.y, cpose.z};
	const kftype m_quat[4] = {cpose.qr, cpose.qx, cpose.qy, cpose.qz};
	
	// Pass to coordinates as seen from this 6D pose:
	kftype jacob_dinv_dpoint[3][3];
	//kftype **ptr_ja1 = &jacob_dinv_dpoint;
	kftype jacob_dinv_dpose[3][7];
	//kftype **ptr_ja2 = &jacob_dinv_dpose;

	// NOTE: Array represents a matrix as Matrix[row][column]
	TPoint3D local;
	inverseComposePoint(m_coord[0],m_coord[1],m_coord[2], m_quat[0],m_quat[1],m_quat[2],m_quat[3], 
						point.x,point.y,point.z,
						&(local.x),&(local.y),&(local.z),
						jacob_dinv_dpoint,jacob_dinv_dpose);
	
	// Range:
	kftype out_range = inverseSqrt(local.x*local.x + local.y*local.y + local.z*local.z); //sqrt(local.x*local.x + local.y*local.y + local.z*local.z);

	// Jacobians are: dryp_dpoint = dryp_dlocalpoint * dinv_dpoint    and    dryp_dpose = dryp_dlocalpoint * dinv_dpose
	// NOTE: Jacobians are undefined if range is 0
	if (local.x != 0 && local.y != 0 && local.z != 0) { //(out_range != 0) {
		const kftype out_range2 = out_range * out_range;
		const kftype _r = out_range;
		const kftype x2 = local.x * local.x;
		const kftype y2 = local.y * local.y;
		const kftype t2 = inverseSqrt(x2 + y2); //sqrt(x2 + y2);
		const kftype _K = t2 * out_range2; //1 / (t2 * out_range2);

		kftype dryp_dlocalpoint[3][3]= {
			{local.x*_r,				local.y*_r,					local.z*_r		},
			{-local.y/(x2*(y2/x2 + 1)),	1/(local.x*(y2/x2+1)),	0				},
			{local.x*local.z*_K,		local.y*local.z*_K,			-(out_range2)/t2} }; // -t2/(out_range2)} };
	
		//out_jacob_dryp_dpoint->multiply(dryp_dlocalpoint,jacob_dinv_dpoint);
		out_jacob_dryp_dpoint[0][0] = dryp_dlocalpoint[0][0]*jacob_dinv_dpoint[0][0] + dryp_dlocalpoint[0][1]*jacob_dinv_dpoint[1][0] + dryp_dlocalpoint[0][2]*jacob_dinv_dpoint[2][0];
		out_jacob_dryp_dpoint[0][1] = dryp_dlocalpoint[0][0]*jacob_dinv_dpoint[0][1] + dryp_dlocalpoint[0][1]*jacob_dinv_dpoint[1][1] + dryp_dlocalpoint[0][2]*jacob_dinv_dpoint[2][1];
		out_jacob_dryp_dpoint[0][2] = dryp_dlocalpoint[0][0]*jacob_dinv_dpoint[0][2] + dryp_dlocalpoint[0][1]*jacob_dinv_dpoint[1][2] + dryp_dlocalpoint[0][2]*jacob_dinv_dpoint[2][2];
	
		out_jacob_dryp_dpoint[1][0] = dryp_dlocalpoint[1][0]*jacob_dinv_dpoint[0][0] + dryp_dlocalpoint[1][1]*jacob_dinv_dpoint[1][0] + dryp_dlocalpoint[1][2]*jacob_dinv_dpoint[2][0];
		out_jacob_dryp_dpoint[1][1] = dryp_dlocalpoint[1][0]*jacob_dinv_dpoint[0][1] + dryp_dlocalpoint[1][1]*jacob_dinv_dpoint[1][1] + dryp_dlocalpoint[1][2]*jacob_dinv_dpoint[2][1];
		out_jacob_dryp_dpoint[1][2] = dryp_dlocalpoint[1][0]*jacob_dinv_dpoint[0][2] + dryp_dlocalpoint[1][1]*jacob_dinv_dpoint[1][2] + dryp_dlocalpoint[1][2]*jacob_dinv_dpoint[2][2];
	
		out_jacob_dryp_dpoint[2][0] = dryp_dlocalpoint[2][0]*jacob_dinv_dpoint[0][0] + dryp_dlocalpoint[2][1]*jacob_dinv_dpoint[1][0] + dryp_dlocalpoint[2][2]*jacob_dinv_dpoint[2][0];
		out_jacob_dryp_dpoint[2][1] = dryp_dlocalpoint[2][0]*jacob_dinv_dpoint[0][1] + dryp_dlocalpoint[2][1]*jacob_dinv_dpoint[1][1] + dryp_dlocalpoint[2][2]*jacob_dinv_dpoint[2][1];
		out_jacob_dryp_dpoint[2][2] = dryp_dlocalpoint[2][0]*jacob_dinv_dpoint[0][2] + dryp_dlocalpoint[2][1]*jacob_dinv_dpoint[1][2] + dryp_dlocalpoint[2][2]*jacob_dinv_dpoint[2][2];
	
		//out_jacob_dryp_dpose->multiply(dryp_dlocalpoint,jacob_dinv_dpose);
		out_jacob_dryp_dpose[0][0] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][0] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][0] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][0];
		out_jacob_dryp_dpose[0][1] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][1] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][1] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][1];
		out_jacob_dryp_dpose[0][2] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][2] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][2] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][2];
		out_jacob_dryp_dpose[0][3] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][3] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][3] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][3];
		out_jacob_dryp_dpose[0][4] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][4] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][4] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][4];
		out_jacob_dryp_dpose[0][5] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][5] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][5] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][5];
		out_jacob_dryp_dpose[0][6] = dryp_dlocalpoint[0][0]*jacob_dinv_dpose[0][6] + dryp_dlocalpoint[0][1]*jacob_dinv_dpose[1][6] + dryp_dlocalpoint[0][2]*jacob_dinv_dpose[2][6];
	
		out_jacob_dryp_dpose[1][0] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][0] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][0] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][0];
		out_jacob_dryp_dpose[1][1] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][1] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][1] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][1];
		out_jacob_dryp_dpose[1][2] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][2] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][2] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][2];
		out_jacob_dryp_dpose[1][3] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][3] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][3] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][3];
		out_jacob_dryp_dpose[1][4] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][4] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][4] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][4];
		out_jacob_dryp_dpose[1][5] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][5] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][5] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][5];
		out_jacob_dryp_dpose[1][6] = dryp_dlocalpoint[1][0]*jacob_dinv_dpose[0][6] + dryp_dlocalpoint[1][1]*jacob_dinv_dpose[1][6] + dryp_dlocalpoint[1][2]*jacob_dinv_dpose[2][6];
	
		out_jacob_dryp_dpose[2][0] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][0] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][0] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][0];
		out_jacob_dryp_dpose[2][1] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][1] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][1] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][1];
		out_jacob_dryp_dpose[2][2] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][2] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][2] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][2];
		out_jacob_dryp_dpose[2][3] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][3] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][3] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][3];
		out_jacob_dryp_dpose[2][4] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][4] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][4] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][4];
		out_jacob_dryp_dpose[2][5] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][5] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][5] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][5];
		out_jacob_dryp_dpose[2][6] = dryp_dlocalpoint[2][0]*jacob_dinv_dpose[0][6] + dryp_dlocalpoint[2][1]*jacob_dinv_dpose[1][6] + dryp_dlocalpoint[2][2]*jacob_dinv_dpose[2][6];
	}

}

void inverseComposePoint(
	const kftype m_coord_x, const kftype m_coord_y, const kftype m_coord_z,
	const kftype m_quat_r, const kftype m_quat_x, const kftype m_quat_y, const kftype m_quat_z,
	const kftype gx,const kftype gy,const kftype gz,
	kftype lx[1],kftype ly[1],kftype lz[1],
	kftype out_jacobian_df_dpoint[3][3],
	kftype out_jacobian_df_dpose[3][7])
{
    const kftype qr = m_quat_r;
	const kftype qx = m_quat_x;
	const kftype qy = m_quat_y;
	const kftype qz = m_quat_z;
	const kftype qx2 = qx * qx;
	const kftype qy2 = qy * qy;
	const kftype qz2 = qz * qz;
	
	const kftype Ax = 2 * (gx - m_coord_x);
	const kftype Ay = 2 * (gy - m_coord_y);
	const kftype Az = 2 * (gz - m_coord_z);
	
	out_jacobian_df_dpoint[0][0] = 1 - 2 * (qy2 + qz2);
	out_jacobian_df_dpoint[0][1] = 2 * (-qr * qz + qx * qy);
	out_jacobian_df_dpoint[0][2] = 2 * (qx * qz + qr * qy);
	
	out_jacobian_df_dpoint[1][0] = 2 * (qx * qy + qr * qz);
	out_jacobian_df_dpoint[1][1] = 1 - 2 * (qx2 + qz2);
	out_jacobian_df_dpoint[1][2] = 2 * (-qr * qx + qy * qz);
	
	out_jacobian_df_dpoint[2][0] = 2 * (-qr * qy + qx * qz);
	out_jacobian_df_dpoint[2][1] = 2 * (qy * qz + qr * qx);
	out_jacobian_df_dpoint[2][2] = 1 - 2 * (qx2 + qy2);
	
	
	kftype normSqr = qr*qr + qx*qx + qy*qy + qz*qz;
	const kftype n = inverseSqrt(normSqr * normSqr * normSqr); //1 / (sqrt(normSqr * normSqr * normSqr));
	
	out_jacobian_df_dpose[0][0] = 2*qy2 + 2*qz2 - 1;
	out_jacobian_df_dpose[0][1] = -2*qr*qz - 2*qx*qy;
	out_jacobian_df_dpose[0][2] = 2*qr*qy - 2*qx*qz;
	out_jacobian_df_dpose[0][3] = n * ( (-qy*Az + qz*Ay)*(qx*qx + qy*qy + qz*qz) + (qy*Ay + qz*Az)*(-qx * qr) + (qx*Ay - 2*qy*Ax - qr*Az)*(-qy * qr) + (qx*Az + qr*Ay - 2*qz*Ax)*(-qz * qr) );
	out_jacobian_df_dpose[0][4] = n * ( (-qy*Az + qz*Ay)*(-qr * qx) + (qy*Ay + qz*Az)*(qr*qr + qy*qy + qz*qz) + (qx*Ay - 2*qy*Ax - qr*Az)*(-qy * qx) + (qx*Az + qr*Ay - 2*qz*Ax)*(-qz * qx) );
	out_jacobian_df_dpose[0][5] = n * ( (-qy*Az + qz*Ay)*(-qr * qy) + (qy*Ay + qz*Az)*(-qx * qy) + (qx*Ay - 2*qy*Ax - qr*Az)*(qr*qr + qx*qx + qz*qz) + (qx*Az + qr*Ay - 2*qz*Ax)*(-qz * qy) );
	out_jacobian_df_dpose[0][6] = n * ( (-qy*Az + qz*Ay)*(-qr * qz) + (qy*Ay + qz*Az)*(-qx * qz) + (qx*Ay - 2*qy*Ax - qr*Az)*(-qy * qz) + (qx*Az + qr*Ay - 2*qz*Ax)*(qr*qr + qx*qx + qy*qy) );
			
	out_jacobian_df_dpose[1][0] = 2*qr*qz - 2*qx*qy;
	out_jacobian_df_dpose[1][1] = 2*qx2 + 2*qz2 - 1;
	out_jacobian_df_dpose[1][2] = -2*qr*qx - 2*qy*qz;
	out_jacobian_df_dpose[1][3] = n * ( (qx*Az - qz*Ax)*(qx*qx + qy*qy + qz*qz) + (qy*Ax - 2*qx*Ay + qr*Az)*(-qx * qr) + (qx*Ax + qz*Az)*(-qy * qr) + (qy*Az - 2*qz*Ay - qr*Ax)*(-qz * qr) );
	out_jacobian_df_dpose[1][4] = n * ( (qx*Az - qz*Ax)*(-qr * qx) + (qy*Ax - 2*qx*Ay + qr*Az)*(qr*qr + qy*qy + qz*qz) + (qx*Ax + qz*Az)*(-qy * qx) + (qy*Az - 2*qz*Ay - qr*Ax)*(-qz * qx) );
	out_jacobian_df_dpose[1][5] = n * ( (qx*Az - qz*Ax)*(-qr * qy) + (qy*Ax - 2*qx*Ay + qr*Az)*(-qx * qy) + (qx*Ax + qz*Az)*(qr*qr + qx*qx + qz*qz) + (qy*Az - 2*qz*Ay - qr*Ax)*(-qz * qy) );
	out_jacobian_df_dpose[1][6] = n * ( (qx*Az - qz*Ax)*(-qr * qz) + (qy*Ax - 2*qx*Ay + qr*Az)*(-qx * qz) + (qx*Ax + qz*Az)*(-qy * qz) + (qy*Az - 2*qz*Ay - qr*Ax)*(qr*qr + qx*qx + qy*qy) );
			
	out_jacobian_df_dpose[2][0] = -2*qr*qy - 2*qx*qz;
	out_jacobian_df_dpose[2][1] = 2*qr*qx - 2*qy*qz;
	out_jacobian_df_dpose[2][2] = 2*qx2 + 2*qy2 - 1;
	out_jacobian_df_dpose[2][3] = n * ( (qy*Ax - qx*Ay)*(qx*qx + qy*qy + qz*qz) + (qz*Ax - qr*Ay - 2*qx*Az)*(-qx * qr) + (qr*Ax + qz*Ay - 2*qy*Az)*(-qy * qr) + (qx*Ax + qy*Ay)*(-qz * qr) );
	out_jacobian_df_dpose[2][4] = n * ( (qy*Ax - qx*Ay)*(-qr * qx) + (qz*Ax - qr*Ay - 2*qx*Az)*(qr*qr + qy*qy + qz*qz) + (qr*Ax + qz*Ay - 2*qy*Az)*(-qy * qx) + (qx*Ax + qy*Ay)*(-qz * qx) );
	out_jacobian_df_dpose[2][5] = n * ( (qy*Ax - qx*Ay)*(-qr * qy) + (qz*Ax - qr*Ay - 2*qx*Az)*(-qx * qy) + (qr*Ax + qz*Ay - 2*qy*Az)*(qr*qr + qx*qx + qz*qz) + (qx*Ax + qy*Ay)*(-qz * qy) );
	out_jacobian_df_dpose[2][6] = n * ( (qy*Ax - qx*Ay)*(-qr * qz) + (qz*Ax - qr*Ay - 2*qx*Az)*(-qx * qz) + (qr*Ax + qz*Ay - 2*qy*Az)*(-qy * qz) + (qx*Ax + qy*Ay)*(qr*qr + qx*qx + qy*qy) );
	
	// Function itself:
	const kftype t2 = -qr*qx; const kftype t3 = -qr*qy; const kftype t4 = -qr*qz;
	const kftype t5 = -qx*qx; const kftype t6 =  qx*qy; const kftype t7 =  qx*qz;
	const kftype t8 = -qy*qy; const kftype t9 =  qy*qz; const kftype t10= -qz*qz;
	*lx = 2 * ( (t8+t10)*(gx-m_coord_x) + (t6-t4)*(gy-m_coord_y)  + (t3+t7)*(gz-m_coord_z) ) + (gx-m_coord_x);
	*ly = 2 * ( (t4+t6)*(gx-m_coord_x)  + (t5+t10)*(gy-m_coord_y) + (t9-t2)*(gz-m_coord_z) ) + (gy-m_coord_y);
	*lz = 2 * ( (t7-t3)*(gx-m_coord_x)  + (t2+t9)*(gy-m_coord_y)  + (t5+t8)*(gz-m_coord_z) ) + (gz-m_coord_z);
}

