#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>            
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#define SIZE 1024

void *readMsg(void *param);
void *writeMsg(void *param);
void stop();

int flag = 1;

struct pps {
	int fd1, fd2;
	char* buf1;
	char* buf2;
	pthread_t tid1, tid2;
} pp;

int main() {
	char buf1[SIZE];
	int fd1 = open("fifo1", O_WRONLY);

	if(fd1 == -1)
		printf("Open fifo1 error!\n");
	else
		printf("Fifo1 opened for writing!\n");

	char buf2[SIZE];
	int fd2 = open("fifo2", O_RDONLY);

	if(fd2 == -1)
		printf("Open fifo2 error!\n");
	else 
		printf("Fifo2 opened for reading!\n");
		
	pp.fd2 = fd2;
	pp.buf2 = buf2;
	pp.fd1 = fd1;
	pp.buf1 = buf1;

	pthread_t tid1,tid2;
	pthread_attr_t attr1, attr2;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_create(&tid1, &attr1, readMsg, &pp);
	pthread_create(&tid2, &attr2, writeMsg, &pp);
	
	pp.tid1 = tid1;
	pp.tid2 = tid2;
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	return 0;
}

void stop(int fd1,int fd2) {
	close(fd1);
	close(fd2);
	flag = 0;
}
	
void *readMsg(void *param) {

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	struct pps *pp;
	pp = ( struct pps*) param;
	
	while(flag) 
	{
		read(pp->fd2, pp->buf2, SIZE);
		printf("\r[A]: %s", pp->buf2);
		
		if(!strcmp(pp->buf1, "88\n") || !strcmp(pp->buf2, "88\n"))
			break;
		
		printf("[B]: ");
		fflush(stdout);
	}

	stop(pp->fd1, pp->fd2);
	pthread_cancel(pp->tid2);
	pthread_exit(NULL);
}

void *writeMsg(void *param) {

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	struct pps *pp;
	pp = ( struct pps*) param;
	
	while(flag) 
	{
		printf("[B]: ");
		fgets(pp->buf1, SIZE, stdin);
		write(pp->fd1, pp->buf1, SIZE);
	
		if(!strcmp(pp->buf1, "88\n") || !strcmp(pp->buf2, "88\n"))
			break;
	}
	
	stop(pp->fd1, pp->fd2);
	pthread_cancel(pp->tid1);
	pthread_exit(NULL);
}
