#include <pthread.h>
#include <stdio.h>

/*------------------------------------------------------*/
#define T 1
#define N 100000

/*------------------------------------------------------*/
struct argumentos{
	int *cont;
	pthread_mutex_t *mutex;
};
typedef struct argumentos ARGS;

/*------------------------------------------------------*/
void *incrementa(void *arg){
	ARGS *para = (ARGS *) arg;

	int *p = para->cont;
	pthread_mutex_t *m = para->mutex;
	int i;

	for(i=0; i<N; i++){
		pthread_mutex_lock(m);
		(*p)++;
		pthread_mutex_unlock(m);
	}
	
}

/*------------------------------------------------------*/
int main(){
	pthread_t tid[T];
	int i, cont = 0;
	ARGS argumentos;
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

	argumentos.cont = &cont;
	argumentos.mutex = &mutex;

	for (i=0; i<T; i++){
		pthread_create(&tid[i], NULL, incrementa, &argumentos);
	}
	
	for (i=0; i<T; i++){
		pthread_join(tid[i],NULL);
	}

	printf("Cont: %d\n", cont);
}
/*------------------------------------------------------*/
