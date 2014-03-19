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


#include <x86-timing.h>


/**************** C o n s t a n t s ******************/
//#define DELAY_TIME 100000000 //Peilong: Without Acc
#define DELAY_TIME  2941176 //Peilong: With Acc

//Acc computation cycles -- from Jason Cong's report
#define DESDelay    72705
#define JacobiDelay 114181
#define IDSIDelay   2187
#define SegDelay    274805
#define SLAMCDelay  104
#define SLAMJDelay  77
#define SURFDelay   10558
#define SWDelay     11709

extern struct x86_cpu_t *x86_cpu; //Peilong Code Here
int syscallflag_gettimeofday = 0;         //Peilong
int syscallflag_acc = 0;
long long int delay_time_gettimeofday = 0;		  //peilong
long long int delay_time_acc = 0;    //Peilong

//Acc can begin flag
int DESAccFlag    = 0;
int JacobiAccFlag = 0;
int IDSIAccFlag   = 0;
int SegAccFlag    = 0;
int SLAMCAccFlag  = 0;
int SLAMJAccFlag  = 0;
int SURFAccFlag   = 0;
int SWAccFlag     = 0;

//Acc cycle elapse counter
unsigned long DES_delay    = 0;
unsigned long Jacobi_delay = 0;
unsigned long IDSI_delay   = 0;
unsigned long Seg_delay    = 0;
unsigned long SLAMC_delay  = 0;
unsigned long SLAMJ_delay  = 0;
unsigned long SURF_delay   = 0;
unsigned long SW_delay     = 0;


/* Return the reason why a thread cannot be dispatched. If it can,
 * return x86_dispatch_stall_used. */
static enum x86_dispatch_stall_t x86_cpu_can_dispatch_thread(int core, int thread)
{
	struct list_t *uopq = X86_THREAD.uop_queue;
	struct x86_uop_t *uop;

	int rob_can_enqueue_alt; //Peilong

	/* Uop queue empty. */
	uop = list_get(uopq, 0);
	if (!uop)
		return !X86_THREAD.ctx || !x86_ctx_get_status(X86_THREAD.ctx, x86_ctx_running) ?
			x86_dispatch_stall_ctx : x86_dispatch_stall_uop_queue;

	rob_can_enqueue_alt = x86_rob_can_enqueue(uop);

