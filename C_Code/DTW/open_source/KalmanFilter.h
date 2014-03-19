/*
 * KalmanFilter.h
 *
 * Created: 21/12/2011 16:42:42
 *  Author: Lo�c Kaemmerlen
 */ 


#ifndef KALMANFILTER_H_
#define KALMANFILTER_H_


#include "mathstools.h"


//////////////////// ACCELEROMETER+COMPASS PART //////////

// Converts given acceleration raw data in g
void accel_g (vectorMe *a);
// Computes angles from scaled and shifted acceleration data
vectorMe accel_angle (vectorMe a);
// Whole function to get angles from accelerometer
vectorMe accel_angle_acquisition(void);
// Whole function to get angles from accelerometer + compass
vectorMe accelcompass_angle_acquisition(vectorMe a, vectorMe m);
// Calculate the accelerometer measurement noise
vectorMe accel_measurement_noise (void);


//////////////////// GYROSCOPE PART //////////////////////

// Converts given gyroscope raw data in degrees per second
void gyro_dps(vectorMe *g);
// Computes the angle moved using the time between 2 measurements, in degrees
vectorMe gyro_angle (vectorMe g);
// Calculate the gyroscope processing noise
vectorMe gyro_measurement_noise (void);




//////////////////// KALMAN PART //////////////////////

void KalmanFilter (Matrix* xk, Matrix xnew, Matrix uk, Matrix* Pk, Matrix R, Matrix Q, Matrix* S, Matrix* K, Matrix I);



#endif /* KALMANFILTER_H_ */
