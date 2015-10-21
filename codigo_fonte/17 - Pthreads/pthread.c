#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#ifndef T
#define T 10
#endif

void * funcao(void *args) {
	int id = *(int *) args;
	printf("Alog mundo: %d\n", id);
	//printf("Alo mundo\n");
}

int main(int argc, char const *argv[])
{
	int i;
	int ntermos, nthreads;
	pthread_t *id;
	int *args;

	printf("Digite o numero de threads\n");
	scanf("%d", &nthreads);

	id = (pthread_t *)malloc(nthreads *sizeof(pthread_t));
	args = (int *)malloc(nthreads *sizeof(int));
	
	// printf("Digite o numero de termos\n");
	// scanf("%d", &ntermos);

	for (i = 0; i < nthreads; i++)
	{
		args[i] = i;
		pthread_create(&id[i], NULL, funcao, (void *)&args[i]);
	}

	for (i = 0; i < nthreads; i++)
	{
		pthread_join(id[i], NULL);
	}
	return 0;
}