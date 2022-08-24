#include <stdio.h>
#include <stdlib.h>

#define Malloc(n, type) ((type *)malloc(n * sizeof(type)))

typedef struct
{
    int x;
} DATA;

typedef struct node
{
    DATA d;
    struct node *lchild, *rchild;
} BTNODE;

BTNODE *NewNode(int x)  //Creating node
{
    BTNODE *ptr;
    if (NULL == (ptr = Malloc(1, BTNODE)))
        printf("Out of memory");
    ptr->d.x = x;
    ptr->lchild = NULL;
    ptr->rchild = NULL;
    return ptr;
}

BTNODE *InsertNode(BTNODE *root, int arr[], int i, int n)
{
    if(i<n)
    {
        root= NewNode(arr[i]);
        BTNODE *temp =root;
        temp->lchild=InsertNode(temp->lchild, arr, 2*i+1, n);  //root at index 0
        temp->rchild=InsertNode(temp->rchild, arr, 2*i+2, n);   //root at index 0
    }
    return root;
}

void PreOrderTraverse(BTNODE *root)
{
    if (NULL != root)
    {
        printf("%d ", root->d.x);
        PreOrderTraverse(root->lchild);
        PreOrderTraverse(root->rchild);
    }
}

void InOrderTraverse(BTNODE *root)
{
    if (NULL != root)
    {
        InOrderTraverse(root->lchild);
        printf("%d ", root->d.x);
        InOrderTraverse(root->rchild);
    }
}

void PostOrderTraverse(BTNODE *root)
{
    if (NULL != root)
    {
        PostOrderTraverse(root->lchild);
        PostOrderTraverse(root->rchild);
        printf("%d ", root->d.x);
    }
}

//Driver
int main()
{
    int i,n,arr[2500];
    BTNODE *root;
    printf("Enter the number of nood :");
    scanf("%d", &n);  
    printf("Enter the elements :");
    for(i=0;i<n;i++)
        scanf("%d", &arr[i]);
    root=InsertNode(root,arr,0,n);
    printf("\nInorder traversal:");
    InOrderTraverse(root);
    printf("\nPreorder traversal:");
    PreOrderTraverse(root);
    printf("\nPostorder traversal:");
    PostOrderTraverse(root);
    return 0;
}