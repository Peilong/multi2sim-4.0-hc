#include "IDSI.h"

#define STDEV_INTEN 20		// stdev of intensity distribution for a given pixel's contribution
#define STDEV_DIST  0.4		// stdev of distance  distribution for a given pixel's contribution
#define RADIUS      20		// feature-patch radius

#define SQRT_2  1.4142135623730951f


float sqrtf(float x)
{
   float xhalf = 0.5f * x;
   int i = *(int*)&x; // store floating-point bits in integer
   i = 0x5f3759d5 - (i >> 1); // initial guess for Newton's method
   x = *(float*)&i; // convert new bits into float
   x = x*(1.5f - xhalf*x*x); // One round of Newton's method
   // invert the inverse-sqrt to get actual sqrt
   return 1.f/x;
}

inline float expf(float x)
{
	// cutoff
	if (x <= -4.f)
		return 0.f;

	// taylor series expansion around x=-2
	x -= -2.f;
	float x2 = x*x;
	float x3 = x2*x;
	float x4 = x2*x2;
	float x5 = x2*x3;

	return /* exp(-2) */ 0.1353352832366127f * (1.f + x + x2/2.f + x3/6.f + x4/24.f + x5/120.f);
}


inline int roundfloat(float value)
{
	return (int)(value + (value >= 0 ? 0.5f : -0.5f));
}


// the contribution of a pixel having (distance,intensity)=(d,i) to the bin for (d0,i0) is:
//
//     exp( -(d-d0)^2 / (2 alpha^2) - (i-i0)^2 / (2 beta^2) )
//
// where alpha=OPT_STD_DIST and beta=OPT_STD_INT

// using current values: the distance term only contributes for the 4 neighbors [-3.125] and the pixel itself [-0]


void computeIDSI(const unsigned char img[IMGH][IMGW], int x, int y, float idsi[DIM_DIST][DIM_INTEN])
{
	int d, i;
	const float k_dist  = -1.f / (2.f * STDEV_DIST *STDEV_DIST );
	const float k_inten = -1.f / (2.f * STDEV_INTEN*STDEV_INTEN);
	
	// zero the histogram
	for (d = 0; d < DIM_DIST; d++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
	for (i = 0; i < DIM_INTEN; i++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
//#pragma AP unroll
		idsi[d][i] = 0.f;
	}}

	// get feature pixel
	unsigned char pixel = img[y][x];
	int dx, dy;

	// image patch bounds
	int dxmin = (x < RADIUS) ? -x : -RADIUS;
	int dxmax = (x + RADIUS >= IMGW) ? IMGW-1-x : RADIUS;

	int dymin = (y < RADIUS) ? -y : -RADIUS;
	int dymax = (y + RADIUS >= IMGH) ? IMGH-1-y : RADIUS;
	
	// fill in histogram
	for (dy = dymin; dy <= dymax; dy++) {
//#pragma AP loop_tripcount min=11 max=21 avg=19
	for (dx = dxmin; dx <= dxmax; dx++) {
//#pragma AP loop_tripcount min=11 max=21 avg=19
//#pragma AP pipeline
		i = img[y+dy][x+dx];

		int di_sq = i - pixel; di_sq *= di_sq;
		int dd_sq = dx*dx + dy*dy;

		i = roundfloat((float)i * ((DIM_INTEN-1)/255.f));

		d = roundfloat(sqrtf(dd_sq) * ((DIM_DIST-1)/(RADIUS*SQRT_2)));

		idsi[d][i] += expf(dd_sq*k_dist + di_sq*k_inten);
	}}
	
	// Normalize histogram to [0,1]
	float min = RADIUS*RADIUS, max = 0.f;

	for (d = 0; d < DIM_DIST; d++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
	for (i = 0; i < DIM_INTEN; i++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
//#pragma AP unroll
		float f = idsi[d][i];
		if (f < min) min = f;
		if (f > max) max = f;
	}}

	float k = (max == min) ? 1.f : 1.f/(max - min);

	for (d = 0; d < DIM_DIST; d++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
	for (i = 0; i < DIM_INTEN; i++) {
//#pragma AP loop_tripcount min=10 max=10 avg=10
//#pragma AP unroll
		idsi[d][i] = (idsi[d][i] - min) * k;
	}}
}


