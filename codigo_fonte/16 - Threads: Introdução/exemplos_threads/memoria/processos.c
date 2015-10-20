/*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------*/
#define N 1024*1024*1024
#define TEMPO 30
/*--------------------------------------------------------------*/
int main(){
	int id;
	char *mem;
	
	mem = (char *) malloc(N*sizeof(char));

	if ( mem == NULL){
		printf("Erro em alocar a memoria\n");
		exit(0);
	}

	id = fork();

	sleep(30);

	wait(NULL);

}
/*--------------------------------------------------------------*/

