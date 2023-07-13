#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdlib.h>

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    //Computes the greatest common divisor of a and b, storing the value of the computed divsor in d
    mpz_t t;
    mpz_init(t);
    mpz_t atemp, btemp;
    mpz_inits(atemp, btemp, NULL);
    mpz_set(atemp, a);
    mpz_set(btemp, b);
    while (mpz_sgn(btemp) != 0) {
        mpz_set(t, btemp);
        mpz_mod(btemp, atemp, btemp);
        mpz_set(atemp, t);
    }
    mpz_set(d, atemp);
    mpz_clears(atemp, btemp, t, NULL);
}
void mod_inverse(mpz_t i, mpz_t a,
    mpz_t
        n) { //Computes the inverse i of a modiulo n. In the event that a modular inverse cannot be found, set i to 0. Note that this pseudocode uses parallel assignments, which C does not support. Thus, you wilneed to use auxiliary variables to fake the parallel assignments.

    mpz_t q;
    mpz_init(q);

    mpz_t r;
    mpz_init(r);

    mpz_t rprime;
    mpz_init(rprime);

    mpz_t t;
    mpz_init(t);

    mpz_t tprime;
    mpz_init(tprime);

    mpz_t argument1;
    mpz_t argument2;

    mpz_init(argument1);
    mpz_init(argument2);

    mpz_t output;
    mpz_init(output);

    mpz_set(r, n);
    mpz_set(rprime, a);

    mpz_set_ui(t, 0);
    mpz_set_ui(tprime, 1);

    while (mpz_cmp_ui(rprime, 0) != 0) {
        mpz_t output;
        mpz_init(output);

        mpz_fdiv_q(q, r, rprime);

        mpz_t argument1;
        mpz_t argument2;

        mpz_init(argument1);
        mpz_init(argument2);

        mpz_set(argument1, r);
        mpz_set(argument2, rprime);
        mpz_set(r, rprime);

        mpz_mul(output, q, argument2);
        mpz_sub(rprime, argument1, output);
        mpz_set(argument1, t);
        mpz_set(argument2, tprime);

        mpz_set(t, tprime);
        mpz_mul(output, q, argument2);
        mpz_sub(tprime, argument1, output);
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(t, 0);
    } else if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    mpz_set(i, t);
    mpz_clears(rprime, t, tprime, r, q, output, argument1, argument2, NULL);
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent,
    mpz_t
        modulus) { //Performs fast modular exponentiation, computing base raised to the exponent power modulo modulus, and storing the computed result in out.
    mpz_t v, p, tempvar;
    mpz_init(v);
    mpz_init(p);
    mpz_t temp;
    mpz_init(temp);
    mpz_t temp2;
    mpz_init(temp2);
    mpz_init(tempvar);
    mpz_set(tempvar, exponent);
    mpz_set_ui(v, 1);
    mpz_set(p, base);
    while (mpz_cmp_ui(tempvar, 0) > 0) {
        if (mpz_odd_p(tempvar) != 0) {
            mpz_set(temp, v);

            mpz_mul(temp, temp, p);
            mpz_mod(v, temp, modulus);
        }
        mpz_set(temp2, p);

        mpz_mul(temp2, temp2, temp2);
        mpz_mod(p, temp2, modulus);
        mpz_fdiv_q_ui(tempvar, tempvar, 2);
    }
    mpz_set(out, v);
    mpz_clears(v, p, tempvar, temp, temp2, NULL);
}
bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t r, nminusone, a, y, j, two, bounds;
    mp_bitcnt_t s = 0;
    mpz_t sval;
    mpz_init(sval);
    mpz_t tempvar1, tempvar2;
    mpz_inits(tempvar1, tempvar2, two, NULL);
    mpz_init_set_ui(r, 0);
    mpz_set_ui(two, 2); //sets two variable to 2
    mpz_inits(nminusone, a, y, j, bounds, NULL);
    mpz_set_ui(a, 0);
    mpz_sub_ui(nminusone, n, 1);
    uint64_t i = 1;
    if (mpz_cmp_ui(n, 0) == 0 || mpz_cmp_ui(n, 1) == 0 || mpz_cmp_ui(n, 4) == 0) {
        mpz_clears(r, nminusone, a, y, j, two, bounds, tempvar1, tempvar2, NULL);
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0 || mpz_cmp_ui(n, 3) == 0) {
        mpz_clears(r, nminusone, a, y, j, two, bounds, tempvar1, tempvar2, NULL);
        return true;
    }
    while (mpz_even_p(r)) {
        mpz_tdiv_q_2exp(r, nminusone, s);
        mpz_fdiv_q_ui(r, r, 2);
        s++;
        mpz_add_ui(sval, sval, 1);
    }
    mpz_sub_ui(bounds, n, 3);
    while (i < iters) {
        mpz_urandomm(a, state, bounds);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, nminusone) != 0)) {
            mpz_set_ui(j, 1);
            mpz_sub_ui(tempvar1, sval, 1);
            mpz_sub_ui(tempvar2, n, 1);
            while (!(mpz_cmp(j, tempvar1) > 0) && mpz_cmp(y, tempvar2) != 0) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) {

                    mpz_clears(r, nminusone, a, y, j, two, bounds, tempvar1, tempvar2, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, tempvar2) != 0) {

                mpz_clears(r, nminusone, a, y, j, two, bounds, tempvar1, tempvar2, NULL);
                return false;
            }
        }
        i++;
    }
    mpz_clears(r, nminusone, a, y, j, two, bounds, tempvar1, tempvar2, NULL);
    return true;
}

/* while(True){
   //a=(die.randrange)(1<<bits - 1 , 1<<bits)<<1)+1;
   //if miller_rabin(a){
   //    return a;
   //}
 }
}*/
void make_prime(mpz_t p, uint64_t bits,
    uint64_t
        iters) { //Generates a prime number stored in p. Generated Prime should be at least bits number of bits long. The primality of the generated number should be tested using is_prim() using iters number of iterations.
    mpz_t number;
    mpz_init(number);
    mpz_urandomb(number, state, bits);
    while (!is_prime(number, iters)) {
        mpz_clear(number);
        mpz_init(number);
        mpz_urandomb(number, state, bits);
        if (is_prime(number, iters)) {
            mpz_set(p, number);
        }
    }
    mpz_clear(number);
}
