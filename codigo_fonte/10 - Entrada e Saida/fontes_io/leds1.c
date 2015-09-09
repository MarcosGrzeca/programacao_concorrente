#include <sys/ioctl.h>
#include <linux/kd.h>
#include <fcntl.h>


int main(int argc, char **argv){
	int teclado = open("/dev/tty0", O_RDONLY);
	int leds = 0;

	while(1) {
		ioctl(teclado, KDSETLED, leds);
		leds++;
		if( leds == 8 ){
		   leds = 0;
                }
		sleep(1);
	}

}
