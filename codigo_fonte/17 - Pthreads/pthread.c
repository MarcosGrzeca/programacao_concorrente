#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"

#ifndef T
#define T 10
#endif

struct argumentos
{
	int id;
	int nthreads;
	int ntermos;
	double resultado;
};

typedef struct argumentos ARGS;

double fatorial(int n) {
	int i;
	double f = 1;
	for (i = 1; i <= n; i++)
	{
		f *= i;
	}
	return f;
}

void * funcao(void *args) {
	ARGS *p = (ARGS *) args;
	int id = p->id;
	int ntermos = p->ntermos;
	int nthreads = p->nthreads;
	int i;
	double res = 0;
	for (i = id; i <= ntermos; i+= nthreads) {
		res += 1/fatorial(i);
	}
	p->resultado = res;
}

int main(int argc, char const *argv[])
{
	int i;
	int ntermos, nthreads;
	pthread_t *id;
	double total = 0;
	ARGS *args;

	printf("Digite o numero de threads\n");
	scanf("%d", &nthreads);

	id = (pthread_t *)malloc(nthreads *sizeof(pthread_t));
	args = (ARGS *)malloc(nthreads *sizeof(ARGS));
	
	printf("Digite o numero de termos\n");
	scanf("%d", &ntermos);

	for (i = 0; i < nthreads; i++)
	{
		args[i].id = i;
		args[i].nthreads = nthreads;
		args[i].ntermos = ntermos;
		args[i].resultado = 0;
		pthread_create(&id[i], NULL, funcao, (void *)&args[i]);
	}

	for (i = 0; i < nthreads; i++)
	{
		pthread_join(id[i], NULL);
		total += args[i].resultado;
	}
	printf("Total %f\n", total);
	return 0;
}