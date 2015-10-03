#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*---------------------------------------------------------------------------*/
#define KEY 1 
#define PI 3.14159265359

/*---------------------------------------------------------------------------*/
double fatorial(int n){
	double f=1;
	int i;
	for (i=1;i<=n;i++){
		f*=i;
	}
	return(f);
}
/*---------------------------------------------------------------------------*/
double calcula_seno(double x, int n, int ini, int sinal){
	double soma = 0;
	int i;

	for(i=ini; i<=n; i+=2){
		soma += sinal * pow(x,2*i-1)/fatorial(2*i-1);		
	}
	return(soma);
}

/*---------------------------------------------------------------------------*/
int main(){
	
	int shmid, pid, n;
	double *memoria, soma = 0;
	double x; 

	if ( ( shmid = shmget (KEY, 2*sizeof(double) ,IPC_CREAT | 0600)) < 0 ){
                printf("Erro na criacao da memoria compartilhada");
	}
 
	if ( ( memoria = shmat (shmid, 0, 0 )) < 0 ){
                printf("Erro na alocacao");
	}

	printf("Digite os valores de x e n: ");
	scanf("%lf %d",&x,&n);

	x = (x * PI)/180; 

	pid = fork();

	if ( pid > 0){
	
		pid = fork();

		if ( pid > 0 ){
			
			wait(NULL);
			wait(NULL);


			printf("Seno: %f\n", memoria[0] + memoria[1]);				

			shmdt(memoria);
			shmctl(shmid,IPC_RMID,NULL);
		}
		else{
			memoria[1] = calcula_seno(x,n,2,-1);
			shmdt(memoria);	

		}
	}else{
		memoria[0] = calcula_seno(x,n,1,1);
		shmdt(memoria);
		
	}

}

/*---------------------------------------------------------------------------*/
