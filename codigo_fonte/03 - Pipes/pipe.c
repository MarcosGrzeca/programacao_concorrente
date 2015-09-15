#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 50

void main(){
	int p[2], p2[2];
	int id;
	char msg[N];
	pipe(p);
	pipe(p2);
	id = fork();
	if (id > 0) {
		close(p[0]);
		close(p2[1]);
		strcpy(msg, "Alo mundo");
		write(p[1], msg, strlen(msg) + 1);
		
		read(p2[0], msg, N);
		printf("!! %s \n", msg);
		close(p[1]);
		close(p2[0]);
	} else {
		close(p[1]);
		close(p2[0]);
		read(p[0], msg, N);
		printf("!! %s \n", msg);
		write(p2[1], msg, strlen(msg) + 1);
		close(p[0]);
		close(p2[1]);
	}
}

