#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt = 0;
    bool test_e = false;
    bool test_euler = false;
    bool test_madhava = false;
    bool test_viete = false;
    bool test_bbp = false;
    bool test_newton = false;
    bool test_statistics = false;
    bool test_info = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            test_e = true;
            test_euler = true;
            test_madhava = true;
            test_viete = true;
            test_bbp = true;
            test_newton = true;
            break;
        case 'e': test_e = true; break;
        case 'b': test_bbp = true; break;
        case 'm': test_madhava = true; break;
        case 'r': test_euler = true; break;
        case 'v': test_viete = true; break;
        case 'n': test_newton = true; break;
        case 's': test_statistics = true; break;
        case 'h': test_info = true; break;
        }
    }
    if (test_e) {
        printf("e() = %16.15lf, M_E = %16.15lf, diff = %16.15lf\n", e(), M_E, absolute(e() - M_E));
        if (test_statistics) {
            printf("e_terms() terms = %d\n", e_terms());
        }
    }
    if (test_euler) {
        printf("pi_euler() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_euler(), M_PI,
            absolute(pi_euler() - M_PI));
        if (test_statistics) {
            printf("pi_euler_terms() terms = %d\n", pi_euler_terms());
        }
    }
    if (test_madhava) {
        printf("pi_madhava() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_madhava(), M_PI,
            absolute(pi_madhava() - M_PI));
        if (test_statistics) {
            printf("pi_madhava_terms() terms = %d\n", pi_madhava_terms());
        }
    }
    if (test_viete) {
        printf("pi_viete() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_viete(), M_PI,
            absolute(pi_viete() - M_PI));
        if (test_statistics) {
            printf("pi_viete_factors() terms = %d\n", pi_viete_factors());
        }
    }
    if (test_bbp) {
        printf("pi_bbp() = %16.15lf, M_PI = %16.15lf, diff = %16.15lf\n", pi_bbp(), M_PI,
            absolute(pi_bbp() - M_PI));
        if (test_statistics) {
            printf("sqrt_newton() terms = %d\n", pi_euler_terms());
        }
    }
    if (test_newton) {
        for (double x = 0.0; x < 10.0; x += 0.1) {
            printf("sqrt_newton(%lf) = %16.15lf, sqrt(%lf) = %16.15lf, diff = %16.15lf\n", x,
                sqrt_newton(x), x, sqrt(x), absolute(sqrt_newton(x) - sqrt(x)));
        }
        if (test_statistics) {
            printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
        }
    }
    if (test_info) {
        printf("SYNOPSIS\n");
        printf("   A test harnass for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("\n");
        printf("OPTIONS\n");
        printf("  -a  Runs all tests.\n");
        printf("  -e  Runs e tests.\n");
        printf("  -b  Runs BBP pi tests.\n");
        printf("  -m  Runs Madhava pi tests.\n");
        printf("  -r  Runs Euler pi tests.\n");
        printf("  -v  Runs Viete pi tests.\n");
        printf("  -n  Runs Newton Square Root tests.\n");
        printf("  -s  Print verbose statistics.\n");
        printf("  -h  Display program synopsis and usage.\n");
    }
}
