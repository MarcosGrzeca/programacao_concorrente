#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>  


sem_t mutex;
sem_t barr;


int a, b, c, d, cont = 0;

void barreira() {
	sem_wait(&mutex);
	cont++;
	if (cont == 2) {
		sem_post(&mutex);
		sem_post(&barr);
	} else {
		sem_post(&mutex);
		sem_wait(&barr);
	}

	sem_wait(&mutex);
	cont--;
	sem_post(&mutex);
}

void barreira() {
	sem_wait(&mutex);
	cont++;
	if (cont == 2) {
		sem_post(&mutex);
		sem_post(&barr);
	} else {
		sem_post(&mutex);
		sem_wait(&barr);
	}
	sem_wait(&mutex);
	cont--;
	sem_post(&mutex);
}

void *funcao(void *args) {
	b = a;

	barreira();
	// sem_wait(&mutex);
	a = a +2;
	// sem_post(&mutex);
	barreira();
}

void main() {
	pthread_t id;
	a = 3;

	sem_init(&mutex, 0, 1);
	sem_init(&barr, 0, 0);

	// sem_wait(&mutex);	
	pthread_create(&id, NULL, funcao, NULL);
	c = a + 1;
	// sem_post(&mutex);

	barreira();

	d = b + c;
	c = b + d;
	barreira();

	printf("Valores finais: %d %d %d %d\n", a, b, c, d);

	sem_destroy(&mutex);
	sem_destroy(&barr);
}