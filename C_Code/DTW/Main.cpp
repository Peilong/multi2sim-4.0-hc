//============================================================================
// Author      : Thomas Calloway
// Version     : 0.1
// Copyright   : UMass Lowell 2012
// Description : Combines Calibration, Kalman Filtering, Gesture recognition
//				 of 3 axis accelerometer, gyroscope, and magnetometer data for
//				 benchmarking purposes only
//============================================================================

#include <stdlib.h>
#include <iostream>
#include <inttypes.h>
#include <pthread.h>
#include <math.h>
#include <string.h>

#include "LoadFile.h"
#include "open_source/sensors.h"		// Include the Compass Library
#include "open_source/KalmanFilter.h"	// Include the Filter Library
#include "open_source/mathstools.h"		// Include the Vectors and Matrix Library

//extern "C"
//{
	#include "uWave.h"
//}

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//  !! Modify configuration settings below to change program behavior !!
//
//  [START OF CONFIGURATION SETTINGS]
//////////////////////////////////////////////////////////////////////////////
//#define VERBOSE
#define CAL_BENCHMARK
//#define KF_BENCHMARK
#define GESTURE_BENCHMARK
#define CONSUMER

const int RECORD_COUNT = 600; 		// Number of records to process from the input
const int DELTA_T = 5E1;		// Inter-sample delay in microseconds, 5E3 by default

const int CPU_CONSUMER = 1;
const int CPU_CAL_KF = 1;
const int CPU_GESTURE = 1;
///////////////////////////////////////////////////////////////////////////////
//  [END OF CONFIGURATION SETTINGS]
//
///////////////////////////////////////////////////////////////////////////////

// Global flags
bool completeCalKF = false;
bool completeGesture = false;
bool consumerReady = false;

bool readyCal = false;
bool readyKF = false;
bool readyGesture = false;

pthread_mutex_t mutexCal = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexKF = PTHREAD_MUTEX_INITIALIZER;

// Calibration sensor output data
double gyro_out[3] = { 0, 0, 0 };
double accel_out[3] = { 0, 0, 0 };
double mag_out[3] = { 0, 0, 0 };
double temp_out = 0.0f;

// Kalman filter Euler output
vectorMe anglesOutput = {0,0,0};

// Gesture output data
int gestureResult = -1;

long recordCount = 0;

//============================================================================
// Description : Prints application configuration settings
//============================================================================
void printStartupMessages()
{
	cout << "Sensor Data Processing Benchmark" << endl;
	cout << "UMass Lowell: CANS Laboratory, 2012" << endl << endl;

	#ifdef CAL_BENCHMARK
		cout << "  Calibration: Enabled" << endl;
	#else
		cout << "  Calibration: Disabled" << endl;
	#endif

	#ifdef KF_BENCHMARK
		cout << "  Kalman Filter: Enabled" << endl;
	#else
		cout << "  Kalman Filter: Disabled" << endl;
	#endif

	#ifdef GESTURE_BENCHMARK
		cout << "  Gesture Recognition: Enabled" << endl;
		cout << "  Gesture Template Count: " << NUM_TEMPLATES << endl;
	#else
		cout << "  Gesture Recognition: Disabled" << endl;
	#endif

	cout << "  Record Count: " << RECORD_COUNT << endl;
	cout << "  Delta T: " << DELTA_T << " microseconds" << endl;
	cout << endl;
}

// Sensor input data
int gyro_data[3] =  { 0, 0, 0 };
int accel_data[3] =  { 0, 0, 0 };
int mag_data[3] =  { 0, 0, 0 };
int temp_data = 0;

