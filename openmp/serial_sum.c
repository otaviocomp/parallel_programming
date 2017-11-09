#include <stdio.h>
#include <time.h>

#define SIZE 100000000

int main()
{
	clock_t t;
	long int i, sum = 0;
	t = clock();
	for(i = 0; i < SIZE; i++)
		sum += i;
	t = clock() - t;
	printf("valor total = %ld time = %e\n", sum, (double)t/CLOCKS_PER_SEC);
}
