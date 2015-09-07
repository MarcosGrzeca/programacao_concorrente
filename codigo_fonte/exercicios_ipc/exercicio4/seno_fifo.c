#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

float log_natural(int inicio, int fim, float x) {
	int i;
	float soma = 0;
	for(i = inicio; i <= fim; i++){
		soma += pow((x-1.0)/x,i) * 1.0 / i;
	}
	return (soma);
}

int main(){
	int i, n;
	float x, soma = 0;
	float soma1, soma2;
	printf("Digite o valor de x: ");
	scanf("%f", &x);
	printf("Digite o numero de termos: ");
	scanf("%d",&n);

	mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

	int pid1, pid2, fd1, fd2;
	pid1 = fork();

	if (pid1 > 0) {
		pid2 = fork();

		if (pid2 > 0) {
			fd1 = open("fifo1", O_RDONLY);
			read(fd1, &soma1, sizeof(float));
			fd2 = open("fifo2", O_RDONLY);
			read(fd2, &soma2, sizeof(float));
			printf("Log natural: %f\n", (soma1 + soma2));

			close("fifo1");			
			close("fifo2");						
			unlink("fifo1");
  		    unlink("fifo2");
		} else {
			fd2 = open("fifo2", O_WRONLY);
			soma2 = log_natural((n/2 +1), n, x);
			write(fd2, &soma2, sizeof(float));
			close(fd2);
		}
	} else {
	  fd1 = open("fifo1", O_WRONLY);
      soma1 = log_natural(1, n/2, x);
	  write(fd1, &soma1, sizeof(float));
	  close(fd1);
	}
}