#include <stdio.h>
#ifndef __USE_GNU
#define __USE_GNU   
#endif  
#include <unistd.h>
#include <sched.h>
#include <pthread.h>

int count;

pthread_mutex_t mutex; //delcare mutex

void *producer(void *param); /* threads call this function */
void *consumer(void *param); /* threads call this function */

long int test_n_set(long int *lock)
{
	long int res;
	asm(
		"mov rax, 0;"
		"mov rbx, 1;"
		"lock cmpchg %1, rbx;"
		"mov %0, rax;"
		:
		:"m"(res), "m"(*lock)
	);

	return res;
}

void my_Lock(long *lock)
{
	while (test_n_set(lock));
}

void my_Unlock(long *lock)
{
	*lock = 0;
}

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */
	pthread_attr_init(&attr); /* get the default attributes */

	pthread_mutex_init(&mutex, NULL); //initialization of mutex lock; 
						//NULL means using the default attribute

	while(1)
	{
		count = 5; //init

		pthread_create(&tid1, &attr, producer, NULL); /* create the thread */
		pthread_create(&tid2, &attr, consumer, NULL); /* create the thread */

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
	CPU_ZERO(&cpuSet);     //clear
        CPU_SET(0, &cpuSet);   //set core 0
	sched_setaffinity(0, sizeof(cpuSet), &cpuSet);

	pthread_mutex_lock(&mutex); //lock
	count++; //produce one element
	pthread_mutex_unlock(&mutex); //unlock

	pthread_exit(0);
}

void *consumer(void *param)
{	
	cpu_set_t cpuSet;
	CPU_ZERO(&cpuSet);     //clear
        CPU_SET(1, &cpuSet);   //set core 1
	sched_setaffinity(0, sizeof(cpuSet), &cpuSet);
	
	while (count == 0);

	pthread_mutex_lock(&mutex); //lock
	count--; //consume one element
	pthread_mutex_unlock(&mutex); //unlock

	pthread_exit(0);
}
