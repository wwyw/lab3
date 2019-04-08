#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
 
char buf[10]={0};
sem_t test1;
sem_t test2;
 
void *worker1() {
	for ( int i = 0; i < 10; ) {
sem_wait(&test1);
	scanf("%c",&buf[i]);
	getchar();
i++;
	i = i%10;
sem_post(&test2);
	}
	return NULL;
}
 
void *worker2() {
 
	for (int i = 0; i < 10; ) {
sem_wait(&test2);
	printf("%c\n",buf[i]);
	sleep(1);
i++;
	i = i%10;
sem_post(&test1);
	}
	return NULL;
}
 
 
 
int main(int argc, char *argv[])
 
{	
sem_init(&test1, 0, 20);
	sem_init(&test2, 0, 0);
	pthread_t p1, p2;
	pthread_create(&p1, NULL, worker1, NULL);
	pthread_create(&p2, NULL, worker2, NULL);
 
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
sem_destroy(&test1);
	sem_destroy(&test2);
 
	return 0;
 
}

