#include "stack.h"

#include <stdlib.h>

struct stack *alloc_node(int value, struct stack *next) {
    struct stack *node = malloc(sizeof(struct stack));
    if (node != NULL) {
        node->value = value;
        node->next = next;
    }
    return node;
}

struct stack *stack_init(void) {
    return alloc_node(0, NULL);
}

void stack_push(struct stack *stack, int value) {
    if (stack != NULL) {
        struct stack *node = alloc_node(value, stack->next);
        if (node != NULL) {
            stack->next = node;
        }
    }
}

int stack_pop(struct stack *stack) {
    int value = 0;
    if (stack != NULL && stack->next != NULL) {
        struct stack *node = stack->next;
        value = node->value;
        stack->next = node->next;
        free(node);
    }
    return value;
}

void stack_destroy(struct stack *stack) {
    while (stack != NULL) {
        struct stack *next = stack->next;
        free(stack);
        stack = next;
    }
}
