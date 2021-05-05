#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
  
int main(void)  
{ 
    	pid_t new_process_id; 
  
    	new_process_id = fork(); 
  
    	if (new_process_id == 0) {  
        	printf("This is in child process: %d\n", getpid());
        	execl("./myhello", " ", NULL); //path + parameters
        	//execl("./mysum", " ", "2", "3", NULL); //path + parameters
        	
        	printf("This is the rest of the child process\n");
    	} 
    	else {
    		printf("This is in parent process: %d\n", getpid());

    	}  

    	return 0;
} 