// ===========================================================================
void applyCalibration()
{
	// Calibration parameters
	double gyro_bias_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double accel_bias_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double gyro_bias_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double accel_bias_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double gyro_bias_c[3] =  { 1E-5, 1E-5, 1E-5 };
	double accel_bias_c[3] =  { 1E-5, 1E-5, 1E-5 };
	double mag_bias_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double mag_bias_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double mag_bias_c[3] =  { 1E-5, 1E-5, 1E-5 };

	double gyro_sf_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double accel_sf_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double mag_sf_a[3] =  { 1E-5, 1E-5, 1E-5 };
	double gyro_sf_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double accel_sf_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double mag_sf_b[3] =  { 1E-5, 1E-5, 1E-5 };
	double gyro_sf_c[3] =  { 1, 1, 1 };
	double accel_sf_c[3] =  { 1, 1, 1 };
	double mag_sf_c[3] =  { 1, 1, 1 };

	double gyro_mx[3] =  { 1, 0, 0 };
	double gyro_my[3] =  { 0, 1, 0 };
	double gyro_mz[3] =  { 0, 0, 1 };
	double accel_mx[3] =  { 1, 0, 0 };
	double accel_my[3] =  { 0, 1, 0 };
	double accel_mz[3] =  { 0, 0, 1 };
	double mag_mx[3] =  { 1, 0, 0 };
	double mag_my[3] =  { 0, 1, 0 };
	double mag_mz[3] =  { 0, 0, 1 };

	temp_data = 1;

	// Biases
	for (int i = 0; i < 3; i++)
	{
		// Bias Compensated Output = input + biasA * t^2 + biasB * t + biasC
		gyro_data[i] = gyro_data[i] - (gyro_bias_a[i]*pow(temp_data,2) + gyro_bias_b[i]*temp_data + gyro_bias_c[i]);
		accel_data[i] = accel_data[i] - (accel_bias_a[i]*pow(temp_data,2) + accel_bias_b[i]*temp_data + accel_bias_c[i]);
		mag_data[i] = mag_data[i] - (mag_bias_a[i]*pow(temp_data,2) + mag_bias_b[i]*temp_data + mag_bias_c[i]);
	}

	// Scale Factors
	for (int i = 0; i < 3; i++)
	{
		// Scale Factor Compensated Output = input * sf * (1 + sfT1 * t^2 + sfT2 * t)
		gyro_data[i] = gyro_data[i] * gyro_sf_c[i] * (1 + gyro_sf_a[i]*pow(temp_data,2) + gyro_sf_b[i]*temp_data);
		accel_data[i] = accel_data[i] * accel_sf_c[i] * (1 + accel_sf_a[i]*pow(temp_data,2) + accel_sf_b[i]*temp_data);
		mag_data[i] = mag_data[i] * mag_sf_c[i] * (1 + mag_sf_a[i]*pow(temp_data,2) + mag_sf_b[i]*temp_data);
	}

	// Misalignments
	for (int i = 0; i < 3; i++)
	{
		gyro_data[i] = gyro_data[i] * gyro_mx[0] + gyro_data[i] * gyro_my[1] + gyro_data[i] * gyro_mz[2];
		accel_data[i] = accel_data[i] * accel_mx[0] + accel_data[i] * accel_my[1] + accel_data[i] * accel_mz[2];
		mag_data[i] = mag_data[i] * mag_mx[0] + mag_data[i] * mag_my[1] + mag_data[i] * mag_mz[2];
	}
}

////////////////////// Begin Kalman Filter Variables //////////////////

// Sensor input data
double gyro_data_kf[3] =  { 0, 0, 0 };
double accel_data_kf[3] =  { 0, 0, 0 };
double mag_data_kf[3] =  { 0, 0, 0 };
double temp_data_kf = 0;

// Acquisition variables
double GyroRate[3] = {0, 0, 0};
double Acc[3] = {0, 0, 0};
double Magn[3] = {0, 0, 0};
double Angles[3] = {0, 0, 0};

// Initial quaternion values
double qUpdate[4] = {0.5f, 0.5f, 0.5f, 0.5f};

// Observation vector
double qOsserv[4] = {0.5f, 0.5f, 0.5f, 0.5f};

vectorMe anglesGyroGlobal;

// Globally saved angle states
vectorMe anglesAccel = {0,0,0};
vectorMe anglesGyro  = {0,0,0};

//KALMAN MATRIX DECLARATIONS
// Steps and variables names are based on the wikipedia page
// http://en.wikipedia.org/wiki/Kalman_filter

Matrix xk (3,3);			// Predicted state k at k-1
Matrix xnew  (3,3);			// New measured state
Matrix uk  (3,3);			// rate k


Matrix I (3,3);				// Identity matrix
Matrix Pk(3,3);				// Covariance matrix
Matrix R (3,3);				// Measurement noise (linked to accelerometer)
Matrix Q (3,3);				// Processing noise (linked to gyroscope)

Matrix S (3,3);
Matrix K (3,3);				// Kalman Gain

// Pointers to matrices which need to be globally saved
Matrix*	xkptr = &xk;
Matrix* Pkptr = &Pk;
Matrix* Sptr = &S;
Matrix* Kptr = &K;

////////////////////// End Kalman Filter Variables //////////////////

