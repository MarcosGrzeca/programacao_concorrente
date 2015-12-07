#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef N
#define N 10
#endif

struct args
{
	int flag;
	char *str;
	int id;
};
typedef struct args ARGS;


void * funcao (void * args){
	ARGS *p = (ARGS *) args;
	int id = p->id;
	char *str = p->str;
	if (str[id] == str[strlen(str) - id - 1]) {
		p->flag = 1;
	} else {
		p->flag = 0;
	}
}

void main()
{
	char str[N];
	pthread_t *id = NULL;
	int i,nthreads;
	ARGS *argumentos = NULL;
	int flag = 1;
	int *ret;

	printf("Digite a string: ");
	gets(str);

	nthreads = strlen(str)/2;

	id = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
	argumentos = (ARGS *)malloc(nthreads * sizeof(ARGS));

	for (i = 0; i < nthreads; ++i)
	{
		argumentos[i].str = str;
		argumentos[i].id = i;
		argumentos[i].flag = 0;
		pthread_create(&id[i], NULL, funcao, (void *) &argumentos[i]);
	}

	for (i = 0; i < nthreads; ++i)
	{
		pthread_join(id[i], NULL);
		if (argumentos[i].flag == 0) {
			flag = 0;
		}
	}

	if (flag == 0) {
		printf("Nao eh\n");
	} else {
		printf("Eh\n");
	}


	
}
