#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int ticketCount = 1000;
int temp;
sem_t test1;
sem_t test2;
 
void *sell1() 
{
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&test1);
	temp = ticketCount;
	pthread_yield();
	temp = temp - 1;
	pthread_yield();
	ticketCount = temp;
        printf("卖出票数：%d ,当前票数: %d \n",i, ticketCount);
        sem_post(&test2);
    }
    return NULL;
}
 
void *return1() 
{
    for (int i = 0; i < 100; i++)
    {
        sem_wait(&test2);
	temp = ticketCount;
	pthread_yield();
	temp = temp + 1;
        pthread_yield();
	ticketCount = temp;
        printf("退回票数：%d ,当前票数: %d \n", i,ticketCount);
        sem_post(&test1);
    }
    return NULL;
 
}
 
int main(int argc, char *argv[])
 
{
        sem_init(&test2, 0, 0);
	sem_init(&test1, 0, 1000);
	pthread_t p1, p2;
	pthread_create(&p1, NULL, sell1, NULL);
        pthread_create(&p2, NULL, return1,NULL);
        pthread_join(p1, NULL);
	pthread_join(p2, NULL);
        sem_destroy(&test1);
	sem_destroy(&test2);
        printf("最终票数为：%d\n",ticketCount);
	return 0;
}

