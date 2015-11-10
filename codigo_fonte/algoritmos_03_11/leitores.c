#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#ifndef R
#define R 5
#endif

#ifndef W
#define W 5
#endif

sem_t mutex;
sem_t db;
int rc = 0;

void *reader() {
	while (1) {
		sem_wait(&mutex);
		rc = rc + 1;
		if (rc == 1) sem_wait(&db);
		sem_post(&mutex);
		//read_data_base();
		printf("Lendo\n");
		sem_wait(&mutex);
		rc = rc - 1;
		if (rc == 0) sem_post(&db);
		sem_post(&mutex);
		//use_data_read();
		sleep(rand()%3);
	}
}

void *writer() {
	int item;
	while (1) {
		//think_up_data();
		sem_wait(&db);
		//write_data_base();
		printf("Escrevendo\n");
		sem_post(&db);
		sleep(rand()%3);
	}
}

int main(int argc, char const *argv[])
{
	int i;
	sem_init(&mutex, 0, 1);
    sem_init(&db, 0, 1);

	pthread_t tir[R];
	pthread_t tiw[W];

	for (i=0; i<R; i++){
	    pthread_create(&tir[i], NULL, reader, NULL);
    }

    for (i=0; i<W; i++){
	    pthread_create(&tiw[i], NULL, writer, NULL);
    }

    for (i=0; i<R; i++){
	    pthread_join(tir[i], NULL);
    }

    for (i=0; i<W; i++){
	    pthread_join(tiw[i], NULL);
    }

	    // sleep(30);
	/* code */
	return 0;
}