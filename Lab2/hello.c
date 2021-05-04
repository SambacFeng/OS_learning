#include <linux/module.h>
#include <linux/kernel.h>

long unsigned int start = 0;
long unsigned int end = 0;

/* This function is called when the module is loaded. */
int hello_entry(void)
{
	printk(KERN_INFO "Module loaded\n");
	start = jiffies;

	printk("Hz: %d\n", HZ);
	printk("jiffies at start: %lu\n", start);
	return 0;
}

/* This function is called when the module is removed. */
void hello_exit(void) 
{
	end = jiffies;

	printk("jiffies at end: %lu\n", end);
	printk("module stayed: %lu\n", (end - start) / HZ);
	printk(KERN_INFO "Module removed\n");
}

/* Macros for registering module entry and exit points. */
module_init(hello_entry);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("OSC_Lab2_Task3");
MODULE_AUTHOR("FengChunlin");

