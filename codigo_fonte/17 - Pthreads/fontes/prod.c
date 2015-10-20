#include <pthread.h>

#define NTHREADS 5
#define TAM 100

pthread_mutex_t mutex; 
int vetor[TAM], prodtotal=0;

void *funcao (void *args){
	int ini, fim, parte, i, prodparc=0;
	ini = (int)args * (TAM/NTHREADS);
	fim = ini + (TAM/NTHREADS);
	for ( i=ini; i<fim ; i++ )	
		prodparc += vetor[i] * vetor[i];

	pthread_mutex_lock(&mutex);	
	prodtotal += prodparc;
	pthread_mutex_unlock(&mutex);	
}

int main() {
	pthread_t tid[NTHREADS];
	int i;
	
	pthread_mutex_init(&mutex,NULL);

	srand(time(NULL));
	for(i=0;i<TAM;i++)
		vetor[i] = rand()%10;

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_create( &tid[i], NULL, funcao, (void *)i);

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_join( tid[i], NULL);

	printf("Total: %i\n",prodtotal);

}