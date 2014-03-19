#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char random_char_gen()
{
	unsigned char a = (unsigned char) (rand() & 0x00ff);
	return a;	
}

void main ()
{
	int i, j;
	FILE *fp;
	fp = fopen("seg_bus.h", "wb");

	fprintf(fp, "\nstatic const float Bus_A[] = {\n");
	for (i=0; i<512; i++)
	{
		for (j=0; j<512; j++)
		{
			fprintf(fp, "%d, ", random_char_gen());
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"};\n\n");

	fprintf(fp, "\nstatic const float Bus_B[] = {\n");
	for (i=0; i<512; i++)
	{
		for (j=0; j<512; j++)
		{
			fprintf(fp, "%d, ", random_char_gen());
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"};");

	fclose(fp);
}

