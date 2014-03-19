#ifndef LOADFILE_H_
#define LOADFILE_H_

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

// Data Status
static const int DATA_ERROR_DATA = -1;
static const int DATA_END = 0;
static const int DATA_OK = 1;

class LoadFile
{
public:
	ifstream dataFile;

	bool openFile(string fileName);

	int getRawRecord(int* gyro, int* accel, int* mag, int* temp);
	int getProcessedRecord(double* gyro, double* accel, double* mag, double* temp);
	int getTemplateRecord(double* accel);

	void closeFile();
};
#endif /* LOADFILE_H_ */
