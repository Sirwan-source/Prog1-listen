// Aus einem Tree eine Liste machen

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct IntNode
{
    int data;
    struct IntNode *next;
} IntNode;

IntNode *newNode(int data)
{
    IntNode *node = malloc(sizeof(IntNode));
    node->data = data;
    return node;
}

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *newTreeNode(int data)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode *createRandomTree(int randomEntries[], TreeNode *node, int index, int arrayLength)
{
    if (index < arrayLength)
    {
        TreeNode *temp = newTreeNode(randomEntries[index]);
        node = temp;
        node->left = createRandomTree(randomEntries, node->left, 2 * index + 1, arrayLength);
        node->right = createRandomTree(randomEntries, node->right, 2 * index + 2, arrayLength);
    }
    return node;
}

IntNode *createRandomList(int randomNumbers[], int arrayLength)
{

    IntNode *head = newNode(0);
    for (int i = 0; i < arrayLength; i++)
    {
        IntNode *next = newNode(randomNumbers[i]);
        head->next = next;
        head = next;
    }

    return head;
}

TreeNode *listToTree(IntNode *head, int listLength)
// {
//     if (listLength <= 0)
//     {
//         return NULL;
//     }

//     TreeNode *left = listToTree(head, listLength / 2);

//     TreeNode *root = newTreeNode(head->data);
//     root->left = left;

//     head = head->next;

//     root->right = listToTree(head, listLength - listLength / 2 - 1);

//     return root;
// }

void inOrderPrint(TreeNode *node)
{
    if (node != NULL)
    {
        inOrderPrint(node->left);
        printf("%d ", node->data);
        inOrderPrint(node->right);
    }
}

int main()
{
    int maxEntities = 12;
    int minIndex = 0;
    int maxIndex = 10;
    int randomEntries[maxEntities];
    srand(time(0));

    for (int i = 0; i < maxEntities; i++)
    {
        randomEntries[i] = rand() % (maxIndex + 1 - minIndex) + minIndex;
        printf("%d|", randomEntries[i]);
    }
    printf("\n");

    IntNode *head = createRandomList(randomEntries, maxEntities);

    int listLength = 0;
    for (IntNode *node = head; node != NULL; node = node->next)
    {
        printf("%d\n", node->data);
        listLength++;
    }
    printf("length: %d\n", listLength);

    TreeNode *constructedTree = listToTree(head, listLength);
    inOrderPrint(constructedTree);
    printf("\n");

    //-------------------------------

    TreeNode *treeHead = newTreeNode(0);
    treeHead = createRandomTree(randomEntries, treeHead, 0, maxEntities);
    inOrderPrint(treeHead);
    printf("\n");
    return 0;
}
