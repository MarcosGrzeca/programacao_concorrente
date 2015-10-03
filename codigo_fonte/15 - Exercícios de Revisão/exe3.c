#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define CHAVE 10
#define PI 3.14159265359


double fatorial(int num) {
	double soma = 1;
	int i;
	for (i = 1; i <= num; i++) {
		soma = soma * i;
	}
	return soma;
}

double seno(double x, int inicial, int n) {
	int i;
	double soma = 0;
	for (i = inicial; i <= n; i+=4) {
		soma += pow(x, i) / fatorial(i);
	}
	return soma;
}

void main(int argc, char const *argv[])
{
	
	pid_t p1, p2;
	double x;
	int shmid,n;
	double *memoria;

	printf("Digite x e n:\n");
	scanf("%lf %d", &x, &n);

	x = (x * PI)/180;

	shmid = shmget(CHAVE, 2 * sizeof(double), 0600 | IPC_CREAT);
	if (shmid < 0) {
		printf("Erro na criação da area de memoria");
	}

	memoria = shmat(shmid, 0, 0);
	if (memoria < 0) {
		printf("Erro na alocacao da area de memoria");	
	}

	p1 = fork();

	if (p1 > 0) {
		p2 = fork();
		if (p2 > 0) {

			wait(NULL);
			wait(NULL);

			printf("Seno: %f\n", memoria[0] - memoria[1]);
			shmdt(memoria);
			shmctl(shmid,IPC_RMID,NULL);

		} else {

			memoria[0] = seno(x, 1, n);
			shmdt(memoria);

		}
	} else {

		memoria[1] = seno(x, 3, n);
		shmdt(memoria);
	}
}