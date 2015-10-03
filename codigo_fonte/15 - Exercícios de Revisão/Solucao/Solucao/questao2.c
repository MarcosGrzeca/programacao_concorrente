#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*-------------------------------------------------------*/
#define N 1000
/*-------------------------------------------------------*/

int ehvogal(char c){

	c = toupper(c);

	if ( c=='A' || c=='E' || c=='I' || c=='O' || c=='U'){
		return(1);
	}
	else{
		return(0);
	}
}

/*-------------------------------------------------------*/
int conta_vogais(char str[N], int ini, int fim){
	int i, cont = 0;
	for (i=ini; i<fim; i++){
		if ( ehvogal(str[i]) ){
			cont++;	
		}
	}
	return(cont);
}

/*-------------------------------------------------------*/
int main(){
	
	int pid, vogais, total;
	int pipe1[2];
	char str[N];

	printf("Digite a string: ");
	fgets(str,N,stdin);
	str[strlen(str)-1]='\0';

	printf("%s\n", str);	
      
	pipe(pipe1);

	pid = fork();

	if (pid > 0){

		close(pipe1[1]);

		total = conta_vogais(str, strlen(str)/2, strlen(str));
						
		read(pipe1[0],&vogais,sizeof(float));

		total += vogais;

		printf("Razao de caracteres: %d/%d\n",total, strlen(str)); 
		close(pipe1[0]);

		wait(NULL);
	}
	else{
		close(pipe1[0]);
		vogais = conta_vogais(str, 0, strlen(str)/2);
		write(pipe1[1],&vogais,sizeof(int));
		close(pipe1[1]);
	}
}
	
/*-------------------------------------------------------*/
