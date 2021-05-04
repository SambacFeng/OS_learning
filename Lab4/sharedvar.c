#include <pthread.h>
#include <stdio.h>

int sum = 0;

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2; /* the thread identifier */
	
	pthread_attr_t attr; /* thread attribute */
	pthread_attr_init(&attr); /* set the default attributes */
	
	printf("The sum is: %d\n", sum);
	
	pthread_create(&tid1, &attr, runner, NULL); // create thread
	pthread_create(&tid2, &attr, runner, NULL); // create thread
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
}

/* The thread will begin control in this function */
void *runner(void *param)
{
	printf("The sum is: %d\n", ++sum);
	pthread_exit(NULL);
}
