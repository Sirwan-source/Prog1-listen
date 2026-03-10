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

// Hängt list2 an das Ende von list1 an und gibt den neuen Kopf zurück.
IntList *mergeLists(IntList *list1, IntList *list2) {
    
    
    if (list1 == NULL) {
        return list2;
    }
    
    // Wenn Liste 2 leer ist, ändert sich an Liste 1 gar nichts.
    if (list2 == NULL) {
        return list1;
    }

    
    IntList *current = list1;

    
    while (current->next != NULL) {
        current = current->next;
    }

    // 3. Die Waggon-Kupplung: Das Ende von Liste 1 zeigt jetzt auf den Anfang von Liste 2
    current->next = list2;

    // Der Kopf der ersten Liste ist jetzt der Kopf des riesigen, langen Zuges.
    return list1;
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