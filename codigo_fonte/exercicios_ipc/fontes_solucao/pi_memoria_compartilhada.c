#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*-------------------------------------------------------------*/
#define CHAVE 8

/*-------------------------------------------------------------*/

double pi_retangulos(double ini, double n, int np){

	double pi =0, x, w;
	double i;
	
	w = 1.0 / n;
	
   	for (i = ini; i <= n; i+=np){
     		x = w * (i - 0.5);
     		pi = pi + 4.0 / (1.0 + (x * x));
   	}
 	pi = pi * w; 

	return(pi);
}

/*-------------------------------------------------------------*/
int main (){
	double pi = 0, n;
	int shmid, pid;
	double *memoria = NULL;
	
	printf("Digite o numero de retangulos: ");
	scanf("%lf", &n);

	shmid = shmget (CHAVE, 3 * sizeof(double), IPC_CREAT | 0600);

	memoria = shmat(shmid, 0, 0 );
	
	pid = fork();

	if ( pid > 0 ){
		pid = fork();
		if ( pid > 0 ){
			pid = fork();
			if ( pid > 0 ){
				pi = pi_retangulos(4,n,4);
				wait(NULL);
				wait(NULL);
				wait(NULL);
				pi += memoria[0];
				pi += memoria[1];
				pi += memoria[2];
				printf("pi e aproximadamente: %.15f\n", pi);
				shmdt(memoria);
				shmctl(shmid,IPC_RMID,NULL);
 			}
			else{
				memoria[2] = pi_retangulos(3,n,4);
				shmdt(memoria);
			}
		}
		else{
			memoria[1] = pi_retangulos(2,n,4);
			shmdt(memoria);
		}
	}
	else{
		memoria[0] = pi_retangulos(1,n,4);		
		shmdt(memoria);
	}
}

/*-------------------------------------------------------------*/
