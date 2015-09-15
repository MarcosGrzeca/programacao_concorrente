#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SO");


int init_module(void) {
	printk ("Hello World\n");
	return 0;
}

void cleanup_module (void) {
	printk ("Goodbye World\n");
}

