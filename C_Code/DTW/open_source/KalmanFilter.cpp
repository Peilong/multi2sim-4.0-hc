/*
 * KalmanFilter.cpp
 *
 * Created: 21/12/2011 16:43:10
 *  Author: Lo�c Kaemmerlen
 */ 

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "KalmanFilter.h"
#include "sensors.h"	
#include "mathstools.h"	

//////////////////// ACCELEROMETER PART //////////////////////

// Converts given acceleration raw data in g
void accel_g (vectorMe *a)
{
	int res = 2;  //the resolution defined for the accelerometer, +-'RES' g
	
	// Calculates the acceleration
	a->x = ((a->x )/32767)*res;
	a->y = ((a->y )/32767)*res;
	a->z = ((a->z )/32767)*res;
	
}


// Computes angles from scaled and shifted acceleration data
vectorMe accel_angle (vectorMe a)
{
	vectorMe angles = {0,0,0};
	
	// Calculates Force Vector value:
	double R = sqrt((a.x*a.x) + (a.y*a.y) + (a.z*a.z));
	
	// Computes inclinations based on the accelerometer values, in degrees
	if (a.z<0)
	{
		angles.x = -acos(a.x / R)*57.29;
		angles.y = -acos(a.y / R)*57.29;
	}
	else
	{
		angles.x = acos(a.x / R)*57.29;
		angles.y = acos(a.y / R)*57.29;		
	}

	angles.z = acos(a.z / R)*57.29;
	
	// Shifts the angles so as to be 0 on horizontal position
	angles.x -= 90;
	if (angles.x <-180)
		{angles.x +=360;}
	angles.y -= 90;
	if (angles.y <-180)
		{angles.y +=360;}
	
	return angles ;
}


// Whole function to get angles from accelerometer
vectorMe accel_angle_acquisition(void)
{
	vectorMe a;
	vectorMe angles;
		
	//compass_read_data(&a, &m);
	accel_g(&a);	
	
	angles = accel_angle(a);

	// Ensures that Z gets negative if pointing downward
	if (angles.x<0)
	{
		angles.z = - angles.z;
	}
	
	return angles;
}

// Whole function to get angles from accelerometer + compass
vectorMe accelcompass_angle_acquisition(vectorMe a, vectorMe m)
{
	// Vector p should be defined as pointing forward, parallel to the ground, with coordinates {X, Y, Z}.
	vectorMe p = {0, -1, 0};
	vectorMe angles;
	float heading;
		
	//compass_read_data(&a, &m);
	heading = get_heading(&a, &m, &p);
	accel_g(&a);	
	
	angles = accel_angle(a);
	
	angles.z= heading;
	
	return angles;
}


// Calculate the accelerometer measurement noise
vectorMe accel_measurement_noise (void)
{
	// Calculated variance: {0.02;0.02;0.02}
	vectorMe a;
	vectorMe store[30];
	vectorMe variance= {0,0,0};
	
	vectorMe sum ={0,0,0};
	vectorMe sum2 ={0,0,0};
	
	// Data acquisition and storage
	for (int i =0; i<20; i++)
	{
		//compass_read_data(&a, &m);
		accel_g(&a);	
		store[i] = accel_angle(a);	
	}

	// Calculate variance //  formula: variance = (sum2 - (sum^2/ number of samples))/(number of samples -1)
	// Calculate the sum of values
	for (int k=0; k<20; k++)
	{
		sum.x = sum.x+store[k].x;
		sum.y = sum.y+store[k].y;
		sum.z = sum.z+store[k].z;
	}
	
	// Calculate the sum of values^2
	for (int k=0; k<20; k++)
	{
		sum2.x = sum2.x+(store[k].x)*(store[k].x);
		sum2.y = sum2.y+(store[k].y)*(store[k].y);
		sum2.z = sum2.z+(store[k].z)*(store[k].z);
	}
			  	
	// Calculate the variance
	variance.x += (sum2.x - ((sum.x)*(sum.x))/20)/19;
	variance.y += (sum2.y - ((sum.y)*(sum.y))/20)/19;
	variance.z += (sum2.z - ((sum.z)*(sum.z))/20)/19;			
	
	return variance;
	
}



