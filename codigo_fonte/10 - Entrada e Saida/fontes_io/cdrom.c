#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------*/
int main(){
	int cdrom;

	if ( (cdrom = open("/dev/cdrom4", O_RDONLY | O_NONBLOCK)) < 0 ){
		perror("open");
		exit(1);
	}

	if ( ioctl(cdrom, CDROMEJECT) < 0 ){
		printf("Nao foi possivel abrir o CDROM\n");
	}

	sleep(5);

	if ( ioctl(cdrom, CDROMCLOSETRAY) < 0 ){
		printf("Nao foi possivel fechar o CDROM\n");
	}

	close(cdrom);
}

/*-----------------------------------------------------------------------*/