	//=============== Peilong ======================//
	if (DESAccFlag || JacobiAccFlag || IDSIAccFlag || SegAccFlag ||
		SLAMCAccFlag || SLAMJAccFlag || SURFAccFlag || SWAccFlag)
	{
		if (DESAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (DES_delay < DESDelay)
			{
				DES_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("3DES Acc done\n");
			printf ("\n==============\n");
			DESAccFlag = 0;
			DES_delay  = 0;
		}

		else if (JacobiAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (Jacobi_delay < JacobiDelay)
			{
				Jacobi_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("Jacobi Acc done\n");
			printf ("\n==============\n");
			JacobiAccFlag = 0;
			Jacobi_delay  = 0;
		}

		else if (IDSIAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (IDSI_delay < IDSIDelay)
			{
				IDSI_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("IDSI Acc done\n");
			printf ("\n==============\n");
			IDSIAccFlag = 0;
			IDSI_delay  = 0;
		}

		else if (SegAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (Seg_delay < SegDelay)
			{
				Seg_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("Segm Acc done\n");
			printf ("\n==============\n");
			SegAccFlag = 0;
			Seg_delay  = 0;
		}

		else if (SLAMCAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (SLAMC_delay < SLAMCDelay)
			{
				SLAMC_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("SLAMC Acc done\n");
			printf ("\n==============\n");
			SLAMCAccFlag = 0;
			SLAMC_delay  = 0;
		}

		else if (SLAMJAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (SLAMJ_delay < SLAMJDelay)
			{
				SLAMJ_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("SLAMJ Acc done\n");
			printf ("\n==============\n");
			SLAMJAccFlag = 0;
			SLAMJ_delay  = 0;
		}

		else if (SURFAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (SURF_delay < SURFDelay)
			{
				SURF_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("SURF Acc done\n");
			printf ("\n==============\n");
			SURFAccFlag = 0;
			SURF_delay  = 0;
		}

		else if (SWAccFlag)
		{
			rob_can_enqueue_alt = 0;
			if (SW_delay < SWDelay)
			{
				SW_delay ++;
				goto aaa;
			}
			printf ("\n==============\n");
			printf ("SW  Acc  done\n");
			printf ("\n==============\n");
			SWAccFlag = 0;
			SW_delay  = 0;
		}
	}

#if 0
	if (syscallflag_gettimeofday == 1)
	{
		rob_can_enqueue_alt = 0;
		//printf("dispatch is stalled intentionally!");
		//printf("CPU cycle: %lld\t", x86_cpu->cycle);
		if (delay_time_gettimeofday < DELAY_TIME)
		{
			delay_time_gettimeofday ++;
			goto aaa;
		}
		syscallflag_gettimeofday = 0;
		delay_time_gettimeofday = 0;
	}

	else if (syscallflag_acc == 1)
	{
		rob_can_enqueue_alt = 0;
		//printf("dispatch is stalled intentionally!");
		//printf("CPU cycle: %lld\t", x86_cpu->cycle);
		if (delay_time_acc < DELAY_TIME)
		{
			delay_time_acc ++;
			goto aaa;
		}
		syscallflag_acc = 0;
		delay_time_acc = 0;
	}
#endif

	/* If iq/lq/sq/rob full, done */
//	if (!x86_rob_can_enqueue(uop))
aaa:if (!rob_can_enqueue_alt) //Peilong
		return x86_dispatch_stall_rob;
	if (!(uop->flags & X86_UINST_MEM) && !x86_iq_can_insert(uop))
		return x86_dispatch_stall_iq;
	if ((uop->flags & X86_UINST_MEM) && !x86_lsq_can_insert(uop))
		return x86_dispatch_stall_lsq;
	if (!x86_reg_file_can_rename(uop))
		return x86_dispatch_stall_rename;
	
	return x86_dispatch_stall_used;
}


static int x86_cpu_dispatch_thread(int core, int thread, int quant)
{
	struct x86_uop_t *uop;
	enum x86_dispatch_stall_t stall;

	while (quant)
	{
		/* Check if we can decode */
		stall = x86_cpu_can_dispatch_thread(core, thread);
		if (stall != x86_dispatch_stall_used)
		{
			X86_CORE.dispatch_stall[stall] += quant;
			break;
		}
	
		/* Get entry from uop queue */
		uop = list_remove_at(X86_THREAD.uop_queue, 0);
		assert(x86_uop_exists(uop));
		uop->in_uop_queue = 0;
		
		/* Rename */
		x86_reg_file_rename(uop);
		
		/* Insert in ROB */
		x86_rob_enqueue(uop);
		X86_CORE.rob_writes++;
		X86_THREAD.rob_writes++;
		
		/* Non memory instruction into IQ */
		if (!(uop->flags & X86_UINST_MEM))
		{
			x86_iq_insert(uop);
			X86_CORE.iq_writes++;
			X86_THREAD.iq_writes++;
		}
		
		/* Memory instructions into the LSQ */
		if (uop->flags & X86_UINST_MEM)
		{
			x86_lsq_insert(uop);
			X86_CORE.lsq_writes++;
			X86_THREAD.lsq_writes++;
		}
		
		/* Another instruction dispatched */
		X86_CORE.dispatch_stall[uop->specmode ? x86_dispatch_stall_spec : x86_dispatch_stall_used]++;
		X86_THREAD.dispatched[uop->uinst->opcode]++;
		X86_CORE.dispatched[uop->uinst->opcode]++;
		x86_cpu->dispatched[uop->uinst->opcode]++;
		quant--;

		/* Trace */
		x86_trace("x86.inst id=%lld core=%d stg=\"di\"\n",
			uop->id_in_core, uop->core);

	}

	return quant;
}


static void x86_cpu_dispatch_core(int core)
{
	int skip = x86_cpu_num_threads;
	int quant = x86_cpu_dispatch_width;
	int remain;

	switch (x86_cpu_dispatch_kind)
	{

	case x86_cpu_dispatch_kind_shared:
		
		do {
			X86_CORE.dispatch_current = (X86_CORE.dispatch_current + 1) % x86_cpu_num_threads;
			remain = x86_cpu_dispatch_thread(core, X86_CORE.dispatch_current, 1);
			skip = remain ? skip - 1 : x86_cpu_num_threads;
			quant = remain ? quant : quant - 1;
		} while (quant && skip);
		break;
	
	case x86_cpu_dispatch_kind_timeslice:
		
		do {
			X86_CORE.dispatch_current = (X86_CORE.dispatch_current + 1) % x86_cpu_num_threads;
			skip--;
		} while (skip && x86_cpu_can_dispatch_thread(core, X86_CORE.dispatch_current) != x86_dispatch_stall_used);
		x86_cpu_dispatch_thread(core, X86_CORE.dispatch_current, quant);
		break;
	}
}


void x86_cpu_dispatch()
{
	int core;
	x86_cpu->stage = "dispatch";
	X86_CORE_FOR_EACH
		x86_cpu_dispatch_core(core);
}
