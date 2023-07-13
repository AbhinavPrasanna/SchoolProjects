#include "ht.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bv.h"
#include "bf.h"
#include "node.h"
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include "salts.h"

struct HashTable {
    Node **trees;
    uint32_t size;
    uint64_t salt[2];
};

HashTable *ht_create(uint32_t size) {
    HashTable *hashtable = (HashTable *) calloc(1, sizeof(HashTable));
    if (hashtable != NULL) {
        hashtable->size = size;
        hashtable->salt[0] = SALT_HASHTABLE_LO;
        hashtable->salt[1] = SALT_HASHTABLE_HI;
        hashtable->trees = (Node **) calloc(size, sizeof(Node *));
    }
    return hashtable;
}

void ht_delete(HashTable **ht) {
    for (uint32_t index = 0; index < ht_size((*ht)); index++) {
        bst_delete(&(*ht)->trees[index]);
    }
    free((*ht)->trees);
    free(*ht);
    *ht = NULL;
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    //uint32_t count = 0;
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    if (ht->trees[index] == NULL) {
        return NULL;
    } else {
        return bst_find(ht->trees[index], oldspeak);
    }
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    uint32_t cnt = 0;
    uint32_t index = 0;
    while (index < ht->size) {
        if (ht->trees[index] != NULL) {
            cnt++;
        }
        index++;
    }
    return cnt;
}

double ht_avg_bst_size(HashTable *ht) {
    double cnt = 0;
    uint32_t init = ht_count(ht);
    for (uint32_t index = 0; index < ht->size; index++) {
        if (ht->trees[index] != NULL) {
            cnt += bst_size(ht->trees[index]);
        }
    }
    cnt = cnt / init;
    return cnt;
}

double ht_avg_bst_height(HashTable *ht) {
    double cnt = 0;
    uint32_t init = ht_count(ht);
    for (uint32_t index = 0; index < ht->size; index++) {
        if (ht->trees[index] != NULL) {
            cnt += bst_height(ht->trees[index]);
        }
    }
    cnt = cnt / init;
    return cnt;
}
void ht_print(HashTable *ht) {
    uint32_t index = 0;
    while (index < ht->size) {
        if (ht->trees[index] != NULL) {
            bst_print(ht->trees[index]);
        }
        index++;
    }
}
