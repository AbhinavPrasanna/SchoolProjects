#include "node.h"
#include "code.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node != NULL) {
        node->left = NULL;
        node->symbol = symbol;
        node->right = NULL;
        node->frequency = frequency;
    }
    return node;
}

void node_delete(Node **n) {
    if (*n != NULL) {
        free(*n);
        *n = NULL;
    }
}

Node *node_join(Node *left, Node *right) {
    Node *node = (Node *) malloc(sizeof(Node));
    if (node != NULL) {
        node->frequency = left->frequency;
        node->frequency += right->frequency;
        node->symbol = '$';
        node->right = right;
        node->left = left;
    }
    return node;
}

void node_print(Node *n) {
    if (n != NULL) {
        printf("%d", n->symbol);
        node_print(n->left);
        node_print(n->right);
    }
}
