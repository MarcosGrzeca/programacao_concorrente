#include "stdio.h"
#include "pthread.h"

#ifndef T
#define T 20
#endif

#ifndef N
#define N 10000
#endif

struct argumentos
{
	int *cont;
	pthread_mutex_t *mutex;
};

typedef struct argumentos ARGS;

void *funcao(void * args) {
	ARGS *a = (ARGS *)args;
	int i;
	int *cont = a->cont;
	pthread_mutex_t *mutex = a->mutex;
	for (i = 0; i < N; i++)
	{
		pthread_mutex_lock(mutex);
		(*cont)++;
		pthread_mutex_unlock(mutex);
	}
}

int main(int argc, char const *argv[])
{

	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_t id[T];
	int cont = 0;
	ARGS arg;

	arg.cont = &cont;
	arg.mutex = &mutex;

	int i;
	for (i = 0; i < T; i++)
	{
		pthread_create(&id[i], NULL, funcao, (void *) &arg);
	}

	for (i = 0; i < T; i++)
	{
		pthread_join(id[i], NULL);
	}
	printf("Cont %d\n", cont);
	/* code */
	return 0;
}