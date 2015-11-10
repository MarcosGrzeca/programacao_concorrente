#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#ifndef N
#define N 5
#endif

#ifndef P
#define P 2
#endif

#ifndef C
#define C 6
#endif

int buffer = 0;
sem_t mutex;
sem_t cheio;
sem_t vazio;

void insert_item(item) {
	buffer += item;
	printf("Produzindo %d\n", buffer);
	// buffer += 1;
}

void consume_item(item) {
	buffer += item;
	printf("Consumindo %d\n", buffer);
	// buffer -= 1;
}

int produce_item() {
	return 1;
}

int remove_item() {
	return -1;
}

void *produtor(void *args) {
	int item;
	// int i = 0;
	while (1) {
		// i++;
		sem_wait(&vazio);
		sem_wait(&mutex);
		item = produce_item();
		insert_item(item);
		sem_post(&mutex);
		sem_post(&cheio);
		sleep(rand()%3);
	}
}

void *conusmidor(void *args) {
	int item;
	// int i = 0;
	while (1) {
		// i++;
		sem_wait(&cheio);
		sem_wait(&mutex);
		item = remove_item();
		consume_item(item);
		sem_post(&mutex);
		sem_post(&vazio);
		sleep(rand()%3);
	}
}

int main(int argc, char const *argv[])
{
	int i, arg[P + C];
	sem_init(&mutex, 0, 1);
    sem_init(&cheio, 0, 0);
    sem_init(&vazio, 0, N);

	pthread_t tip[P];
	pthread_t tic[C];

	for (i=0; i<P; i++){
	    pthread_create(&tip[i], NULL, produtor, NULL);
    }

    for (i=0; i<C; i++){
	    pthread_create(&tic[i], NULL, conusmidor, NULL);
    }

    for (i=0; i<P; i++){
	    pthread_join(tip[i], NULL);
    }

    for (i=0; i<C; i++){
	    pthread_join(tic[i], NULL);
    }

	    // sleep(30);
	/* code */
	return 0;
}