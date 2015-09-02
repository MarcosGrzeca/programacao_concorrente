#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>

#define CHAVE 2
#define N 24

int main (){
	double i, w, n, pi= 0.0, x;

	key_t chave = CHAVE;
	int shmid, pid1, pid2, pid3, pid4;
	int ehPai = 0, inicialInicialFor = 0;

	printf("Digite o numero de retangulos: ");
	scanf("%lf", &n);

	w = 1/n;

	double *memoria = NULL;

	shmid = shmget(chave, (3 * sizeof(double)), IPC_CREAT | 0600);
	memoria = shmat(shmid, 0, 0);

	pid1 = fork();
	if (pid1 > 0) {
		pid2 = fork();
		if (pid2 > 0) {
			pid3 = fork();
			if (pid3 > 0) {
				ehPai = 1;
			} else {
				inicialInicialFor = 3;
			}
		} else {
			inicialInicialFor = 2;
		}
	} else {
		inicialInicialFor = 1; 
	}

   	for (i = (1 + inicialInicialFor); i <= n; i+=4){
     	x = w * (i - 0.5);
     	pi = pi + 4.0 / (1.0 + (x * x));
   	}

	pi = pi * w;

	if (ehPai == 1) {
		wait(NULL);
		wait(NULL);
		wait(NULL);

		double calculo1 = memoria[0];
		double calculo2 = memoria[1];
		double calculo3 = memoria[2];

      	pi = pi + calculo1 + calculo2 + calculo3;
		printf("pi é aproximadamente: %f\n", pi);
		shmdt(memoria);
		shmctl(shmid, IPC_RMID, NULL);
	} else {
		int pos = (inicialInicialFor - 1);
		memoria[pos] = pi;
		shmdt(memoria);
	}
}