#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int numofterms = 0;

int pi_bbp_terms(void) {
    return numofterms;
}

double pi_bbp(void) {
    double numerator = 0.0;
    double denominator = 0.0;
    double currentterm = (47.0 / 15.0);
    double total = 0.0;
    double exponent = 1.0;
    double finaldenominator = 0.0;
    int k = 1;
    while (currentterm >= EPSILON) {
        total += currentterm;
        exponent *= 16;
        numerator = (k * ((120 * k) + 151) + 47);
        denominator = k * (k * (k * ((512 * k) + 1024) + 712) + 194) + 15;
        finaldenominator = denominator * exponent;
        currentterm = numerator / finaldenominator;
        ++k;
    }
    numofterms = k;
    return total;
}