// ===========================================================================
void filter(vectorMe accels, vectorMe gyros, vectorMe mags)
{
	// Get new sensor values
	anglesGyro = gyro_angle(gyros);
	anglesAccel = accelcompass_angle_acquisition(accels, mags);

	// Put those values in the right measurement/processing matrices
	xnew.mat[0][0] = anglesAccel.x; xnew.mat[1][1] = anglesAccel.y; xnew.mat[2][2] = anglesAccel.z;
	uk.mat[0][0] = anglesGyro.y;  uk.mat[1][1] = -anglesGyro.x;  uk.mat[2][2] = -anglesGyro.z;

	// Run the filter
	KalmanFilter( xkptr,  xnew,  uk,  Pkptr,  R, Q, Sptr,  Kptr,  I);

	// Shift results
	anglesOutput.x = xk(0,0);
	anglesOutput.y = xk(1,1);
	anglesOutput.z = xk(2,2);

	if(anglesOutput.x >180)
		{anglesOutput.x-=360;}
	if(anglesOutput.x <-180)
		{anglesOutput.x+=360;}
	if(anglesOutput.y >180)
		{anglesOutput.y-=360;}
	if(anglesOutput.y <-180)
		{anglesOutput.y+=360;}
	if(anglesOutput.z >180)
		{anglesOutput.z-=360;}
	if(anglesOutput.z <-180)
		{anglesOutput.z+=360;}

	#ifdef VERBOSE
			cout << "Euler Angles: " << anglesOutput.x << ", " << anglesOutput.y << ", " << anglesOutput.z << endl << endl;
	#endif
}

//============================================================================
// Description : Manages Calibration & KF functionality
//============================================================================
void *live_thread( void *ptr )
{
	#ifdef CONSUMER
		while (!consumerReady)
		{
			usleep(DELTA_T);  // Don't proceed until the consumer is ready
		}
	#endif

	// Process is starting
	completeCalKF = false;

	#ifdef CAL_BENCHMARK
		LoadFile rawDataFile;

		int data_rate = (1 / (DELTA_T / 1E9));

		// Open raw data file (once at the beginning)
		if (!rawDataFile.openFile("rawSignalInput.txt"))
		{
			cout << "Error reading raw data file." << endl;
			return(0);
		}
	#endif

	#ifdef KF_BENCHMARK
		LoadFile compDataFile;

		// Open compensated data file (once at the beginning)
		if (!compDataFile.openFile("compSignalInput.txt"))
		{
			cout << "Error reading KF input data file" << endl;
			return(0);
		}

		anglesGyroGlobal.x = 0;
		anglesGyroGlobal.y = 0;
		anglesGyroGlobal.z = 0;

		// Kalman filter matrix initializations
		Pk.mat[0][0]=1; Pk.mat[1][1]=1; Pk.mat[2][2]=1;
		I.mat[0][0]=1; I.mat[1][1]=1; I.mat[2][2]=1;					// Identity matrix

		///////////////// COVARIANCE NOISE MATRICES /////////////////
		R.mat[0][0]=0.5; R.mat[1][1]=0.5; R.mat[2][2]=0.01;				// Measurement noise (accelerometer)
		Q.mat[0][0]=0.005;  Q.mat[1][1]=0.005;	Q.mat[2][2]=0.0001;	// Processing noise (gyro)

		vectorMe accels, gyros, mags;
	#endif

	// Loop through data file until EOF
	while (recordCount < RECORD_COUNT)
	{
		#ifdef CAL_BENCHMARK
			if (rawDataFile.getRawRecord(gyro_data, accel_data, mag_data, &temp_data) != DATA_OK)
			{
				cout << "Reached raw data EOF prematurely." << endl;
				return NULL;
			}

			// Apply Calibration
			applyCalibration();

			pthread_mutex_lock(&mutexCal);
			// Convert to physical units
			for (int i = 0; i < 3; i++)
			{
				gyro_out[i] = gyro_data[i] * 0.00000625 * data_rate;
				accel_out[i] = accel_data[i] * 0.0000390625 * data_rate;
				mag_out[i] = mag_data[i] * 1.000001 * 1.000001;
				temp_out = temp_data;
			}

			#ifdef GESTURE_BENCHMARK
				if (recordCount < MAX_ACC_LEN)
				{
					accBuffer[accIndex][0] = (accel_out[0] / 9.81) * 10; // (accel_data[0] / 9.81) * 10;
					accBuffer[accIndex][1] = (accel_out[1] / 9.81) * 10;
					accBuffer[accIndex][2] = (accel_out[2] / 9.81) * 10;
					accIndex++;
				}
			#endif

			#ifdef VERBOSE
				cout << "[ Record Counter: " << recordCount << "]" << endl;
				cout << "Raw Gyros: " << gyro_data[0] << ", " << gyro_data[1] << ", " << gyro_data[2] << endl;
				cout << "Raw Accels: " << accel_data[0] << ", " << accel_data[1] << ", " << accel_data[2] << endl;
				cout << "Raw Mags: " << mag_data[0] << ", " << mag_data[1] << ", " << mag_data[2] << endl;
				cout << "Comp Gyros: " << gyro_out[0] << ", " << gyro_out[1] << ", " << gyro_out[2] << endl;
				cout << "Comp Accels: " << accel_out[0] << ", " << accel_out[1] << ", " << accel_out[2] << endl;
				cout << "Comp Mags: " << mag_out[0] << ", " << mag_out[1] << ", " << mag_out[2] << endl;
				cout << "Temperature: " << temp_out << endl;
			#endif
			readyCal = true;
			pthread_mutex_unlock(&mutexCal);
		#endif

		#ifdef KF_BENCHMARK
			#ifndef CAL_BENCHMARK
				if (compDataFile.getProcessedRecord(gyro_data_kf, accel_data_kf, mag_data_kf, &temp_data_kf) != DATA_OK)
				{
					cout << "Reached compensated data EOF prematurely." << endl;
					return NULL;
				}
			#else
				memcpy(gyro_data_kf, gyro_out, sizeof(gyro_data_kf));
				memcpy(accel_data_kf, accel_out, sizeof(accel_data_kf));
				memcpy(mag_data_kf, mag_out, sizeof(mag_data_kf));
			#endif

			pthread_mutex_lock(&mutexKF);
			// Copy data into single buffer
			accels.x = accel_data_kf[0];
			accels.y = accel_data_kf[1];
			accels.z = accel_data_kf[2];

			gyros.x = gyro_data_kf[0];
			gyros.y = gyro_data_kf[1];
			gyros.z = gyro_data_kf[2];

			mags.x = mag_data_kf[0];
			mags.y = mag_data_kf[1];
			mags.z = mag_data_kf[2];

			filter(accels, gyros, mags);
			readyKF = true;
			pthread_mutex_unlock(&mutexKF);
		#endif

		usleep(DELTA_T);
		recordCount++;
	}

	#ifdef CAL_BENCHMARK
		rawDataFile.closeFile();
	#endif

	#ifdef KF_BENCHMARK
		compDataFile.closeFile();
	#endif

	// Process is complete
	completeCalKF = true;

	return NULL;
}

