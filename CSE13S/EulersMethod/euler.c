#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int numofterms = 0;

int pi_euler_terms(void) {
    return numofterms;
}

double pi_euler(void) {
    double sum = 1.0;
    double numofterms = 2.0;
    double finalsum = 0.0;
    while (sum >= EPSILON) {
        finalsum = finalsum + sum;
        sum = 1.0 / (numofterms * numofterms);
        ++numofterms;
    }
    finalsum = sqrt_newton(6.0 * finalsum);
    return finalsum;
}
