#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 200000
#define MAX 10000

int a[SIZE];

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

void QuickSort(int l, int r)
{
    int ll = l, lr = r, mid = a[(l + r) / 2];
    while (ll < lr)
    {
        while (a[ll] < mid)
            ll++;
        while (a[lr] > mid)
            lr--;
        if (ll <= lr)
        {
            swap(&a[ll], &a[lr]);
            ll++;
            lr--;
        }
    }
    if (l < lr)
        QuickSort(l, lr);
    if (ll < r)
        QuickSort(ll, r);
}

int main()
{
    init();
    QuickSort(0, SIZE - 1);
    int i;
    for (i = 0; i < SIZE; i++)
    	printf("%d", a[i]);
    return 0;
}
