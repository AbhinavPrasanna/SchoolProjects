#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <gmp.h>
#include "randstate.h"
#include "numtheory.h"
#include "rsa.h"
#define OPTIONS "b:n:d:s:c:vh"

int main(int argc, char **argv) {
    bool verbose = false;
    uint64_t SEED = time(NULL);
    uint64_t bits = 256;
    bool verbosevalues = false;
    uint64_t iters = 50;
    int opt = 0;
    FILE *pbfile = NULL;
    char *pbfilename = "rsa.pub";
    FILE *pvfile = NULL;
    char *pvfilename = "rsa.priv";
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bits = atoi(optarg); break;
        case 'n': pbfilename = strdup(optarg); break;
        case 'd': pvfilename = strdup(optarg); break;
        case 'c': iters = atoi(optarg); break;
        case 's': SEED = atoi(optarg); break;
        case 'v': verbosevalues = true; break;
        case 'h': verbose = true; break;
        default: verbose = true;
        }
    }
    if (verbose) {
        printf("SYNPOSIS\n");
        printf(" Generates an RSA public/private key pair.\n");
        printf(" USAGE\n");
        printf("     ./keygen [-hv] [-b bits] -n pbfile -d pvfile\n");
        printf(" OPTIONS\n");
        printf("   -h               Display program help and usage.\n");
        printf("   -v               Display verbose program output.\n");
        printf("   -b bits          Minimum bits needed for public key n.\n");
        printf("   -c confidence    Miller-Rabin iterations for testing primes (default 50).\n");
        printf("   -n pbfile        Public key file (default: rsa.pub).\n");
        printf("   -d pvfile        Private key file (default: rsa.priv).\n");
        printf("   -s seed          Random seed for testing  for the random state initialization "
               "(default: the seconds since the");
        printf("UNIX epoch, given by time(NULL)).\n");
    }
    randstate_init(SEED);
    pbfile = fopen(pbfilename, "w+");
    pvfile = fopen(pvfilename, "w+");
    mpz_t pvalue, qvalue, nvalue, exponent, dvalue, strvalue, svalue;
    mpz_inits(pvalue, qvalue, nvalue, exponent, dvalue, strvalue, svalue, NULL);
    rsa_make_pub(pvalue, qvalue, nvalue, exponent, bits, iters);
    rsa_make_priv(dvalue, exponent, pvalue, qvalue);
    char *username = getenv("USER");
    mpz_set_str(strvalue, username, 62);
    rsa_sign(svalue, strvalue, dvalue, nvalue);
    rsa_write_pub(nvalue, exponent, svalue, username, pbfile);
    rsa_write_priv(nvalue, dvalue, pvfile);
    if (verbosevalues == true) {
        gmp_printf("Username is %s\n Signature(%zu bits) = %Zx\n P(%zu bits = %Zx\n Q(%zu bits) = "
                   "%Zx\n N(%zu bits) = %Zx\n Exponent(%zu bits) = %Zx\n D(%zu bits) = %Zx\n",
            username, mpz_size(svalue), svalue, mpz_size(pvalue), pvalue, mpz_size(qvalue), qvalue,
            mpz_size(nvalue), nvalue, mpz_size(exponent), exponent, mpz_size(dvalue), dvalue);
    }
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(pvalue, qvalue, nvalue, exponent, dvalue, strvalue, svalue, NULL);
}
