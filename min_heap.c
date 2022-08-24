#include <stdio.h>
#include <stdlib.h>
#define MAX 2000
#define Malloc(n, type) ((type *)malloc(n * sizeof(type)))

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void *MinHeapify(int arr[], int i, int n)  
{
    int smallest = i;
    int lchild = 2 * i + 1;
    int rchild = 2 * i + 2;
    if (lchild < n && arr[smallest] > arr[lchild])
        smallest = lchild;
    if (rchild < n && arr[smallest] > arr[rchild])
        smallest = rchild;
    if (i != smallest)
    {
        swap(&arr[smallest], &arr[i]);
        MinHeapify(arr, smallest, n);
    }
}

void *BuildHeap(int arr[], int n)  //Creating min heap from an array
{
    int i;
    for (i = n / 2; i >= 0; i--)
        MinHeapify(arr, i, n);
}

void *Insert(int arr[], int n, int key)  //Insert an element in min-heap
{
    arr[n - 1] = key;
    BuildHeap(arr, n);
}

void *delete (int arr[], int n)  //Delete minimum element from min-heap
{
    arr[0] = arr[n - 1];
    BuildHeap(arr, n);
}

void *Print(int arr[], int n)  //Print of min heap
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
    BuildHeap(arr, n);
    printf("After heapify\n");
    Print(arr, n);

    printf("Enter the element to insert :");
    scanf("%d", &x);
    n++;
    Insert(arr, n, x);
    printf("After insertion\n");
    Print(arr, n);

    printf("Deleting :\n");
    while (n)
    {
        delete (arr, n);
        n--;
        Print(arr, n);
    }

    return 0;
}