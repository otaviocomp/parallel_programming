#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
	int iterations, result;
	int threads = strtol(argv[1], NULL, 10);
	printf("number of iterations: ");
	scanf("%d", &iterations);

	#pragma omp parallel num_threads(threads)
	{
		int i, sum = 0;
		int rank = omp_get_thread_num();
		int size = omp_get_num_threads();
		int my_first = (iterations/threads)*rank;
		int my_last = my_first + iterations/threads;
		printf("thread %d: iterations: %d - %d\n", rank, my_first, my_last);
		for(i = my_first; i < my_last; i++)
			sum += i;
		#pragma omp critical
			result += sum;
	}
	printf("result = %d\n", result);
}


