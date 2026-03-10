// "IntList* intersperse(IntList *list, int x)", die zwischen die Listenelemente
// den übergebenen Wert x einfügt. Die Funktion soll dabei die Ursprungsliste nicht
// verändern, sondern einen Zeiger auf die veränderte Kopie zurückgeben. Diese muss
// dynamisch allokiert werden - [ ] dies konnte man mit einer node()-Funktion bspw.
// erledigen, die bereits in der .c-Datei vorhanden war.
// Beispiele (Testfälle waren wieder vorgegeben):
// intersperse([1, 2, 3], -3) = [1, -3, 2, -3, 3]
// intersperse([1, 2], -3) = [1, -3, 2]
// Wichtigster Testfall war noch:
// intersperse([ ], -3) = [ ]
// Je nach Implementation konnte vorkommen, dass ihr im letzten Testfall statt "[ ]"
// "[0]" erhaltet. Lösung: man musste für den Fall, dass die übergebene IntList
// NULL ist, NULL zurückgeben.

#include <stdlib.h>
#include <stdio.h>

typedef struct IntList
{
    int data;
    struct IntList *next;
} IntList;

IntList *newNode(int data)
{
    IntList *temp = malloc(sizeof(IntList));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

void push(IntList **head, int data)
{
    IntList *temp = newNode(data);
    temp->next = (*head);
    (*head) = temp;
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

void printList(IntList *head)
{
    while (head != NULL)
    {
        printf("%d, ", head->data);
        head = head->next;
    }
    printf("\n");
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

// intersperse([1, 2, 3], -3) = [1, -3, 2, -3, 3]
IntList *interperseList(IntList *head, int n){
    
}
// {
//     IntList *result = NULL;
//     int listSize = getListSize(head);
//     if (listSize == 0)
//     {
//         return NULL;
//     }
//     int i = 0;
//     while (head != NULL)
//     {
//         if (i % 2 == 0)
//         {
//             push(&result, head->data);
//             head = head->next;
//         }
//         else
//         {
//             push(&result, n);
//         }
//         i++;
//     }
//     return result;
// }

void pop(IntList **head)
{
    (*head) = (*head)->next;
}

int main()
{
    IntList *head = NULL;
    push(&head, 2);
    push(&head, 3);
    append(head, 4);
    pop(&head);
    printList(interperseList(head, 10));
}