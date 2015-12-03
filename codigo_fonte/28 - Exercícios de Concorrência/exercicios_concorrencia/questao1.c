#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*-----------------------------------------------------*/

struct args {
	int id;
	int nthreads;
	int ntermos;
	double resultado;
};
typedef struct args ARGS;

/*-----------------------------------------------------*/
void * funcao (void * args){
	ARGS *p = (ARGS *) args;

	int id = p->id;
	int nthreads = p->nthreads;
	int ntermos = p->ntermos;
	int i;
	double parcial = 0; 
	
	for ( i=id ;  i<=ntermos ; i+=nthreads ){

		if ( i % 2 ){
			parcial += 1.0 / (2*i-1);
		}
		else {
			parcial -= 1.0 / (2*i-1);
		}	
	}

	p->resultado = parcial;
}
/*-----------------------------------------------------*/
int main(){
	pthread_t *id = NULL;
	int i, ntermos, nthreads;
	ARGS *argumentos = NULL;
	double total = 0;

	printf("Digite o numero de termos: ");
	scanf("%d",&ntermos);

	printf("Digite o numero de threads: ");
	scanf("%d",&nthreads);

	id = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	argumentos = (ARGS *)malloc(nthreads * sizeof(ARGS));

	for ( i=0; i<nthreads; i++ ){
		argumentos[i].id = i+1;
		argumentos[i].ntermos = ntermos;
		argumentos[i].nthreads = nthreads;
		argumentos[i].resultado = 0;		
		pthread_create(&id[i],NULL,funcao, (void *)&argumentos[i]);
	}

	for ( i=0; i<nthreads; i++){
		pthread_join(id[i],NULL);
		total += argumentos[i].resultado;
	}
	
	printf("PI= %.15f\n", 4 * total);
}
/*-----------------------------------------------------*/

