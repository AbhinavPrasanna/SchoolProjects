#include "stats.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
int max_child(Stats *stats, uint32_t *A, int first, int last) {
    int left = 2 * first;
    int right = left + 1;
    if ((right <= last) && cmp(stats, A[right - 1], A[left - 1] == 1)) {
        return right;
    }
    return left;
}
void fix_heap(Stats *stats, uint32_t *A, int first, int last) {
    bool found = false;
    int mother = first;
    int great = max_child(stats, A, first, last);
    while ((mother <= (last / 2)) && (!found)) {
        if (cmp(stats, A[mother - 1], A[great - 1]) == -1) {
            swap(stats, &A[mother], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}
void build_heap(Stats *stats, uint32_t *A, int first, int last) {
    for (int father = (last / 2); father >= first - 1; father -= 1) {
        fix_heap(stats, A, father, last);
    }
}
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    int first = 1;
    int last = n;
    build_heap(stats, A, first, last);
    for (int leaf = last; leaf >= first; leaf--) {
        swap(stats, &(A[first - 1]), &(A[leaf - 1]));
        fix_heap(stats, A, first, leaf - 1);
    }
}
