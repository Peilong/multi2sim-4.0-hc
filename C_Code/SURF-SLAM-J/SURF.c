#include "SURF.h"


#define ORI_RADIUS     6
#define ORI_WIN        60
#define ORI_SEARCH_INC 5

#define PATCH_SZ 20

#define CV_PI 3.1415926535897932384626433832795f

#define DBL_EPSILON 2.2204460492503131e-16f

#define NPTS 113

static const int xs[NPTS] = {0,-3,-2,-1,0,1,2,3,-4,-3,-2,-1,0,1,2,3,4,-5,-4,-3,-2,-1,0,1,2,3,4,5,-5,-4,-3,-2,-1,0,1,2,3,4,5,-5,-4,-3,-2,-1,0,1,2,3,4,5,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,-5,-4,-3,-2,-1,0,1,2,3,4,5,-5,-4,-3,-2,-1,0,1,2,3,4,5,-5,-4,-3,-2,-1,0,1,2,3,4,5,-4,-3,-2,-1,0,1,2,3,4,-3,-2,-1,0,1,2,3,0,};

static const int ys[NPTS] = {-6,-5,-5,-5,-5,-5,-5,-5,-4,-4,-4,-4,-4,-4,-4,-4,-4,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,6,};

static const float wts[NPTS] = {0.170041,0.100158,0.138701,0.170414,0.182792,0.170414,0.138701,0.100158,0.0895298,0.123134,0.161677,0.19339,0.205768,0.19339,0.161677,0.123134,0.0895298,0.100158,0.123134,0.156738,0.195281,0.226994,0.239372,0.226994,0.195281,0.156738,0.123134,0.100158,0.138701,0.161677,0.195281,0.233824,0.265537,0.277915,0.265537,0.233824,0.195281,0.161677,0.138701,0.170414,0.19339,0.226994,0.265537,0.29725,0.309628,0.29725,0.265537,0.226994,0.19339,0.170414,0.170041,0.182792,0.205768,0.239372,0.277915,0.309628,0.322006,0.309628,0.277915,0.239372,0.205768,0.182792,0.170041,0.170414,0.19339,0.226994,0.265537,0.29725,0.309628,0.29725,0.265537,0.226994,0.19339,0.170414,0.138701,0.161677,0.195281,0.233824,0.265537,0.277915,0.265537,0.233824,0.195281,0.161677,0.138701,0.100158,0.123134,0.156738,0.195281,0.226994,0.239372,0.226994,0.195281,0.156738,0.123134,0.100158,0.0895298,0.123134,0.161677,0.19339,0.205768,0.19339,0.161677,0.123134,0.0895298,0.100158,0.138701,0.170414,0.182792,0.170414,0.138701,0.100158,0.170041,};

static const float patch_wts[PATCH_SZ/2][PATCH_SZ/2] = { \
	{3.69535e-06,8.44457e-06,1.76043e-05,3.34795e-05,5.80844e-05,9.19306e-05,0.000132733,0.000174832,0.000210078,0.000230284,},
	{8.44457e-06,1.92974e-05,4.0229e-05,7.65068e-05,0.000132734,0.000210079,0.00030332,0.000399524,0.000480067,0.000526241,},
	{1.76043e-05,4.0229e-05,8.38648e-05,0.000159493,0.000276708,0.000437947,0.000632328,0.000832881,0.00100079,0.00109705,},
	{3.34795e-05,7.65068e-05,0.000159493,0.000303321,0.000526238,0.000832881,0.00120255,0.00158396,0.00190328,0.00208634,},
	{5.80844e-05,0.000132734,0.000276708,0.000526238,0.000912983,0.00144499,0.00208633,0.00274805,0.00330205,0.00361965,},
	{9.19306e-05,0.000210079,0.000437947,0.000832881,0.00144499,0.00228699,0.00330206,0.00434936,0.00522619,0.00572885,},
	{0.000132733,0.00030332,0.000632328,0.00120255,0.00208633,0.00330206,0.00476765,0.0062798,0.00754579,0.00827156,},
	{0.000174832,0.000399524,0.000832881,0.00158396,0.00274805,0.00434936,0.0062798,0.00827154,0.00993907,0.010895,},
	{0.000210078,0.000480067,0.00100079,0.00190328,0.00330205,0.00522619,0.00754579,0.00993907,0.0119428,0.0130914,},
	{0.000230284,0.000526241,0.00109705,0.00208634,0.00361965,0.00572885,0.00827156,0.010895,0.0130914,0.0143506,},
};

static const int dx_s[2][5] = {{0, 0, 2, 4, -1}, {2, 0, 4, 4, 1}};
static const int dy_s[2][5] = {{0, 0, 4, 2, 1}, {0, 2, 4, 4, -1}};

