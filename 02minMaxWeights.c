// Aus einer Liste Hanteln(mit Gewicht und Preis)so auswählen, dass man ein bestimmtes Gewicht möglichst günstig erreicht.
// Die beste kombinaton sollte man durch "einfach alles ausprobieren" herausfinden.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct IntList
{
    int data;
    int price;
    struct IntList *next;
} IntList;

IntList *newNode(int data, int price)
{
    IntList *node = malloc(sizeof(IntList));
    node->data = data;
    node->price = price;
    node->next = NULL;
    return node;
}

void push(IntList **head, int data, int price)
{
    IntList *new = newNode(data, price);
    new->next = (*head);
    (*head) = new;
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
        printf("%d.weight %d, price: %d\n", i, current->data, current->price);
        current = current->next;
        i++;
    }
}

int sumListPrice(IntList *head)
{
    int listSum = 0;
    IntList *copy = head;
    while (copy != NULL)
    {
        listSum += copy->price;
        copy = copy->next;
    }
    return listSum;
}

int minMaxWeight(IntList *head)
{
    int threshold = 0;
    int elementAmount = 0;
    IntList *copy = head;
    while (threshold < ((sumListPrice(head) / 2) + 1) && copy != NULL)
    {
        threshold += copy->price;
        elementAmount = elementAmount + 1;
        copy = copy -> next;
    }
    printf("elementCount = %d: ", elementAmount);
    return threshold;
}

/* function to swap data of two nodes a and b*/
void swap(IntList *a, IntList *b)
{
    int tempPrice = a->price;
    a->price = b->price;
    b->price = tempPrice;

    int tempData = a->data;
    a->data = b->data;
    b->data = tempData;
}

/* Bubble sort the given linked list */
void bubbleSort(IntList *start)
{
    int swapped, i;
    IntList *ptr1;
    IntList *lptr = NULL;

    /* Checking for empty list */
    if (start == NULL)
        return;

    do
    {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr)
        {
            if (ptr1->price < ptr1->next->price)
            {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

int getListSize(IntList *head){
    if(head == NULL) return 0;

    int listsize = 0;
    IntList *copy = head;
    for(IntList* n = head; n != NULL; n = n -> next){
        listsize++;
        copy = copy -> next;
    }
    return listsize;
}

int main()
{
    IntList *head = NULL;
    int maxAmount = 10;
    int upperWeightLimit = 50;
    int upperPriceLimit = 200;
    srand(time(NULL));
    for (int i = 0; i < maxAmount; i++)
    {
        push(&head, rand() % upperWeightLimit, rand() % upperPriceLimit);
    }
    printList(head);
    // printf("\n");
    printf("list sum: %d€\n", sumListPrice(head));
    bubbleSort(head);
    printList(head);
    printf("sum: %d\n", minMaxWeight(head));
}