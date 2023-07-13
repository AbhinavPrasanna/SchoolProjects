#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "node.h"
#include "speck.h"
#include "bf.h"
#include "bv.h"

Node *node_create(char *oldspeak, char *newspeak) {
    Node *node = (Node *) calloc(1, sizeof(Node));
    if (node) {
        node->right = NULL;
        node->left = NULL;
        if (oldspeak) {
            node->oldspeak = calloc(1, strlen(oldspeak) + 1);
            if (node->oldspeak) {
                node->oldspeak = strdup(oldspeak);
            }
        } else {
            node->oldspeak = NULL;
        }
        if (newspeak) {
            node->newspeak = calloc(1, strlen(newspeak) + 1);
            if (node->newspeak) {
                node->newspeak = strdup(newspeak);
            }
        } else {
            node->newspeak = NULL;
        }
    }
    return node;
}

void node_delete(Node **n) {
    if ((*n)->newspeak) {
        free((*n)->newspeak);
    }
    if ((*n)->oldspeak) {
        free((*n)->oldspeak);
    }
    if (*n) {
        free((*n));
        *n = NULL;
    }
}

void node_print(Node *n) {
    bool check = n->oldspeak != NULL;
    bool check2 = n->newspeak != NULL;
    if (check && check2) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
    } else {
        printf("%s\n", n->oldspeak);
    }
}
