#include <stdio.h>
#include <stdlib.h>
#define Malloc(n, type) ((type *)malloc(n * sizeof(type)))
#define Realloc(ptr, n, type) ((type *)realloc(ptr, n * sizeof(type)))

typedef struct
{
    int x;
} DATA;
typedef struct node
{
    DATA data;
    struct node *next;
} NODE;

struct node *Head(int x)  //Creating head of the linked list
{
    struct node *head = Malloc(1, struct node);  
    head->data.x = x;
    head->next = NULL;
    return head;
}

void Print(struct node *head)  //Printing linked list
{
    int count = 0;
    if (NULL == head)
        printf("List is empty");
    struct node *ptr = NULL;
    ptr = head;
    while (NULL != ptr)
    {
        printf(" %d ", ptr->data);
        ptr = ptr->next;
        count++;
    }
    printf("\nnumber of node=%d", count);
}

struct node *insert_at_end(struct node *head, int x)  //Insert an element at the end of the linked list
{
    struct node *ptr, *temp;
    ptr = head;
    temp = Malloc(1, struct node);
    temp->next = NULL;
    temp->data.x = x;
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = temp;
    return head;
}

struct node *insert_at_front(struct node *head, int x)  //Insert an element at the front of the linked list
{
    struct node *temp;
    temp = Malloc(1, struct node);
    temp->data.x = x;
    temp->next = head;
    head = temp;
    return head;
}

struct node *insert_at_position(struct node *head, int x, int pos)  //Insert an element except front and end of the linked list
{
    struct node *temp, *ptr;
    ptr = head;
    int i = 1;
    temp = Malloc(1, struct node);
    temp->data.x = x;
    temp->next = NULL;
    while (i != pos - 1)
    {
        ptr = ptr->next;
        i++;
    }
    temp->next = ptr->next;
    ptr->next = temp;
    return head;
}

struct node *delete_first(struct node *head)  //Delete element from front of the linked list
{
    head = head->next;
    return head;
}

struct node *delete_position(struct node *head, int pos)  //Delete element except front and end of the linked list
{
    struct node *ptr1, *ptr2;
    ptr1 = head;
    ptr2 = head->next;
    int i = 1;
    while (i != pos - 1)
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        i++;
    }
    ptr1->next = ptr2->next;
    free(ptr2);
    return head;
}

struct node *delete_last(struct node *head)  //Delete element from end of the linked list
{
    struct node *ptr1, *ptr2;
    ptr1 = head;
    ptr2 = head->next;
    while (NULL != ptr2->next)
    {
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    ptr1->next = NULL;
    free(ptr2);
    return head;
}

//Driver
int main()
{
    struct node *head, *current;
    int i, j, k, l, n = 0,a[2000];
    printf("Enter elements : ");
	do
	{
		scanf("%d", &a[n]);
		n++;
	} while (getchar() != '\n');
    head = Head(a[0]);
    for (i = 1; i < n; i++)
    {
        head = insert_at_end(head, a[i]);
    }
    Print(head);
    printf("\nEnter the element:");
    scanf("%d", &l);
    printf("Enter the pos:");
    scanf("%d", &k);
    head = insert_at_position(head, l, k);   
    Print(head);
    printf("\n");
    head = delete_position(head, k);
    Print(head);
    return 0;
}