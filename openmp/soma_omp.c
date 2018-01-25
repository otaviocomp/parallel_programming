#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 1000000000

int main(int argc, char *argv[])
{
	clock_t t;
	long int total = 0;
	int threads = strtol(argv[1], NULL, 10);

	t = clock();
	#pragma omp parallel num_threads(threads)
	{ 
		long int i, soma = 0;
		int rank = omp_get_thread_num();
		int size = omp_get_num_threads();
		long int my_first = (SIZE/size)*rank;
		long int my_last = my_first + SIZE/size;
		for(i = my_first; i < my_last; i++)
			soma += i;
		#pragma omp critical
			total += soma;	
	}
	t = (clock() - t)/threads;
	printf("valor total = %ld\n executado no tempo = %e\n", total, (float)t/CLOCKS_PER_SEC);
}	
