#include "pq.h"

#include "node.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *priorityqueue = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (priorityqueue != NULL) {
        priorityqueue->capacity = capacity;
        priorityqueue->size = 0;
        priorityqueue->items = malloc(capacity * sizeof(Node));
    }
    return priorityqueue;
}

static inline int parentindex(uint32_t index) {
    int integer = (int) (index - 1) / 2;
    return integer;
}

static inline uint32_t leftindex(uint32_t index) {
    uint32_t integer = 2 * index + 1;
    return integer;
}

static inline uint32_t rightindex(uint32_t index) {
    uint32_t integer = 2 * index + 2;
    return integer;
}

void pq_delete(PriorityQueue **q) {
    if (*q != NULL && (*q)->items != NULL) {
        free((*q)->items);
        (*q)->items = NULL;
        free(*q);
        *q = NULL;
    }
}

void pq_swap(PriorityQueue *q, uint32_t index, uint32_t index2) {
    Node *temp = q->items[index];
    q->items[index] = q->items[index2];
    q->items[index2] = temp;
}

bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}
//helper functions
void heap_up(PriorityQueue *q) {
    uint32_t index = q->size - 1;
    bool check1 = parentindex(index) >= 0;
    bool check2 = (q->items[parentindex(index)]->frequency > q->items[index]->frequency);
    bool check = check1 && check2;
    if (check) {
        pq_swap(q, parentindex(index), index);
        index = parentindex(index);
        check1 = parentindex(index) >= 0;
        check2 = (q->items[parentindex(index)]->frequency > q->items[index]->frequency);
        check = check1 && check2;
    }
}

void heap_down(PriorityQueue *q) {
    int index = 0;
    bool check1 = leftindex(index) < q->size;
    bool check2 = (rightindex(index) < q->size) && (q->items[leftindex(index)]->frequency);
    int smallchildind = leftindex(index);
    bool check3 = (q->items[index]->frequency > q->items[smallchildind]->frequency);
    while (check1) {
        smallchildind = leftindex(index);
        check2 = (rightindex(index) < q->size) && (q->items[leftindex(index)]->frequency);
        if (check2) {
            smallchildind = rightindex(index);
        }
        check3 = (q->items[index]->frequency > q->items[smallchildind]->frequency);
        if (check3) {
            pq_swap(q, index, smallchildind);
        } else {
            break;
        }
        index = smallchildind;
        check1 = leftindex(index) < q->size;
    }
}
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

bool enqueue(PriorityQueue *q, Node *n) {
    bool qcheck = q->size == q->capacity;
    if (qcheck) {
        return false;
    }
    q->items[q->size] = n;
    q->size = q->size + 1;
    heap_up(q);
    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    bool qcheck = q->size == 0;
    if (qcheck) {
        return false;
    }
    *n = q->items[0];
    q->items[0] = q->items[q->size - 1];
    q->size = q->size - 1;
    heap_down(q);
    return true;
}

void pq_print(PriorityQueue *q) {
    int index = 0;
    while ((uint32_t) index < q->size) {
        node_print(q->items[index]);
        index++;
    }
}