typedef struct _CvSurfHF
{
    int p0, p1, p2, p3;
    float w;
} CvSurfHF;
CvSurfHF dx_t[2], dy_t[2];

float X[NPTS], Y[NPTS], angle[NPTS];

float DX[PATCH_SZ][PATCH_SZ], DY[PATCH_SZ][PATCH_SZ];

unsigned char patch[PATCH_SZ+1][PATCH_SZ+1];


inline float fabsf(float x)
{
	return (x < 0.f) ? -x : x;
}

inline int cvRound(float value)
{
	return (int)(value + (value >= 0 ? 0.5f : -0.5f));
}


float invSqrt(float x)
{
   float xhalf = 0.5f * x;
   int i = *(int*)&x;			// store floating-point bits in integer
   i = 0x5f3759d5 - (i >> 1);	// initial guess for Newton's method
   x = *(float*)&i;				// convert new bits into float
   x = x*(1.5f - xhalf*x*x);	// One round of Newton's method
   return x;
}


inline float
icvCalcHaarPattern(const int* origin, const CvSurfHF* f, int n)
{
    float d = 0.f;
	int k;
    for(k = 0; k < n; k++) {
//#pragma AP loop_tripcount min=2 max=2 avg=2
//#pragma AP pipeline
        d += (origin[f[k].p0] + origin[f[k].p3] - origin[f[k].p1] - origin[f[k].p2]) * f[k].w;
    }
    return d;
}


void						// [3or4][5]
icvResizeHaarPattern( const int src[][5], CvSurfHF* dst, int n, int oldSize, int newSize, int widthStep)
{
    float ratio = (float)newSize/oldSize;
	int k;
    for(k = 0; k < n; k++) {
//#pragma AP loop_tripcount min=2 max=2 avg=2
//#pragma AP pipeline
        int dx1 = cvRound(ratio*src[k][0]);
        int dy1 = cvRound(ratio*src[k][1]);
        int dx2 = cvRound(ratio*src[k][2]);
        int dy2 = cvRound(ratio*src[k][3]);
        dst[k].p0 = dy1*widthStep + dx1;
        dst[k].p1 = dy2*widthStep + dx1;
        dst[k].p2 = dy1*widthStep + dx2;
        dst[k].p3 = dy2*widthStep + dx2;
        dst[k].w = src[k][4]/((float)(dx2-dx1)*(dy2-dy1));
    }
}


float fastAtan2(float y, float x)
{
	float a, x2 = (float)x*x, y2 = (float)y*y;
	if( y2 <= x2 )
	{
		a = (180./CV_PI)*x*y/(x2 + 0.28*y2 + DBL_EPSILON);
		return (float)(x < 0 ? a + 180 : y >= 0 ? a : 360+a);
	}
	a = (180./CV_PI)*x*y/(y2 + 0.28*x2 + DBL_EPSILON);
	return (float)(y >= 0 ? 90 - a : 270 - a);
}


