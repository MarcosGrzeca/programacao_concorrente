#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void main(){
	FILE *f = NULL;

	f = fopen ("teste.txt","w+");

	fprintf(f, "CACHE BUFFER\n");
	fflush(f);
	
	kill(getpid(),SIGKILL);

	fclose(f);  	
}
