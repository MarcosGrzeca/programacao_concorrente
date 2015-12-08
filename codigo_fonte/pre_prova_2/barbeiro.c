#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <semaphore.h>

#ifndef CADEIRAS
#define CADEIRAS 5
#endif

#ifndef CLIENTES
#define CLIENTES 20
#endif

sem_t mutex;
sem_t barbeiros;
sem_t clientes;

int waiting = 0;

void *barbeiro(void *args) {
	while (1) {
		sem_wait(&clientes);
		sem_wait(&mutex);
		waiting = waiting-1;
		sem_post(&mutex);
		sem_post(&barbeiros);
		printf("Cortando cabelo\n");
		
		sleep(rand()%10);
	}
}

void *cliente(void *args) {
	sem_wait(&mutex);
	if (waiting < CADEIRAS) {
		waiting = waiting +1;
		sem_post(&clientes);
		sem_post(&mutex);
		sem_wait(&barbeiros);
		printf("Sentado e servindo\n");
		sleep(rand()%3);
	} else {
		sem_post(&mutex);
	}

}

void  main(int argc, char const *argv[])
{

	sem_init(&mutex, 0, 1);
	sem_init(&barbeiros, 0, 0);
	sem_init(&clientes, 0, 0);
	
	pthread_t ids[CLIENTES+1];
	int i;

	pthread_create(&ids[0], NULL, barbeiro, NULL);

	for (i = 1; i <= CLIENTES; i++)
	{
		pthread_create(&ids[i], NULL, cliente, NULL);
	}

	for (i = 1; i <= CLIENTES; i++)
	{
		pthread_join(ids[i], NULL);
	}

}