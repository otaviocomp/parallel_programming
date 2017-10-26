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

int i, j;

void *thread_function(void *arg);
pthread_mutex_t work_mutex;

int main() {
    int res;
	i = 1;
	clock_t t;
	srand(t); // randomico
    pthread_t a_thread; // pthread_t
    pthread_create(&a_thread, NULL, thread_function, NULL); //criar thread
	pthread_mutex_init(&work_mutex, NULL);
	// trilho 1
    while(1) 
	{
		printf("sou a thread MAIN, entrei no trilho %d\n", i);
		res = rand()%3 + 1;
		sleep(res);
		i++;
		if(i == 3)
			pthread_mutex_lock(&work_mutex);	
		if(i == 4)
		{
			i = 1;
			pthread_mutex_unlock(&work_mutex);
		}
    }
}

void *thread_function(void *arg) {
    int res;
	clock_t t;
	srand(t);
	j = 3;
	// trilho 2
	while(1)
	{
		printf("sou a thread FUNCTION, entrei no trilho %d\n", j);
		res = rand()%3 + 1;
		sleep(res);
		j++;
		if(j == 3)
			pthread_mutex_lock(&work_mutex);
		if(j == 4)
			pthread_mutex_unlock(&work_mutex);
		if(j == 6)
			j = 3;
	}
    pthread_exit(0);
}
