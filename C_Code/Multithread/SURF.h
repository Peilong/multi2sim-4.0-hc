#ifndef __SURF_ACC_H
#define __SURF_ACC_H

#define IMGW 320
#define IMGH 240

#define DESC_SIZE 128

typedef struct _SURFPoint
{
    float x, y;
    int size;
    float dir;
} SURFPoint;

void SURFdescriptor(SURFPoint *keypoint, float descriptor[DESC_SIZE], unsigned char img[IMGH][IMGW], unsigned int sum[IMGH+1][IMGW+1]);

#endif
