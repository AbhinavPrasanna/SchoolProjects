#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int numofterms = 0.0;

int pi_viete_factors(void) {
    return numofterms;
}

double pi_viete(void) {
    double denominator = 2.0;
    double originalnumerator = sqrt_newton(2.0);
    double updatednumerator = sqrt_newton(2.0);
    double total = sqrt_newton(2.0) / 2.0;
    double fraction = 0.0;
    for (double k = 1.0; absolute(1.0 - fraction) >= EPSILON; k++) {
        originalnumerator = updatednumerator;
        updatednumerator = sqrt_newton(2.0 + (originalnumerator));
        fraction = updatednumerator / denominator;
        total *= fraction;
        numofterms++;
    }
    total = 2.0 / total;
    return total;
}