//============================================================================
// Description : Manages Gesture Recognition functionality
//============================================================================
void *gesture_thread( void *ptr )
{
	// Process is starting
	completeGesture = false;

	#ifdef CAL_BENCHMARK
		while (recordCount < MAX_ACC_LEN)
		{
			usleep(50E3);  // Wait for the data to come in
		}
	#endif

	LoadFile gestureFile;

	if (!gestureFile.openFile("gestureSignalInput.txt"))
	{
		cout << "  Failed to open gesture file (!)" << endl;
		return NULL;
	}

	#ifndef CAL_BENCHMARK
		// Sensor input data
		double gyro_data[3] =  { 0, 0, 0 };
		double accel_data[3] =  { 0, 0, 0 };
		double mag_data[3] =  { 0, 0, 0 };
		double temp_data = 0;

		// Loop through data file one record at a time
		for (int i = 0; i < MAX_ACC_LEN; i++)
		{
			if (gestureFile.getProcessedRecord(gyro_data, accel_data, mag_data, &temp_data) == DATA_OK)
			{
				accBuffer[i][0] = (accel_data[0] / 9.81) * 10; //(accel_data[0] / 9.81) * 10;
				accBuffer[i][1] = (accel_data[1] / 9.81) * 10;
				accBuffer[i][2] = (accel_data[2] / 9.81) * 10;
				accIndex++;
			}
			else
			{
				break;
			}
		}
	#endif

	gestureFile.closeFile();

	gestureResult = endGesture();

	#ifdef VERBOSE
		cout << "(!) Gesture ID Recognized: " << gestureResult << endl;
	#endif

	// Process is complete
	readyGesture = true;

	usleep(200E3);
	completeGesture = true;

	return NULL;
}

