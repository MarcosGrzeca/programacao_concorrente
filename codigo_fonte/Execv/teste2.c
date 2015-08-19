#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void main(){
        printf("PID do processo pai %i\n",getpid());
        if ( execvp("./execv", NULL) < 0) {
            printf("Erro na criacao do processo\n");
	}
	printf("DEPOis do exec\n");
}

