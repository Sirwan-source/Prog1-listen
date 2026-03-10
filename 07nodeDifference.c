// Differenz zwischen dem minimalen und dem maximalem Element in einer Liste von INT berechnen
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

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
    while (head != NULL)
    {
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("\n");
}

int diffMinMax(IntList *head){
    if(head == NULL) return 0;
    int min = INT_MAX;
    int max = INT_MIN;

    for(IntList* current = head; current != NULL; current = current -> next){
    
        if(current -> data < min) min = current -> data;
        if(current -> data > max) max = current -> data;

        // head = head -> next;
    }
    return abs(max - min);
}
//     if(head == NULL) return 0;

//     int min = head -> data;
//     int max = head -> data;

//     while(head != NULL){
//         if(head -> data < min) min = head -> data;

//         if(head -> data > max) max = head -> data;

//         head = head -> next;
//     }
//     return max - min;
// }


int main()
{
    IntList *testList = NULL;
    push(&testList, 2);
    push(&testList, 3);
    push(&testList, 5);
    push(&testList, 4);

    printList(testList);
    printf("%d\n", diffMinMax(testList));
}