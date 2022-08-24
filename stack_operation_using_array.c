#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
    int size, top;
    int *arr;
} STACK;

STACK *create_stack(int size)  //Creating stack
{
    STACK *sp = ((STACK *)malloc(sizeof(STACK)));
    sp->size = size;
    sp->top = -1;
    sp->arr = ((int *)malloc(sp->size * (sizeof(int))));
    return sp;
}

int IsEmpty(STACK *stack)  //Checking stack Empty 
{
    if (stack->top == -1)
        return 1;
    else
        return 0;
}

int IsFull(STACK *stack)  //Checking stack Full
{
    if (stack->top == stack->size - 1)
        return 1;
    else
        return 0;
}

void push(STACK *sp, int x)  //Push in stack
{
    if (IsFull(sp))
        printf("Stack is full.Push is denied");
    else
    {
        sp->top++;
        sp->arr[sp->top] = x;
    }
}

int pop(STACK *sp)  //Pop in stack
{
    if (IsEmpty(sp))
        printf("Stack is empty.Nothing to pop");
    else
    {
        int val = sp->arr[sp->top];
        sp->top--;
        return val;
    }
}

//Driver
int main()
{
    STACK *sp = create_stack(10);
    
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, i;
    printf("Before pushing, Empty: %d\n", IsEmpty(sp));
    printf("Before pushing, Full: %d\n", IsFull(sp));
    for (i = 0; i < 10; i++)
        push(sp, i);
    printf("After pushing, Empty: %d\n", IsEmpty(sp));
    printf("After pushing, Full: %d\n", IsFull(sp));
    pop(sp);
    printf("After poping, Empty: %d\n", IsEmpty(sp));
    printf("After poping, Full: %d\n", IsFull(sp));
    return 0;
}