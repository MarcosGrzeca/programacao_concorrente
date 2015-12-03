#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/*-----------------------------------------------------*/
#define N 100
/*-----------------------------------------------------*/
struct args {
	int id;
	char *str;
};
typedef struct args ARGS;

/*-----------------------------------------------------*/
void * funcao (void * args){
	ARGS *p = (ARGS *) args;
	int *ret = (int *)malloc(sizeof(int));

	int i = p->id;
	char *str = p->str;

	if ( str[i] == str[strlen(str)-1-i] ){
		*ret = 1;
	}
	else {
		*ret = 0;
	}
	pthread_exit((void *)ret);
}
/*-----------------------------------------------------*/
int main(){
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

	for ( i=0; i<nthreads; i++ ){
		argumentos[i].id = i;
		argumentos[i].str = str;
		pthread_create(&id[i], NULL, funcao, (void *)&argumentos[i]);
	}


	for ( i=0; i<nthreads; i++){
		pthread_join(id[i],(void **)&ret);
		flag &= *ret;
	}

	if ( flag ){
		printf("A palavra %s e palindrome\n", str);
	}
	else{
		printf("A palavra nao %s e palindrome\n", str);
	}
	
}
/*-----------------------------------------------------*/

