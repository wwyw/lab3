#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
 
char buf[10]={0};
 
void *worker1() {
	for ( int i = 0; i < 10; ) {
	scanf("%c",&buf[i]);
	getchar();
i++;
	i = i%10;
	}
	return NULL;
}
 
void *worker2() {
 
	for (int i = 0; i < 10; ) {
	printf("%c\n",buf[i]);
	sleep(1);
i++;
	i = i%10;
	}
	return NULL;
}
 
 
 
int main(int argc, char *argv[])
 
{	
	pthread_t p1, p2;
	pthread_create(&p1, NULL, worker1, NULL);
	pthread_create(&p2, NULL, worker2, NULL);
 
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
 
	return 0;
 
}

