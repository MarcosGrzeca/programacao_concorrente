#include <pthread.h>

#define NTHREADS 5

void *funcao (void *args){
	printf("Hello World %i\n", pthread_self());
}

int main() {
	pthread_t tid[NTHREADS];
	int i;
	for ( i=0 ; i< NTHREADS; i++ )
		pthread_create( &tid[i], NULL, funcao, (void *)i );

	for ( i=0 ; i< NTHREADS; i++ )
		pthread_join( tid[i],NULL);

}