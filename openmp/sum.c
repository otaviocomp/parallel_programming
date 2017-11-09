#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define SIZE 100000000

int main(int arcv, char *argv[])
{
	clock_t t;
	long int total = 0;
	int size;
	//int threads = strtol(argv[1], NULL, 10);

	t = clock();
	#pragma omp parallel reduction(+: total)
	{
		size = omp_get_num_threads();
		long int i, soma = 0;
		#pragma omp for
		for(i = 0; i < SIZE; i++)
			soma += i;
		total += soma;
	}
	t = (clock() - t)/size;
	printf("valor total = %ld\nexecutado no tempo = %e\n", total, (float)t/CLOCKS_PER_SEC);
}
