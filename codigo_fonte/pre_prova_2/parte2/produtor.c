#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>

int capacidade = 100;
int quantidade = 0;
sem_t mutex;
sem_t temProduzir;
sem_t temConsumir;

void * produzir(void * args) {
	int id = (int)args;
	while (1) {
		sem_wait(&temProduzir);
		sem_wait(&mutex);
		quantidade++;
		printf("Produzindo %i \n", id);
		sem_post(&mutex);
		sem_post(&temConsumir);
	}
}

void * consumir(void * args) {
	int id = (int)args;
	while (1) {
		sem_wait(&temConsumir);
		sem_wait(&mutex);
		quantidade--;
		printf("Consumindo %i \n", id);
		sem_post(&mutex);
		sem_post(&temProduzir);
	}
}


int main(int argc, char const *argv[])
{
	sem_init(&mutex, 0, 1);
	sem_init(&temProduzir, 0, 1);
	sem_init(&temConsumir, 0, 0);

	pthread_t consumidores[5];
	pthread_t produtores[5];
	int i;
	
	for (i = 0; i < 5; i++) {
		pthread_create(&produtores[i], NULL, produzir, (void *) i);
	}

	for (i = 0; i < 5; i++) {
		pthread_create(&consumidores[i], NULL, consumir, (void *) i);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(produtores[i], NULL);
	}

	for (i = 0; i < 5; i++) {
		pthread_join(consumidores[i], NULL);
	}
	
	/* code */
	return 0;
}