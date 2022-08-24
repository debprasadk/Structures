#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 2000

#define Malloc(n, type) ((type *)malloc(n * sizeof(type)))

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void *maxheapify(int arr[], int i, int n)
{
    int largest = i;
    int lchild = 2 * i + 1;
    int rchild = 2 * i + 2;
    if (lchild < n && arr[lchild] > arr[largest])
        largest = lchild;
    if (rchild < n && arr[rchild] > arr[largest])
        largest = rchild;
    if (largest != i)
    {
        swap(&arr[largest], &arr[i]);
        maxheapify(arr, largest, n);
    }
}

void *build_heap(int arr[], int n)  //Creating min heap from an array
{
    int i;
    for (i = n / 2; i >= 0; i--)
        maxheapify(arr, i, n);
}

void *Insert(int arr[], int n, int key)  //Insert an element in max-heap
{
    arr[n - 1] = key;
    build_heap(arr, n);
}

void *delete (int arr[], int n)  //Delete minimum element from max-heap
{
    arr[0] = arr[n - 1];
    build_heap(arr, n);
}

void *Print(int arr[], int n)  //Print of max-heap
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

//Driver 
int main()
{
    int i, n = 0, arr[MAX], x, y;
    printf("Enter elements:");
    do
    {
        scanf("%d", &arr[n]);
        n = n + 1;
    } while (getchar() != '\n');
    build_heap(arr, n);
    Print(arr, n);

    delete (arr, n);
    n--;
    printf("After deletion\n");
    Print(arr, n);

    printf("Enter the element to insert :");
    scanf("%d", &x);
    n++;
    Insert(arr, n, x);
    printf("After insertion\n");
    Print(arr, n);

    return 0;
}