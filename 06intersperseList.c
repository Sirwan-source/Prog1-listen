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
// Fügt den Wert 'n' zwischen alle Elemente der Liste ein.
IntList *interperseList(IntList *head, int n) {
    
    // 1. Der allerwichtigste Testfall (aus der Aufgabenstellung):
    // Wenn die übergebene Liste leer ist, gib NULL zurück.
    if (head == NULL) {
        return NULL;
    }

    // 2. Den "Anker" und "Greifarm" für die neue Liste vorbereiten.
    // Das erste Element der alten Liste übernehmen wir direkt, 
    // denn VOR dem ersten Element soll ja kein 'n' stehen!
    IntList *result_head = newNode(head->data);
    IntList *result_tail = result_head;

    // 3. Den Motor starten: Wir wandern durch den REST der Original-Liste
    IntList *current = head->next; 
    
    while (current != NULL) {
        // A) Zuerst das Trennzeichen 'n' in die neue Liste einhängen
        result_tail->next = newNode(n);
        result_tail = result_tail->next; // Greifarm weiterschieben

        // B) Danach das eigentliche Element aus der Original-Liste einhängen
        result_tail->next = newNode(current->data);
        result_tail = result_tail->next; // Greifarm weiterschieben

        // C) In der Original-Liste einen Schritt weitergehen
        current = current->next;
    }

    return result_head;
}

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