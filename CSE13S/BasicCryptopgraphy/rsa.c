#include "rsa.h"
#include "numtheory.h"
#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <string.h>
#include <unistd.h>
#include "randstate.h"
#include <stdint.h>

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits,
    uint64_t
        iters) { //Creates parts of a new RSA public key: two large primes p and q, their product n, and the public exponent e.
    /*1.Begin by creating primes p and q using make_prime(). Decide the number of bits that go to each prime respectively such that log_2(n) >= nbits. Let the number of bits for p be a random number in the range [nbits/4,(3 x nbits)/4]. The remaining bits will go to q. The number of Miller-Rabin iterations is specified by iters.
  2.Next, compute (p-1)(q-1)
  3. Need to fina suitable public exponent e. Generate random numbers around nbits using mpz_urandomb(). Compute gcd() of each random number and computed totient. Stop the loop you have found a number coprime with the totient: that will be the public exponent 
 */
    mpz_t pvalminusone, qvalminusone, finalval, exponent, gcdval;
    mpz_inits(pvalminusone, qvalminusone, finalval, exponent, gcdval, NULL);
    uint64_t size = 0;
    uint64_t qbits = 0;
    while (mpz_sizeinbase(n, 2) < nbits) {
        size = ((random() % (nbits / 2)) + (nbits / 4));
        qbits = nbits - size;
        make_prime(p, size, iters);
        make_prime(q, qbits, iters);
        mpz_mul(n, p, q);
    }
    mpz_sub_ui(pvalminusone, p, 1);
    mpz_sub_ui(qvalminusone, q, 1);
    mpz_mul(finalval, pvalminusone, qvalminusone);
    mpz_urandomb(exponent, state, nbits);
    gcd(gcdval, exponent, finalval);
    while (mpz_cmp_ui(gcdval, 1) != 0) {
        mpz_urandomb(exponent, state, nbits);
        gcd(gcdval, exponent, finalval);
    }
    mpz_set(e, exponent);
    mpz_clears(finalval, exponent, gcdval, qvalminusone, pvalminusone, NULL);
}
void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[],
    FILE *
        pbfile) { //Writes a public RSA key to pbfile. The format of a public key should be n,e,s then the username,each of which are written with a trailing newline. The values n,e, and s should be written as hexstrings.
    gmp_fprintf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}
void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    //i
    gmp_fscanf(pbfile, "%Zx\n%Zx\n%Zx\n%s\n", n, e, s, username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {
    mpz_t temp, pval, qval;
    mpz_inits(temp, pval, qval, NULL);
    mpz_sub_ui(pval, p, 1);
    mpz_sub_ui(qval, q, 1);
    mpz_mul(temp, pval, qval);
    mod_inverse(d, e, temp);
    mpz_clears(temp, pval, qval, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", n, d);
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", n, d);
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n);
}
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    size_t k = (mpz_sizeinbase(n, 2) - 1) / 8;
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));
    arr[0] = 0xFF;
    size_t text = 1;
    while (text > 0) {
        //printf("While Loop Passed\n");
        text = fread(arr + 1, sizeof(uint8_t), k - 1, infile);
        mpz_import(m, text + 1, 1, sizeof(uint8_t), 1, 0, arr);
        rsa_encrypt(c, m, e, n);
        //gmp_printf("%Zx\n", c);
        gmp_fprintf(outfile, "%Zx\n", c);
    }
    free(arr);
    mpz_clears(m, c, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n);
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t mval, cval;
    mpz_inits(mval, cval, NULL);
    size_t k = ((mpz_sizeinbase(n, 2) - 1) / 8);
    uint8_t *array = (uint8_t *) calloc(k, sizeof(uint8_t));
    size_t text;
    gmp_fscanf(infile, "Zx\n", cval);
    while (!feof(infile)) {
        gmp_fscanf(infile, "%Zx\n", cval);
        rsa_decrypt(mval, cval, d, n);
        mpz_export(array, &text, 1, sizeof(uint8_t), 1, 0, mval);
        fwrite(array + 1, sizeof(uint8_t), text - 1, outfile);
    }
    free(array);
    mpz_clears(mval, cval, NULL);
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_init(t);
    pow_mod(t, s, e, n);
    if (mpz_cmp(m, t) == 0) {
        mpz_clear(t);
        return true;
    } else {
        mpz_clear(t);
        return false;
    }
}
