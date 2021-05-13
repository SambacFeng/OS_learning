#include <stdio.h>
#ifndef __USE_GNU //double underscore
#define __USE_GNU //double underscore  
#endif
#include <unistd.h>        
#include <sched.h>
#include <sys/resource.h>  

/*
**************sudo to execute this program*******************
*/


int main( )
{
	int i;
	
	cpu_set_t curr_set;
	
	CPU_ZERO(&curr_set);    //clear cpu setting
        CPU_SET(0, &curr_set);   //set core 0
	sched_setaffinity(0, sizeof(curr_set), &curr_set);  //0 represent current process	
							//affinity will be inherted by child process
	
	pid_t pid = fork();
	
	if(pid == 0)
	{
		printf("Parent and child's old pri: %d\n", getpriority(PRIO_PROCESS, 0)); //get priority
		setpriority(PRIO_PROCESS, 0, -5); //two approaches to set
							 //PRIO_PROCESS means to set the priority of a process,
							 //rather than a group of processes
		printf("Child's new pri: %d\n", getpriority(PRIO_PROCESS, 0));
		
		while(1);
	}
	else
	{
		printf("\nThe child pid: %d\n", pid);
		printf("The parent pid: %d\n\n", getpid());
		
		while(1);
	}
		
	return 0;
}

//dmesg | tail -n : to display only the last n lines of kernel buffer
