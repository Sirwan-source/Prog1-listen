/* Compile:
 * (Mac OS X)
 * gcc -Wall -Werror -ferror-limit=1 -o GroupItems GroupItems.c
 * bzw. (Linux)
 * gcc -Wall -Werror -std=c99 -o GroupItems GroupItems.c
 * 
 * Run:
 * ./GroupItems
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    void *value;
    struct Node *next;
} Node;

typedef struct List
{
    Node *first;
    Node *last;
} List;

typedef struct Item
{
    char *name;
    char *category;
    double amount;
} Item;

typedef struct Group
{
    char *category;
    double sum;
    int count;
    double max;
} Group;

Item *newItem(char *name, char *category, double amount)
{
    Item *item = calloc(1, sizeof(Item));
    item->name = name;
    item->category = category;
    item->amount = amount;
    return item;
}

void printItem(void *vitem)
{
    Item *item = vitem;
    printf("(%s, %s, %.2f)", item->name, item->category, item->amount);
}

Group *newGroup(char *category, double sum, int count, double max)
{
    Group *group = calloc(1, sizeof(Group));
    group->category = category;
    group->sum = sum;
    group->count = count;
    group->max = max;
    return group;
}

void printGroup(void *vgroup)
{
    Group *group = vgroup;
    printf("(%s, %.2f, %d, %.2f)", group->category, group->sum, group->count, group->max);
}

List *newList(void)
{
    return calloc(1, sizeof(List));
}

Node *newNode(void *value)
{
    Node *node = calloc(1, sizeof(Node));
    node->value = value;
    return node;
}

void print(List *list, void (*printItem)(void *))
{
    if (list == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("[");
        for (Node *node = list->first; node != NULL; node = node->next)
        {
            printItem(node->value);
            if (node->next != NULL)
            {
                printf(" ");
            }
        }
        printf("]\n");
    }
}

void append(List *list, void *value)
{
    Node *p = newNode(value);
    if (list->last != NULL)
        list->last->next = p;
    list->last = p;
    if (list->first == NULL)
        list->first = p;
}

Group *findGroup(List *list, char *category)
{
    for (Node *node = list->first; node != NULL; node = node->next)
    {
        Group *group = node->value;
        if (strcmp(group->category, category) == 0)
        {
            return group;
        }
    }
    return NULL;
}

/* Gruppiert Elemente in der Liste nach Kategorie. Die übergebene Liste 
 * enthält Elemente vom Typ Item. Die zurückgegebene Liste enthält Elemente 
 * vom Typ Group. Jede Gruppe enthält den Namen der Kategorie, die Summe der 
 * Item-Werte, das Maximum der Item-Werte sowie die Anzahl der Items in der 
 * Kategorie. */
List *groupItems(List *list)
{
    // todo: implement
    List *groups = newList();
    for (Node *node = list->first; node != NULL; node = node->next)
    {
        Item *item = node->value;
        Group *group = findGroup(groups, item->category);
        if (group == NULL)
        {
            group = newGroup(item->category, 0, 0, -1e100);
            append(groups, group);
        }
        group->sum += item->amount;
        group->count++;
        if (item->amount > group->max)
        {
            group->max = item->amount;
        }
    }
    return groups;
}

int tests(void)
{
    List *items = newList();
    append(items, newItem("bread", "food", 3.00));        // €
    append(items, newItem("cake", "food", 5.00));         // €
    append(items, newItem("apple juice", "drink", 2.00)); // €
    append(items, newItem("water", "drink", 1.50));       // €
    print(items, printItem);
    List *groups = groupItems(items);
    print(groups, printGroup);

    items = newList();
    append(items, newItem("Giraffe", "Paarhufer", 1600.0));    // kg
    append(items, newItem("Hirschferkel", "Paarhufer", 12.0)); // kg
    append(items, newItem("Flusspferd", "Paarhufer", 4000.0)); // kg
    append(items, newItem("Honigbiene", "Insekt", 82));        // mg
    append(items, newItem("Ameise", "Insekt", 10));            // mg
    append(items, newItem("Marienkäfer", "Insekt", 87));       // mg
    append(items, newItem("Karpfen", "Fisch", 30));            // kg
    append(items, newItem("Walhai", "Fisch", 12000));          //
    print(items, printItem);
    groups = groupItems(items);
    print(groups, printGroup);

    return 0;
}

int main(void)
{
    tests();
    return EXIT_SUCCESS;
}
