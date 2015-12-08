#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct args
{
	int id;
	int ntermos;
	int nthreads;
	double resultado;	
};

typedef struct args ARGS;

void * calcularPi(void * args) {
	ARGS *p = (ARGS *) args;
	int i;
	double resultado;
	for (i = p->id; i < p.ntermos; i += p.nthreads) {
		if (i % 2) {
			resultado += 1 / (i * 2 - 1);
		} else {
			resultado -= 1 / (i * 2 - 1);
		}
		
	}

	p->resultado = resultado;
}

int main(int argc, char const *argv[])
{
	
	int ntermos = 20, int nthreads = 10, int i;
	ARGS *argumentos = NULL;

	argumentos = (ARGS*)malloc(nthreads * sizeof(ARGS)));

	pthread_t ids[nthreads];

	for (i = 0; i < nthreads; i++)
	{
		argumentos[i].id = i +1;
		argumentos[i].ntermos = ntermos;
		argumentos[i].nthreads = nthreads;
		argumentos[i].resultado = 0;
		pthread_create(&ids[i], NULL, calcularPi, (void *) &argumentos[i]);
	}

	double total = 0;

	for (i = 0; i < nthreads; i++)
		pthread_join(ids[i], NULL);
		total += argumentos[i].resultado;
	}
	printf("PI= %.15f\n", 4 * total);
	return 0;
}