#include "node.h"
#include "bst.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "speck.h"
Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    if (root == NULL) {
        return 0;
    } else if (root->left == NULL && root->right == NULL) {
        return 1;
    } else {
        if (bst_height(root->left) > bst_height(root->right)) {
            return 1 + bst_height(root->left);
        } else {
            return 1 + bst_height(root->right);
        }
    }
}

uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return bst_size(root->left) + 1 + bst_size(root->right);
    }
}

Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }
        return root;
    }
    return NULL;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    /*if(root->oldspeak){

        printf("root->oldspeak = %s\n",root->oldspeak);
    }
    printf("oldspeak= %s\n", oldspeak);*/
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            root->left = bst_insert(root->left, oldspeak, newspeak);
        } else if (strcmp(root->oldspeak, oldspeak) < 0) {
            root->right = bst_insert(root->right, oldspeak, newspeak);
        }
        return root;
    }
    return node_create(oldspeak, newspeak);
}
void bst_print(Node *root) {
    if (root == NULL) {
        return;
    }
    bst_print(root->left);
    node_print(root);
    bst_print(root->right);
}
void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&(*root)->left);
        bst_delete(&(*root)->right);
        node_delete(root);
    }
}
