#include <pthread.h>

#define NTHREADS 5

pthread_mutex_t mutex; 

void *funcao (void *args){
	pthread_mutex_lock(&mutex);
	printf("Hello World %i\n",args);
	sleep(5);
	pthread_mutex_unlock(&mutex);
}

int main() {
	pthread_t tid[NTHREADS];
	int i;
	
	pthread_mutex_init(&mutex,NULL);

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_create( &tid[i], NULL, funcao, (void *)i);

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_join( tid[i], NULL);

}