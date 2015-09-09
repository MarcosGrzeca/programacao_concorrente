#include <fcntl.h>       /* O_WRONLY */
#include <stdio.h>       /* fprintf, stderr, printf */
#include <stdlib.h>      /* exit */
#include <unistd.h>      /* STDIN_FILENO */
#include <linux/kd.h>    /* KIOCSOUND */

#define DO  262  
#define RE  294
#define MI  330
#define FA  349
#define SOL 392
#define LA  440
#define SI  494

#define CLOCK_TICK_RATE 1193182

/*---------------------------------------------------------*/
void play(unsigned int *freq, unsigned int *time){
    int console, i;
  
    if((console = open("/dev/console", O_WRONLY)) == -1) { 
       fprintf(stderr, "Impossivel abrir /dev/console para escrita.\n");
       exit(1);  
    }
	
    for(i=0;i<7;i++){
	ioctl(console, KIOCSOUND, (int)(CLOCK_TICK_RATE/freq[i]));
	usleep(10000*time[i]); 
	ioctl(console, KIOCSOUND, 0);
  }

  close(console); 
}

/*---------------------------------------------------------*/
int main(){

	unsigned int freq[] = { DO,RE,MI,FA,SOL,LA,SI,0 };
	unsigned int time[] = { 100,100,100,100,100,100,100 };
	play(freq, time);
}

