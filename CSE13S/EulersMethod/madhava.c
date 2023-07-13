#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-14

static int terms = 0;

int pi_madhava_terms(void) {
    return terms;
}

double pi_madhava(void) {
    double numerator = 1;
    double denomnator = 1;
    double seriesresult = 100;
    double finalseriesresult = 1;
    int terms = 0;
    for (int i = 1; absolute(seriesresult) >= EPSILON; i++) {
        numerator *= 1.0 / -3.0;
        denomnator += 2.0;
        seriesresult = (numerator / denomnator);
        terms++;
        finalseriesresult += seriesresult;
    }
    return sqrt_newton(12.0) * finalseriesresult;
}
