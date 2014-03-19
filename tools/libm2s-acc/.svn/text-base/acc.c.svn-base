/*
 *  Multi2Sim
 *  Copyright (C) 2012  Rafael Ubal (ubal@ece.neu.edu)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <m2s-acc.h>
//#include <debug.h>
#include <list.h>
#include <misc.h>
#include <unistd.h>


/*
 * Error Messages
 */

/*
#define __X86_ACC_NOT_IMPL__  fatal("%s: not implemented.\n%s", \
	__FUNCTION__, err_x86_acc_not_impl);
*/

//static char *err_x86_opengl_not_impl = 
//	"\tMulti2Sim provides partial support for the OpenGL library.\n" 
//	"\tTo request the implementation of a certain functionality, please\n" 
//	"\temail development@multi2sim.org.\n";

/*static char *err_x86_opengl_version =
	"\tYour guest application is using a version of the OpenGL runtime library\n"
	"\tthat is incompatible with this version of Multi2Sim. Please download the\n"
	"\tlatest Multi2Sim version, and recompile your application with the latest\n"
	"\tOpengl runtime library ('libm2s-opengl').\n";*/




/* Multi2Sim OPENGL Runtime required */
#define X86_ACC_RUNTIME_VERSION_MAJOR	0
#define X86_ACC_RUNTIME_VERSION_MINOR	669

struct x86_acc_version_t
{
	int major;
	int minor;
};

typedef struct arglist
{
	int** sample1;
	int length1;
	int** sample2;
	int length2;
	int i;
	int j;
	int* table;
} arglist;

/*
 * ACC call #1 - accDTW
 *
 * accDTW - DTW algorithm, return distance
 *
 * @return
 *	The function always returns DTW distance
 */

//=========== DTW algorithm acceleration =============//
int accDTW(int** sample1, int length1, int** sample2, int length2, int i, int j, int* table)
{
	printf("\n*************************************\n");	
	printf("calling dynamic lib function 'accDTW'\n");
	struct arglist acc_args;
	acc_args.sample1 = sample1; //2-d Address
	acc_args.length1 = length1;
	acc_args.sample2 = sample2; //2-d Address
	acc_args.length2 = length2;
	acc_args.i       = i;
	acc_args.j       = j;
	acc_args.table   = table;   //Address

	printf("\t\tacc_args[0] = %p (%p)\n", acc_args.sample1, &(acc_args.sample1[0][0]));
	printf("\t\tacc_args[1] = %u (%p)\n", acc_args.length1, &acc_args.length1);
	printf("\t\tacc_args[2] = %p (%p)\n", acc_args.sample2, &(acc_args.sample2[0][0]));
	printf("\t\tacc_args[3] = %u (%p)\n", acc_args.length2, &acc_args.length2);
	printf("\t\tacc_args[4] = %u (%p)\n", acc_args.i, &acc_args.i);
	printf("\t\tacc_args[5] = %u (%p)\n", acc_args.j, &acc_args.j);
	printf("\t\tacc_args[6] = %p (%p)\n", acc_args.table, &acc_args.table[0]);

	int ret = syscall(X86_ACC_SYS_CODE, x86_acc_call_accDTW, &acc_args);

	return ret;
}



/*
 * ACC call #2 - accArith
 *
 * accRSENC - Reed-Solomon encoding algorithm
 *
 * @return
 *	The function always returns jas_image_t pointer if running properly;
 *	ruturns 0 if not decode image correctly.
 */

int accArith (double *A)
{
	printf("\n***************************************\n");	
	printf("calling dynamic lib function 'accArith'\n");

//	printf();
/*
	printf("\t\tA1 = %f (0x%x)\n", *A1,A1);
	printf("\t\tA2 = %f (0x%x)\n", *A2,A2);
	printf("\t\tA3 = %f (0x%x)\n", *A3,A3);
	printf("\t\tA4 = %f (0x%x)\n", *A4,A4);
	printf("\t\tN  = %f (0x%x)\n", *N, N);
*/
/*
	unsigned int args[5];
	args[0] = (unsigned int)N;
	args[1] = (unsigned int)A1;
	args[2] = (unsigned int)A2;
	args[3] = (unsigned int)A3;
	args[4] = (unsigned int)A4;
*/
	
	double *args = A;
/*
	args[0] = A1;
	args[1] = A2;
	args[2] = A3;
	args[3] = A4;
	args[4] = N;
	printf("\t\targs[0] = %u (0x%x)\n", args[0], args[0]);
	printf("\t\targs[1] = %u (0x%x)\n", args[1], args[1]);
	printf("\t\targs[2] = %u (0x%x)\n", args[2], args[2]);
	printf("\t\targs[3] = %u (0x%x)\n", args[3], args[3]);
	printf("\t\targs[4] = %u (0x%x)\n", args[4], args[4]);
*/
	syscall(X86_ACC_SYS_CODE, x86_acc_call_accArith, &args);
	return 0;
}


/*
 * ACC call #3 - accPrintCycle
 *
 * accPrintCycle - Print out the current CPU cycle 
 *
 * @return
 *	True of False
 */

void accPrintCycle (void)
{
	syscall(X86_ACC_SYS_CODE, x86_acc_call_accPrintCycle);
}

