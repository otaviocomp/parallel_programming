#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define SIZE 10000000000

int main()
{
	clock_t t;
	long int total = 0;
	t = clock();
	//int threads = strtol(argv[1], NULL, 10);

	#pragma omp parallel
	{ 
		int rank = omp_get_thread_num();
		int size = omp_get_num_threads();
		long int i, soma = 0;
		long int my_first = (SIZE/size)*rank;
		long int my_last = my_first + SIZE/size;
		for(i = my_first; i < my_last; i++)
			soma += i;
		#pragma omp critical
			total += soma;	
	}
	t = clock()	- t;
	printf("valor total = %ld\n executado no tempo = %f\n", total, (float)t/CLOCKS_PER_SEC);
}	