//////////////////// GYROSCOPE PART //////////////////////


// Converts given gyroscope raw data in degrees per second
void gyro_dps(vectorMe *g)
{
	int res = 500;		// The resolution defined for the gyroscope
	
	g->x = (g->x/65535)*res;
	g->y = (g->y/65535)*res;
	g->z = (g->z/65535)*res;
	
}


// Computes the angle moved using the time between 2 measurements, in degrees
vectorMe gyro_angle (vectorMe g)
{
	// Time between 2 measurements in seconds
	double dtTimer   = 0.001;
	
	vectorMe angle = {0,0,0};
	angle.x = g.x * dtTimer;
	angle.y = g.y * dtTimer;
	angle.z = g.z * dtTimer;
	
	return angle;
}	

// Calculate the gyroscope processing noise
vectorMe gyro_measurement_noise (void)
{
	// Calculated variance: {0.0000;0.0000;0.0000}
	// This was to be expected since the Gyro is really accurate on short time periods
	vectorMe store[30];
	vectorMe variance= {0,0,0};
	
	vectorMe sum ={0,0,0};
	vectorMe sum2 ={0,0,0};
	
	// Data acquisition and storage
	for (int i =0; i<20; i++)
	{
		vectorMe g;
		gyro_dps(&g);	
		store[i] = gyro_angle(g);
	}

	// Calculate variance //  formula: variance = (sum2 - (sum^2/ number of samples))/(number of samples -1)
	// Calculate the sum of values
	for (int k=0; k<20; k++)
	{
		sum.x = sum.x+store[k].x;
		sum.y = sum.y+store[k].y;
		sum.z = sum.z+store[k].z;
	}
	
	// Calculate the sum of values^2
	for (int k=0; k<20; k++)
	{
		sum2.x = sum2.x+(store[k].x)*(store[k].x);
		sum2.y = sum2.y+(store[k].y)*(store[k].y);
		sum2.z = sum2.z+(store[k].z)*(store[k].z);
	}
			  	
	// Calculate the variance
	variance.x += (sum2.x - ((sum.x)*(sum.x))/20)/19;
	variance.y += (sum2.y - ((sum.y)*(sum.y))/20)/19;
	variance.z += (sum2.z - ((sum.z)*(sum.z))/20)/19;			
	
	return variance;
	
}


//////////////////// KALMAN PART //////////////////////


void KalmanFilter (Matrix* xk, Matrix xnew, Matrix uk, Matrix* Pk, Matrix R, Matrix Q, Matrix* S, Matrix* K, Matrix I)
{
	
	// Steps and variables names are based on the wikipedia page
	// http://en.wikipedia.org/wiki/Kalman_filter
	
	
////////  Variables declaration
Matrix yk  (3,3); // Observation
	
	
////////  PREDICTION
	// Predicted (a priori) state estimate: 
	*xk = *xk + uk;
	
	// Predicted (a priori) estimate covariance
	*Pk = *Pk + Q;
		
////////  UPDATE
	// Innovation or measurement residual
	yk = xnew - *xk;
	// The following is just to hinder a bit the singularity happening when one of the angles goes from -180 to +180�
	if(yk.mat[0][0]>320){yk.mat[0][0] = yk.mat[0][0]-360; }
	if(yk.mat[0][0]<320){yk.mat[0][0] = yk.mat[0][0]+360; }
		
	if(yk.mat[1][1]>320){yk.mat[1][1] = yk.mat[1][1]-360; }
	if(yk.mat[1][1]<320){yk.mat[1][1] = yk.mat[1][1]+360; }
		
	if(yk.mat[2][2]>320){yk.mat[2][2] = yk.mat[2][2]-360; }
	if(yk.mat[2][2]<320){yk.mat[2][2] = yk.mat[2][2]+360; }
	// Innovation covariance
	*S = *Pk + R ;
	// Optimal Kalman Gain
	*K = *Pk * ( S->invert_3x3() );
	// Updated state estimate
	*xk = *xk + (*K * yk);
	// Updated estimate covariance
	*Pk = ( I - *K) * (*Pk);

	
}
