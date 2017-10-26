//
//  thread7.cpp
//  
//
//  Created by Affonso on 25/10/16.
//
//

// #include "thread7.hpp"

// Programa que sincroniza threads utilizando-se mutexes
// Para compilá-lo utilise: g++ -o thread7 thread7.cpp -lpthread


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *thread_function(void *arg);

int main() {
	printf("porra");
    int res;
	int i;
	void *j;
	clock_t t;
	srand(t);
    pthread_t a_thread;
    pthread_create(&a_thread, NULL, thread_function, j);
   	printf("foda-se");
	i = 1;
    while(1) 
	{
		printf("sou a thread main, entrei no trilho %d", i);
		res = rand()%3 + 1;
		sleep(res);
		i++;
		if(res == 4)
			i = 1;
    }
    printf("\nMAIN() --> Esperando a thread terminar...\n");
    printf("MAIN() --> Thread foi juntada com sucesso\n");
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int res;
	clock_t t;
	srand(t);
	int *j = (int*)arg;
	*j = 3;
	while(1)
	{
		printf("sou a thread, entrei no trilho %d", *j);
		res = rand()%3 + 1;
		sleep(res);
		*j++;
		if(res == 6)
			*j = 3;
	}
    pthread_exit(0);
}
