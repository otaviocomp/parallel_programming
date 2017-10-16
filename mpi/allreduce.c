#include <stdio.h>
#include <mpi.h>
#include <time.h>

#define SIZE_PROBLEM 1000000

int main()
{
	clock_t t;
	int soma = 0, my_first, my_last, tam, rank, i;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &tam);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	t = clock();
	my_first = (SIZE_PROBLEM / tam) * rank;
	my_last = my_first + SIZE_PROBLEM / tam;
	for(i = my_first; i < my_last; i++)
		soma = soma + i;
	int final;	
	MPI_Allreduce(&soma, &final, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	printf("resultado: %d\n", final);
	t = clock() - t;
	printf("o tempo de execucao foi: %f\n", (float)t / (float)CLOCKS_PER_SEC);
	MPI_Finalize();
}
