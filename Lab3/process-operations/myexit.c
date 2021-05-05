#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/wait.h>
  
int main(void)  
{ 
    	pid_t new_process_id; 
    	int status;
  
    	new_process_id = fork(); 
  
    	if (new_process_id == 0) {  
        	printf("This is in child process: %d\n", getpid());
        	//while(1);
        	exit(-1);
    	} 
    	else {
    		printf("This is in parent process: %d\n", getpid());
    	
        	wait(&status);
        	printf("child exit status: %d\n", WEXITSTATUS(status));
    	}  

    return 0;
} 
