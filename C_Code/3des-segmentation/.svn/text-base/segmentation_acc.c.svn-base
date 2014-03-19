#include "segmentation_acc.h"
#include <math.h>


void fetch(int step, volatile float* bus, float array[m][p])
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < p; j++)
	//#pragma AP PIPELINE II = 1
			array[i][j] = bus[step*m*p + i*m + j];
}

void write(int step, volatile float* bus, float array[m][p])
{
	int i, j;
	for (i = 0; i < m; i++)
		for (j = 0; j < p; j++)
	//	#pragma AP PIPELINE II = 1
			bus[step*m*p + i*m + j] = array[i][j];
}

void compute(float array0[m][p], float array1[m][p], float array2[m][p], float u0[m][p], float res[m][p], float n1, float n2)
{
	float mu = 0.18 * 255 * 255;
    //float nu = 0.0;
    float lambda1 = 1.0;
    float lambda2 = 1.0;

    float dx = 1.0;
    float dy = 1.0;
    float dz = 1.0;

    float dx2 = 2.0;
    float dy2 = 2.0;
    float dz2 = 2.0;

	float c1 = n1, c2 = n2;

	int j, k;

    for(j=1; j < m-1; j++)
    {
        for(k=1; k < p-1; k++)
        {
//	#pragma AP PIPELINE II = 1
            float Dx_p = (array1[j+1][k] - array1[j][k])/dx;
            float Dx_m = (array1[j][k] - array1[j-1][k])/dx;
            float Dy_p = (array2[j][k] - array1[j][k])/dy;
            float Dy_m = (array1[j][k] - array0[j][k])/dy;
            float Dz_p = (array1[j][k+1] - array1[j][k])/dz;
            float Dz_m = (array1[j][k] - array1[j][k-1])/dz;

            float Dx_0 = (array1[j+1][k] - array1[j-1][k])/dx2;
            float Dy_0 = (array2[j][k] - array0[j][k])/dy2;
            float Dz_0 = (array1[j][k+1] - array1[j][k-1])/dz2;

            float Dxx = (Dx_p - Dx_m) / dx;
            float Dyy = (Dy_p - Dy_m) / dy;
            float Dzz = (Dz_p - Dz_m) / dz;

            float Dxy = ( array2[j+1][k] - array0[j+1][k] - array2[j-1][k] + array0[j-1][k] ) / (4*dx*dy);
            float Dxz = ( array1[j+1][k+1] - array1[j+1][k-1] - array1[j-1][k+1] + array1[j-1][k-1] ) / (4*dx*dz);
            float Dyz = ( array2[j][k+1] - array2[j][k-1] - array0[j][k+1] + array0[j][k-1] ) / (4*dy*dz);

            float K  = (  Dx_0*Dx_0*Dyy - 2.0f*Dx_0*Dy_0*Dxy + Dy_0*Dy_0*Dxx
                    + Dx_0*Dx_0*Dzz - 2.0f*Dx_0*Dz_0*Dxz + Dz_0*Dz_0*Dxx
                    + Dy_0*Dy_0*Dzz - 2.0f*Dy_0*Dz_0*Dyz + Dz_0*Dz_0*Dyy )
                   /* / ( pow(Dx_0*Dx_0 + Dy_0*Dy_0 + Dz_0*Dz_0, 1.5) + 10e-10);*/
                    / (sqrtf((Dx_0*Dx_0 + Dy_0*Dy_0 + Dz_0*Dz_0)*(Dx_0*Dx_0 + Dy_0*Dy_0 + Dz_0*Dz_0)*(Dx_0*Dx_0 + Dy_0*Dy_0 + Dz_0*Dz_0))
					+ 10e-10);

            float Grad = sqrtf(Dx_0*Dx_0 + Dy_0*Dy_0 + Dz_0*Dz_0);

            res[j][k] = Grad * ( mu * K + lambda1*(u0[j][k]-c1)*(u0[j][k]-c1)
                        - lambda2*(u0[j][k]-c2)*(u0[j][k]-c2) );
        }
    }

}

void segmentation_acc(volatile float* A_bus, volatile float* B_bus, volatile float* C_bus, int c[2]) //( float phi[M][N][P], const float u0[M][N][P] )
{
//#pragma AP INTERFACE ap_ctrl_hs port = return
//#pragma AP INTERFACE ap_bus port = A_bus
//#pragma AP INTERFACE ap_bus port = B_bus
//#pragma AP INTERFACE ap_bus port = C_bus

	float phi0[m][p], phi1[m][p], phi2[m][p], phi3[m][p], u0[m][p], u1[m][p];
	float curvature_motion_part0[m][p];
	float curvature_motion_part1[m][p];
	//int flag;
	int i;

    float c1; 	//negative num/den 
    float c2;	//positive num/den

	c1 = c[0];
	c2 = c[1];

	fetch(0, A_bus, phi0);
	fetch(1, A_bus, phi1);
	fetch(2, A_bus, phi2);
	fetch(1, B_bus, u0);
	compute(phi0, phi1, phi2, u0, curvature_motion_part1, c1, c2);

	fetch(3, A_bus, phi3);
	fetch(2, B_bus, u1);

    for(i=2; i < n-2; i++)
    {
		//fetch(i-1, A_bus, phi_before);
		//fetch(i, A_bus, phi);
	//#pragma AP PIPELINE II = 1
		if (i%4 == 0)
		{
            fetch(i+2, A_bus, phi2);
            fetch(i+1, B_bus, u0);
            compute(phi3, phi0, phi1, u1, curvature_motion_part0, c1, c2);
            write(i, C_bus, curvature_motion_part1);
        }
		else if (i%4 == 1)
		{
			fetch(i+2, A_bus, phi3);
			fetch(i+1, B_bus, u1);
			compute(phi0, phi1, phi2, u0, curvature_motion_part1, c1, c2);
			write(i, C_bus, curvature_motion_part0);
		}
		else if (i%4 == 2)
		{
			fetch(i+2, A_bus, phi0);
            fetch(i+1, B_bus, u0);
            compute(phi1, phi2, phi3, u1, curvature_motion_part0, c1, c2);
            write(i, C_bus, curvature_motion_part1);
		}
		else
        {
            fetch(i+2, A_bus, phi1);
            fetch(i+1, B_bus, u1);
            compute(phi2, phi3, phi0, u0, curvature_motion_part1, c1, c2);
            write(i, C_bus, curvature_motion_part0);
        }
	}

	compute(phi2, phi3, phi0, u0, curvature_motion_part1, c1, c2);
	write(58, C_bus, curvature_motion_part0);
	write(59, C_bus, curvature_motion_part1);
}

