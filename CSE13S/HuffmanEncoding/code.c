#include "defines.h"
#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

Code code_init(void) {
    Code code = { 0, { 0 } };
    return code;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool code_full(Code *c) {
    if (c->top < MAX_CODE_SIZE) {
        return false;
    }
    return true;
}

bool code_set_bit(Code *c, uint32_t i) {
    if (i < MAX_CODE_SIZE) {
        c->bits[i] = 1;
        return true;
    }
    return false;
}

bool code_clr_bit(Code *c, uint32_t i) {
    if (i < MAX_CODE_SIZE) {
        c->bits[i] = 0;
        return true;
    }
    return false;
}

bool code_get_bit(Code *c, uint32_t i) {
    if (i < MAX_CODE_SIZE && c->bits[i] == 1) {
        return true;
    }
    return false;
}

bool code_push_bit(Code *c, uint8_t bit) {
    if (!(c->top < MAX_CODE_SIZE)) {
        return false;
    }
    if (bit) {
        c->bits[(c->top++ / 8)] |= (1 << (c->top++ % 8));
    } else {
        c->bits[(c->top++ / 8)] &= ~(1 << (c->top++ % 8));
    }
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    bool topequalszero = (c->top == 0);
    if (topequalszero) {
        return false;
    }
    uint32_t bitposition = 0;
    uint32_t byteposition = 0;
    --c->top;
    bitposition = c->top % 8;
    byteposition = c->top / 8;
    *bit = (c->bits[byteposition] >> bitposition) & 1;
    return true;
}
void code_print(Code *c) {
    uint32_t index = 0;
    while (index < c->top) {
        printf("%d ", c->bits[index]);
        index++;
    }
    printf("\n");
}
