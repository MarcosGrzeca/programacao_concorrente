#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/*-----------------------------------------------------------------------*/
int main(){
	int cdrom;
	struct cdrom_tochdr header;

	if ( (cdrom = open("/dev/cdrom", O_RDONLY)) < 0 ){
		perror("open");
		exit(1);
	}

	if ( ioctl(cdrom,CDROMREADTOCHDR,(void *) &header) < 0){
		printf("Erro ao pegar as faixas\n");
		exit(1);
	}

	printf("Faixa inicial: %d - Faixa final %d\n", header.cdth_trk0,header.cdth_trk1);

	close(cdrom);
}


/*-----------------------------------------------------------------------*/


