// Zwei Listen mergen
#include <stdio.h>
#include <stdlib.h>

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
    IntList *node = newNode(data);
    node->next = (*head);
    (*head) = node;
}

void printList(IntList *head)
{
    IntList *temp = head;
    while (temp != NULL)
    {
        printf("%d, ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void pop(IntList **head)
{
    (*head) = (*head)->next;
}

IntList *append(IntList *head, int data)
{
    IntList *copy = head;
    IntList *temp = copy;
    IntList *new = newNode(data);
    while (copy->next != NULL)
    {
        copy = copy->next;
    }
    copy->next = new;
    return temp;
}

IntList *mergeLists(IntList *list1, IntList *list2)
{
    IntList *result = NULL;
    while (list1 != NULL)
    {
        push(&result, list1->data);
        while (list2 != NULL)
        {
            push(&result, list2->data);
            list2 = list2->next;
        }
        list1 = list1->next;
    }
    return result;
}

int getListSize(IntList *head)
{
    int result = 0;
    while (head != NULL)
    {
        result++;
        head = head->next;
    }
    return result;
}

int main()
{
    IntList *test = newNode(2);
    push(&test, 3);
    append(test, 4);

    IntList *test2 = NULL;
    push(&test2, 9);
    push(&test2, 8);
    printList(mergeLists(test, test2));
    printf("%d\n", getListSize(test));
    return 0;
}