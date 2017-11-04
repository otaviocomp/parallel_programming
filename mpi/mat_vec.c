#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
	int n, m, i; //n = rows; m = columns
	int comm_sz, rank;
	float *matrix, *vector, *vector_t, parcial, result;

	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if(rank == 0)
	{
		printf("number of rows: ");
		fflush(stdout);
		scanf("%d", &n);
		printf("number of columns: ");
		fflush(stdout);
		scanf("%d", &m);
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// allocate vectors
	vector_t = malloc(m*sizeof(float));
	vector = malloc(m*sizeof(float));
	
	if(rank == 0)
	{
		matrix = malloc(n*m*sizeof(float)); //matrix de entrada
		printf("matrix:\n");
		for(i = 0; i < n*m; i++)
			scanf("%f", &matrix[i]);
		printf("vector:\n");
		for(i = 0; i < m; i++)
			scanf("%f", &vector[i]);
		MPI_Scatter(matrix, n, MPI_FLOAT, vector_t, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}
	else
		MPI_Scatter(matrix, n, MPI_FLOAT, vector_t, n, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(vector, m, MPI_FLOAT, 0, MPI_COMM_WORLD);

	parcial = 0.0;
	for(i = 0; i < m; i++)
		parcial = vector_t[i]*vector[i] + parcial;
	


	// operation 
	if(rank == 0)
		MPI_Gather(&parcial, 1, MPI_FLOAT, vector, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	else 
		MPI_Gather(&parcial, 1, MPI_FLOAT, vector, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		
	if(rank == 0)
	{
		int i, j;
		printf("\n--matrix--\n");
		fflush(stdout);
		for(i = 0; i < n; i++)
		{
			for(j = 0; j < m; j++)
				printf("%f ", matrix[i*m + j]);
			printf("\n");
		}
		printf("\n\n--vector--\n");
		fflush(stdout);
		for(i = 0; i < m; i++)
			printf("%f ", vector[i]);
		printf("\n");	
	}	

	MPI_Finalize();
	return 0;
}

