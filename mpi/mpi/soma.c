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
	if(rank == 0)
		t = clock();
	my_first = (SIZE_PROBLEM / tam) * rank;
	my_last = my_first + SIZE_PROBLEM / tam;
	for(i = my_first; i < my_last; i++)
		soma = soma + i;
	if(rank != 0)
		MPI_Send(&soma, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); 
	else
	{
		int final;
		final = soma;
		for(i = 1; i < tam; i++)
		{
			MPI_Recv(&soma, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			final = final + soma;
		}
		printf("resultado: %d\n", final);
		t = clock() - t;
		printf("o tempo de execucao foi: %f\n", (float)t / (float)CLOCKS_PER_SEC);
	}
	MPI_Finalize();
}
