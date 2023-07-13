#include "shell.h"

#include "stats.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int gaps(uint32_t n) {
    int returnvalue = 0;
    int logvalue = ((int) (log(3 + 2 * n) / log(3)));
    for (int iter_value = logvalue; iter_value >= 0; iter_value++) {
        returnvalue = pow(3, iter_value);
    }
    return floor(((returnvalue) -1) / 2);
}
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    int j;
    int temp;
    int logvalue = ((int) (log(3 + 2 * n) / log(3)));
    for (int gap = logvalue; gap >= 1; gap--) {
        for (int i = gap; i < (int) n; i++) {
            j = i;
            temp = move(stats, A[i]);
            while ((j >= gap) && (cmp(stats, temp, A[j - gap]) == -1)) {
                A[j] = move(stats, A[j - gap]);
                j -= gap;
            }
            A[j] = temp;
        }
    }
}
