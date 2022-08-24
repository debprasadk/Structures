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
BTNODE *NewNode(int x)
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
        temp->lchild=InsertNode(temp->lchild, arr,2*i+1,n);  //root at index 0
        temp->rchild=InsertNode(temp->rchild,arr,2*i+2,n);   //root at index 0
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
int serach_element(int x, int Inorder[], int start, int end){
    for(int i = start; i <= end; i++){
        if(x == Inorder[i])
            return i;
    }
}
BTNODE *making_tree_InAndPreOrder(BTNODE *root, int Preorder[], int Inorder[], int start, int end){
    static int ind_p = 0;
    int cur;
    if(start > end)
        return NULL;
    root = NewNode(Preorder[ind_p++]);
    if(end == start)
        return root;
    cur = serach_element(root->d.x, Inorder, start,end);
    root->lchild = making_tree_InAndPreOrder(root->lchild,Preorder, Inorder, start, cur - 1);
    root->rchild = making_tree_InAndPreOrder(root->rchild, Preorder, Inorder, cur + 1, end);
    return root;
}

int main()
{
    
    int i, n = 0;
    BTNODE *root;
    int Inorder[25], Preorder[25];
    printf("Enter elements in Preorder traversal:");
    do
    {
        scanf("%d", &Preorder[n++]);
    } while (getchar() != '\n');
    printf("Enter elements in Inorder traversal:");
    for(i = 0; i < n; i++)
        scanf("%d",&Inorder[i]);
    printf("Pre order is ");
    for(i = 0; i < n; i++)
        printf("%d ",Preorder[i]);
    printf("\nIn order is ");
    for(i = 0; i < n; i++)
        printf("%d ",Inorder[i]);
    root = making_tree_InAndPreOrder(root,Preorder, Inorder, 0, n-1);
    printf("\nPostOrderTraverse is ");
    PostOrderTraverse(root);
    printf("\nPreOrderTraverse is ");
    PreOrderTraverse(root);
    printf("\nInOrderTraverse is ");
    InOrderTraverse(root);
    return 0;
}