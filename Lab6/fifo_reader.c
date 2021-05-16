#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>            
#include <string.h>
#define SIZE 1024

//ssize_t read(int fd, void *buf, size_t count);


int main()
{	
	char str[SIZE];

	int fd = open("myfifo", O_RDONLY);

	if(fd == -1)
		printf("Open fifo error!\n");
	else 
		printf("Fifo opened for reading!\n");

	read(fd, str, SIZE);
	while(strcmp(str, "88\n"))
	{
		printf("String read: %s", str);
		read(fd, str, SIZE);
	}
	printf("String read: %s", str);

	close(fd);
	return 0;
}
