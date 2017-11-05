#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
	int n, m, i; //n = rows; m = columns; 
	int comm_sz, rank;
	float *matrix, *vector, *vector_t, parcial, result, x;
	MPI_Datatype col, column;

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
	vector_t = malloc(n*sizeof(float));
	matrix = malloc(n*m*sizeof(float)); //matrix de entrada

	MPI_Type_vector(m, 1, m, MPI_FLOAT, &column);
	MPI_Type_commit(&column);
	
	if(rank == 0)
	{
		vector = malloc(m*sizeof(float));
		printf("matrix:\n");
		for(i = 0; i < n*m; i++)
			scanf("%f", &matrix[i]);
		printf("vector:\n");
		for(i = 0; i < m; i++)
			scanf("%f", &vector[i]);	
		for(i = 1; i < comm_sz; i++)
			MPI_Send(matrix + i, 1, column, i, 0, MPI_COMM_WORLD);
		//MPI_Scatter(matrix, 1, column, vector_t, 1, column, 0, MPI_COMM_WORLD); 
		MPI_Scatter(vector, 1, MPI_FLOAT, &x, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}
	else
	{
		MPI_Recv(matrix, 1, column, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Scatter(vector, 1, MPI_FLOAT, &x, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	}
	for(i = 0; i < n; i++)
		vector_t[i] = matrix[i*m];

	printf("\n\n--vector-- process %d\n", rank);
	fflush(stdout);
	for(i = 0; i < n; i++)
		printf("%f ", vector_t[i]);
	printf("\n");	

	for(i = 0; i < n; i++)
	{
		parcial = vector_t[i]*x;
		MPI_Reduce(&parcial, vector + i, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	}
		
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

