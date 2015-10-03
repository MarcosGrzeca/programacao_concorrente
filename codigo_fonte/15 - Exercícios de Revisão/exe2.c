#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>

#define TAM 50

int numeroVogais(char frase, inicio, fim) {
	int i, nroVogais = 0;
	for (i = inicio; i < fim; i++) {
		if (frase[i] == 'a' || frase[i] == 'A' || 
			frase[i] == 'e' || frase[i] == 'E' ||
			frase[i] == 'i' || frase[i] == 'I' ||
			frase[i] == 'o' || frase[i] == 'O' ||
			frase[i] == 'u' || frase[i] == 'U') {
			nroVogais++;
		}
	}
	return nroVogais;
}

void main(int argc, char const *argv[])
{
	/* code */

	char string[50];
	int fd[2]; //0 - Leitura  1 - Escrita
	pid_t pid;
	int nroVogais = 0;

	printf("Digite a string: ");
	/*fgets(str, TAM, stdin);
	str[strlen(str)-1]='\0';*/

    strcpy(string, "Maguila derruba Tyson");


    pipe(fd);
    pid = fork();

    if (pid > 0) {
    	close(fd[1]);


		nroVogais = numeroVogais(string, 0, strlen(string) / 2);
		int nroVogaisFilho;
		read(fd[0], nroVogaisFilho, sizeof(int));
		nroVogais += nroVogaisFilho;
		printf("Total vogais %i / %i \n", nroVogais, strlen(string));
		close(fd[1]);
		wait(NULL);
    } else {
    	close(fd[0]);
    	nroVogais = numeroVogais(string, strlen(string) / 2, strlen(string));
    	write(fd[1], nroVogais, sizeof(int));
    }
}