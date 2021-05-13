#include <unistd.h>
#include <stdio.h>
#ifndef __USE_GNU //__ not _
#define __USE_GNU   
#endif     
#include <sched.h>


int main()
{
	cpu_set_t curr_set; //128 Byte, 1024 CPU

	//get cpu affinity
	sched_getaffinity(0, // 0 represents current process
                          sizeof(curr_set), //128B
                          &curr_set); //get current cpu set

        printf("core 0 is set: %d\n", CPU_ISSET(0, &curr_set)); //check if core i set
        printf("core 1 is set: %d\n", CPU_ISSET(1, &curr_set));

	getchar();

	//set cpu affinity
	CPU_ZERO(&curr_set);     //clear
        CPU_SET(1, &curr_set);   //set core 1
        sched_setaffinity(0, sizeof(curr_set), &curr_set); // 0 represents current process

        printf("Parent process core 0 is set: %d\n", CPU_ISSET(0, &curr_set)); //check if core i set
        printf("Parent process core 1 is set: %d\n", CPU_ISSET(1, &curr_set));

        pid_t pid = fork();
	if(pid == 0) //child process
	{
		//set cpu affinity
		CPU_ZERO(&curr_set);     //clear
		CPU_SET(0, &curr_set);   //set core 0ss
		sched_setaffinity(0, sizeof(curr_set), &curr_set);

		printf("Child process core 0 is set: %d\n", CPU_ISSET(0, &curr_set)); //check if core i set
		printf("Child process core 1 is set: %d\n", CPU_ISSET(1, &curr_set));
	}

        while(1);                          
}

//printf("number of cores: %ld\n", sysconf(_SC_NPROCESSORS_CONF)); //number of cores
	
