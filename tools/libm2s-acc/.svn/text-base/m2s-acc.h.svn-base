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


#ifndef M2S_ACC_H
#define M2S_ACC_H

//#include <jas_image.h>
//#include <jas_stream.h>

//#include <GL/gl.h>

/* System call for ACC runtime */
#define X86_ACC_SYS_CODE  330


/* List of ACC runtime calls */
enum x86_acc_call_t
{
	x86_acc_call_invalid,
#define X86_ACC_DEFINE_CALL(name, code) x86_acc_call_##name = code,
#include "/home/pli/multi2sim-4.0-hc/src/arch/x86/emu/acc.dat"
#undef X86_ACC_DEFINE_CALL
	x86_acc_call_count
};

#endif

