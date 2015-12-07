#include <stdio.h>
#include <math.h>
#include <pthread.h>

void *funcao(){
	printf("ESTOU ACA");
}

void main() {
	pthread_t ids[10];
	int i;

	for (i = 0; i <10; i++) {
		pthread_create(&ids[i], NULL, funcao, NULL);
	}

	for (i = 0; i <10; i++) {
		pthread_join(&ids[i], NULL);
	}
}