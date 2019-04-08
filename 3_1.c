#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

sem_t *signalA = NULL;
sem_t *signalB = NULL;
sem_t *signalC = NULL;

int main(int argc, char *argv[])
{
    pid_t pid,pid1,pid2;
    
    signalA=sem_open("signalA",O_CREAT,0666,0);
    signalB=sem_open("signalB",O_CREAT,0666,0);
    signalC=sem_open("signalC",O_CREAT,0666,0);
    pid = fork();
    if(pid == 0)
    {
        sem_wait(signalA);
        printf("I am the process P2\n");
        sem_post(signalA);
        sem_post(signalB);
       
        pid1 = fork();
        if(pid1 == 0)
        {
            sem_wait(signalB);
            sem_wait(signalC);
            printf("I am the process P4\n");
        }
    }

    else if(pid>0)
    {
        printf("I am the process P1\n");
        sem_post(signalA);

        pid2 = fork();
     
        if(pid2 == 0)
        {
            sem_wait(signalA);
            printf("I am the process P3\n");
            sem_post(signalA);
            sem_post(signalC);
            return 0;

        }
    }

    sem_close(signalA);
    sem_close(signalB);
    sem_close(signalC);
    return 0;

}


