#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>            
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#define SIZE 1024

int flag = 1;

//ssize_t read(int fd, void *buf, size_t count);
void *inputMsg(void *p)
{
	char msg[SIZE];

	int fd = open("fifo2", O_WRONLY);
	if(fd == -1)
		printf("Open fifo2 error!\n");
	else
		printf("Fifo2 opened for inputting!\n");
	
	fgets(msg, SIZE, stdin);
	while(strcmp(msg, "88\n") && flag)
	{
		write(fd, msg, SIZE);
		fgets(msg, SIZE, stdin);
	}
	write(fd, msg, SIZE);
	flag = 0;

	close(fd);
	pthread_exit(NULL);
}

void *outputMsg(void *p)
{
	char msg[SIZE];

	int fd = open("fifo1", O_RDONLY);
	if(fd == -1)
		printf("Open fifo1 error!\n");
	else 
		printf("Fifo1 opened for outputting!\n");
	
	read(fd, msg, SIZE);
	while(strcmp(msg, "88\n") && flag)
	{
		printf("[B]: %s", msg);
		read(fd, msg, SIZE);
	}
	
	close(fd);
	pthread_exit(NULL);
}

int main()
{	
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&tid, &attr, inputMsg, NULL);
	pthread_create(&tid, &attr, outputMsg, NULL);

	pthread_join(tid, NULL);
	pthread_join(tid, NULL);
	
	return 0;
}
