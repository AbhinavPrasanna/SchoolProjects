#include "randstate.h"
#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include <stdlib.h>

gmp_randstate_t state;

void randstate_init(uint64_t
        seed) { //Initializes the global random state named state with a Mersenne Twister algorithm, using seed as the random seed. This entails a call to gmp_randinit_mt() and a call to gmp_randseed_ui().
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

void randstate_clear(
    void) { //Clears and frees all memory used by the initialized global random state named state. This should just be a single call to gmp_randclear().
    gmp_randclear(state);
}
