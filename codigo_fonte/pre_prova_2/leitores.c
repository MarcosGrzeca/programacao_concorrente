#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>  

#define NESCRITORES 1
#define NLEITORES 3

int leitores = 0;
sem_t mutex;
sem_t db;

void * leitor(void * args) {
	while (1) {
		sem_wait(&mutex);
		leitores++;
		if (leitores == 1) {
			sem_wait(&db);
		}
		sem_post(&mutex);
		sleep(rand()%10);

		sem_wait(&mutex);
		leitores--;
		if (leitores == 0) {
			sem_post(&db);
		}
		sem_post(&mutex);

	}
}

void * escritor(void * args) {
	while (1) {
		sem_wait(&db);
		sleep(rand()%10);
		sem_post(&db);
		sleep(rand()%10);
	}
}

void main(int argc, char const *argv[])
{

	pthread_t escritores[NESCRITORES];
	pthread_t leitores[NLEITORES];
	
	sem_init(&mutex, 0, 1);
	sem_init(&db, 0, 1);
	int i;

	for (i = 0; i < NESCRITORES; i++) {
		pthread_create(&escritores[i], NULL, escritor, NULL);
	}

	for (i = 0; i < NLEITORES; i++) {
		pthread_create(&leitores[i], NULL, leitor, NULL);
	}

	for (i = 0; i < NESCRITORES; i++) {
		pthread_join(escritores[i], NULL);
	}

	for (i = 0; i < NLEITORES; i++) {
		pthread_join(leitores[i], NULL);
	}
}