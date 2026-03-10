#include "base.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

typedef struct s_List {
    int value;
    struct s_List* next;
} List;

List* prepend(int value, List* before) {
    List* new = xmalloc(sizeof(List));
    new->value = value;
    new->next = before;
    return new;
}

void print_list(List* list) {
    printf("[");
    while (list != NULL) {
        printf("%d", list->value);
        List* next = list->next;
        if (next) {
            printf(", ");
        }
        list = next;
    }
    printf("]\n");
}

// TODO: Die Funktion soll die letzten beiden ungeraden Zahlen in einer Liste identifizieren, wobei die Reihenfolge ihres Auftretens beibehalten wird.
int odd_last_two(List* list, int* out) {
    int count = 0;
    int letze_ungerade = 0;
    int vorletzte_ungerade = 0;

    // Unser altbekannter Listen-Motor
    for (List* n = list; n != NULL; n = n->next) {
        
        // Ist die Zahl ungerade? (Rest bei Division durch 2 ist nicht 0)
        if (n->value % 2 != 0) {
            
            // Das Fließband: Die bisher letzte wird zur vorletzten...
            vorletzte_ungerade = letze_ungerade;
            // ...und die neu gefundene wird zur neuen letzten.
            letze_ungerade = n->value;
            
            count++; // Wir haben eine ungerade Zahl gefunden, also mitzählen!
        }
    }

    // Nach der Schleife werten wir aus, was wir gefunden haben:
    if (count == 0) {
        return 0; 
    } else if (count == 1) {
        // Nur eine gefunden: Kommt an die erste Stelle im out-Array
        out[0] = letze_ungerade;
        return 1;
    } else {
        // Zwei oder mehr gefunden: Wir geben unsere beiden gemerkten Werte zurück
        out[0] = vorletzte_ungerade;
        out[1] = letze_ungerade;
        return 2;
    }
}


int main() {
    int out[2];

    List* list_0 = NULL;
    printf("Input: ");
    print_list(list_0);
    test_equal_i(odd_last_two(list_0, out), 0);

    List* list_1 = prepend(2,NULL);
    printf("Input: ");
    print_list(list_1);
    test_equal_i(odd_last_two(list_1, out), 0);

    List* list_2 = prepend(7,NULL);
    printf("Input: ");
    print_list(list_2);
    test_equal_i(odd_last_two(list_2, out), 1);
    test_equal_i(out[0], 7);
    printf("Output: ");
    printialn(out, 1);

    List* list_3 = prepend(9, prepend(11, NULL));
    printf("Input: ");
    print_list(list_3);
    test_equal_i(odd_last_two(list_3, out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 9);
    test_equal_i(out[1], 11);

    List* list_4 = prepend(1, prepend(2, prepend(3, prepend(4, prepend(5, NULL)))));
    printf("Input: ");
    print_list(list_4);
    test_equal_i(odd_last_two(list_4, out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 3);
    test_equal_i(out[1], 5);

    List* list_5 = prepend(1, prepend(2, prepend(3, prepend(4, prepend(5, prepend(6, prepend(7, prepend(8, NULL))))))));
    printf("Input: ");
    print_list(list_5);
    test_equal_i(odd_last_two(list_5, out), 2);
    printf("Output: ");
    printialn(out, 2);
    test_equal_i(out[0], 5);
    test_equal_i(out[1], 7);
    return 0;
}