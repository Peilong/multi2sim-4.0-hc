#include "LoadFile.h"
using namespace std;

// ===========================================================================
bool LoadFile::openFile(string fileName)
{
	dataFile.open(fileName.c_str(), ifstream::in);

	if (dataFile.is_open())
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

// ===========================================================================
int LoadFile::getRawRecord(int* gyro, int* accel, int* mag, int* temp)
{
	string dataLine;

	// Read line
	getline(dataFile, dataLine);
	if (dataLine.length() == 0)
	{
		return (DATA_END);
	}

	// Parse line
	int j = 0;
	string valString[12];

	for (unsigned int i = 0; i < dataLine.length(); i++)
	{
		valString[j].append(1, dataLine[i]);

		if (dataLine[i] == ',')
		{
			j++;
		}
	}

	gyro[0] = atoi(valString[0].c_str());
	gyro[1] = atoi(valString[1].c_str());
	gyro[2] = atoi(valString[2].c_str());

	accel[0] = atoi(valString[3].c_str());
	accel[1] = atoi(valString[4].c_str());
	accel[2] = atoi(valString[5].c_str());

	mag[0] = atoi(valString[6].c_str());
	mag[1] = atoi(valString[7].c_str());
	mag[2] = atoi(valString[8].c_str());

	temp[0] = atoi(valString[10].c_str());

	return (DATA_OK);
}

// ===========================================================================
int LoadFile::getTemplateRecord(double* accel)
{
	string dataLine;

	// Read line
	getline(dataFile, dataLine);
	if (dataLine.length() == 0)
	{
		return (DATA_END);
	}

	// Parse line
	int j = 0;
	string valString[12];

	for (unsigned int i = 0; i < dataLine.length(); i++)
	{
		valString[j].append(1, dataLine[i]);

		if (dataLine[i] == ' ')
		{
			j++;
		}
	}

	accel[0] = atof(valString[0].c_str());
	accel[1] = atof(valString[1].c_str());
	accel[2] = atof(valString[2].c_str());

	return (DATA_OK);
}

// ===========================================================================
int LoadFile::getProcessedRecord(double* gyro, double* accel, double* mag, double* temp)
{
	string dataLine;

	// Read line
	getline(dataFile, dataLine);
	if (dataLine.length() == 0)
	{
		return (DATA_END);
	}

	// Parse line
	int j = 0;
	string valString[12];

	for (unsigned int i = 0; i < dataLine.length(); i++)
	{
		valString[j].append(1, dataLine[i]);

		if (dataLine[i] == ',')
		{
			j++;
		}
	}

	gyro[0] = atof(valString[0].c_str());
	gyro[1] = atof(valString[1].c_str());
	gyro[2] = atof(valString[2].c_str());

	accel[0] = atof(valString[3].c_str());
	accel[1] = atof(valString[4].c_str());
	accel[2] = atof(valString[5].c_str());

	mag[0] = atof(valString[6].c_str());
	mag[1] = atof(valString[7].c_str());
	mag[2] = atof(valString[8].c_str());

	temp[0] = atof(valString[10].c_str());

	return (DATA_OK);
}

// ===========================================================================
void LoadFile::closeFile()
{
	dataFile.close();
}
