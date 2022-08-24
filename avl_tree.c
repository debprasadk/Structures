#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define Malloc(n, type) (type *)malloc((unsigned)((n) * sizeof(type)))
#define Realloc(loc, n, type) (type *)realloc((char *)(loc), (unsigned)((n) * sizeof(type)))
#define FAILURE -1
#define MAX_NODES 100
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define HEIGHT(T, nodeindex) (((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height)

typedef struct node
{
    int data;
    int left, right, parent, height;
} AVL_NODE;

typedef struct
{
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    AVL_NODE *nodelist;
} AVL_TREE;

void balance(AVL_TREE *tree, int parent, int *node);

int create(AVL_TREE *tree)
{
    int i;
    assert(tree != NULL);
    tree->num_nodes = 0;
    tree->max_nodes = MAX_NODES;
    if (NULL == (tree->nodelist = Malloc(tree->max_nodes, AVL_NODE)))
        printf("Out of memory");
    tree->root = -1;
    tree->free_list = 0;
    for (i = 1; i < tree->max_nodes; i++)
    {
        tree->nodelist[i - 1].left = i;
        tree->nodelist[i - 1].right = -1;
    }
    tree->nodelist[i - 1].left = -1;
    return 0;
}

int grow_tree(AVL_TREE *tree)
{
    int i;
    assert(tree != NULL && tree->num_nodes == tree->max_nodes && tree->free_list == -1);
    tree->max_nodes *= 2;
    if (NULL == (tree->nodelist = Realloc(tree->nodelist, tree->max_nodes, AVL_NODE)))
        printf("grow_tree: out of memory");
    tree->free_list = tree->num_nodes;
    for (i = tree->num_nodes + 1; i < tree->max_nodes; i++)
    {
        tree->nodelist[i - 1].left = i;
        /* tree->nodelist[i-1].right = tree->nodelist[i-1].parent = -1; */
        /* tree->nodelist[i-1].height = 0; */
    }
    tree->nodelist[i - 1].left = -1;
    return 0;
}

int get_new_node(AVL_TREE *tree)
{
    int newnode;
    if (tree->free_list == -1 && FAILURE == grow_tree(tree))
        return FAILURE;
    newnode = tree->free_list;
    tree->free_list = tree->nodelist[tree->free_list].left;
    return newnode;
}

int insert(AVL_TREE *tree, int parent, int *root, int d)
{
    int newnode, thisnode = *root;
    if (thisnode == -1)
    {
        /* INSERT HERE */
        if (FAILURE == (newnode = get_new_node(tree)))
            return FAILURE;
        tree->nodelist[newnode].data = d;
        tree->nodelist[newnode].left = -1;
        tree->nodelist[newnode].right = -1;
        tree->nodelist[newnode].parent = parent;
        tree->nodelist[newnode].height = 0;
        tree->num_nodes++;
        *root = newnode;
    }
    else if (d < tree->nodelist[thisnode].data &&
             FAILURE == insert(tree, thisnode, &(tree->nodelist[thisnode].left), d))
        return FAILURE;
    else if (d > tree->nodelist[thisnode].data &&
             FAILURE == insert(tree, thisnode, &(tree->nodelist[thisnode].right), d))
        return FAILURE;
    balance(tree, parent, root);
    return 0;
}

void rotate_on_insert_LL(AVL_TREE *tree, int parent, int *node)
{
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.34 */
#ifdef DEBUG
    printf("LL (right) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k2 = *node;
    int k1 = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;
    int X = tree->nodelist[k1].left;
    int Y = tree->nodelist[k1].right;

    /* rotate */
    tree->nodelist[k2].left = Y;
    tree->nodelist[k1].right = k2;

    /* parents (optional) */
    tree->nodelist[k1].parent = parent;
    tree->nodelist[k2].parent = k1;
    if (Y != -1)
        tree->nodelist[Y].parent = k2;

    /* update heights */
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, Y), HEIGHT(tree, Z));
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, k2));

    *node = k1;
    return;
}

