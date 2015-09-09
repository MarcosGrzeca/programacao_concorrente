#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <math.h>

#define KEYSEM 7
#define KEYSHM 4

int main()
{
	
	int shmid, semid;
	int id, pid;
	key_t chave = KEYSEM;
	float a, b, c;
	float *resultado;

	/*
	1 - contador
	2 - operacao
	3 - Liberar ou nao o semaforo caso função ter dado erro

	*/

	printf("Digite os valores de a, b, c: \n");
	scanf("%f %f %f", &a, &b, &c);

	shmid = shmget(KEYSHM, 2 * sizeof(float), IPC_CREAT | 0600);
	resultado = shmat(shmid, 0, 0);

	struct sembuf semaforo;
	semid = semget(chave, 1, IPC_CREAT | 0600);
	semctl(semid, 0, SETVAL, 0);
	
	semaforo.sem_num = 0;
	semaforo.sem_flg = SEM_UNDO;

	pid = fork();
	if (pid > 0) {
		pid = fork();
		if (pid > 0) {
			//Pai
			semaforo.sem_op = -1; //Down
			semop(semid, &semaforo, 1);
			semop(semid, &semaforo, 1);

			printf("%f %f\n", resultado[0], resultado[1]);
			shmdt(resultado);
			shmctl(shmid, IPC_RMID, NULL);
		} else {
			//Filho 2
			resultado[1] = (-b + sqrt(b*b - 4*a*c))/(2*a);
			shmdt(resultado);
			semaforo.sem_op = 1; //UP
			semop(semid, &semaforo, 1);
		}
	} else {
		//Filho 1
		resultado[0] = (-b - sqrt(b*b - 4*a*c))/(2*a);
		shmdt(resultado);		
		semaforo.sem_op = 1; //UP
		semop(semid, &semaforo, 1);
	}
}