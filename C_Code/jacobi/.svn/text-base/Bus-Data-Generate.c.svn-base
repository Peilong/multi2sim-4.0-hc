#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void main ()
{
	int i, j;
	FILE *fp;
	fp = fopen("jacobi_data.h", "wb");

	fprintf(fp, "\nstatic const float a[128][128] = {\n");
	for (i=0; i<128; i++)
	{
		fprintf(fp,"{");
		for (j=0; j<128; j++)
		{
			fprintf(fp, "%f, ", (float)(rand()%1000));
		}
		fprintf(fp,"},");
		fprintf(fp,"\n");
	}
	fprintf(fp,"};\n\n");

	fprintf(fp, "\nstatic const float d[128] = {\n");
	for (i=0; i<128; i++)
	{
		fprintf(fp, "%f, ", (float)(rand()%1000));
		fprintf(fp,"\n");
	}
	fprintf(fp,"};");

	fclose(fp);
}

