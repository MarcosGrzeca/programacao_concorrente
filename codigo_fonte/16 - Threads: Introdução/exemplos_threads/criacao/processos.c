/*--------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>

/*--------------------------------------------------------------*/
#define N 10000
/*--------------------------------------------------------------*/
int main(){
	int i, id;

	for( i=0; i<N; i++){
		id = fork();
		if ( id == 0 ){
			break;
		}
		waitpid(id,NULL,0);
	}
}
/*--------------------------------------------------------------*/

