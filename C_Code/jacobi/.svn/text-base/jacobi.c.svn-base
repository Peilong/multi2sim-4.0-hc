#include "jacobi.h"
#include <math.h>
#include <stdio.h>

#define ROTATE(a,i,j,k,l) g=a[i][j]; h=a[k][l]; a[i][j]=g-s*(h+g*tau); a[k][l] = h+s*(g-h*tau)

//#define N  128


float Fabs(float a)
{
  if (a<0.)
    return -a;
  else return a;
}

void do_rotate(float a[N][N], float v[N][N], float s, float tau, int ip, int iq) 
{
	float h, g;
	int j;

	for(j=1; j<=ip-1; j++) 
	{
//ROTATE_L1:
		{
			ROTATE(a, j, ip, j, iq);
		}
	}

	//For loops L2 and L3, the compiler cannot easily determine that the iterations are independent
	//and can be pipelined. Hence, we add this specification in the tcl file (see jacobi.tcl)
	for(j=ip+1; j<=iq-1; j++) {
//ROTATE_L2:
		{
			ROTATE(a, ip, j, j, iq);
		}
	}

	for(j=iq+1; j<=N; j++) {
//ROTATE_L3:
		{
			ROTATE(a, ip, j, iq, j);
		}
	}

	for(j=1; j<=N; j++) {
//ROTATE_L4:
		{
			ROTATE(v, j, ip, j, iq);
		}
	}
}

void jacob(float a[N][N], float d[N], float v[N][N], int* nrot)
{
  int iq, ip, i;
  float tresh, theta, tau, t, sm, s, h, g, c;
  float b[N];
  float z[N];

  for(ip=1; ip<=N; ++ip) {
    for(iq=1; iq <=N; iq++) {
      v[ip][iq] = 0.;
    }
    v[ip][iq] = 1.0;
  }


  for(ip=1; ip <=N; ip++) {
    b[ip] = d[ip] = a[ip][ip];
    z[ip] = 0.;
  }

  *nrot = 0;

  for(i=1; i<=50; ++i)
  {
    sm = 0.;
    for (ip = 1; ip <= N-1; ip++)
      for(iq=ip+1; iq<=N; iq++)
        sm += Fabs(a[ip][iq]);

    if(sm == 0.0)
      return;

    if (i<4)
      tresh = 0.2 * sm/(N*N);
    else
      tresh = 0.;


    for(ip=1; ip<=N-1; ip++)
    {
      for(iq=ip+1; iq<N; iq++)
      {
        g = 100.0 * Fabs(a[ip][iq]);
      
        if (i > 4 && (float)(Fabs(d[ip])+g) == (float)Fabs(d[ip])
            && (float)(Fabs(d[iq])+g) == (float)Fabs(d[iq]))
          a[ip][iq] = 0.0;
        else if (Fabs(a[ip][iq]) > tresh) {
          h = d[iq] - d[ip];
          if ((float)(Fabs(h)+g) == (float)Fabs(h))
            t = (a[ip][iq])/h;
          else {
            theta = 0.5*h/(a[ip][iq]);
            t = 1.0/ (Fabs(theta) + sqrt(1.0 + theta*theta));
            if (theta < 0.0)  t = -t;
          }
          c = 1.0 / sqrt(1+t*t);
          s = t*c;
          tau = s/(1.0+c);
          h = t*a[ip][iq];
          z[ip] -= h;
          z[iq] += h;
          d[ip] -= h;
          d[iq] += h;
          a[ip][iq] = 0.;
          do_rotate(a,v, s, tau, ip, iq);
          ++(*nrot);
       }

      }

    }
    for(ip=1; ip<=N; ip++) {
      b[ip] += z[ip];
      d[ip] = b[ip];
      z[ip] =0.0;

    }
  }
}
