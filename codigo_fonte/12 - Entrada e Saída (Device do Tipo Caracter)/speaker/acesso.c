#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include "driver.h"

int main(int argc, char **argv){
	int fd;

	if (argc != 2){
		printf("%s <delay>\n",argv[0]);
		exit(0);
	}

	if ((fd = open("/dev/so", O_RDWR)) < 0) {
		printf("Erro ao abrir o dispositivo\n");
		exit(0);
	}

	if (ioctl(fd, WRITE_IOCTL, argv[1]) < 0){
		printf("Problema no ioctl\n");
		exit(0);
	}

	close(fd);
}

			
