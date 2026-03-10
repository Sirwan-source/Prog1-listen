/*
make crop_list && ./crop_list
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

// Counts the number of values in list.
int length_list(Node* list) {
    // todo: implement
    int count = 0;
    for(Node* n = list; n != NULL; n = n ->next){
        count++;
    }
    return count;
}

// Creates a result list from the input list, by removing the first r and the last r elements from the input list. For example, crop([1, 2, 3, 4], 1) becomes [2, 3]. Maintains the original order of the remaining elements. Does not change the input list.
Node* crop_list(Node* list, int r) {
    require("not negative", r >= 0);
    // todo: implement
    int len = length_list(list);
    Node* res_head = NULL;
    Node* res_tail = NULL;

    int count = 0;
    for(Node* n = list; n != NULL; n = n ->next){
        if(count >= r && count < (len - r)){
            Node* current_new_node = new_node(n->value,NULL);
            if(res_head == NULL){
                res_head = current_new_node;
                res_tail = current_new_node;
            } else {
                res_tail ->next = current_new_node;
                res_tail = current_new_node;
            }
        }
        count++;
    }
    return res_head;
}

void test(void) {
    Node *list0, *list;

    Node* list_a = NULL;
    test_equal_i(length_list(list_a), 0);

    list_a = new_node(1, list_a);
    test_equal_i(length_list(list_a), 1);

    list_a = new_node(2, list_a);
    test_equal_i(length_list(list_a), 2);

    list_a = new_node(3, list_a);
    test_equal_i(length_list(list_a), 3);

    list0 = NULL;
    list = crop_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 0);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[1, 2, 3, 4]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 1);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2, 3]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(1, new_node(2, new_node(3, new_node(4, NULL))));
    list = crop_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL)))));
    list = crop_list(list0, 2);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[2]");

    list0 = new_node(0, new_node(1, new_node(2, new_node(3, new_node(4, NULL)))));
    list = crop_list(list0, 3);
    fprint_list("mytmp.txt", list);
    test_equal_s(s_read_file("mytmp.txt"), "[]");
}

int main(void) {
    test();
    return 0;
}