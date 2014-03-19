/*---------------------------------------------------------------
                    jacobiansPoseComposition
----------------------------------------------------------------*/

/*---------------------------------------------------------------
                         USAGE:
 CPose3DQuatPDFGaussian::jacobiansPoseComposition(
							robotPose,
							sensorPoseOnRobot,
							H_senpose_vehpose,
							H_senpose_senrelpose,
							&sensorPoseAbs);
----------------------------------------------------------------*/

#include <math.h>
#include "Jacobians.h"


float inverseSqrt(float x)
{
   float xhalf = 0.5f * x;
   int i = *(int*)&x;			// store floating-point bits in integer
   i = 0x5f3759d5 - (i >> 1);	// initial guess for Newton's method
   x = *(float*)&i;				// convert new bits into float
   x = x * (1.5f - xhalf*x*x);	// One round of Newton's method
   return x;
}

void jacobiansPoseComposition(
		const CPose3DQuat X,
		const CPose3DQuat U,
		kftype df_dx[7][4],
		CPose3DQuat out_X_oplus_U[1]
	)
{
	// Note: First 3 columns of df_dx (e.g. [][0], [][1], and [][2])
	//       are const vals, so only 7x4 is needed instead of 7x7

	//const kftype qx2 = X.qx * X.qx;
	//const kftype qy2 = X.qy * X.qy;
	//const kftype qz2 = X.qz * X.qz;
	
	
	CPose3DQuat  X_plus_U = {X.x+U.x, X.y+U.y, X.z+U.z, X.qr+U.qr, X.qx+U.qx, X.qy+U.qy, X.qz+U.qz};
	kftype norm_jacob[4][4];
	kftype X_plus_U_normSqr = X_plus_U.qr*X_plus_U.qr + X_plus_U.qx*X_plus_U.qx + X_plus_U.qy*X_plus_U.qy + X_plus_U.qz*X_plus_U.qz;
	const kftype X_plus_U_n = inverseSqrt(X_plus_U_normSqr * X_plus_U_normSqr * X_plus_U_normSqr);
	norm_jacob[0][0] = X_plus_U_n * (X_plus_U.qx*X_plus_U.qx + X_plus_U.qy*X_plus_U.qy + X_plus_U.qz*X_plus_U.qz);
	norm_jacob[0][1] = X_plus_U_n * (-X_plus_U.qr * X_plus_U.qx);
	norm_jacob[0][2] = X_plus_U_n * (-X_plus_U.qr * X_plus_U.qy);
	norm_jacob[0][3] = X_plus_U_n * (-X_plus_U.qr * X_plus_U.qz);
	
	norm_jacob[1][0] = X_plus_U_n * (-X_plus_U.qx * X_plus_U.qr);
	norm_jacob[1][1] = X_plus_U_n * (X_plus_U.qr*X_plus_U.qr + X_plus_U.qy*X_plus_U.qy + X_plus_U.qz*X_plus_U.qz);
	norm_jacob[1][2] = X_plus_U_n * (-X_plus_U.qx * X_plus_U.qy);
	norm_jacob[1][3] = X_plus_U_n * (-X_plus_U.qx * X_plus_U.qz);

	norm_jacob[2][0] = X_plus_U_n * (-X_plus_U.qy * X_plus_U.qr);
	norm_jacob[2][1] = X_plus_U_n * (-X_plus_U.qy * X_plus_U.qx);
	norm_jacob[2][2] = X_plus_U_n * (X_plus_U.qr*X_plus_U.qr + X_plus_U.qx*X_plus_U.qx + X_plus_U.qz*X_plus_U.qz);
	norm_jacob[2][3] = X_plus_U_n * (-X_plus_U.qy * X_plus_U.qz);

	norm_jacob[3][0] = X_plus_U_n * (-X_plus_U.qz * X_plus_U.qr);
	norm_jacob[3][1] = X_plus_U_n * (-X_plus_U.qz * X_plus_U.qx);
	norm_jacob[3][2] = X_plus_U_n * (-X_plus_U.qz * X_plus_U.qy);
	norm_jacob[3][3] = X_plus_U_n * (X_plus_U.qr*X_plus_U.qr + X_plus_U.qx*X_plus_U.qx + X_plus_U.qy*X_plus_U.qy);
	
	
	kftype norm_jacob_X[4][4];
	kftype X_normSqr = X.qr*X.qr + X.qx*X.qx + X.qy*X.qy + X.qz*X.qz;
	const kftype X_n = inverseSqrt(X_normSqr * X_normSqr * X_normSqr);
	norm_jacob_X[0][0] = X_n * (X.qx*X.qx + X.qy*X.qy + X.qz*X.qz);
	norm_jacob_X[0][1] = X_n * (-X.qr * X.qx);
	norm_jacob_X[0][2] = X_n * (-X.qr * X.qy);
	norm_jacob_X[0][3] = X_n * (-X.qr * X.qz);
	
	norm_jacob_X[1][0] = X_n * (-X.qx * X.qr);
	norm_jacob_X[1][1] = X_n * (X.qr*X.qr + X.qy*X.qy + X.qz*X.qz);
	norm_jacob_X[1][2] = X_n * (-X.qx * X.qy);
	norm_jacob_X[1][3] = X_n * (-X.qx * X.qz);

	norm_jacob_X[2][0] = X_n * (-X.qy * X.qr);
	norm_jacob_X[2][1] = X_n * (-X.qy * X.qx);
	norm_jacob_X[2][2] = X_n * (X.qr*X.qr + X.qx*X.qx + X.qz*X.qz);
	norm_jacob_X[2][3] = X_n * (-X.qy * X.qz);

	norm_jacob_X[3][0] = X_n * (-X.qz * X.qr);
	norm_jacob_X[3][1] = X_n * (-X.qz * X.qx);
	norm_jacob_X[3][2] = X_n * (-X.qz * X.qy);
	norm_jacob_X[3][3] = X_n * (X.qr*X.qr + X.qx*X.qx + X.qy*X.qy);
	
		
	// df_dx ===================================================
	
	const kftype valsX[3][4] = {
		{	2 * (-X.qz*U.y + X.qy*U.z ),
			2 * ( X.qy*U.y + X.qz*U.z ),
			2 * (-2*X.qy*U.x + X.qx*U.y + X.qr*U.z ),
			2 * (-2*X.qz*U.x - X.qr*U.y + X.qx*U.z )	},

		{	2 * ( X.qz*U.x - X.qx*U.z ),
			2 * ( X.qy*U.x - 2*X.qx*U.y - X.qr*U.z ),
			2 * ( X.qx*U.x + X.qz*U.z ),
			2 * ( X.qr*U.x - 2*X.qz*U.y + X.qy*U.z )	},

		{	2 * (-X.qy*U.x + X.qx*U.y ),
			2 * ( X.qz*U.x + X.qr*U.y - 2*X.qx*U.z ),
			2 * (-X.qr*U.x + X.qz*U.y - 2*X.qy*U.z ),
			2 * ( X.qx*U.x + X.qy*U.y )					}
	};
	
	const kftype aux44_dataX[4][4] = {
		{U.qr,-U.qx,-U.qy,-U.qz},
		{U.qx, U.qr, U.qz,-U.qy},
		{U.qy,-U.qz, U.qr, U.qx},
		{U.qz, U.qy,-U.qx, U.qr}
	};
	
	//df_dx[0][0] = 1;
	//df_dx[0][1] = 0;
	//df_dx[0][2] = 0;
	df_dx[0][0/*3*/] = valsX[0][0]*norm_jacob_X[0][0] + valsX[0][1]*norm_jacob_X[1][0] + valsX[0][2]*norm_jacob_X[2][0] + valsX[0][3]*norm_jacob_X[3][0];
	df_dx[0][1/*4*/] = valsX[0][0]*norm_jacob_X[0][1] + valsX[0][1]*norm_jacob_X[1][1] + valsX[0][2]*norm_jacob_X[2][1] + valsX[0][3]*norm_jacob_X[3][1];
	df_dx[0][2/*5*/] = valsX[0][0]*norm_jacob_X[0][2] + valsX[0][1]*norm_jacob_X[1][2] + valsX[0][2]*norm_jacob_X[2][2] + valsX[0][3]*norm_jacob_X[3][2];
	df_dx[0][3/*6*/] = valsX[0][0]*norm_jacob_X[0][3] + valsX[0][1]*norm_jacob_X[1][3] + valsX[0][2]*norm_jacob_X[2][3] + valsX[0][3]*norm_jacob_X[3][3];
	
	//df_dx[1][0] = 0;
	//df_dx[1][1] = 1;
	//df_dx[1][2] = 0;
	df_dx[1][0/*3*/] = valsX[1][0]*norm_jacob_X[0][0] + valsX[1][1]*norm_jacob_X[1][0] + valsX[1][2]*norm_jacob_X[2][0] + valsX[1][3]*norm_jacob_X[3][0];
	df_dx[1][1/*4*/] = valsX[1][0]*norm_jacob_X[0][1] + valsX[1][1]*norm_jacob_X[1][1] + valsX[1][2]*norm_jacob_X[2][1] + valsX[1][3]*norm_jacob_X[3][1];
	df_dx[1][2/*5*/] = valsX[1][0]*norm_jacob_X[0][2] + valsX[1][1]*norm_jacob_X[1][2] + valsX[1][2]*norm_jacob_X[2][2] + valsX[1][3]*norm_jacob_X[3][2];
	df_dx[1][3/*6*/] = valsX[1][0]*norm_jacob_X[0][3] + valsX[1][1]*norm_jacob_X[1][3] + valsX[1][2]*norm_jacob_X[2][3] + valsX[1][3]*norm_jacob_X[3][3];
	
	//df_dx[2][0] = 0;
	//df_dx[2][1] = 0;
	//df_dx[2][2] = 1;
	df_dx[2][0/*3*/] = valsX[2][0]*norm_jacob_X[0][0] + valsX[2][1]*norm_jacob_X[1][0] + valsX[2][2]*norm_jacob_X[2][0] + valsX[2][3]*norm_jacob_X[3][0];
	df_dx[2][1/*4*/] = valsX[2][0]*norm_jacob_X[0][1] + valsX[2][1]*norm_jacob_X[1][1] + valsX[2][2]*norm_jacob_X[2][1] + valsX[2][3]*norm_jacob_X[3][1];
	df_dx[2][2/*5*/] = valsX[2][0]*norm_jacob_X[0][2] + valsX[2][1]*norm_jacob_X[1][2] + valsX[2][2]*norm_jacob_X[2][2] + valsX[2][3]*norm_jacob_X[3][2];
	df_dx[2][3/*6*/] = valsX[2][0]*norm_jacob_X[0][3] + valsX[2][1]*norm_jacob_X[1][3] + valsX[2][2]*norm_jacob_X[2][3] + valsX[2][3]*norm_jacob_X[3][3];
	
	//df_dx[3][0] = 0;
	//df_dx[3][1] = 0;
	//df_dx[3][2] = 0;
	df_dx[3][0/*3*/] = norm_jacob[0][0]*aux44_dataX[0][0] + norm_jacob[0][1]*aux44_dataX[1][0] + norm_jacob[0][2]*aux44_dataX[2][0] + norm_jacob[0][3]*aux44_dataX[3][0];
	df_dx[3][1/*4*/] = norm_jacob[0][0]*aux44_dataX[0][1] + norm_jacob[0][1]*aux44_dataX[1][1] + norm_jacob[0][2]*aux44_dataX[2][1] + norm_jacob[0][3]*aux44_dataX[3][1];
	df_dx[3][2/*5*/] = norm_jacob[0][0]*aux44_dataX[0][2] + norm_jacob[0][1]*aux44_dataX[1][2] + norm_jacob[0][2]*aux44_dataX[2][2] + norm_jacob[0][3]*aux44_dataX[3][2];
	df_dx[3][3/*6*/] = norm_jacob[0][0]*aux44_dataX[0][3] + norm_jacob[0][1]*aux44_dataX[1][3] + norm_jacob[0][2]*aux44_dataX[2][3] + norm_jacob[0][3]*aux44_dataX[3][3];
	
	//df_dx[4][0] = 0;
	//df_dx[4][1] = 0;
	//df_dx[4][2] = 0;
	df_dx[4][0/*3*/] = norm_jacob[1][0]*aux44_dataX[0][0] + norm_jacob[1][1]*aux44_dataX[1][0] + norm_jacob[1][2]*aux44_dataX[2][0] + norm_jacob[1][3]*aux44_dataX[3][0];
	df_dx[4][1/*4*/] = norm_jacob[1][0]*aux44_dataX[0][1] + norm_jacob[1][1]*aux44_dataX[1][1] + norm_jacob[1][2]*aux44_dataX[2][1] + norm_jacob[1][3]*aux44_dataX[3][1];
	df_dx[4][2/*5*/] = norm_jacob[1][0]*aux44_dataX[0][2] + norm_jacob[1][1]*aux44_dataX[1][2] + norm_jacob[1][2]*aux44_dataX[2][2] + norm_jacob[1][3]*aux44_dataX[3][2];
	df_dx[4][3/*6*/] = norm_jacob[1][0]*aux44_dataX[0][3] + norm_jacob[1][1]*aux44_dataX[1][3] + norm_jacob[1][2]*aux44_dataX[2][3] + norm_jacob[1][3]*aux44_dataX[3][3];
	
	//df_dx[5][0] = 0;
	//df_dx[5][1] = 0;
	//df_dx[5][2] = 0;
	df_dx[5][0/*3*/] = norm_jacob[2][0]*aux44_dataX[0][0] + norm_jacob[2][1]*aux44_dataX[1][0] + norm_jacob[2][2]*aux44_dataX[2][0] + norm_jacob[2][3]*aux44_dataX[3][0];
	df_dx[5][1/*4*/] = norm_jacob[2][0]*aux44_dataX[0][1] + norm_jacob[2][1]*aux44_dataX[1][1] + norm_jacob[2][2]*aux44_dataX[2][1] + norm_jacob[2][3]*aux44_dataX[3][1];
	df_dx[5][2/*5*/] = norm_jacob[2][0]*aux44_dataX[0][2] + norm_jacob[2][1]*aux44_dataX[1][2] + norm_jacob[2][2]*aux44_dataX[2][2] + norm_jacob[2][3]*aux44_dataX[3][2];
	df_dx[5][3/*6*/] = norm_jacob[2][0]*aux44_dataX[0][3] + norm_jacob[2][1]*aux44_dataX[1][3] + norm_jacob[2][2]*aux44_dataX[2][3] + norm_jacob[2][3]*aux44_dataX[3][3];
	
	//df_dx[6][0] = 0;
	//df_dx[6][1] = 0;
	//df_dx[6][2] = 0;
	df_dx[6][0/*3*/] = norm_jacob[3][0]*aux44_dataX[0][0] + norm_jacob[3][1]*aux44_dataX[1][0] + norm_jacob[3][2]*aux44_dataX[2][0] + norm_jacob[3][3]*aux44_dataX[3][0];
	df_dx[6][1/*4*/] = norm_jacob[3][0]*aux44_dataX[0][1] + norm_jacob[3][1]*aux44_dataX[1][1] + norm_jacob[3][2]*aux44_dataX[2][1] + norm_jacob[3][3]*aux44_dataX[3][1];
	df_dx[6][2/*5*/] = norm_jacob[3][0]*aux44_dataX[0][2] + norm_jacob[3][1]*aux44_dataX[1][2] + norm_jacob[3][2]*aux44_dataX[2][2] + norm_jacob[3][3]*aux44_dataX[3][2];
	df_dx[6][3/*6*/] = norm_jacob[3][0]*aux44_dataX[0][3] + norm_jacob[3][1]*aux44_dataX[1][3] + norm_jacob[3][2]*aux44_dataX[2][3] + norm_jacob[3][3]*aux44_dataX[3][3];
	
	
	out_X_oplus_U->x  = X_plus_U.x;
	out_X_oplus_U->y  = X_plus_U.y;
	out_X_oplus_U->z  = X_plus_U.z;
	out_X_oplus_U->qr = X_plus_U.qr;
	out_X_oplus_U->qx = X_plus_U.qx;
	out_X_oplus_U->qy = X_plus_U.qy;
	out_X_oplus_U->qz = X_plus_U.qz;

}