//============================================================================
// Description : The main application entry point
//============================================================================
int main()
{
	cpu_set_t cpu_info;
	pthread_t threadLive, threadGesture, threadConsumer;
	pthread_attr_t attr_CalKf, attr_Gesture;
	pthread_attr_init(&attr_CalKf);
	pthread_attr_init(&attr_Gesture);

	threadConsumer = pthread_self(); // Get the current (consumer) thread ID
	CPU_ZERO(&cpu_info);
	CPU_SET(CPU_CONSUMER, &cpu_info);
	if (0 != pthread_setaffinity_np(threadConsumer, sizeof(cpu_set_t), &cpu_info))
	{
		cout << "Consumer: set affinity failed\n";
	}

	#ifdef VERBOSE
		printStartupMessages();
	#endif

	// Launch benchmarks
	#ifdef GESTURE_BENCHMARK
			beginGesture(); // Allocate buffers

			pthread_create( &threadGesture, &attr_Gesture, gesture_thread, NULL);
	#else
		completeGesture = true;
	#endif

	#if (defined CAL_BENCHMARK) || (defined KF_BENCHMARK)
			pthread_create( &threadLive, &attr_CalKf, live_thread, NULL);
	#endif

	// Setup worker thread affinities
	#ifdef CAL_BENCHMARK
		CPU_ZERO(&cpu_info);
		CPU_SET(CPU_CAL_KF, &cpu_info);
		if (0 != pthread_attr_setaffinity_np(&attr_CalKf, sizeof(cpu_set_t), &cpu_info))
		{
			cout << "Cal / KF: set affinity failed\n";
		}
	#else
		completeCalKF = true;
	#endif

	#ifdef KF_BENCHMARK
		CPU_ZERO(&cpu_info);
		CPU_SET(CPU_GESTURE, &cpu_info);
		if (0 != pthread_attr_setaffinity_np(&attr_Gesture, sizeof(cpu_set_t), &cpu_info))
		{
			cout << "Gesture: set affinity failed\n";
		}
	#else
		completeCalKF = true;
	#endif

	#ifdef CONSUMER
		#if (defined CAL_BENCHMARK) || (defined KF_BENCHMARK)
			// Perform consumer duties (read and output cal / kf / gesture results)
			while (!completeCalKF || !completeGesture)
			{
				consumerReady = true;

				#if (defined CAL_BENCHMARK)
					pthread_mutex_lock(&mutexCal);
						if (readyCal)
						{
							cout << "(Consumer) [ Record Counter: " << recordCount << "]" << endl;
							cout << "(Consumer) Raw Gyros: " << gyro_data[0] << ", " << gyro_data[1] << ", " << gyro_data[2] << endl;
							cout << "(Consumer) Raw Accels: " << accel_data[0] << ", " << accel_data[1] << ", " << accel_data[2] << endl;
							cout << "(Consumer) Raw Mags: " << mag_data[0] << ", " << mag_data[1] << ", " << mag_data[2] << endl;
							cout << "(Consumer) Comp Gyros: " << gyro_out[0] << ", " << gyro_out[1] << ", " << gyro_out[2] << endl;
							cout << "(Consumer) Comp Accels: " << accel_out[0] << ", " << accel_out[1] << ", " << accel_out[2] << endl;
							cout << "(Consumer) Comp Mags: " << mag_out[0] << ", " << mag_out[1] << ", " << mag_out[2] << endl;
							cout << "(Consumer) Temperature: " << temp_out << endl;
							readyCal = false;
						}
					pthread_mutex_unlock(&mutexCal);
				#endif

				#if (defined KF_BENCHMARK)
					pthread_mutex_lock(&mutexKF);
						if (readyKF)
						{
							cout << "(Consumer) [ Record Counter: " << recordCount << "]" << endl;
							cout << "(Consumer) Euler Angles: " << anglesOutput.x << ", " << anglesOutput.y << ", " << anglesOutput.z << endl << endl;
							readyKF = false;
						}
					pthread_mutex_unlock(&mutexKF);
				#endif

				#ifdef GESTURE_BENCHMARK
					if (readyGesture)
					{
						cout << "(Consumer) Gesture ID Recognized: " << gestureResult << endl << endl;
						readyGesture = false;
					}
				#endif

				usleep(100);  // No need to monopolize the CPU completely
			}
		#endif
	#endif

	#ifndef CONSUMER
		// Wait for benchmark completion
		#if (defined CAL_BENCHMARK) || (defined KF_BENCHMARK)
			pthread_join( threadLive, NULL);
		#endif

		#ifdef GESTURE_BENCHMARK
			pthread_join( threadGesture, NULL);
		#endif
	#endif

	#ifdef VERBOSE
		cout << endl;
	#endif

	return 0;
}
