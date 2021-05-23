#include <stdio.h>
#ifndef __USE_GNU
#define __USE_GNU   
#endif  
#include <unistd.h>
#include <sched.h>
#include <pthread.h>

int count;

void *producer(void *param); /* threads call this function */
void *consumer(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */
	pthread_attr_init(&attr); /* get the default attributes */

	while(1)
	{
		count = 5; //init

		pthread_create(&tid1, &attr, producer, NULL); /* create a thread */
		pthread_create(&tid2, &attr, consumer, NULL); /* create a thread */

		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
	
		printf("count is: %d\n", count);
	
		if(count == 4 || count == 6)
		{
			printf("press enter to continue\n");
			getchar();
		}
	
	}//end-of-while
}

void *producer(void *param)
{	
	cpu_set_t cpuSet;
	CPU_ZERO(&cpuSet);    //clear
        CPU_SET(0, &cpuSet);   //set core i
	sched_setaffinity(0, sizeof(cpuSet), &cpuSet);

	count++; //produce one element

	pthread_exit(0);
}

void *consumer(void *param)
{	
	cpu_set_t cpuSet;
	CPU_ZERO(&cpuSet);    //clear
        CPU_SET(1, &cpuSet);   //set core i
	sched_setaffinity(0, sizeof(cpuSet), &cpuSet);
	
	count--; //consume one

	pthread_exit(0);
}
