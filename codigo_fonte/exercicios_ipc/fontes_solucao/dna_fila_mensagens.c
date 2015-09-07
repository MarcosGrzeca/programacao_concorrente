#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>

/*--------------------------------------------------------------*/
#define N 1000000
#define CHAVE 6

/*---------------------------------------------------------*/
struct msg{
	long tipo;
	int gc;
};
/*--------------------------------------------------------------*/
void  le_dna(char *arquivo, char *dna){

	char c;
	int i = 0;

	FILE *f = fopen(arquivo,"r"); 
	while ( ( c = fgetc(f) ) != EOF &&  c!='\n' ){
		dna[i++] = c;
	}	

	dna[i] = '\0';
}

/*--------------------------------------------------------------*/
int conta_gc(char *str, int ini, int fim){

	int i, gc = 0;

	for ( i=ini; i<fim; i++ ){
		if ( str[i]=='C' || str[i]=='G'){ 
			gc++;	
		}	
	}
	return(gc);
}
/*--------------------------------------------------------------*/
int main(int argc, char **argv){ 
	int fila, pid;
	struct msg msg; 
	int total = 0; 
	char str[N];

	fila = msgget(CHAVE,0600|IPC_CREAT);
      
	le_dna("dna.txt",str);


	pid = fork();

	if ( pid > 0 ){

		pid = fork();

		if ( pid > 0 ){
			msgrcv(fila,&msg,sizeof(msg.gc),0,0);
			total += msg.gc;
			msgrcv(fila,&msg,sizeof(msg.gc),0,0);
			total += msg.gc;
			wait(NULL);
			wait(NULL);
			msgctl(fila, IPC_RMID, NULL);				
	 		printf("Conteudo GC: %.2f\n", (float)total/strlen(str)); 
		}
		else{
			msg.tipo = 2;		
			msg.gc = conta_gc(str, strlen(str)/2, strlen(str));
			msgsnd(fila,&msg,sizeof(msg.gc),0);
		}
	}
	else{
		msg.tipo = 1;		
		msg.gc = conta_gc(str, 0,strlen(str)/2);
		msgsnd(fila,&msg,sizeof(msg.gc),0);
	}
} 

