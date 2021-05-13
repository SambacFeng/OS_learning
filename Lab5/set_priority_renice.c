#include <unistd.h>
#include <stdio.h>
#ifndef __USE_GNU //__ not _
#define __USE_GNU   
#endif          
#include <sched.h>


int main(int argc, char *argv[])
{
	int i = 0;

	cpu_set_t curr_set; //128 Byte, 1024 CPU
	CPU_ZERO(&curr_set);     //clear
        CPU_SET(0, &curr_set);   //set core 0
        sched_setaffinity(0, sizeof(curr_set), &curr_set); // 0 represents current process, inherited by child
	
	pid_t pid = fork();

	if(pid == 0)
	{
		while(1)
		{
			printf("child: %d\n", i); //This will make the gnome-terminal process take much cpu time
			i++;
		}
	}
	else
	{
		while(1)
		{
			printf("parent: %d\n", i);
			i++;
		}
	}
		
	return 0;
}


