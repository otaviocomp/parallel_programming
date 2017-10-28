#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void get_dims(int *n, int *m, int rank);
void allocate(int n, int m, double *vector, double *matrix, double *vector_t, int rank);	
void read_mat_vec(int n, int m, double *vector, double *matrix, int rank);
void print_input(int n, int m, double *matrix, double *vector, int rank);

int main()
{
	int n, m; //n = rows; m = columns
	int comm_sz, rank;
	double *matrix, *vector, *vector_t;

	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	get_dims(&n, &m, rank);
	allocate(n, m, vector, matrix, vector_t, rank);
	read_mat_vec(n, m, vector, matrix, rank);
	print_input(n, m, matrix, vector, rank);

	MPI_Finalize();
	return 0;
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

void allocate(int n, int m, double *vector, double *matrix, double *vector_t, int rank)
{
	vector = malloc(m*sizeof(double));
	vector_t = malloc(m*sizeof(double));
	if(rank == 0)
		matrix = malloc(n*m*sizeof(double));
}

void read_mat_vec(int n, int m, double *vector, double *matrix, int rank)
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


void print_input(int n, int m, double *matrix, double *vector, int rank)
{
	if(rank == 0)
	{
		int i = 0;
		printf("\n--matrix--\n");
		for(i = 0; i < n*m; i++)
			printf("%e ", matrix[i]);
		printf("\n--vector--\n");
		for(i = 0; i < m; i++)
			printf("%e ", vector[i]);
	}
}

