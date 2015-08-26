#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/*---------------------------------------------------------------*/
#define CHAVE 1
#define N 30

int main(int argc, char const *argv[])
{
	key_t chave = CHAVE;
	int shmid;

	shmid = shmget(chave, N, IPC_CREAT | 0600);

	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}