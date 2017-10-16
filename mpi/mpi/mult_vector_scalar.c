#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void input(int *n, int *escalar, int rank, int size, int *local_n); 
void preencher(int *vetor1, int *vetor2, int rank, int n);

int main()
{
	int n, escalar, local_n, i, soma_local = 0, resposta, size, rank;

	MPI_Init(NULL, NULL);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// entrada de dados
	input(&n, &escalar, rank, size, &local_n);

	// envia
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&local_n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&escalar, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// alocar os vetores. Todos os processos terão esses vetores
	int *vetor1 = malloc(n*sizeof(int));
	int *vetor2 = malloc(n*sizeof(int));
	int *vetor_local1 = malloc(local_n*sizeof(int));
	int *vetor_local2 = malloc(local_n*sizeof(int));
	
	// preencher os vetores
	preencher(vetor1, vetor2, rank, n);

	// scatter
	if(rank == 0)
	{
		MPI_Scatter(vetor1, local_n, MPI_INT, vetor_local1, local_n, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter(vetor2, local_n, MPI_INT, vetor_local2, local_n, MPI_INT, 0, MPI_COMM_WORLD);
		free(vetor1);
		free(vetor2);
	}
	else
	{
		MPI_Scatter(vetor1, local_n, MPI_INT, vetor_local1, local_n, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Scatter(vetor2, local_n, MPI_INT, vetor_local2, local_n, MPI_INT, 0, MPI_COMM_WORLD);
	}

	// calcular somas locais
	for(i = 0; i < local_n; i++)
	{
		vetor_local1[i] = vetor_local1[i]*escalar;
		vetor_local1[i] = vetor_local1[i]*vetor_local2[i];
		soma_local = vetor_local1[i] + soma_local; 
	}

	MPI_Reduce(&soma_local, &resposta, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0)
		printf("a resposta eh: %d\n", resposta);

	MPI_Finalize();	
}

void input(int *n, int *escalar, int rank, int size, int *local_n)
{
	if(rank == 0)
		{
			printf("digite o tamanho dos vetores: ");
			fflush(stdout);
			scanf("%d",n);
			printf("digite o valor do escalar: ");
			fflush(stdout);
			scanf("%d", escalar);
			*local_n = *n/size;
		}
}

void preencher(int *vetor1, int *vetor2, int rank, int n)
{
	int i;
	if(rank == 0)
	{
		printf("preencha o primeiro vetor:\n");
		for(i = 0; i < n; i++)
			scanf("%d", &vetor1[i]);
		printf("preencha o segundo vetor:\n");
		for(i = 0; i < n; i++)
			scanf("%d", &vetor2[i]);
	}
}
