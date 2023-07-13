#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int terms = 0;
int e_terms(void) {
    return terms;
}
double e(void) {
    double seriesamount = 100;
    double kval = 1;
    double finalseriesamount = 1;
    for (int k = 1; absolute(seriesamount) >= EPSILON; k++) {
        kval *= k;
        seriesamount = 1 / kval;
        finalseriesamount += seriesamount;
        terms += 1;
    }
    return finalseriesamount;
}