void rotate_on_insert_RR(AVL_TREE *tree, int parent, int *node)
{
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.36 */
#ifdef DEBUG
    printf("RR (left) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k1 = *node;
    int X = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int Y = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;

    /* rotate */
    tree->nodelist[k1].right = Y;
    tree->nodelist[k2].left = k1;

    tree->nodelist[k2].parent = parent;
    tree->nodelist[k1].parent = k2;
    if (Y != -1)
        tree->nodelist[Y].parent = k1;

    /* update heights */
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, Y));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, Z));

    *node = k2;
    return;
}

void rotate_on_insert_LR(AVL_TREE *tree, int parent, int *node)
{
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.2, Figure 4.38 */
#ifdef DEBUG
    printf("LR (double) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k3 = *node;
    int k1 = tree->nodelist[k3].left;
    int D = tree->nodelist[k3].right;
    int A = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int B = tree->nodelist[k2].left;
    int C = tree->nodelist[k2].right;

    /* rotate */
    tree->nodelist[k2].left = k1;
    tree->nodelist[k2].right = k3;
    tree->nodelist[k1].right = B;
    tree->nodelist[k3].left = C;

    /* TODO: update parent index of affected nodes */

    /* update heights */
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, A), HEIGHT(tree, B));
    tree->nodelist[k3].height = 1 + MAX(HEIGHT(tree, C), HEIGHT(tree, D));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, k3));

    *node = k2;
    return;
}

