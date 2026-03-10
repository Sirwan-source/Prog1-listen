// Aus einer Liste letztes Element, list Size herausfinden und Append List funktion schreiben

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct IntList
{
    int data;
    struct IntList *next;
} IntList;

IntList *newNode(int data)
{
    IntList *node = malloc(sizeof(IntList));
    node->data = data;
    node->next = NULL;
    return node;
}

void push(IntList **head, int data)
{
    IntList *new = newNode(data);
    new->next = (*head);
    (*head) = new;
}

void pop(IntList **head)
{
    (*head) = (*head)->next;
}

void printList(IntList *head)
{
    if (head == NULL)
    {
        printf("nothing to print, since list is empty\n");
    }
    IntList *current = head;
    int i = 1;
    while (current != NULL)
    {
        printf("%d.data %d\n", i, current->data);
        current = current->next;
        i++;
    }
}

int getListSize(IntList *head)
{
    int listSize = 0;
    IntList *copy = head;
    while (copy != NULL)
    {
        listSize++;
        copy = copy->next;
    }
    return listSize;
}

int getLastElement(IntList *head)
{
    IntList *copy = head;
    int result = 0;
    while (copy != NULL)
    {
        if (copy->next == NULL)
        {
            result = copy->data;
        }

        copy = copy->next;
    }
    return result;
}

IntList *append(IntList *head, int data)
{
    IntList *copy = head;
    IntList *temp = copy;
    while (copy->next != NULL)
    {
        copy = copy->next;
    }
    IntList *new = newNode(data);
    copy->next = new;
    return temp;
}

int main()
{
    IntList *head = NULL;
    int maxAmount = 10;
    int upperLimit = 50;

    srand(time(NULL));
    for (int i = 0; i < maxAmount; i++)
    {
        push(&head, rand() % upperLimit);
    }
    printList(head);
    printf("last element: %d\n", getLastElement(head));

    printList(append(head, 100));
}
