#include <stdio.h>  
#include <stdlib.h>  

int main(int argc, char *argv[])
{
   	if(argc != 3)
   	{
   		printf("Please input two integers as the arguments!\n");
   		return -1;
   	}
   	printf("The sum is: %d\n", atoi(argv[1]) + atoi(argv[2]));

	return 0;
}
