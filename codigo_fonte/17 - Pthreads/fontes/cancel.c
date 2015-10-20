#include <pthread.h>

void *funcao (void *args){
	while(1)
		printf("Hello World\n");
}

int main() {
	pthread_t tid;
	pthread_create( &tid, NULL, funcao, NULL );
	sleep(1);
	pthread_cancel(tid);
	pthread_join(tid,NULL);
}