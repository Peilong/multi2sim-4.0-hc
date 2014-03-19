/* csw_test.c -- Test the speed of the bit-parallel constrained Smith-Waterman algorithm for
                comparison with standard Smith-Waterman algorithm */
#include "smithwaterman.h"

/* Query Sequence = d1xpa_1 a.6.1.2 (134-210) from ASTRAL 1.67 40% */
void SmithWaterman(char aa[21], char q[STRLEN])
{
	long  j, d_loc, q_loc, H_temp[10], Carry, CarryNot, AgtB, AeqB, AgtBnot;
	long  q_index[STRLEN];
	long  H0[STRLEN][STRLEN], Hg0[STRLEN][STRLEN];
	long  H1[STRLEN][STRLEN], Hg1[STRLEN][STRLEN];
	long  H2[STRLEN][STRLEN], Hg2[STRLEN][STRLEN];
	long  H3[STRLEN][STRLEN], Hg3[STRLEN][STRLEN];
	long  H4[STRLEN][STRLEN], Hg4[STRLEN][STRLEN];
	long  H5[STRLEN][STRLEN], Hg5[STRLEN][STRLEN];
	long  H6[STRLEN][STRLEN], Hg6[STRLEN][STRLEN];
	long  H7[STRLEN][STRLEN], Hg7[STRLEN][STRLEN];
	long  H8[STRLEN][STRLEN], Hg8[STRLEN][STRLEN];
	long  H9[STRLEN][STRLEN], Hg9[STRLEN][STRLEN];

	/* Database increment and decrement values - random, just for timing */
	long d_inc = 1958837644, d_dec = 728749138;

	/* Convert residue characters to indices */
	for (q_loc=0; q_loc<77; q_loc++)
		for (j=0; j<20; j++)
			if (q[q_loc] == aa[j])
				q_index[q_loc] = j;


	/* Intialize H and Hg*/
	for (d_loc=0; d_loc<75+1; d_loc++) {
		H0[d_loc][0] = 0;
		H1[d_loc][0] = 0;
		H2[d_loc][0] = 0;
		H3[d_loc][0] = 0;
		H4[d_loc][0] = 0;
		H5[d_loc][0] = 0;
		H6[d_loc][0] = 0;
		H7[d_loc][0] = 0;
		H8[d_loc][0] = 0;
		H9[d_loc][0] = 0;
		Hg0[d_loc][0] = 0;
		Hg1[d_loc][0] = 0;
		Hg2[d_loc][0] = 0;
		Hg3[d_loc][0] = 0;
		Hg4[d_loc][0] = 0;
		Hg5[d_loc][0] = 0;
		Hg6[d_loc][0] = 0;
		Hg7[d_loc][0] = 0;
		Hg8[d_loc][0] = 0;
		Hg9[d_loc][0] = 0;
	}
	for (q_loc=1; q_loc<77+1; q_loc++) {
		H0[0][q_loc] = 0;
		H1[0][q_loc] = 0;
		H2[0][q_loc] = 0;
		H3[0][q_loc] = 0;
		H4[0][q_loc] = 0;
		H5[0][q_loc] = 0;
		H6[0][q_loc] = 0;
		H7[0][q_loc] = 0;
		H8[0][q_loc] = 0;
		H9[0][q_loc] = 0;
		Hg0[0][q_loc] = 0;
		Hg1[0][q_loc] = 0;
		Hg2[0][q_loc] = 0;
		Hg3[0][q_loc] = 0;
		Hg4[0][q_loc] = 0;
		Hg5[0][q_loc] = 0;
		Hg6[0][q_loc] = 0;
		Hg7[0][q_loc] = 0;
		Hg8[0][q_loc] = 0;
		Hg9[0][q_loc] = 0;
	}      

	/* Do scoring */
	for (d_loc=0; d_loc<75; d_loc++)
		for (q_loc=0; q_loc<77; q_loc++) {
			{

				/* Increment H(-1,-1) into H_temp */
				H_temp[0] = d_inc ^ H0[d_loc][q_loc];
				Carry = d_inc & H0[d_loc][q_loc];
				H_temp[1] = Carry ^ H1[d_loc][q_loc];
				Carry = Carry & H1[d_loc][q_loc];
				H_temp[2] = d_inc ^ H2[d_loc][q_loc];
				Carry = d_inc & H2[d_loc][q_loc];
				H_temp[3] = Carry ^ H3[d_loc][q_loc];
				Carry = Carry & H3[d_loc][q_loc];
				H_temp[4] = Carry ^ H4[d_loc][q_loc];
				Carry = Carry & H4[d_loc][q_loc];
				H_temp[5] = Carry ^ H5[d_loc][q_loc];
				Carry = Carry & H5[d_loc][q_loc];
				H_temp[6] = Carry ^ H6[d_loc][q_loc];
				Carry = Carry & H6[d_loc][q_loc];
				H_temp[7] = d_inc ^ H7[d_loc][q_loc];
				Carry = d_inc & H7[d_loc][q_loc];
				H_temp[8] = Carry ^ H8[d_loc][q_loc];
				Carry = Carry & H8[d_loc][q_loc];
				H_temp[9] = Carry ^ H9[d_loc][q_loc];
				Carry = Carry & H9[d_loc][q_loc];

				/* Saturate high H_temp */
				H_temp[0] = H_temp[0] | Carry;
				H_temp[1] = H_temp[1] | Carry;
				H_temp[2] = H_temp[2] | Carry;
				H_temp[3] = H_temp[3] | Carry;
				H_temp[4] = H_temp[4] | Carry;
				H_temp[5] = H_temp[5] | Carry;
				H_temp[6] = H_temp[6] | Carry;
				H_temp[7] = H_temp[7] | Carry;
				H_temp[8] = H_temp[8] | Carry;
				H_temp[9] = H_temp[9] | Carry;

				/* Decrement H_temp */
				H_temp[0] = d_dec ^ H_temp[0];
				Carry = d_dec & (~H_temp[0]);
				H_temp[1] = Carry ^ H_temp[1];
				Carry = Carry & (~H_temp[1]);
				H_temp[2] = Carry ^ H_temp[2];
				Carry = Carry & (~H_temp[2]);
				H_temp[3] = Carry ^ H_temp[3];
				Carry = Carry & (~H_temp[3]);
				H_temp[4] = Carry ^ H_temp[4];
				Carry = Carry & (~H_temp[4]);
				H_temp[5] = Carry ^ H_temp[5];
				Carry = Carry & (~H_temp[5]);
				H_temp[6] = Carry ^ H_temp[6];
				Carry = Carry & (~H_temp[6]);
				H_temp[7] = Carry ^ H_temp[7];
				Carry = Carry & (~H_temp[7]);
				H_temp[8] = Carry ^ H_temp[8];
				Carry = Carry & (~H_temp[8]);
				H_temp[9] = Carry ^ H_temp[9];
				Carry = Carry & (~H_temp[9]);

				/* Saturate low H_temp */
				CarryNot = ~Carry;
				H_temp[0] = H_temp[0] & CarryNot;
				H_temp[1] = H_temp[1] & CarryNot;
				H_temp[2] = H_temp[2] & CarryNot;
				H_temp[3] = H_temp[3] & CarryNot;
				H_temp[4] = H_temp[4] & CarryNot;
				H_temp[5] = H_temp[5] & CarryNot;
				H_temp[6] = H_temp[6] & CarryNot;
				H_temp[7] = H_temp[7] & CarryNot;
				H_temp[8] = H_temp[8] & CarryNot;
				H_temp[9] = H_temp[9] & CarryNot;

				/* Compare Hg(0,-1) to H_temp */
				AgtB = Hg0[d_loc+1][q_loc] & (~H_temp[0]);
				AeqB = ~(Hg0[d_loc+1][q_loc] ^ H_temp[0]);
				AgtB = ((Hg1[d_loc+1][q_loc] & (~H_temp[1])) & AeqB) | AgtB;
				AeqB = (~(Hg1[d_loc+1][q_loc] ^ H_temp[1])) & AeqB;
				AgtB = ((Hg2[d_loc+1][q_loc] & (~H_temp[2])) & AeqB) | AgtB;
				AeqB = (~(Hg2[d_loc+1][q_loc] ^ H_temp[2])) & AeqB;
				AgtB = ((Hg3[d_loc+1][q_loc] & (~H_temp[3])) & AeqB) | AgtB;
				AeqB = (~(Hg3[d_loc+1][q_loc] ^ H_temp[3])) & AeqB;
				AgtB = ((Hg4[d_loc+1][q_loc] & (~H_temp[4])) & AeqB) | AgtB;
				AeqB = (~(Hg4[d_loc+1][q_loc] ^ H_temp[4])) & AeqB;
				AgtB = ((Hg5[d_loc+1][q_loc] & (~H_temp[5])) & AeqB) | AgtB;
				AeqB = (~(Hg5[d_loc+1][q_loc] ^ H_temp[5])) & AeqB;
				AgtB = ((Hg6[d_loc+1][q_loc] & (~H_temp[6])) & AeqB) | AgtB;
				AeqB = (~(Hg6[d_loc+1][q_loc] ^ H_temp[6])) & AeqB;
				AgtB = ((Hg7[d_loc+1][q_loc] & (~H_temp[7])) & AeqB) | AgtB;
				AeqB = (~(Hg7[d_loc+1][q_loc] ^ H_temp[7])) & AeqB;
				AgtB = ((Hg8[d_loc+1][q_loc] & (~H_temp[8])) & AeqB) | AgtB;
				AeqB = (~(Hg8[d_loc+1][q_loc] ^ H_temp[8])) & AeqB;
				AgtB = ((Hg9[d_loc+1][q_loc] & (~H_temp[9])) & AeqB) | AgtB;

				/* MUX result into H_temp */
				AgtBnot = ~AgtB;
				H_temp[0] = (AgtB & Hg0[d_loc+1][q_loc]) | (AgtBnot & H_temp[0]);
				H_temp[1] = (AgtB & Hg1[d_loc+1][q_loc]) | (AgtBnot & H_temp[1]);
				H_temp[2] = (AgtB & Hg2[d_loc+1][q_loc]) | (AgtBnot & H_temp[2]);
				H_temp[3] = (AgtB & Hg3[d_loc+1][q_loc]) | (AgtBnot & H_temp[3]);
				H_temp[4] = (AgtB & Hg4[d_loc+1][q_loc]) | (AgtBnot & H_temp[4]);
				H_temp[5] = (AgtB & Hg5[d_loc+1][q_loc]) | (AgtBnot & H_temp[5]);
				H_temp[6] = (AgtB & Hg6[d_loc+1][q_loc]) | (AgtBnot & H_temp[6]);
				H_temp[7] = (AgtB & Hg7[d_loc+1][q_loc]) | (AgtBnot & H_temp[7]);
				H_temp[8] = (AgtB & Hg8[d_loc+1][q_loc]) | (AgtBnot & H_temp[8]);
				H_temp[9] = (AgtB & Hg9[d_loc+1][q_loc]) | (AgtBnot & H_temp[9]);

				/* Compare Hg(-1,0) to H_temp */
				AgtB = Hg0[d_loc][q_loc+1] & (~H_temp[0]);
				AeqB = ~(Hg0[d_loc][q_loc+1] ^ H_temp[0]);
				AgtB = ((Hg1[d_loc][q_loc+1] & (~H_temp[1])) & AeqB) | AgtB;
				AeqB = (~(Hg1[d_loc][q_loc+1] ^ H_temp[1])) & AeqB;
				AgtB = ((Hg2[d_loc][q_loc+1] & (~H_temp[2])) & AeqB) | AgtB;
				AeqB = (~(Hg2[d_loc][q_loc+1] ^ H_temp[2])) & AeqB;
				AgtB = ((Hg3[d_loc][q_loc+1] & (~H_temp[3])) & AeqB) | AgtB;
				AeqB = (~(Hg3[d_loc][q_loc+1] ^ H_temp[3])) & AeqB;
				AgtB = ((Hg4[d_loc][q_loc+1] & (~H_temp[4])) & AeqB) | AgtB;
				AeqB = (~(Hg4[d_loc][q_loc+1] ^ H_temp[4])) & AeqB;
				AgtB = ((Hg5[d_loc][q_loc+1] & (~H_temp[5])) & AeqB) | AgtB;
				AeqB = (~(Hg5[d_loc][q_loc+1] ^ H_temp[5])) & AeqB;
				AgtB = ((Hg6[d_loc][q_loc+1] & (~H_temp[6])) & AeqB) | AgtB;
				AeqB = (~(Hg6[d_loc][q_loc+1] ^ H_temp[6])) & AeqB;
				AgtB = ((Hg7[d_loc][q_loc+1] & (~H_temp[7])) & AeqB) | AgtB;
				AeqB = (~(Hg7[d_loc][q_loc+1] ^ H_temp[7])) & AeqB;
				AgtB = ((Hg8[d_loc][q_loc+1] & (~H_temp[8])) & AeqB) | AgtB;
				AeqB = (~(Hg8[d_loc][q_loc+1] ^ H_temp[8])) & AeqB;
				AgtB = ((Hg9[d_loc][q_loc+1] & (~H_temp[9])) & AeqB) | AgtB;

				/* MUX result into H(0,0) */
				AgtBnot = ~AgtB;
				H0[d_loc+1][q_loc+1] = (AgtB & Hg0[d_loc][q_loc+1]) | (AgtBnot & H_temp[0]);
				H1[d_loc+1][q_loc+1] = (AgtB & Hg1[d_loc][q_loc+1]) | (AgtBnot & H_temp[1]);
				H2[d_loc+1][q_loc+1] = (AgtB & Hg2[d_loc][q_loc+1]) | (AgtBnot & H_temp[2]);
				H3[d_loc+1][q_loc+1] = (AgtB & Hg3[d_loc][q_loc+1]) | (AgtBnot & H_temp[3]);
				H4[d_loc+1][q_loc+1] = (AgtB & Hg4[d_loc][q_loc+1]) | (AgtBnot & H_temp[4]);
				H5[d_loc+1][q_loc+1] = (AgtB & Hg5[d_loc][q_loc+1]) | (AgtBnot & H_temp[5]);
				H6[d_loc+1][q_loc+1] = (AgtB & Hg6[d_loc][q_loc+1]) | (AgtBnot & H_temp[6]);
				H7[d_loc+1][q_loc+1] = (AgtB & Hg7[d_loc][q_loc+1]) | (AgtBnot & H_temp[7]);
				H8[d_loc+1][q_loc+1] = (AgtB & Hg8[d_loc][q_loc+1]) | (AgtBnot & H_temp[8]);
				H9[d_loc+1][q_loc+1] = (AgtB & Hg9[d_loc][q_loc+1]) | (AgtBnot & H_temp[9]);

				/* Decrement by two H(0,0) into Hg(0,0) */
				Hg0[d_loc+1][q_loc+1] = H0[d_loc+1][q_loc+1];
				Hg1[d_loc+1][q_loc+1] = ~H1[d_loc+1][q_loc+1];
				Hg2[d_loc+1][q_loc+1] = Hg1[d_loc+1][q_loc+1] ^ H2[d_loc+1][q_loc+1];
				Carry = Hg1[d_loc+1][q_loc+1] & (~H2[d_loc+1][q_loc+1]);
				Hg3[d_loc+1][q_loc+1] = Carry ^ H3[d_loc+1][q_loc+1];
				Carry = Carry & (~H3[d_loc+1][q_loc+1]);
				Hg4[d_loc+1][q_loc+1] = Carry ^ H4[d_loc+1][q_loc+1];
				Carry = Carry & (~H4[d_loc+1][q_loc+1]);
				Hg5[d_loc+1][q_loc+1] = Carry ^ H5[d_loc+1][q_loc+1];
				Carry = Carry & (~H5[d_loc+1][q_loc+1]);
				Hg6[d_loc+1][q_loc+1] = Carry ^ H6[d_loc+1][q_loc+1];
				Carry = Carry & (~H6[d_loc+1][q_loc+1]);
				Hg7[d_loc+1][q_loc+1] = Carry ^ H7[d_loc+1][q_loc+1];
				Carry = Carry & (~H7[d_loc+1][q_loc+1]);
				Hg8[d_loc+1][q_loc+1] = Carry ^ H8[d_loc+1][q_loc+1];
				Carry = Carry & (~H8[d_loc+1][q_loc+1]);
				Hg9[d_loc+1][q_loc+1] = Carry ^ H9[d_loc+1][q_loc+1];
				Carry = Carry & (~H9[d_loc+1][q_loc+1]);

				/* Saturate low Hg(0,0) */
				CarryNot = ~Carry;
				Hg0[d_loc+1][q_loc+1] = Hg0[d_loc+1][q_loc+1] & CarryNot;
				Hg1[d_loc+1][q_loc+1] = Hg1[d_loc+1][q_loc+1] & CarryNot;
				Hg2[d_loc+1][q_loc+1] = Hg2[d_loc+1][q_loc+1] & CarryNot;
				Hg3[d_loc+1][q_loc+1] = Hg3[d_loc+1][q_loc+1] & CarryNot;
				Hg4[d_loc+1][q_loc+1] = Hg4[d_loc+1][q_loc+1] & CarryNot;
				Hg5[d_loc+1][q_loc+1] = Hg5[d_loc+1][q_loc+1] & CarryNot;
				Hg6[d_loc+1][q_loc+1] = Hg6[d_loc+1][q_loc+1] & CarryNot;
				Hg7[d_loc+1][q_loc+1] = Hg7[d_loc+1][q_loc+1] & CarryNot;
				Hg8[d_loc+1][q_loc+1] = Hg8[d_loc+1][q_loc+1] & CarryNot;
				Hg9[d_loc+1][q_loc+1] = Hg9[d_loc+1][q_loc+1] & CarryNot;

			}
		}
}