void SURFdescriptor(SURFPoint *keypoint, float descriptor[DESC_SIZE], unsigned char img[IMGH][IMGW], unsigned int sum[IMGH+1][IMGW+1])
{
	const float s = keypoint->size * (1.2f/9.0f);
	const float kpx = keypoint->x;
	const float kpy = keypoint->y;
	int i, j, k, x, y;

	int grad_wav_size = cvRound(4.f * s);
	if (grad_wav_size > IMGH+1 || grad_wav_size > IMGW+1)
	{
		keypoint->size = -1;
		return;
	}

	// setup gradient wavelets
	icvResizeHaarPattern(dx_s, dx_t, 2, 4, grad_wav_size, IMGW+1);
	icvResizeHaarPattern(dy_s, dy_t, 2, 4, grad_wav_size, IMGW+1);

	const float px_grsz = kpx - (float)(grad_wav_size-1)/2;
	const float py_grsz = kpy - (float)(grad_wav_size-1)/2;
	int nangle;

	// compute gradients
	for(k = 0, nangle = 0; k < NPTS; k++) {
//#pragma AP loop_tripcount min=113 max=113 avg=113
	    x = cvRound(px_grsz + xs[k]*s);
	    y = cvRound(py_grsz + ys[k]*s);

	    if( (unsigned)y >= (unsigned)((IMGH+1) - grad_wav_size) ||
		    (unsigned)x >= (unsigned)((IMGW+1) - grad_wav_size) )
	        continue;

	    float vx = icvCalcHaarPattern(&sum[y][x], dx_t, 2);
		float vy = icvCalcHaarPattern(&sum[y][x], dy_t, 2);

	    X[nangle] = vx * wts[k];
		Y[nangle] = vy * wts[k];
	    nangle++;
	}
	if (nangle == 0) {
		keypoint->size = -1;
		return;
	}

	// gradient angles
	for (k = 0; k < nangle; k++) {
//#pragma AP loop_tripcount min=1 max=113 avg=100
//#pragma AP pipeline
		angle[k] = fastAtan2(Y[k], X[k]);
	}

	// find best orientation
	float bestx = 0.f, besty = 0.f, descriptor_mod = 0.f;
	for(i = 0; i < 360; i += ORI_SEARCH_INC) {
//#pragma AP loop_tripcount min=72 max=72 avg=72
	    float sumx = 0, sumy = 0, temp_mod;
	    for(j = 0; j < nangle; j++) {
//#pragma AP loop_tripcount min=1 max=113 avg=100
//#pragma AP pipeline
	        int d = fabsf(cvRound(angle[j]) - i);
	        if( d < ORI_WIN/2 || d > 360-ORI_WIN/2 )
	        {
	            sumx += X[j];
	            sumy += Y[j];
	        }
	    }
	    temp_mod = sumx*sumx + sumy*sumy;
	    if(temp_mod > descriptor_mod)
	    {
	        descriptor_mod = temp_mod;
	        bestx = sumx;
	        besty = sumy;
	    }
	}

	// save descriptor direction
	float descriptor_dir = fastAtan2(besty, bestx);
	keypoint->dir = descriptor_dir;
	descriptor_dir *= (float)(CV_PI/180);


	// EXTRACT PATCH OF SIZE (PATCH_SZ+1) BY SAMPLING ORIENTED RECT OF SIZE (PATCH_SZ+1)*s
	float invmag = invSqrt(descriptor_mod);
	float sin_dir = besty*invmag;
	float cos_dir = bestx*invmag;

	for (i = 0; i < PATCH_SZ+1; i++) {
//#pragma AP loop_tripcount min=21 max=21 avg=21
	for (j = 0; j < PATCH_SZ+1; j++) {
//#pragma AP loop_tripcount min=21 max=21 avg=21
//#pragma AP pipeline
		float win_x = (j-(PATCH_SZ/2)) * s;
		float win_y = (i-(PATCH_SZ/2)) * s;
	
		int ix = cvRound( (cos_dir*win_x - sin_dir*win_y) - kpx );
		int iy = cvRound( (sin_dir*win_x + cos_dir*win_y) - kpy );

		if (ix < 0) ix = 0;
		else if (ix >= IMGW) ix = IMGW-1;
		if (iy < 0) iy = 0;
		else if (iy >= IMGH) iy = IMGH-1;

		patch[i][j] = img[iy][ix];
	}}

	// Calculate gradients in x and y with wavelets of size 2s
	for(i = 0; i < PATCH_SZ; i++) {
//#pragma AP loop_tripcount min=20 max=20 avg=20
	for(j = 0; j < PATCH_SZ; j++) {
//#pragma AP loop_tripcount min=20 max=20 avg=20
//#pragma AP pipeline
		int pi = (i >= PATCH_SZ/2) ? PATCH_SZ-1-i : i;
		int pj = (j >= PATCH_SZ/2) ? PATCH_SZ-1-i : i;
		float dw = patch_wts[pi][pj];
		float vx = (patch[i][j+1] - patch[i][j] + patch[i+1][j+1] - patch[i+1][j])*dw;
		float vy = (patch[i+1][j] - patch[i][j] + patch[i+1][j+1] - patch[i][j+1])*dw;
		DX[i][j] = vx;
		DY[i][j] = vy;
	}}

	// Compute descriptor
	// assume `descriptor` has zeros
	//float sq_mag = 0.f;
	k = 0;

	for( i = 0; i < 4; i++ ) {
//#pragma AP loop_tripcount min=4 max=4 avg=4
	for( j = 0; j < 4; j++ ) {
//#pragma AP loop_tripcount min=4 max=4 avg=4
		for( y = i*5; y < i*5+5; y++ ) {
//#pragma AP loop_tripcount min=5 max=5 avg=5
		for( x = j*5; x < j*5+5; x++ ) {
//#pragma AP loop_tripcount min=5 max=5 avg=5
//#pragma AP pipeline
			float tx = DX[y][x], ty = DY[y][x];
			if (ty >= 0)
			{
				descriptor[k+0] += tx;
				descriptor[k+1] += (float)fabsf(tx);
			} else {
				descriptor[k+2] += tx;
				descriptor[k+3] += (float)fabsf(tx);
			}
			if (tx >= 0)
			{
				descriptor[k+4] += ty;
				descriptor[k+5] += (float)fabsf(ty);
			} else {
				descriptor[k+6] += ty;
				descriptor[k+7] += (float)fabsf(ty);
			}
			//sq_mag += 2.f*(tx*tx + ty*ty);
		}}
		k += 8;
	}}
}

