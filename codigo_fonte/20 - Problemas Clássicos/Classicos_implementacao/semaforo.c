#include <stdio.h>    
#include <stdlib.h>   
#include <pthread.h>  
#include <semaphore.h>  

/*---------------------------------------------------------------------------*/
#define N 6

/*---------------------------------------------------------------------------*/
sem_t mutex;

/*---------------------------------------------------------------------------*/
void * funcao ( void *arg ){
	int id = *(int *) arg;

	sem_wait(&mutex);

	printf("Thread %d entrou na secao critica\n", id);

	sleep(rand()%10);
	sem_post(&mutex);

	printf("Thread %d saiu da secao critica\n", id);
}

/*---------------------------------------------------------------------------*/
int main(){
    
    pthread_t tid[N];
    int i, arg[N];

    sem_init(&mutex, 0, 2);    

    for (i=0; i<N; i++){
	    arg[i] = i;
	    pthread_create (&tid[i], NULL, funcao, (void *)&arg[i]);
    }

    for (i=0; i<N; i++){
	    pthread_join(tid[i], NULL);
    }

    sem_destroy(&mutex); 
} 

/*----------------------------------------------------------------------------*/


