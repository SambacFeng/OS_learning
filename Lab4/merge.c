#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE 200000
#define MAX 10000

int res[SIZE];
int p1[SIZE / 2];
int p2[SIZE / 2];

void init()
{
    int i;
    srand((unsigned)time(NULL));
    for (i = 0; i < SIZE; i++)
    {
        p1[i] = rand() % MAX;
        p2[i] = rand() % MAX;
    }
}

void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
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
    printf("p: %d, q: %d, r: %d\n", p, q, r);
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

int main()
{
    init();
    QuickSort(p1, 0, SIZE / 2 - 1);
    QuickSort(p2, 0, SIZE / 2 - 1);
    merge(p1, p2, res);
    int i;
    for (i = 0; i < SIZE / 2; i++)
        printf("1: %d: %d\n", i, p1[i]);
    for (i = 0; i < SIZE / 2; i++)
        printf("2: %d: %d\n", i, p2[i]);
    for (i = 0; i < SIZE; i++)
        printf("3: %d: %d\n", i, res[i]);
    return 0;
}
