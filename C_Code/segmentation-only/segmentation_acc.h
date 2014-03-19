#ifndef __SEGMENTATION_ACC_H
#define __SEGMENTATION_ACC_H

#define m 66
#define n 61
#define p 66
#define TMP_SIZE 4

void fetch(int step, volatile float* bus, float array[m][p]);
void write(int step, volatile float* bus, float array[m][p]);
void compute(float array0[m][p], float array1[m][p], float array2[m][p], float u0[m][p], float res[m][p], float n1, float n2);
void segmentation_acc(volatile float* A_bus, volatile float* B_bus, volatile float* C_bus, int c[2]) ;

#endif
