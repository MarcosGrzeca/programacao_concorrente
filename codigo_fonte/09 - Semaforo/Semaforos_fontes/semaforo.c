#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

/*----------------------------------------------------------------------*/
#define KEYSEM 1 

/*----------------------------------------------------------------------*/
int main(){
	
	pid_t pid;
	int semid;
	key_t keysem = KEYSEM;
	struct sembuf semaforo;
	
	int i; 

	if ( ( semid = semget ( keysem, 1, IPC_CREAT | 0600 )) < 0 ){
		printf("Erro na criacao do semaforo"); 
	}

	semctl(semid, 0, SETVAL,1);	

	pid = fork();

	if ( pid > 0){
		sleep(1);
		semaforo.sem_num = 0;
		semaforo.sem_op = -1;
		semaforo.sem_flg = SEM_UNDO;
		semop(semid,&semaforo,1);
		printf("Pai entrou\n");
		sleep(1);
		printf("Pai saiu\n");
						 
		
		semaforo.sem_num = 0;
		semaforo.sem_op = 1;
		semaforo.sem_flg = SEM_UNDO;
		 
		semop(semid,&semaforo,1);  	
		
		wait(NULL);
		semctl(semid,IPC_RMID,0);
		
	}else{

		semaforo.sem_num = 0;
                semaforo.sem_op = -1;
		semaforo.sem_flg = SEM_UNDO;
		 
                semop(semid,&semaforo,1);
		printf("Filho entrou\n");
		sleep(2);
		printf("Filho saiu\n");
                
		semaforo.sem_num=0;
                semaforo.sem_op = 1;
		semaforo.sem_flg = SEM_UNDO;
		 
                semop(semid,&semaforo,1);
                   
	}
}
/*----------------------------------------------------------------------*/

