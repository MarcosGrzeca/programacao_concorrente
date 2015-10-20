#include <pthread.h>

#define NTHREADS 5

pthread_mutex_t mutex; 
pthread_cond_t cond;
int barreira=0;


void *funcao (void *args){
	sleep((int)args*5);
	pthread_mutex_lock(&mutex);
	barreira++;
	
	if ( barreira < NTHREADS ){
		printf("Thread %i foi bloqueada\n",args);
		pthread_cond_wait(&cond,&mutex);
	}
	printf("Thread %i foi desbloqueada\n",args);
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex);
}

int main() {
	pthread_t tid[NTHREADS];
	int i;
	
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_create( &tid[i], NULL, funcao, (void *)i);

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_join( tid[i], NULL);

}