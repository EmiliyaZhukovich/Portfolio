#include "list.h"

#include <stdio.h>

int test_add_door() {
    struct door door1 = {1, 1};
    struct door door2 = {2, 0};

    struct node* root = init(&door1);
    if (!root) return FAIL;

    struct node* new_node = add_door(root, &door2);
    if (!new_node || root->next != new_node || new_node->data != &door2) return FAIL;

    destroy(root);
    return SUCCESS;
}

int test_remove_door() {
    struct door door1 = {1, 1};
    struct door door2 = {2, 0};

    struct node* root = init(&door1);
    if (!root) return FAIL;

    struct node* new_node = add_door(root, &door2);
    if (!new_node) return FAIL;

    root = remove_door(new_node, root);
    if (root->next != NULL) return FAIL;

    root = remove_door(root, root);
    if (root != NULL) return FAIL;

    return SUCCESS;
}

int main() {
    if (test_add_door() == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    if (test_remove_door() == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    return 0;
}