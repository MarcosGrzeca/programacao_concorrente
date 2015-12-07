/*--------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <pthread.h>

/*--------------------------------------------------------------*/
#define N 100000000
/*--------------------------------------------------------------*/

void * funcao(void *args){

	int i;
	
	for( i=0; i<N; i++){
		sqrt(pow(rand()%10,rand()%10));	
	}
}

/*--------------------------------------------------------------*/

int main(){
	
	pthread_t id1, id2;

	pthread_create(&id1,NULL,funcao,NULL);
	pthread_create(&id2,NULL,funcao,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	
}
/*--------------------------------------------------------------*/

