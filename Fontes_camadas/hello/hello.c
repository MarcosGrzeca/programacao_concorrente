#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SO");
MODULE_AUTHOR("Marcos Augusto Grzeca");

void speaker(unsigned int freq, unsigned int delay){
	int bit;
    
	outb(0xb6,0x43);  
	outb((freq & 0xff),0x42); 
	outb((freq >> 8),0x42); 
	bit=inb(0x61);
	printk(" %d \n",bit);
	outb(3 | bit,0x61); 
	mdelay(delay);
	outb(0xfc | bit,0x61);  
}

void play(unsigned int *freq, unsigned int *time){
    int i;

    for(i=0;freq[i]!=0;i++){
        speaker(freq[i], time[i]);
    }
   
}

void initSpeaker(){

	unsigned int freq[]={
		196,262,262,262,330,294,262,294,330,294,262,
		330,394,440,440,394,330,330,262,294,262,294,
		330,294,262,230,230,196,262,440,394,330,330,
		262,294,262,294,440,394,330,330,394,440,523,
		394,330,330,262,294,262,294,330,294,262,230,
		230,196,262,440,394,330,330,262,294,262,294,
		440,394,330,330,394,440,523,394,330,330,262,
		294,262,294,330,294,262,230,230,196,262,0
	};

	unsigned int time[]={
		25,38,12,25,25,38,12,25,12,12,56,25,25,50,25,
		38,12,12,12,38,12,25,12,12,38,12,25,25,100,25,
		38,12,12,12,38,12,25,25,38,12,25,25,100,25,38,
		12,12,12,38,12,25,12,12,38,12,25,25,100,25,38,
		12,12,12,38,12,25,25,38,12,25,25,100,25,38,12,
		12,12,38,12,25,12,12,38,12,25,25,100
	};
 
	outb(0x0 ,0x61);  
	play(freq, time);
}


int init_module(void) {
	printk ("Aula de terca\n");
	initSpeaker();
	return 0;
}

/*----------------------------------------------------------*/

/*----------------------------------------------------------*/

void cleanup_module (void) {
	printk ("Goodbye World (Tchau)\n");
}