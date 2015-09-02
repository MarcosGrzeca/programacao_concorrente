#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

/*---------------------------------------------------------------*/
#define CHAVE 1
#define N 30

int main(int argc, char const *argv[])
{
	key_t chave = CHAVE;
	int shmid, pid;
	char *memoria = NULL;

	shmid = shmget(chave, N, IPC_CREAT | 0600);
	memoria = shmat(shmid, 0, 0);

	pid = fork();
	if (pid > 0) {
		wait(NULL);
		printf("Alfabeto %s\n", memoria);
		shmctl(shmid, IPC_RMID, NULL);
	} else {
		sleep(1);
		int i;
		for (i = 0; i < 26; i++)
		{
			memoria[i] = 'A' + i;
		}
		// memoria[10] = 0;
		memoria[i] = '\0';
	}

	// shmctl(shmid, IPC_RMID, NULL);
	return 0;
}