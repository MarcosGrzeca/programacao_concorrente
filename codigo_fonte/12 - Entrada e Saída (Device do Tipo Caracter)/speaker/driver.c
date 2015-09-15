#include <linux/kernel.h>	
#include <linux/module.h>	
#include <linux/fs.h>
#include <linux/string.h>
#include <asm/uaccess.h>
#include <linux/delay.h>
#include "driver.h"

/*-----------------------------------------------------------------------------*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andre Luis Martinotto");
MODULE_DESCRIPTION("Disciplina SO");

/*----------------------------------------------------------------------------*/
#define DEVICE 50
#define DEVICE_NAME "so"
#define BUF_MSG 80

#define DO  262  
#define RE  294
#define MI  330
#define FA  349
#define SOL 392
#define LA  440
#define SI  494

/*----------------------------------------------------------------------------*/

int init_device(void);
void cleanup_device(void);
static int device_open(struct inode *inode, struct file *file);
static int device_release(struct inode *inode, struct file *file);
static ssize_t device_read(struct file *file, char __user *buffer, size_t length,loff_t * offset);
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset);
static long ioctl_funcs(struct file *filp, unsigned int cmd, unsigned long arg);

/*----------------------------------------------------------------------------*/

module_init(init_device);
module_exit(cleanup_device)

/*----------------------------------------------------------------------------*/
static int aberto = 0;
static char mensagem[BUF_MSG];

/*----------------------------------------------------------------------------*/
struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release,
	.unlocked_ioctl = ioctl_funcs,	
};

/*---------------------------------------------------------*/
void speaker(int delay){
    unsigned int freq[] = { DO,RE,MI,FA,SOL,LA,SI,0 };
    int i, bit;

    if ( delay >= 0 && delay <= 1000){
   
    	for(i=0;freq[i]!=0;i++){
		outb(0xb6,0x43);  
		outb((freq[i] & 0xff),0x42); 
		outb((freq[i] >> 8),0x42); 
		bit=inb(0x61);
		outb(3 | bit,0x61); 
		mdelay(delay);
		outb(0xfc | bit,0x61);
    	}
    }  
    else{ 
    	printk(KERN_ALERT "Delay invalido (0-1000).\n");
    }
}

/*----------------------------------------------------------------------------*/
int init_device(){

	int ret;

	ret = register_chrdev(DEVICE, DEVICE_NAME, &fops);

	if (ret < 0) {
		printk("Erro ao carregar o dispositivo %d\n.",DEVICE);	
		return ret;
	}

	speaker(100);

	printk("O dispositivo %d foi carregado.\n", DEVICE);

	return 0;
}

/*----------------------------------------------------------------------------*/

void cleanup_device(){

	speaker(100);
	unregister_chrdev(DEVICE, DEVICE_NAME);
	printk("O dispositivo %d foi descarregado.\n", DEVICE);
}


/*----------------------------------------------------------------------------*/
static int device_open(struct inode *inode, struct file *file){
	

	if (aberto){
		return -EBUSY;
	}
	aberto++;

	try_module_get(THIS_MODULE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static int device_release(struct inode *inode, struct file *file){
	
	aberto--;

	module_put(THIS_MODULE);
	return 0;
}

/*----------------------------------------------------------------------------*/
static ssize_t device_read(struct file *file, char __user * buffer, size_t length, loff_t * offset){

	printk(KERN_ALERT "Essa operacao nao e permitida.\n");
	return 0;

}

/*----------------------------------------------------------------------------*/
static ssize_t device_write(struct file *file, const char __user * buffer, size_t length, loff_t * offset){
	
	int delay,i;

	for (i = 0; i < length && i < BUF_MSG; i++){
		get_user(mensagem[i], buffer + i);
	}
	
	
	sscanf(mensagem,"%d",&delay);
	printk("%d\n",delay);
	speaker(delay);
	
	return i;
}

/*----------------------------------------------------------------------------*/

static long ioctl_funcs(struct file *file, unsigned int cmd, unsigned long arg){

	switch(cmd) {
		case WRITE_IOCTL:  		
			return device_write(file, (char *)arg, BUF_MSG, &file->f_pos);
		default:
			return -ENOTTY;
	}

}
/*----------------------------------------------------------------------------*/

