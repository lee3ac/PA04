/*GROUP 6 - Sean Hurley, Andrew Lee*/

#include "wrappers.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

//test test
pid_t Fork(void)
{
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork failed");
        exit(-1);
    }
    return id;
}

void unix_error(char *msg)
{
    printf("unix error:%s\n", msg);
}

int Shmget(key_t key, size_t size, int shmflg)
{
    int ret = shmget(key, size, shmflg);
    if(ret < 0)
    {
        printf("failed to get shared memory\n");
        perror("reason");
        exit(-1);
    }
    return ret;  
}

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
    if(shmat(shmid, shmaddr, shmflg) == (void*) -1)
    {
        perror("Failed to attach shmem reason: ");
    }       
}

int Shmdt(const void *shmaddr) 
{
	int ret = shmdt(shmaddr);
    if(ret == -1)
    {
        perror("Failed to attach shared mem");
    }
    return ret;
}

sem_t *Sem_open( const char *name, int oflag, mode_t mode, unsigned int value )
{      
    sem_t *mutex;
    mutex = sem_open(name, oflag, mode, value);
    if (mutex == SEM_FAILED) { perror("sem_open failed"); exit(-1); }
    return mutex;  
}

sem_t *Sem_open2( const char *name, int oflag )
{
	sem_t *mutex;
	mutex = sem_open(name, oflag);
    if (mutex == SEM_FAILED) { perror("sem_open2 failed"); exit(-1); }
    return mutex;
}


int Sem_close( sem_t *sem )
{
    int ret = sem_close(sem);
    if (ret < 0)
    {
        perror("sem_close failed");
        exit(-1);
    }    
    return ret;
}

int Sem_unlink( const char *name )
{
    int ret = sem_unlink(name);
    if (ret < 0)
    {
        perror("sem_unlink failed");
        exit(-1);
    }  
    return ret;
}

int Sem_wait( sem_t *sem ) 
{
    int ret = sem_wait(sem);
    if(ret < 0) {perror("sem_open failed"); exit(-1);}
    return ret;
}


int Sem_post( sem_t *sem ) 
{

    int ret = sem_post(sem);
    if(ret < 0){perror("sem_open failed"); exit(-1);}
    return ret;
}


int Sem_init( sem_t *sem, int pshared, unsigned int value ) 
{
    int ret = sem_init(sem, pshared, value); 
    {
        perror("sem_init failed");
        exit(-1);
    } 
    return ret; 
}


int Sem_destroy( sem_t *sem ) 
{
    int ret  = sem_destroy(sem);
    {
        perror("sem_destroy failed");
        exit(-1);
    }  
    return ret;
}

int Msgget( key_t key, int msgflg )
{
    int ret = msgget(key, msgflg);
    if(ret < 0){perror("msgget failed"); exit(-1);}    
    return ret;
}




void Pthread_join(pthread_t tid, void **thread_return){

    int code = pthread_join(tid, thread_return);
    if(code != 0 ){
        perror("failed to join thread\n");
        exit(-1);
    }

}
void Pthread_create(pthread_t *tidp, pthread_attr_t *attrp,
                    void * (*routine)(void*), void *argp){
     
     int code = pthread_create(tidp, attrp, routine, argp);
     if(code != 0){
        perror("afailed to create thread\n");
        exit(-1);
     }
                    
    }

