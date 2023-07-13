#include "node.h"

#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "stack.h"
struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *stack = calloc(1, sizeof(Stack));
    if (stack != NULL) {
        stack->capacity = capacity;
        stack->items = malloc(capacity * sizeof(Node));
        stack->top = 0;
    }
    return stack;
}

void stack_delete(Stack **s) {
    if (*s != NULL && (*s)->items != NULL) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_empty(Stack *s) {
    bool returnvalue = false;
    if (s->top == 0) {
        returnvalue = true;
    }
    return returnvalue;
}

bool stack_full(Stack *s) {
    bool returnvalue = false;
    if (s->top == s->capacity) {
        returnvalue = true;
    }
    return returnvalue;
}

bool stack_push(Stack *s, Node *n) {
    bool returnvalue = false;
    if (stack_full(s) == false) {
        returnvalue = true;
        s->items[s->top] = n;
        s->top++;
    }
    return returnvalue;
}

bool stack_pop(Stack *s, Node **n) {
    bool returnvalue = false;
    if (stack_empty(s) == false) {
        returnvalue = true;
        s->top = s->top - 1;
        *n = s->items[s->top];
        s->items[s->top] = 0;
    }
    return returnvalue;
}

void stack_copy(Stack *dst, Stack *src) {
    uint32_t index = 0;
    while (index < src->capacity) {
        dst->items[index] = src->items[index];
        index++;
    }
    dst->top = src->top;
    return;
}

void stack_print(Stack *s) {
    uint32_t index = 0;
    while (index < s->top) {
        node_print(s->items[index]);
        index++;
    }
}
