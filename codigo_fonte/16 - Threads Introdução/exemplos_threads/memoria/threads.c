/*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*--------------------------------------------------------------*/
#define N 1024*1024*1024
#define TEMPO 30
/*--------------------------------------------------------------*/
void *funcao(){
	return;
}

/*--------------------------------------------------------------*/
int main(){
	pthread_t id;
	char *mem;

	mem = (char *)malloc(N*sizeof(char));

	if ( mem == NULL){
		printf("Erro em alocar a memoria\n");
		exit(0);
	}
	 
	pthread_create(&id,NULL,funcao,NULL);

	sleep(TEMPO);
	
	pthread_join(id,NULL);

	free(mem);
}
/*--------------------------------------------------------------*/

