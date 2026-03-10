/*
make skip_list && ./skip_list
*/

#include "base.h"

// Represents a list node.
typedef struct Node Node;
struct Node {
    int value;
    Node* next;
};

// Creates a new list node.
Node* new_node(int value, Node* next) {
    Node* node = xcalloc(1, sizeof(Node));
    node->value = value;
    node->next = next;
    return node;
}

// Prints the list into the given file.
void fprint_list(char* filename, Node* list) {
    require_not_null(filename);
    FILE* f = fopen(filename, "w");
    fprintf(f, "[");
    for (Node* n = list; n; n = n->next) {
        fprintf(f, "%d", n->value);
        if (n->next) fprintf(f, ", ");
    }
    fprintf(f, "]");
    fclose(f);
}

// Reverses list recursively.
Node* reverse_list_rec(Node* list, Node* result) {
    if (list == NULL) return result;
    return reverse_list_rec(list->next, new_node(list->value, result));
}

// Reverses list.
Node* reverse_list(Node* list) {
    return reverse_list_rec(list, NULL);
}

// <purpose statement>
Node* skip_list(Node* list, int gap) {
    require("not negative", gap >= 0);
    Node* res_head = NULL;
    Node* res_tail = NULL;
    
    int count = 0;
    for(Node* n = list; n != NULL; n = n->next){
        if(count % (gap+1) == 0){
            Node* current_new_node = new_node(n->value, NULL);
            if(res_head == NULL){
                res_head = current_new_node;
                res_tail = current_new_node;
            } else {
                res_tail -> next = current_new_node;
                res_tail = current_new_node;
            }
        }
        count++;
    }
    return res_head;
}

void test(void) {
    Node *list0, *list;

    list0 = NULL;
    list = skip_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = skip_list(list0, 0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 3, 4]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, 
            new_node(5, new_node(6, NULL))))));
    list = skip_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 3, 5]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = skip_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 3]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = skip_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 4]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = skip_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = skip_list(list0, 99);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1]");
}

int main(void) {
    test();
    return 0;
}