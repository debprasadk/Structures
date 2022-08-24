#include <stdio.h>
#include <stdlib.h>

typedef struct queue
{
    int size, rear, front;
    int *arr;
} QUEUE;

QUEUE *create_queue(int size)  //Creating queue
{
    QUEUE *que = ((QUEUE *)malloc(sizeof(QUEUE)));
    que->front = -1;
    que->rear = -1;
    que->size = size;
    que->arr = ((int *)malloc(que->size * (sizeof(int))));
    return que;
}

int IsFull(QUEUE *que)    //Checking queue Full
{
    if (que->rear == que->size - 1)
        return 1;
    else
        return 0;
}

int IsEmpty(QUEUE *que)  //Checking queue Empty 
{
    if (que->front == que->rear)
        return 1;
    else
        return 0;
}

void enqueue(QUEUE *que, int x)  //enqueue in queue
{
    if (IsFull(que))
        printf("Queue is full.Enqueue is denied\n");
    else
    {
        que->rear++;
        que->arr[que->rear] = x;
    }
}

int dequeue(QUEUE *que)  //dequeue in queue
{
    if (IsEmpty(que))
        printf("Queue is empty.Nothing to dequeue\n");
    else
    {
        que->front++;
        int val = que->arr[que->front];
        return val;
    }
}

//Driver
int main(){
    struct queue *q = create_queue(4);
    // Enqueue few elements
    enqueue(q, 12);
    enqueue(q, 15);
    enqueue(q, 1); 
    printf("Dequeuing element %d\n", dequeue(q));
    printf("Dequeuing element %d\n", dequeue(q));
    printf("Dequeuing element %d\n", dequeue(q)); 
    enqueue(q, 45);
    enqueue(q, 45);
    enqueue(q, 45);
 
    printf("Dequeuing element %d\n", dequeue(q));
    printf("Dequeuing element %d\n", dequeue(q));
    return 0;
}