#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define KEY 10


struct msg
{
	long tipo;
	int totalPrimos;
};

int primo(int n){
	int i;
	
	if ( n<= 1){
		return(0);
	}

	if ( n == 2){
		return(1);
	}

	if ( n % 2 == 0){
		return(0);
	}

	for (i=2; i<=sqrt(n); i++){
		if ( !(n % i) ){
			return(0);
		} 
	}
	return (1);
}

void int main(int argc, char const *argv[])
{

	int vetor[1000], i, totalPrimos = 0, fila;
	struct msg msg;
	
	fila = msgget(KEY,0600|IPC_CREAT);

	srand(time(NULL));
	for (i = 0; i < 1000; i++) {
		vetor[i] = rand() % 100;
	}

	pid_t p1, p2;

	p1 = fork();
	if (p1 > 0) {
		p2 = fork();
		if (p2 > 0) {
			msgrcv(fila, &msg, sizeof(msg.cont),0,0);
			totalPrimos = msg.totalPrimos;
			msgrcv(fila, &msg, sizeof(msg.cont),0,0);
			totalPrimos += msg.totalPrimos;
			printf("Total primos %i\n", totalPrimos);
			msgctl(fila, IPC_RMID, NULL);
		} else {
			for (i = 500; i < 1000; i++) {
				totalPrimos += primo(vetor[i]);
			}
			msg.totalPrimos = totalPrimos;
			msgsnd(fila, &msg, sizeof(msg.cont), 0);
		}
	} else {
		for (i = 0; i < 500; i++) {
			totalPrimos += primo(vetor[i]);
		}
		msg.totalPrimos = totalPrimos;
		msgsnd(fila,&msg,sizeof(msg.cont),0);
	}
}