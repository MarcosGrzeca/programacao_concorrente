#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------*/
#define N 8

int fatorial(int n) {
	int i,f = 1;
	for (i = 1; i <= n; i++)
	{
		f *= i;
	}
	return f;
}

int main(int argc, char const *argv[])
{

	int pid, pid2;
	int n, p, fatn, fatp, fatnp;
	int f1, f2;
	
	printf("Digite os valores de n e p:\n");
	scanf("%d %d", &n, &p);
	// n = 5, p = 3;

	char fifo[N];

   	mkfifo("fifo1", 0666);
	mkfifo("fifo2", 0666);

	pid = fork();
	if (pid > 0) {
		pid = fork();
		if (pid > 0) {
			fatnp = fatorial(n-p);
			f1 = open("fifo1", O_RDONLY);
			f2 = open("fifo2", O_RDONLY);
			read(f1, &fatn, sizeof(int));
			read(f2, &fatp, sizeof(int));
			printf("Binomio %s\n", );

			printf("Resultado %f\n", (float)fatn/(fatp*fatnp));
			close(f2);
			close(f1);
		} else {
			f2 = open("fifo2", O_WRONLY);
			fatp = fatorial(p);
			write(f2, fatn, sizeof(int));
			close(f2);
		}
	} else {
		f1 = open("fifo1", O_WRONLY);
		fatn = fatorial(n);
		write(f1, fatn, sizeof(int));
		close(f1);
	}
	return 0;
}