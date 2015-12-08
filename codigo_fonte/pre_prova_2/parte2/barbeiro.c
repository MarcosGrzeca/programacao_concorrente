#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>

#ifndef B
#define B 2
#endif

#ifndef C
#define C 15
#endif

#ifndef CADEIRAS
#define CADEIRAS 5
#endif

sem_t barbeiro;
sem_t cliente;
sem_t mutex;
int clientesEspera = 0;


void * souBarbeiro(void * args) {
	while (1) {
		sem_wait(&cliente);
		sem_wait(&mutex);
		clientesEspera--;
		sem_post(&mutex);
		sem_post(&barbeiro);
		printf("Cortando cabelo\n");
		sleep(rand()%10);
	}
}

void * souCliente(void * args) {
	sem_wait(&mutex);
	if (clientesEspera < CADEIRAS) {
		clientesEspera++;
		sem_post(&mutex);
		sem_post(&cliente);
		sem_wait(&barbeiro);
		printf("Sentado e servindo\n");
		sleep(rand()%3);
	} else {
		sem_post(&mutex);
	}
}

void main(int argc, char const *argv[])
{

	sem_init(&mutex, 1);
	sem_init(&barbeiro, 0);
	sem_init(&cliente, 0);

	pthread_t clientes[C], barbeiros[B];
	int i;

	for (i = 0; i < B; ++i)
	{
		pthread_create(&barbeiros[i], NULL, souBarbeiro, NULL);
	}

	for (i = 0; i < C; ++i)
	{
		pthread_create(&clientes[i], NULL, souCliente, NULL);
	}

}