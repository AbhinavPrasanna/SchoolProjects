#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#define EPSILON 1e-14

static int terms = 0;

double sqrt_newton(double number) {
    double z = 0.0;
    double y = 1.0;
    while (absolute(y - z) > EPSILON) {
        z = y;
        y = 0.5 * (z + number / z);
        terms++;
    }
    return y; //Code provided by Professor Long of CSE13S
}

int sqrt_newton_iters(void) {
    return terms;
}
