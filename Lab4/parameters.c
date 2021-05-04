#include <pthread.h>
#include <stdio.h>

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	int argument = 12345;

	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */

	/*set the default attributes */
	pthread_attr_init(&attr);

	/* create the thread */
	pthread_create(&tid, &attr, runner, &argument);
	
	printf("This is in parent thread!\n");

	pthread_join(tid, NULL); //wait for the created thread to terminate
}
void *runner(void *param)
{
	printf("The passed argument to the created thread: %d\n", *(int *)param);
	
	pthread_exit(NULL); //exit
}
