#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000


int main(int argc, char *argv[])
{
	int i;
	double x[N], start_time, run_time;
	srand(time(0)); //seed
	for (i=0; i<N; i++)
	{
		x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
	}

	for (i=0; i<32; i++)
	{
		double maxval = 0.0;
		int maxloc = 0, j;
		
		start_time = omp_get_wtime();
		for (j=0; j<N; j++)
		{
			if (x[j] > maxval)
			{
				maxval = x[j];
				maxloc = j;
			}
		}
		run_time = omp_get_wtime() - start_time;
		printf("%f\n", run_time);
	}
	return 0;
}

	
