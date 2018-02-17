#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4
#define LIMIT 10000000

void *threads(void *arg) 
{
	clock_t r;
	srand(r);
	float number = 1.5;
	int i;
	for(i = 1; i < LIMIT; i++)
		number = number*(rand()%10 + 1)*i;
}
int main()
{
	pthread_t t[NUM_THREADS];
	int i;
	for(i = 0; i < NUM_THREADS; i++)
		pthread_create(&t[i], NULL, threads, NULL);
	for(i = 0; i < NUM_THREADS; i++)
		pthread_join(t[i], NULL);
}
		
