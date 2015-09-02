#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

/*---------------------------------------------------------------*/
#define CHAVE 1
#define N 8

int fatorial(int n) {
	int i,f = 1;
	for (i = 1; i <= n; i++)
	{
		f *= i;
	}
	return f;
}

int main(int argc, char const *argv[])
{
	key_t chave = CHAVE;
	int shmid, pid, pid2;
	int n, p, fatn, fatp, fatnp;

	printf("Digite os valores de n e p:\n");
	// scanf("%d %d", &n, &p);
	n = 5, p = 3;

	char *memoria = NULL;

	shmid = shmget(chave, N, IPC_CREAT | 0600);
	memoria = shmat(shmid, 0, 0);

	pid = fork();
	if (pid > 0) {
		pid = fork();
		if (pid > 0) {
			fatnp = fatorial(n-p);
			wait(NULL);
			wait(NULL);
			fatn = memoria[0];
			fatp = memoria[1];

			printf("Resultado %f\n", (float)fatn/(fatp*fatnp));
			shmdt(memoria);
			shmctl(shmid, IPC_RMID, NULL);
		} else {
			memoria[1] = fatorial(p);
			shmdt(memoria);
		}
	} else {
		memoria[0] = fatorial(n);
		shmdt(memoria);
	}

	// shmctl(shmid, IPC_RMID, NULL);
	return 0;
}