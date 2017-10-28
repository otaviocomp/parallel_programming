#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void get_dims(int *n, int *m, int rank);
void allocate(int n, int m, double *vector, double *matrix);	
void read(int n, int m, double *vector, double *matrix, int rank);

int main()
{
	int n, m; //n = rows; m = columns
	int comm_sz, rank;
	double *matrix, *vector;

	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	get_dims(&n, &m, rank);
	allocate(n, m, vector, matrix);
	read(n, m, vector, matrix, rank);

	MPI_Finalize();
}

void get_dims(int *n, int *m, int rank)
{
	if(rank == 0)
	{
		printf("number of rows: ");
		fflush(stdout);
		scanf("%d", n);
		printf("number of columns: ");
		fflush(stdout);
		scanf("%d", m);
	}
}

void allocate(int n, int m, double *vector, double *matrix)
{
	vector = malloc(m*sizeof(double));
	matrix = malloc(n*m*sizeof(double));
}
		
void read(int n, int m, double *vector, double *matrix, int rank)
{
	if(rank == 0)
	{
		int i = 0;
		printf("matrix:\n");
		for(i = 0; i < n*m; i++)
			scanf("%e", matrix[i]);
		printf("vector:\n");
		for(i = 0; i < m; i++);
			scanf("%e", vector[i]);
	}
}
