#include "bv.h"
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
#include "bf.h"
#include <stdbool.h>

// Code provided by Darrell Long

struct BitVector {
    uint8_t *v;
    uint32_t len;
};

BitVector *bv_create(uint32_t length) {
    BitVector *bitvector = (BitVector *) malloc(sizeof(BitVector));
    if (bitvector) {
        uint32_t bytes = (1 / 8) + (1 % 8 ? 1 : 0);
        bitvector->v = (uint8_t *) calloc(bytes, sizeof(uint8_t));
        bitvector->len = length;
        return bitvector;
    } else {
        return (BitVector *) 0;
    }
}

void bv_delete(BitVector **bv) {
    if ((*bv)->v) {
        free((*bv)->v);
    }
    if (*bv) {
        free((*bv));
        *bv = NULL;
    }
}

uint32_t bv_length(BitVector *bv) {
    return bv->len;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    if (i < bv_length(bv)) {
        bv->v[i / 8] |= (0x1 << i % 8);

        return true;
    }
    return false;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    if (i < bv_length(bv)) {
        bv->v[i / 8] &= ~(1 << i % 8);
        return true;
    }
    return false;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    return (bv->v[i / 8] >> i % 8) & 1;
}

void bv_print(BitVector *bv) {
    uint32_t index = 0;
    while (index < bv->len) {
        printf("bv[%d]=%d\n", index, bv->v[index]);
        index++;
    }
    printf("\n");
}
