// Int wird vorgeben und jede Dezimalziffer soll in eine Liste übergeben werden

#include <stdlib.h>
#include <stdio.h>

typedef struct IntList
{
    int data;
    struct IntList *next;
} IntList;

IntList *newNode(int data)
{
    IntList *node = malloc(sizeof(IntList));
    node->data = data;
    node->next = malloc(sizeof(IntList));
    return node;
}

void push(IntList **head, int data)
{
    IntList *temp = newNode(data);
    temp->next = (*head);
    (*head) = temp;
}

void printList(IntList *head)
{
    IntList *temp = head;
    while (temp != NULL)
    {
        printf("%d,", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    IntList *head = NULL;
    IntList *headBin = NULL;
    int source = 12345;
    int sourceBin = source;
    while (source != 0)
    {
        push(&head, source % 10);
        source /= 10;
    }
    while (sourceBin != 0)
    {
        push(&headBin, sourceBin % 2);
        sourceBin /= 2;
    }

    printList(head);
    printList(headBin);
}