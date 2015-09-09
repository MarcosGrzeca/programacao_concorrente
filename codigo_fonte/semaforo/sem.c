#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define CHAVE 5

int main()
{
	
	int id, semid, pid;
	key_t chave = CHAVE;

	/*
	1 - contador
	2 - operacao
	3 - Liberar ou nao o semaforo caso função ter dado erro

	*/
	struct sembuf semaforo;
	semid = semget(chave, 1, IPC_CREAT | 0600);

	semctl(semid, 0, SETVAL, 1);

	printf("VALOR: %d\n", semctl(semid, 0, GETVAL, 0));

	// sleep(30);

	pid = fork();
	if (pid > 0) {
		// sleep(5);
		semaforo.sem_num = 0;
		semaforo.sem_op = -1; //Down
		semaforo.sem_flg = SEM_UNDO;
		semop(semid, &semaforo, 1);
		printf("PAI PEGOU SEMAFORO\n");

		semaforo.sem_num = 0;
		semaforo.sem_op = 1; //UP
		semaforo.sem_flg = SEM_UNDO;
		semop(semid, &semaforo, 1);

		semctl(semid, IPC_RMID, 0);
	} else {
		// sleep(5);
		semaforo.sem_num = 0;
		semaforo.sem_op = -1; //Down
		semaforo.sem_flg = SEM_UNDO;
		semop(semid, &semaforo, 1);
		printf("FILHO PEGOU SEMAFORO\n");

		semaforo.sem_num = 0;
		semaforo.sem_op = 1; //UP
		semaforo.sem_flg = SEM_UNDO;
		semop(semid, &semaforo, 1);
	}

}