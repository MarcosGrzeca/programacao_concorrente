#include <pthread.h>

#define NTHREADS 5

void *funcao (void *args){
	printf("Hello World Thread %i\n", args);
}

int main() {
	pthread_t tid[NTHREADS];
	int i;
	for ( i=0 ; i< NTHREADS; i++ )
		pthread_create( &tid[i], NULL, funcao, (void *)i );

}