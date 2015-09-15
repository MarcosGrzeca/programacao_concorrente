#include <linux/module.h>
#include <linux/kernel.h>

static int valor = 0;
module_param(valor, int, S_IRUGO | S_IWUSR);

MODULE_DESCRIPTION("SO");
MODULE_LICENSE("GPL");


int init_module(void) {
	int i;
	for (i=0; i<valor; i++){
		printk ("Hello World = %d!\n",i);
	}
	return 0;
}

void cleanup_module (void) {
	printk ("Goodbye World\n");
}

