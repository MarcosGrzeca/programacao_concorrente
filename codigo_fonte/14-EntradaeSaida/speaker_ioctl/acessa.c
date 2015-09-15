#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "driver.h"

/*-----------------------------------------------------*/
#define DEVICE_NAME "/dev/so"

/*-----------------------------------------------------*/
int main(int argc, char **argv) {

	int fp, ret;

	if (argc != 2 ){
		printf("Execute: %s < delay >\n",argv[0]);
		exit(0);
	}

	fp = open("/dev/so", O_RDWR);


	if ( fp < 0 ){
		perror("Nao foi possivel acessar\n");
		exit(0);
	}

	ret = ioctl(fp, IOCTL_SET_SPEAKER, argv[1]);

	if(ret < 0){
		printf("Erro ao setar o delay");
		exit(0);
	}

	close(fp);
} 
/*-----------------------------------------------------*/
