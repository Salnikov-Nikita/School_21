#ifndef STACK_H
#define STACK_H

struct stack {
    int value;
    struct stack *next;
};

struct stack *stack_init(void);
void stack_push(struct stack *stack, int value);
int stack_pop(struct stack *stack);
void stack_destroy(struct stack *stack);

#endif
