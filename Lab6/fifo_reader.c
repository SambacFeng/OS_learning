#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>            
#include <string.h>

//ssize_t read(int fd, void *buf, size_t count);


int main()
{	
	char buf[1024]; //buffer

	int fd = open("myfifo", O_RDONLY);

	if(fd == -1)
		printf("Open fifo error!\n");
	else 
		printf("Fifo opened for reading!\n");

	while(1)
	{
		read(fd, buf, 1024);
	}
	printf("String read: %s\n", buf);

	close(fd);
	return 0;
}
