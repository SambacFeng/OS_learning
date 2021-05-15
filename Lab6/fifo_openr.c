#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>       


int main()
{
	
	int fd = open("myfifo", O_RDONLY);

	if(fd == -1)
		printf("Open fifo error!\n");
	else
		printf("Open for reading: the file descriptor: %d\n", fd);
	
	close(fd);

	return 0;
}
