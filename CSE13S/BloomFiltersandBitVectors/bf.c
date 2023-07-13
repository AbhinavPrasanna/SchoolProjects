#include "bf.h"
#include "bv.h"
#include "speck.h"
#include "salts.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct BloomFilter {
    uint64_t tert[2];
    BitVector *fil;
    uint64_t prim[2];
    uint64_t second[2];
};

BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bloomfilter = (BloomFilter *) calloc(1, sizeof(BloomFilter));
    bool check = (bloomfilter != NULL);
    if (check) {
        bloomfilter->tert[0] = SALT_TERTIARY_LO;
        bloomfilter->tert[1] = SALT_TERTIARY_HI;

        bloomfilter->prim[0] = SALT_PRIMARY_LO;
        bloomfilter->prim[1] = SALT_PRIMARY_HI;

        bloomfilter->second[0] = SALT_SECONDARY_LO;
        bloomfilter->second[1] = SALT_SECONDARY_HI;

        bloomfilter->fil = bv_create(size);
        bool check2 = (bloomfilter->fil == NULL);
        if (check2) {
            free(bloomfilter);
            bloomfilter = NULL;
        }
    }
    return bloomfilter;
}

void bf_delete(BloomFilter **bf) {
    if ((*bf) && (*bf)->fil) {
        bv_delete(&(*bf)->fil);
        free(*bf);
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->fil);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    //printf("running bf insert\n");
    uint32_t index1 = hash(bf->prim, oldspeak) % bv_length(bf->fil);
    uint32_t index2 = hash(bf->second, oldspeak) % bv_length(bf->fil);
    uint32_t index3 = hash(bf->tert, oldspeak) % bv_length(bf->fil);
    bv_set_bit(bf->fil, index1);
    bv_set_bit(bf->fil, index2);
    bv_set_bit(bf->fil, index3);
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    bool check1 = bv_get_bit(bf->fil, hash(bf->tert, oldspeak) % bf_size(bf));
    bool check2 = bv_get_bit(bf->fil, hash(bf->prim, oldspeak) % bf_size(bf));
    bool check3 = bv_get_bit(bf->fil, hash(bf->second, oldspeak) % bf_size(bf));
    bool statement = false;
    if (check1 && check2 && check3) {
        statement = true;
    }
    return statement;
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t cnt = 0;
    for (uint32_t index = 0; index < bv_length(bf->fil); index++) {
        if (bv_get_bit(bf->fil, index)) {
            cnt++;
        }
    }
    return cnt;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->fil);
}
