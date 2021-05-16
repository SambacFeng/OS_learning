#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


//int mkfifo(const char *filename, mode_t mode);

int main()
{

	int res1 = mkfifo("./fifo1", 0644);
	int res2 = mkfifo("./fifo2", 0644);

	if(res1 == 0)
		printf("Named pipe1 created!\n");
	else if(res1 == -1)
		printf("Failed to create FIFO!\n");
	else
		printf("Error!\n");
	if(res2 == 0)
		printf("Named pipe2 created!\n");
	else if(res2 == -1)
		printf("Failed to create FIFO!\n");
	else
		printf("Error!\n");

	return 0;
}
