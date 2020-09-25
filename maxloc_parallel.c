#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000


int main(int argc, char *argv[])
{
	int i;
	double x[N], start_time, run_time;
	int sizes[9] = {1, 2, 4, 8, 16, 20, 24, 28, 32};
	srand(time(0)); //seed
	for (i=0; i<N; i++)
	{
		x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
	}

	for (i=0; i<9; i++)
	{
		omp_set_num_threads(sizes[i]);
		double maxval = 0.0;
		int maxloc = 0;
		
		start_time = omp_get_wtime();

		#pragma omp parallel for
			for (int j=0; j<N; j++)
			{
				#pragma omp critical
				{
					if (x[j] > maxval)
					{
						maxval = x[j];
						maxloc = j;
					}
				}
			}
		run_time = omp_get_wtime() - start_time;
		printf("%d & %f\\\\\n", sizes[i], run_time);
	}
	return 0;
}

	
