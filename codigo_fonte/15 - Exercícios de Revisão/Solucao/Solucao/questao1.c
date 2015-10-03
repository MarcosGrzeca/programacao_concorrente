#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

/*---------------------------------------------------------*/
#define KEY 8 
#define N 11
/*---------------------------------------------------------*/
struct msg{
	long tipo;
	int cont;
};

/*---------------------------------------------------------*/
void gera_vetor(int vet[N]){
	int i;
	srand(time(NULL));
	for (i=0; i<N; i++){
		vet[i] = rand() % 10;
	}
}
/*---------------------------------------------------------*/
int primo(int n){
	int i;
	
	if ( n<= 1){
		return(0);
	}

	for (i=2; i<=sqrt(n); i++){
		if ( !(n % i) ){
			return(0);
		} 
	}
	return (1);
}

/*---------------------------------------------------------*/
int conta_primos(int vet[N], int ini, int fim){
	int i, cont = 0;
	for (i=ini; i<fim; i++){
		if ( primo(vet[i]) ){
			cont++;
		}
	}
	return(cont);
}

/*---------------------------------------------------------*/
int main(){

	int pid, fila, cont;
	struct msg msg; 
	int vet[N];

       	fila = msgget(KEY,0600|IPC_CREAT);
     
	gera_vetor(vet);
	
	pid = fork();

	if (pid > 0){
		pid = fork();
		if (pid > 0){
			msgrcv(fila,&msg,sizeof(msg.cont),0,0);
			cont = msg.cont;
			msgrcv(fila,&msg,sizeof(msg.cont),0,0);
			cont += msg.cont;
			wait(NULL);
			wait(NULL);
			msgctl(fila, IPC_RMID, NULL);				
			printf("Total de primos = %d\n", cont);
		}
		else{
			msg.cont = conta_primos(vet,N/2,N);
			msgsnd(fila,&msg,sizeof(msg.cont),0);
		}
			
	}else{
		msg.cont = conta_primos(vet,0,N/2);
		msgsnd(fila,&msg,sizeof(msg.cont),0);
	}	
}
/*---------------------------------------------------------*/
	
