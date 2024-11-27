#include "stack.h"

#include <stdlib.h>

struct stack* init() {
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    if (!s) return NULL;
    s->top = NULL;
    return s;
}

int push(struct stack* s, int value) {
    if (!s) return FAIL;
    struct stack_node* new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    if (!new_node) return FAIL;
    new_node->data = value;
    new_node->next = s->top;
    s->top = new_node;
    return SUCCESS;
}

int pop(struct stack* s, int* value) {
    if (!s || !s->top) return FAIL;
    struct stack_node* temp = s->top;
    *value = temp->data;
    s->top = s->top->next;
    free(temp);
    return SUCCESS;
}

void destroy(struct stack* s) {
    if (!s) return;
    struct stack_node* current = s->top;
    while (current) {
        struct stack_node* next = current->next;
        free(current);
        current = next;
    }
    free(s);
}