#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int pid1;
static int pid2;
module_param(pid1, int, S_IRUGO);
module_param(pid2, int, S_IRUGO);


int cfs_module_init(void)
{
	struct task_struct *p;   
    	for_each_process(p) {  
       		if(p->pid == pid1 || p->pid == pid2)   
                	//printk("%d runtime:%llu\n", p->pid, p->se.sum_exec_runtime);  //nano-seconds; real runtime
					printk("%d runtime:%llu, vruntime:%lld\n", p->pid, p->se.sum_exec_runtime, p->se.vruntime);  
    	}     
   	return 0; 
}

void cfs_module_exit(void) {

	printk(KERN_INFO "Module removed!\n");
}

module_init(cfs_module_init);
module_exit(cfs_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("execution time");
MODULE_AUTHOR("zhaohj");

//printk("%d runtime:%llu, vruntime:%lld\n", p->pid, p->se.sum_exec_runtime, p->se.vruntime);  
