#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <math.h>

/*---------------------------------------------------------------------*/
#define KEYSHM 2
#define KEYSEM 3

/*---------------------------------------------------------------------*/	
int main(){

	int shm, sem;
	int pid1, pid2;
	float a, b, c;
	float *memoria;
	struct sembuf semaforo;

	shm = shmget(KEYSHM , 8, 0600|IPC_CREAT);

	memoria = shmat(shm,0,0);

	sem = semget ( KEYSEM, 2, 0600 | IPC_CREAT );

	semctl(sem,0, SETVAL,0);	
	semctl(sem,1, SETVAL,0);

	printf("Digite os valores de a, b e c: ");
	scanf("%f %f %f",&a,&b,&c);

	pid1 = fork();

	if ( pid1 > 0 ){

		pid2 = fork();

		if ( pid2 > 0 ){
			
			semaforo.sem_num = 0;
	                semaforo.sem_op = -1;
			semaforo.sem_flg = SEM_UNDO;			
			semop(sem,&semaforo,1);

			semaforo.sem_num = 1;
	                semaforo.sem_op = -1;
			semaforo.sem_flg = SEM_UNDO;			
			semop(sem,&semaforo,1);


			printf("%f %f\n", memoria[0], memoria[1]);
			shmdt(memoria);
			shmctl(shm, IPC_RMID, NULL);
			
			semctl(sem,0,IPC_RMID,0);

		}
		else{
			memoria[1] = (-b + sqrt(b*b - 4*a*c))/(2*a);	
			semaforo.sem_num = 1;
	                semaforo.sem_op = 1;
			semaforo.sem_flg = SEM_UNDO;
			 
	                semop(sem,&semaforo,1);		
		}
	}
	else{
		memoria[0] = (-b - sqrt(b*b - 4*a*c))/(2*a);
		
		semaforo.sem_num = 0;
                semaforo.sem_op = 1;
		semaforo.sem_flg = SEM_UNDO;
		 
                semop(sem,&semaforo,1);	
	}
}
/*---------------------------------------------------------------------*/	

