#include "stack.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    int64_t *items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *stack = calloc(1, sizeof(Stack));
    if (stack != NULL) {
        stack->capacity = capacity;
        stack->items = (int64_t *) malloc(capacity * sizeof(int64_t));
        stack->top = 0;
        if (!stack->items) {
            free(stack);
            stack = NULL;
        }
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

bool stack_push(Stack *s, uint32_t x) {
    bool returnvalue = false;
    if (stack_full(s) == false) {
        returnvalue = true;
        s->items[s->top] = x;
        s->top++;
    }
    return returnvalue;
}

bool stack_pop(Stack *s, uint32_t *x) {
    bool returnvalue = false;
    if (stack_empty(s) == false) {
        returnvalue = true;
        s->top = s->top - 1;
        *x = s->items[s->top];
        s->items[s->top] = 0;
    }
    return returnvalue;
}

bool stack_peek(Stack *s, uint32_t *x) {
    bool returnvalue = false;
    if (stack_empty(s) == false) {
        returnvalue = true;
        *x = s->items[s->top - 1];
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

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    uint32_t index = 0;
    while (index < s->top) {
        fprintf(outfile, "%s", cities[s->items[index]]);
        if (index + 1 < s->top) {
            fprintf(outfile, " -> ");
        }
        index++;
    }
    fprintf(outfile, "\n");
}
