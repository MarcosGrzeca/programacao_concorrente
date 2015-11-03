#include <stdio.h>
#include <pthread.h>  
#include <semaphore.h>  

/*-----------------------------------------------------------------*/
#define NESCRITORES 1
#define NLEITORES 3

/*-----------------------------------------------------------------*/
sem_t mutex; 
sem_t db;
int nleitores=0;

/*-----------------------------------------------------------------*/
void *funcao_escritor (void *args){
	int id = *(int *)args;

	while(1){
		sem_wait(&db);
		printf("Escritor %i Acessando a base\n",id);
		sleep(rand()%10);
		printf("Escritor %i Saindo da base\n",id);
		sem_post(&db);		
		sleep(rand()%10);
	}
}

/*-----------------------------------------------------------------*/
void *funcao_leitor (void *args){

	int id = *(int *)args;

	while(1){
		sem_wait(&mutex);
		nleitores++;
		if (nleitores == 1){
			sem_wait(&db);
		}
		sem_post(&mutex);

		printf("Leitor %i Acessando a base\n",id);
		sleep(rand()%10);
		printf("Leitor %i Saindo da base\n",id);
		
		sem_wait(&mutex);
		nleitores--;
		if (nleitores == 0)
			sem_post(&db);
		sem_post(&mutex);

		sleep(rand()%10);
	}
}

/*-----------------------------------------------------------------*/
int main() {
	int i, leit[NLEITORES], esc[NESCRITORES];
	pthread_t leitores[NLEITORES];
	pthread_t escritores[NESCRITORES];

	sem_init(&mutex, 0, 1);
        sem_init(&db, 0, 1);    
    
	for ( i =0 ;i < NESCRITORES; i++){
		esc[i] = i;
		pthread_create(&escritores[i], NULL, funcao_escritor, (void *) &esc[i]);
	}

	for ( i =0 ;i < NLEITORES; i++){
		leit[i] = i;
		pthread_create(&leitores[i],NULL,funcao_leitor, (void *)&leit[i]);
	}
	
	for ( i =0 ;i < NESCRITORES; i++){
		pthread_join(escritores[i],NULL);
	}

	for ( i =0 ;i < NLEITORES; i++){
		pthread_join(leitores[i],NULL);
	}

	sem_destroy(&mutex);
	sem_destroy(&db); 
}
/*-----------------------------------------------------------------*/
