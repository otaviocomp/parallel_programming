#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *arg){
	while(1)
	{
		printf("thread");
		sleep(1);
	}
}

int main(){
	pthread_t t;
	pthread_create(&t, NULL, thread, NULL);
	while(1)
	{
		printf("thread main\n");
		sleep(1);
	}
}