/*
 * ACC call #4 - accConfigReq
 *
 * accConfigReq -  Before calling a certain kind of system call, first try to 
 *				request an ACC configuration. Request is only admitted
 *				when counter is counted to N.
 *
 * @return
 *	True of False
 */

int accConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accConfigReq);
}

 /*
  * ACC call #5 - accConfigPrepared
  *
  * accConfigPrepared -	After request is admitted, 'ConfigCycle' number of 
  *				cycles have to be passed until ACC configuration is 
  *				ready.
  *
  * @return
  *  True of False
  */
 
 int accConfigPrepared (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accConfigPrepared);
}
 
//************************************************************
//************************************************************
//
//  ACC call #6 - acc3DESConfigReq
//
//  accConfigReq - 3DES ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int acc3DESConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_acc3DESConfigReq);
}


//************************************************************
//************************************************************
//
//  ACC call #7 - accJacobiConfigReq
//
//  accConfigReq - Jacobi ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accJacobiConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accJacobiConfigReq);
}

//************************************************************
//************************************************************
//
//  ACC call #8 - accIDSIConfigReq
//
//  accConfigReq - IDSI ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accIDSIConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accIDSIConfigReq);
}


//************************************************************
//************************************************************
//
//  ACC call #9 - accSegConfigReq
//
//  accConfigReq - IDSI ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accSegConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSegConfigReq);
}


//************************************************************
//************************************************************
//
//  ACC call #10 - accSWConfigReq
//
//  accConfigReq - Seg ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accSWConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSWConfigReq);
}

//************************************************************
//************************************************************
//
//  ACC call #11 - accSLAMCConfigReq
//
//  accConfigReq - SLAMC ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accSLAMCConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMCConfigReq);
}


//************************************************************
//************************************************************
//
//  ACC call #12 - accSLAMJConfigReq
//
//  accConfigReq - SLAMJ ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accSLAMJConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMJConfigReq);
}


//************************************************************
//************************************************************
//
//  ACC call #13 - accSURFConfigReq
//
//  accConfigReq - SURF ACC request
//  return - Admitted: 1; Denied: 0 (Number of requests are not enough)
//
//************************************************************
//************************************************************
int accSURFConfigReq (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSURFConfigReq);
}

//************************************************************
//************************************************************
//
//  ACC call #14 - acc3DESConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int acc3DESConfigPrepared (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_acc3DESConfigPrepared);
}

//************************************************************
//************************************************************
//
//  ACC call #15 - accJacobiConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accJacobiConfigPrepared (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accJacobiConfigPrepared);
}

//************************************************************
//************************************************************
//
//  ACC call #16 - accIDSIConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accIDSIConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accIDSIConfigPrepared);
}

//************************************************************
//************************************************************
//
//  ACC call #17 - accSegConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accSegConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSegConfigPrepared);
}

//************************************************************
//************************************************************
//
//  ACC call #18 - accSWConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accSWConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSWConfigPrepared);
}


//************************************************************
//************************************************************
//
//  ACC call #19 - accSLAMCConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accSLAMCConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMCConfigPrepared);
}


//************************************************************
//************************************************************
//
//  ACC call #20 - accSLAMJConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accSLAMJConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMJConfigPrepared);
}


//************************************************************
//************************************************************
//
//  ACC call #21 - accSURFConfigPrepared
//
//  accConfigPrepared - After request is admitted, 'CofigCycle' number of 
//				cycles have to be passed until ACC configuration is 
//				ready.
//
//  @return - Preprared: 1; Not Prepared Yet: 0
//
//************************************************************
//************************************************************
int accSURFConfigPrepared(void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSURFConfigPrepared);
}

//************************************************************
//************************************************************
//
//  ACC call #22 - acc3DESRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int acc3DESRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_acc3DESRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #23 - accJacobiRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accJacobiRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accJacobiRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #24 - accIDSIRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accIDSIRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accIDSIRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #25 - accSegRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSegRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSegRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #26 - accSWRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSWRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSWRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #27 - accSLAMCRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSLAMCRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMCRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #28 - accSLAMJRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSLAMJRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMJRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #29 - accSURFRelease
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSURFRelease (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSURFRelease);
}


//************************************************************
//************************************************************
//
//  ACC call #30 - acc3DES
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int acc3DES (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_acc3DES);
}


//************************************************************
//************************************************************
//
//  ACC call #31 - accJacobi
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accJacobi (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accJacobi);
}


//************************************************************
//************************************************************
//
//  ACC call #32 - accIDSI
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accIDSI (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accIDSI);
}


//************************************************************
//************************************************************
//
//  ACC call #33 - accSeg
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSeg (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSeg);
}


//************************************************************
//************************************************************
//
//  ACC call #34 - accSW
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSW (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSW);
}


//************************************************************
//************************************************************
//
//  ACC call #35 - accSLAMC
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSLAMC (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMC);
}


//************************************************************
//************************************************************
//
//  ACC call #36 - accSLAMJ
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSLAMJ (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSLAMJ);
}

//************************************************************
//************************************************************
//
//  ACC call #37 - accSURF
//
//  Clear the "withAcc" status, return acc type to NOACC and clear counters
//
//  @return - None
//
//************************************************************
//************************************************************
int accSURF (void)
{
	return syscall(X86_ACC_SYS_CODE, x86_acc_call_accSURF);
}

