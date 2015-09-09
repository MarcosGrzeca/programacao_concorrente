#include<stdio.h>
#include<sys/io.h>

/*---------------------------------------------------------------*/
#define R 1
#define L 2
#define M 4

#define porta 0x60
/*---------------------------------------------------------------*/
void leds(char led){
	outb(0xed,porta);
	while((inb(porta+4)&2)); // aguarda o ok da controladora
	outb(led,porta);
	while((inb(porta+4)&2)); 
	sleep(1);
}
/*---------------------------------------------------------------*/
int main(){
	char led,i;
	ioperm(porta,5,1);
	for( i=0 ; i<3 ; i++ ){ 	
		leds(L);
		leds(M);
		leds(R);
	}
	ioperm(porta,5,0);
	return(0);
}
/*---------------------------------------------------------------*/
