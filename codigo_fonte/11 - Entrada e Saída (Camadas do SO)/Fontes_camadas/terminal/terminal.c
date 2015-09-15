#include <stdio.h>
#include <stdlib.h>


int main() {
	FILE *fp;
	fp = fopen("/dev/tty", "rw+");

	if ( fp == NULL ){
		perror("Nao foi possivel abrir o terminal\n");
		exit(0);
	}

	fprintf(fp, "Alo mundo\n");
	fclose(fp);
} 
