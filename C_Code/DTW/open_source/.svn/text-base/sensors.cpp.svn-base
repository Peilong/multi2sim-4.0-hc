/*
 * sensors.cpp
 *
 * Created: 09/12/2011 13:22:37
 *  Author: Lo�c KAEMMERLEN
 
 * Based on the pololu libraries for LSM303 and L3G4200D
 */ 

#include <math.h>
#include <stdlib.h>
#include <string.h>
	
#include "mathstools.h"
#include "sensors.h"

// Calibration values using compass_calibration. This needs to be done!

vectorMe m_min = {-492, -503, -549};
vectorMe m_max = {579, 494, 322};

// Returns a heading (in degrees) given an acceleration vector a due to gravity, a magnetic vector m, and a facing vector p.
float get_heading(vectorMe *a, vectorMe *m, vectorMe *p)
{
	
	// shift and scale
	m->x = (m->x - m_min.x) / (m_max.x - m_min.x) * 2 - 1.0;
	m->y = (m->y - m_min.y) / (m_max.y - m_min.y) * 2 - 1.0;
	m->z = (m->z - m_min.z) / (m_max.z - m_min.z) * 2 - 1.0;
	
	
	vectorMe E;
	vectorMe N;

	// cross magnetic vector (magnetic north + inclination) with "down" (acceleration vector) to produce "east"
	vector_cross(m, a, &E);
	vector_normalize(&E);

	// cross "down" with "east" to produce "north" (parallel to the ground)
	vector_cross(a, &E, &N);
	vector_normalize(&N);

	// compute heading
	float heading = round(atan2(vector_dot(&E, p), vector_dot(&N, p)) * 180 / M_PI);
	
	if (heading > 180)
		heading -= 360;
	if (heading < -180)
		heading += 360;
	return heading;
}
