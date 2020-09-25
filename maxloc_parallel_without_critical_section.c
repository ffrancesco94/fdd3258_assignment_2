#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000
#define MAX_THREADS 32


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
		double mval;
		int mloc;

		typedef struct
		{
			double val;
			int loc;
			char pad[128];
		} tvals;

		tvals maxinfo[MAX_THREADS];
		start_time = omp_get_wtime();

		#pragma omp parallel shared(maxinfo)
		{
			int id = omp_get_thread_num();
			maxinfo[id].val = -1.0e30;
			#pragma omp for
			for (int j=0; j<N; j++)
			{
				if (x[j] > maxinfo[id].val)
				{
					maxinfo[id].val = x[j];
					maxinfo[id].loc = j;
				}
			}
		}
		mloc = maxinfo[0].loc;
		mval = maxinfo[0].val;
		for (int j=0; j<MAX_THREADS; j++)
		{
			if (maxinfo[j].val > mval)
			{
				mval = maxinfo[j].val;
				mloc = maxinfo[j].loc;
			}
		}
		run_time = omp_get_wtime() - start_time;
		printf("%d %f\\\\\n", sizes[i], run_time);
	}
	return 0;
}

	
