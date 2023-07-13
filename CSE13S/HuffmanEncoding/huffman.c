#include "pq.h"
#include "stack.h"
#include "huffman.h"
#include "io.h"

#include <stdio.h>

static uint8_t buffer[BLOCK];

Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *l;
    Node *join = NULL;
    Node *node;
    Node *r;
    PriorityQueue *priorityqueue = pq_create(ALPHABET);
    int index = 0;
    while (index < ALPHABET) {
        if (hist[index] != 0) {
            node = node_create(index, hist[index]);
            enqueue(priorityqueue, node);
        }
    }
    while (pq_size(priorityqueue) > 1) {
        dequeue(priorityqueue, &l);
        dequeue(priorityqueue, &r);
        join = node_join(l, r);
        enqueue(priorityqueue, join);
    }
    dequeue(priorityqueue, &join);
    pq_delete(&priorityqueue);
    return join;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    static Code code = { 0, { 0 } };
    uint8_t bit;

    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            table[root->symbol] = code;
        } else {
            code_push_bit(&code, 0);
            build_codes(root->left, table);
            code_pop_bit(&code, &bit);
            code_push_bit(&code, 1);
            build_codes(root->right, table);
            code_pop_bit(&code, &bit);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);
        if (root->left == NULL && root->right == NULL) {
            write_bytes(outfile, buffer, 'L');
            write_bytes(outfile, buffer, root->symbol);
        } else {
            write_bytes(outfile, buffer, 'I');
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    int index = 0;
    Node *l;
    Node *node;
    Node *r;
    Stack *stack = stack_create(ALPHABET);
    while (index < nbytes) {
        if (tree[index] == 'L') {
            index += 1;
            node = node_create(tree[index], 0);
            stack_push(stack, node);
        } else {
            stack_pop(stack, &r);
            stack_pop(stack, &l);
            stack_push(stack, node_join(l, r));
        }
    }
    stack_pop(stack, &node);
    stack_delete(&stack);
    return node;
}

void delete_tree(Node **root) {
    if (*root != NULL) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
}
