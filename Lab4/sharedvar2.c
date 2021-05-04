#include <stdio.h>
#include <unistd.h>

int sum = 0;

int main()
{
	pid_t pid;
	
	printf ("The sum is %d\n", sum);
	
	pid = fork();
	
	if(pid == 0)
		printf("The sum is: %d\n", ++sum);
	else
		printf("The sum is: %d\n", ++sum);
		
	return 0;
}
