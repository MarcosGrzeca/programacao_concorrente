#include <stdio.h>
#include <math.h>
#include <pthread.h>

struct args {
	int id;
	int termos;
	int threads;
	int resultado;
};


typedef struct args ARGS;

void *funcao (void * args) {
	ARGS *p = (ARGS *) args;

	int id = p->id;
	int termos = p->termos;
	int threads = p->threads;
	int i;
	double resultado;

	for (i = id; i <= termos; i+= threads) {
		if (i % 2) {
			resultado += 1/(i * 2 -1);
		} else {
			resultado -= 1/(i * 2 -1);
		}
	}

	p->resultado = resultado;
}

void main() {

	pthread_t id[3];
	int i, termos = 10, threads = 3;
	ARGS *argumentos = NULL;
	double total;

	argumentos = (ARGS *)malloc(threads * sizeof(ARGS));

	for (i = 0; i < threads; i++) {
		argumentos[i]->id = i + 1; 
		argumentos[i]->termos = termos;
		argumentos[i]->threads = threads;
		pthread_create(&id[i], NULL, funcao, (void *) &argumentos[i]);
	}

	for (i = 0; i < threads; i++) {
		pthread_join(id[i],NULL);
		total += argumentos[i]->resultado;
	}

	printf("%.15f\n", 4 * total);



}