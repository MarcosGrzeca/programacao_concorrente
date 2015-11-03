#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#ifndef CADEIRAS
#define CADEIRAS 5
#endif

#ifndef CLIENTES
#define CLIENTES 10
#endif

#ifndef BARBEIROS
#define BARBEIROS 1
#endif

sem_t customers;
sem_t barbers;
sem_t mutex;
int waiting = 0;

void * barber() {
	while (1) {
		sem_wait(&customers);
		sem_wait(&mutex);
		waiting = waiting - 1;
		sem_post(&barbers);
		sem_post(&mutex);
		printf("Cortando cabelo\n");
		sleep(rand()%10);
	}
}

void * customer() {
	sem_wait(&mutex);
	if (waiting < CADEIRAS) {
		waiting = waiting +1;
		sem_post(&customers);
		sem_post(&mutex);
		sem_wait(&barbers);
		printf("Sentado e servindo\n");
		sleep(rand()%3);
	} else{
		sem_post(&mutex);
		printf("Indo embora\n");
	}
}

int main(int argc, char const *argv[])
{
	int i;
	sem_init(&customers, 0, 0);
    sem_init(&barbers, 0, 0);
	sem_init(&mutex, 0, 1);    

	pthread_t ti_barbeiros[BARBEIROS];
	pthread_t ti_clientes[CLIENTES];

	for (i=0; i<BARBEIROS; i++){
	    pthread_create(&ti_barbeiros[i], NULL, barber, NULL);
    }

    for (i=0; i<CLIENTES; i++){
	    pthread_create(&ti_clientes[i], NULL, customer, NULL);
    }

    for (i=0; i<BARBEIROS; i++){
	    pthread_join(ti_barbeiros[i], NULL);
    }

    for (i=0; i<CLIENTES; i++){
	    pthread_join(ti_clientes[i], NULL);
    }

	    // sleep(30);
	/* code */
	return 0;
}