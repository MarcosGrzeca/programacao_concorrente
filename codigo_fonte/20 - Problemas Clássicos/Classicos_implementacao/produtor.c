#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>  

/*-----------------------------------------------------------------*/
#define N 5
#define P 1
#define C 4

/*-----------------------------------------------------------------*/
sem_t mutex; 
sem_t cheio;
sem_t vazio;

int item = 0;


/*-----------------------------------------------------------------*/
void *funcao_produtor(void *args){
	int id = (int)args;

	while(1){
		sem_wait(&vazio);
		sem_wait(&mutex);
			
		printf("Produtor %d produzindo item: %d\n", id, ++item);

		sem_post(&mutex);
		sem_post(&cheio);		
		sleep(rand()%10);
	}
}

/*-----------------------------------------------------------------*/
void *funcao_consumidor (void *args){

	int id = (int)args;

	while(1){
		sem_wait(&cheio);
		sem_wait(&mutex);

		printf("Consumidor %d removendo %d\n", id, item--);

		sem_post(&mutex);
		sem_post(&vazio);
		sleep(rand()%20);
	}
}

/*-----------------------------------------------------------------*/
int main() {
	pthread_t prod[P];
	pthread_t cons[C];
	int i;

	sem_init(&mutex, 0, 1);
        sem_init(&cheio, 0, 0);
	sem_init(&vazio, 0,N);    
    
	for ( i =0 ;i < P; i++){
		pthread_create(&prod[i], NULL, funcao_produtor, (void *) i);
	}

	for ( i =0 ;i < C; i++){
		pthread_create(&cons[i],NULL, funcao_consumidor, (void *) i);
	}
	
	for ( i =0 ;i < P; i++){
		pthread_join(prod[i],NULL);
	}

	for ( i =0 ;i < C; i++){
		pthread_join(cons[i],NULL);
	}

	sem_destroy(&mutex);
	sem_destroy(&cheio);
	sem_destroy(&vazio);
 
}
/*-----------------------------------------------------------------*/
