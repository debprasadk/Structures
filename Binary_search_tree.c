#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
	int data;
	struct node *left, *right;
} tree;

void insert(int value, tree **node)  //insert in proper manner
{
	tree *temp = (tree *)malloc(sizeof(tree));
	temp->data = value;
	temp->right = NULL;
	temp->left = NULL;
	if (*node == NULL)
		*node = temp;
	else
	{
		if (value <= ((*node)->data))
			insert(value, &(*node)->left);
		else
			insert(value, &(*node)->right);
	}
}

tree *createtree(tree *root)  //input elements to create bst
{
	int j = 0, n = 0;
	int a[200];
	printf("Enter elements : ");
	do
	{
		scanf("%d", &a[n]);
		n++;
	} while (getchar() != '\n');
	while (j < n)
	{
		insert(a[j], &root);
		j++;
	}
	return root;
}

tree *Search(tree *node, int d)  //searching an element in bst
{
	tree *root = node;
	if (root == NULL)
		return NULL;
	if (d == root->data)
	{
		return root;
	}
	else if (d < root->data)
	{
		root = Search(root->left, d);
	}
	else
	{
		root = Search(root->right, d);
	}
}

tree *detach_successor(tree *node)  //finding inorder successor
{
    tree *nptr;
    assert(node != NULL);
    /* Go to right child, then as far left as possible */
    nptr = node->right;
    if (nptr == NULL) /* no successors */
        return NULL;
    if (nptr->left == NULL)
    {
        node->right = nptr->right;
        return nptr;
    }
    while (nptr->left != NULL)
    {
        node = nptr;
        nptr = nptr->left;
    }
    node->left = nptr->right;
    return nptr;
}

void delete (tree **nodeptr, int d)  //deleting element if the element is in the bst
{
    tree *node, *s;
    assert(nodeptr != NULL);
    node = *nodeptr;
    if (node == NULL){
        printf("Nothing to delete");
		return;
	}
    if (d < node->data)
        delete (&(node->left), d);
    else if (d > node->data)
        delete (&(node->right), d);
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            /* Case I: leaf, just delete */
            *nodeptr = NULL;
            free(node);
            return;
        }
        if (node->left == NULL)
        {
            /* Case II: only one child */
            *nodeptr = node->right;
            free(node);
            return;
        }
        if (node->right == NULL)
        {
            *nodeptr = node->left;
            free(node);
            return;
        }
        /* Case III: both sub-trees present */
        s = detach_successor(node);
        node->data = s->data;
        free(s);
    }
    return;
}

void InOrderTraverse(tree *root)
{
	if (NULL != root)
	{
		InOrderTraverse(root->left);
		printf("%d ", root->data);
		InOrderTraverse(root->right);
	}
}

//Driver
int main()
{
	tree *root = NULL;
	int x, y;

	root = createtree(root);
	printf("\nIn-order traversal: ");
	InOrderTraverse(root);

	printf("\nEnter element to search :");
	scanf("%d", &x);
	if (NULL != Search(root, x))
		printf("Element found");
	else
		printf("Element not found");

	printf("\nEnter element to delete :");
	scanf("%d", &y);
	delete(&root, y);
	printf("\nAfter delete: ");
	InOrderTraverse(root);

	return 0;
}
