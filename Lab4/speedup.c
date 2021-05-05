#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 2000000
#define MAX 10000

int a[SIZE];
int b[SIZE];

void init()
{
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE; i++)
        a[i] = rand() % MAX;
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void QuickSort(int *a, int l, int r)
{
    int ll = l, lr = r, mid = a[(l + r) / 2];
    while (ll < lr)
    {
        while (a[ll] < mid)
            ll++;
        while (a[lr] > mid)
            lr--;
        if (ll <= lr)
            swap(&a[ll++], &a[lr--]);
    }
    if (l < lr)
        QuickSort(a, l, lr);
    if (ll < r)
        QuickSort(a, ll, r);
}

void merge(int *a, int *b, int *c)
{
    int p = 0, q = 0, r = 0;
    while (p < SIZE / 2 && q < SIZE / 2)
        if (a[p] <= b[q])
            c[r++] = a[p++];
        else
            c[r++] = b[q++];
    if (p == SIZE / 2)
        while(q < SIZE / 2)
            c[r++] = b[q++];
    else
        while(p < SIZE / 2)
            c[r++] = a[p++];
    //printf("p: %d, q: %d, r: %d\n", p, q, r);
}

void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	int i = 0;
	int p1[SIZE / 2];
	int p2[SIZE / 2];
	
	init();
	for (i = 0; i < SIZE / 2; i++)
	{
		p1[i] = a[i];
		p2[i] = a[i + SIZE / 2];
	}
	
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */
	pthread_attr_init(&attr);/*set the default attributes */

	pthread_create(&tid, &attr, runner, p1);/* create the thread */
	pthread_create(&tid, &attr, runner, p2);/* create the thread */

	pthread_join(tid, NULL); //wait for the created thread to terminate
	pthread_join(tid, NULL); //wait for the created thread to terminate
	
	merge(p1, p2, b);
}

void *runner(void *param)
{
	QuickSort(param, 0, SIZE / 2 - 1);
	pthread_exit(NULL); //exit
}
