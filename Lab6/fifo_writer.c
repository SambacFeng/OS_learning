#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>       
#include <unistd.h>  
#include <string.h>     


//ssize_t write(int fd, const void *buf, size_t count);


int main()
{
	char buf[1024];

	int fd = open("myfifo", O_WRONLY);

	if(fd == -1)
		printf("Open fifo error!\n");
	else
		printf("Fifo opened for writing!\n");
	
	char c;
	c = getchar();
	while(c != '!')
	{
		memset(buf, c, 1);
		write(fd, buf, 1);
	}
	// getchar();

	// memset(buf, 'A', 10);
	// memset(buf + 10, '\0', 1);
	// write(fd, buf, 11);

	close(fd);
	return 0;
}