void rotate_on_insert_RL(AVL_TREE *tree, int parent, int *node)
{
    /* See CMSC 420 Lecture Notes by David M. Mount, UMCP, pg. 39. */
#ifdef DEBUG
    printf("RL (double) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k1 = *node;
    rotate_on_insert_LL(tree, k1, &(tree->nodelist[k1].right));
    rotate_on_insert_RR(tree, parent, node);
    return;
}

void balance(AVL_TREE *tree, int parent, int *node)
{
    int thisnode = *node;
    int left = tree->nodelist[thisnode].left;
    int right = tree->nodelist[thisnode].right;

    if (HEIGHT(tree, left) - HEIGHT(tree, right) > 1)
    {
#ifdef DEBUG
        printf("Left sub-tree too high at %d\n", tree->nodelist[thisnode].data);
#endif // DEBUG

        if (HEIGHT(tree, tree->nodelist[left].left) >= HEIGHT(tree, tree->nodelist[left].right))
            rotate_on_insert_LL(tree, parent, node);
        else
            rotate_on_insert_LR(tree, parent, node);
    }
    else if (HEIGHT(tree, right) - HEIGHT(tree, left) > 1)
    {
#ifdef DEBUG
        printf("Right sub-tree too high at %d\n", tree->nodelist[thisnode].data);
#endif // DEBUG
        if (HEIGHT(tree, tree->nodelist[right].right) >= HEIGHT(tree, tree->nodelist[right].left))
            rotate_on_insert_RR(tree, parent, node);
        else
            rotate_on_insert_RL(tree, parent, node);
    }

    thisnode = *node;
    left = tree->nodelist[thisnode].left;
    right = tree->nodelist[thisnode].right;
    tree->nodelist[thisnode].height = 1 + MAX(HEIGHT(tree, left), HEIGHT(tree, right));
    return;
}

void free_up_node(AVL_TREE *tree, int index)
{
    tree->nodelist[index].left = tree->free_list;
    /* tree->nodelist[index].right = tree->nodelist[index].parent = -1; */
    /* tree->nodelist[index].height = 0; */
    tree->free_list = index;
    return;
}

int find_successor(AVL_TREE *tree, int node)
{
    int child;
    assert(node != -1);
    /* Go to right child, then as far left as possible */
    child = tree->nodelist[node].right;
    if (child == -1) /* no successors */
        return -1;
    if (tree->nodelist[child].left == -1)
    {
        /* Don't do this here for AVL trees */
        /* tree->nodelist[node].right = tree->nodelist[child].right; */
        /* if (tree->nodelist[child].right != -1) */
        /*     tree->nodelist[tree->nodelist[child].right].parent = node; */
        return child;
    }
    while (tree->nodelist[child].left != -1)
    {
        node = child;
        child = tree->nodelist[child].left;
    }
    /* Don't do this here for AVL trees */
    /* tree->nodelist[node].left = tree->nodelist[child].right; */
    /* if (tree->nodelist[child].right != -1) */
    /*     tree->nodelist[tree->nodelist[child].right].parent = node; */
    return child;
}

int delete (AVL_TREE *tree, int parent, int *root, int d)
{
    int thisnode = *root;
    if (thisnode == -1)
        return 0;
    if (d < tree->nodelist[thisnode].data)
    {
#ifdef DEBUG
        printf("Deleting recursively from left subtree ");
        PRINT_NODE(tree, tree->nodelist[thisnode].left);
#endif
        if (FAILURE == delete (tree, thisnode, &(tree->nodelist[thisnode].left), d))
            return FAILURE;
    }
    else if (d > tree->nodelist[thisnode].data)
    {
#ifdef DEBUG
        printf("Deleting recursively from right subtree ");
        PRINT_NODE(tree, tree->nodelist[thisnode].right);
#endif
        if (FAILURE == delete (tree, thisnode, &(tree->nodelist[thisnode].right), d))
            return FAILURE;
    }
    else
    {
        /* DELETE THIS NODE */
        if (tree->nodelist[thisnode].left != -1 &&
            tree->nodelist[thisnode].right != -1)
        {
            int successor = find_successor(tree, thisnode);
            assert(successor != -1);
            tree->nodelist[thisnode].data = tree->nodelist[successor].data;
#ifdef DEBUG
            printf("Replacing ");
            PRINT_NODE(tree, thisnode);
            printf(" by successor ");
            PRINT_NODE(tree, thisnode);
#endif
            if (FAILURE == delete (tree, thisnode, &(tree->nodelist[thisnode].right),
                                   tree->nodelist[successor].data))
                return FAILURE;
        }
        else
        {
            /* EITHER LEAF or ONLY ONE CHILD */
#ifdef DEBUG
            printf("Deleting ");
            PRINT_NODE(tree, thisnode);
#endif
            if (tree->nodelist[thisnode].left != -1)
            {
                *root = tree->nodelist[thisnode].left;
                tree->nodelist[*root].parent = parent;
#ifdef DEBUG
                printf(" replacing by ");
                PRINT_NODE(tree, *root);
#endif
            }
            else if (tree->nodelist[thisnode].right != -1)
            {
                *root = tree->nodelist[thisnode].right;
                tree->nodelist[*root].parent = parent;
#ifdef DEBUG
                printf(" replacing by ");
                PRINT_NODE(tree, *root);
#endif
            }
            else
            {
#ifdef DEBUG
                printf(" (leaf)\n");
#endif
                *root = -1;
            }
            free_up_node(tree, thisnode);
            tree->num_nodes--;
            if (parent != -1)
            {
                int left = tree->nodelist[parent].left;
                int right = tree->nodelist[parent].right;
                tree->nodelist[parent].height = 1 + MAX(HEIGHT(tree, left), HEIGHT(tree, right));
            }
        }
    }
    balance(tree, parent, root);
    return 0;
}

void inorder(AVL_TREE *tree, int root)
{
    if (root == -1)
        return;
    inorder(tree, tree->nodelist[root].left);
    printf("data = %d   height = %d\n", tree->nodelist[root].data, tree->nodelist[root].height);
    inorder(tree, tree->nodelist[root].right);
    return;
}

int main()
{
    AVL_TREE tree;
    int i, n = 0, t[200], x;
    create(&tree);
    printf("Enter elements : ");
    do
    {
        scanf("%d", &t[n++]);
    } while (getchar() != '\n');
    for (i = 0; i < n; i++)
    {
        insert(&tree, -1, &(tree.root), t[i]);
    }
    inorder(&tree,tree.root);
    printf("\nInserting\n");
    insert(&tree, -1, &(tree.root), 500);
    inorder(&tree,tree.root);
    printf("Enter element to delete : ");
    scanf("%d",&x);
    printf("\nDeleting %d:\n",x);
    delete(&tree,-1,&tree.root,x);
    inorder(&tree,tree.root);
    return 0;
}