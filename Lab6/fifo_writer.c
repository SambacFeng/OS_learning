#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>  
#include <string.h>     
#define SIZE 1024

//ssize_t write(int fd, const void *buf, size_t count);


int main()
{
	char str[SIZE];

	int fd = open("myfifo", O_WRONLY);

	if(fd == -1)
		printf("Open fifo error!\n");
	else
		printf("Fifo opened for writing!\n");
	
	fgets(str, SIZE, stdin);
	while(strcmp(str, "88\n"))
	{
		write(fd, str, SIZE);
		fgets(str, SIZE, stdin);
	}
	write(fd, str, SIZE);

	close(fd);
	return 0;
}
