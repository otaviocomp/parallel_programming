#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int n = 10000000;
	double start, finish;
	int threads = strtol(argv[1], NULL, 10);

	start = omp_get_wtime();
	#pragma omp parallel num_threads(threads)
	{
		int i;
		double my_sum = 0.0;
		for(i = 0; i < n; i++)
		{
			#pragma omp atomic
			my_sum += sin(i);
		}
	}
	finish = omp_get_wtime();
	printf("thread(s) = %d, time = %e\n", threads, finish - start);
}


