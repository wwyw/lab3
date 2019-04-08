#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int ticketCount = 1000;
int temp;
sem_t *test=NULL;
 
void *sell1() 
{
    for (int i = 0; i < 100; i++)
    {
	temp = ticketCount;
	pthread_yield();
	temp = temp - 1;
	pthread_yield();
	ticketCount = temp;
        printf("卖出票数：%d ,当前票数: %d \n",i, ticketCount);
    }
    return NULL;
}
 
void *return1() 
{
    for (int i = 0; i < 100; i++)
    {
	temp = ticketCount;
	pthread_yield();
	temp = temp + 1;
        pthread_yield();
	ticketCount = temp;
        printf("退回票数：%d ,当前票数: %d \n", i,ticketCount);
    }
    return NULL;
 
}
 
int main(int argc, char *argv[])
 
{
        test=sem_open("test",O_CREAT,0666,1);
	pthread_t p1, p2;
	pthread_create(&p1, NULL, sell1, NULL);
        pthread_create(&p2, NULL, return1,NULL);
        pthread_join(p1, NULL);
	pthread_join(p2, NULL);
        sem_close(test);
        printf("最终票数为：%d\n",ticketCount);
	return 0;
}

