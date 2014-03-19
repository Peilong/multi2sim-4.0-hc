#ifndef __IDSI_ACC_H
#define __IDSI_ACC_H

#define IMGW 640
#define IMGH 480

#define DIM_INTEN   10		// spin-image intenstity dimension
#define DIM_DIST    10		// spin-image distance   dimension

void computeIDSI(const unsigned char img[IMGH][IMGW], int x, int y, float idsi[DIM_DIST][DIM_INTEN]);

#endif
