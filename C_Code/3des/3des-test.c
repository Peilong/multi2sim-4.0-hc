//============== jacobi-smithwaterman.c =================//

//----------- I n c l u d e s ---------------------------//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "des.h"

int main(int argc, char *argv[]) 
{

	accPrintCycle();
	int i, j, u, v;
	des_context ctx;
	des3_context ctx3;
	int iter;
	unsigned char buf[8 * 1024];
	long loop=0;

	while (1)
	{
		for( i = 0; i < 2; i++ )
		{
			u = 0;
			v = i & 1;

			//printf( "  DES%c-EBC-%3d (%s): ",
			//( u == 0 ) ? ' ' : '3', 64 + u * 64,
			//( v == 0 ) ? "enc" : "dec" );

			for(iter=0; iter<1024; ++iter)
			memcpy( buf + iter*8, DES3_init, 8 );

			if( u == 0 )
			des_set_key( &ctx,  (unsigned char *) DES3_keys );

			if( u == 1 )
			des3_set_2keys( &ctx3, (unsigned char *) DES3_keys );

			if( u == 2 )
			des3_set_3keys( &ctx3, (unsigned char *) DES3_keys );

			for( j = 0; j < 1; j++ )
			{
				if( u == 0 )
				{
					if( v == 0 ) des_encrypt( &ctx, buf, buf );
					if( v == 1 ) des_decrypt( &ctx, buf, buf );
				}
				else
				{
					if( v == 0 ) des3_encrypt( &ctx3, buf, buf );
					if( v == 1 ) des3_decrypt( &ctx3, buf, buf );
				}
			}
		}
		printf("Loop: %lu\n", loop++);

	}
	accPrintCycle();
	return 1;
}


