#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void input(int *n, int rank);
void build_mpi_datatype(int *m, int n, MPI_Datatype *new);
void input_m(int *m, int n);
void print(int *m, int n);

int main()
{
	int rank, size, n;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	input(&n, rank); // receber valores 
	int *m = malloc(n*n*sizeof(int)); // aloca a matriz
	MPI_Datatype new; // criar novo tipo
	build_mpi_datatype(m, n, &new);
	if(rank == 0)
	{
		input_m(m, n);
		MPI_Send(m, 1, new, 1, 0, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(m, 1, new, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		print(m, n);
	}
	MPI_Type_free(&new);
	MPI_Finalize();
}

void input(int *n, int rank)
{
	if(rank == 0)
	{
		printf("digite o tamanho de n: ");
		fflush(stdout);
		scanf("%d", n);
		MPI_Send(n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else
		MPI_Recv(n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

void build_mpi_datatype(int *m, int n, MPI_Datatype *new)
{
	int *block_size = malloc(n*sizeof(int));
	int *distance_size = malloc(n*sizeof(int));
	distance_size[0] = 0;
	int i, j = n;
	for(i = 0; i < n; i++)
	{
		block_size[i] = j;
		j--;
	}
	for(i = 1; i < n; i++)
		distance_size[i] = i*n + i;
	MPI_Type_indexed(n, block_size, distance_size, MPI_INT, new);
	MPI_Type_commit(new);
}

void input_m(int *m, int n)
{
	printf("digite os elementos da matriz:\n");
	fflush(stdout);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", m[i*n + j]);
}

void print(int *m, int n)
{
	printf("\nmatriz:\n\n");
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf("%d ", m[i*n + j]);
		printf("\n");
	}
}
			
		
