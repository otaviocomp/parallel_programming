#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void get_dims(int *n, int *m, int rank);
void read_mat_vec(int n, int m, float *vector, float *vector_t, float *matrix, int rank);
void print_input(int n, int m, float *matrix, float *vector, int rank);

int main()
{
	int n, m; //n = rows; m = columns
	int comm_sz, rank;
	float *matrix, *vector, *vector_t;

	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	get_dims(&n, &m, rank);
	read_mat_vec(n, m, vector, vector_t, matrix, rank);
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

void read_mat_vec(int n, int m, float *vector, float *vector_t, float *matrix, int rank)
{
	// alocar vector_t (vetor de trabalho) e vector
	vector_t = malloc(m*sizeof(float));
	vector = malloc(m*sizeof(float));

	if(rank == 0)
	{
		matrix = malloc(n*m*sizeof(float)); //matrix de entrada
		int i;
		printf("matrix:\n");
		for(i = 0; i < n*m; i++)
			scanf("%f", &matrix[i]);
		printf("vector:\n");
		for(i = 0; i < m; i++);
			scanf("%f", &vector[i]);
	}
}


void print_input(int n, int m, float *matrix, float *vector, int rank)
{
	if(rank == 0)
	{
		int i;
		printf("\n--matrix--\n");
		for(i = 0; i < n*m; i++)
			printf("%f ", matrix[i]);
		printf("\n--vector--\n");
		for(i = 0; i < m; i++)
			printf("%f ", vector[i]);
		printf("\n");	
	}
}
