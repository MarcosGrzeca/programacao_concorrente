#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char const *argv[])
{
	int pid;
	pid = fork();

	if (pid > 0) {
		sleep(5);
		kill(pid, SIGSTOP);
		sleep(10);
		kill(pid, SIGCONT);
		sleep(5);
		kill(pid, SIGKILL);
	} else {
		while (1) {
			printf("!");
		}		
	}
	return 0;
}
