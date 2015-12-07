#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>  


#ifndef C
#define C 5
#endif

#ifndef P
#define P 4
#endif

#ifndef N
#define N 10
#endif

sem_t mutex;
sem_t vazio;
sem_t cheio;

int itens = 0;

void *produtor(void * args) {
	int id = (int)args;
	while (1) {
		sem_wait(&vazio);
		sem_wait(&mutex);
		printf("Produzindo itens\n");
		itens++;
		sem_post(&mutex);
		sem_post(&cheio);
		sleep(rand()%10);
	}
}

void *consumidor(void * args) {
	int id = (int)args;
	while (1) {
		sem_wait(&cheio);
		sem_wait(&mutex);
		itens--;
		printf("Consumindo itens\n");
		sem_post(&mutex);
		sem_post(&vazio);
		sleep(rand()%10);
	}
}

void main() {

	pthread_t produtores[P];
	pthread_t consumidores[C];

	sem_init(&mutex, 0, 1);
	sem_init(&vazio, 0, 1);
	sem_init(&cheio, 0, 0);
	int i;

	for (i = 0; i < P; ++i)
	{
			pthread_create(&produtores[i], NULL, produtor, NULL);
	}

	for (i = 0; i < C; ++i)
	{
			pthread_create(&consumidores[i], NULL, consumidor, NULL);
	}

	for (i = 0; i < P; ++i)
	{
			pthread_join(produtores[i], NULL);
	}

	for (i = 0; i < C; ++i)
	{
			pthread_join(consumidores[i], NULL);
	}

}