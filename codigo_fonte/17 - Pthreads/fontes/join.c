#include <pthread.h>

#define NTHREADS 5

int fatorial(int n){
	if (n<2)	
		return(1);
	else return( n * fatorial(n-1));
}

void *funcao (void *args){
	int fat = fatorial((int)args);
	return (void *)fat;
}

int main() {
	int n,p, fatp, fatn, fatnp;
	pthread_t thidN, thidP;
	printf("Digite o valor de n,p: ");
	scanf("%i %i",&n,&p);
	printf("%i %i\n",n,p);
	
	pthread_create(&thidN,NULL,funcao,(void *)n);
	pthread_create(&thidP,NULL,funcao,(void *)p);

	fatnp = fatorial(n-p);

	pthread_join(thidN,(void *)&fatn);
	pthread_join(thidP,(void *)&fatp);
	
	printf("Binomio: %f\n", (float)fatn/(fatp*fatnp)); 
}