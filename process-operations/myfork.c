#include <unistd.h>  
#include <stdio.h>  
  
int main()  
{ 
    	pid_t new_process_id;  //pid_t: type
  
 	new_process_id = fork();  //system call
  
    	if (new_process_id == 0) //in child process
    	{
        	printf("This is in child process: %d\n", getpid()); //get process ID
        	while(1);
        }
    	else //in parent process
    	{
    		printf("This is in parent process: %d\n", getpid()); //get process ID
    		while(1);
    	}

    	return 0;
} 
