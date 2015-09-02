#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 50
#define PI 3.14159265359

double fatorial(int n) {
	int i;
	double f = 1;
	for (i = 1; i <= n; i++)
	{
		f *= i;
	}
	return f;
}

double seno(int inicial, int n, double x) {
	double valor = 0, tmp;
	int i;

	for (i = inicial; i < (n*2); i+=4) {
		tmp = pow(x, i)/ fatorial(i);
		if (inicial == 1) {
			valor += tmp;
		} else {
			valor -= tmp;
		}
	}
	return valor;
}

void main(){
	int pf1[2], pf2[2];
	int pid1, pid2, n;
	double ang, total, total2;
	// double msg[N];
	pipe(pf1);
	pipe(pf2);

	printf("Digite o angulo: ");
	scanf("%lf", &ang);

	printf("Digite o numero de termos: ");
	scanf("%d", &n);

	ang = ang * PI / 180; 

	pid1 = fork();
	if (pid1 > 0) {

		pid2 = fork();
		if (pid2 > 0) {
			close(pf1[1]);
			close(pf2[1]);
			read(pf1[0], &total, sizeof(double));
			read(pf2[0], &total2, sizeof(double));
			total += total2;
			printf("Seno %.15f \n", total);
			close(pf1[0]);
			close(pf2[0]);
		} else {
			close(pf2[0]);
			close(pf1[0]);
			close(pf1[1]);
			double valor = seno(3, n, ang);
			write(pf2[1], &valor, sizeof(double) + 1);
			close(pf2[1]);
		}
	} else {
		close(pf1[0]);
		close(pf2[0]);
		close(pf2[1]);
		double valor = seno(1, n, ang);

		write(pf1[1], &valor, sizeof(double) + 1);
		close(pf1[1]);
	}
}