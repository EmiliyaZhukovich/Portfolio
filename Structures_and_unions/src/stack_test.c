#include "stack.h"

#include <stdio.h>

int test_push() {
    struct stack* s = init();
    if (!s) return FAIL;

    if (push(s, 10) != SUCCESS) return FAIL;
    if (s->top->data != 10) return FAIL;

    if (push(s, 20) != SUCCESS) return FAIL;
    if (s->top->data != 20) return FAIL;

    destroy(s);
    return SUCCESS;
}

int test_pop() {
    struct stack* s = init();
    if (!s) return FAIL;

    if (push(s, 10) != SUCCESS) return FAIL;
    if (push(s, 20) != SUCCESS) return FAIL;

    int value;
    if (pop(s, &value) != SUCCESS || value != 20) return FAIL;
    if (pop(s, &value) != SUCCESS || value != 10) return FAIL;

    if (pop(s, &value) != FAIL) return FAIL;

    destroy(s);
    return SUCCESS;
}

int main() {
    if (test_push() == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    if (test_pop() == SUCCESS) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }

    return 0;
}