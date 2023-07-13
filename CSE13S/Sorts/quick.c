#include "quick.h"

#include "stats.h"

#include <stdint.h>
#include <stdio.h>
uint32_t partition(uint32_t *A, uint32_t low, uint32_t high, Stats *stats) {
    uint32_t i = low - 1;
    for (uint32_t j = low; j <= high; j++) {
        if (cmp(stats, A[j - 1], A[high - 1]) == -1) {
            i++;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[high - 1]);
    return i + 1;
}
void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {
    if (low < high) {
        uint32_t p = partition(A, low, high, stats);
        quick_sorter(stats, A, low, p - 1);
        quick_sorter(stats, A, p + 1, high);
    }
}
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
