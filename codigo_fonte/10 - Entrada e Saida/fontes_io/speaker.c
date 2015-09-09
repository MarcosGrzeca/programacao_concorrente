#include <sys/io.h>
#include <unistd.h>
#include <stdio.h>

#define DO  262  
#define RE  294
#define MI  330
#define FA  349
#define SOL 392
#define LA  440
#define SI  494

/*---------------------------------------------------------*/
void play(unsigned int *freq, unsigned int *time){
    int i;

    for(i=0;freq[i]!=0;i++){
        speaker(freq[i], time[i]);
    }
}

/*---------------------------------------------------------*/

int speaker(unsigned int freq, unsigned int delay){
	int bit;
    
	if (iopl(3))
		printf("Erro\n");
	else{
		outb(0xb6,0x43);  
		outb((freq & 0xff),0x42); 
		outb((freq >> 8),0x42); 
		bit=inb(0x61);
		printf(" %d \n",bit);
		outb(3 | bit,0x61); 
		usleep(100000*delay);
		outb(0xfc | bit,0x61);  
	}
}
/*---------------------------------------------------------*/


void main(){

	unsigned int freq[] = { DO,RE,MI,FA,SOL,LA,SI,0 };
	unsigned int time[] = { 10,10,10,10,10,10,10 };
	play(freq, time);
}

