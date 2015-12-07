#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct args {
	int id;
	int threads;
	int termos;
	double resultado;
};
typedef struct args ARGS;

void *funcao (void * args) {
	ARGS *p = (ARGS *) args;

	int id = p->id;
	int termos = p->termos;
	int threads = p->threads;
	int i;
	double parcial = 0;

	for (i = id; i <= termos; i+= threads) {
		if (i % 2) {
			parcial += 1.0/(i * 2 -1);
		} else {
			parcial -= 1.0/(i * 2 -1);
		}
	}
	p->resultado = parcial;
}

void main() {

	pthread_t *id = NULL;
	int i, termos = 40, threads = 5;
	ARGS *argumentos = NULL;
	double total = 0;

	argumentos = (ARGS *)malloc(threads * sizeof(ARGS));
	id = (pthread_t *)malloc(threads * sizeof(pthread_t));

	for (i = 0; i < threads; i++) {
		argumentos[i].id = i + 1; 
		argumentos[i].termos = termos;
		argumentos[i].threads = threads;
		argumentos[i].resultado = 0;
		pthread_create(&id[i], NULL, funcao, (void *) &argumentos[i]);
	}

	for (i = 0; i < threads; i++) {
		pthread_join(id[i],NULL);
		total += argumentos[i].resultado;
	}

	printf("PI= %.15f\n", 4 * total);



}