#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <gmp.h>
#include "numtheory.h"
#include "rsa.h"
#include "randstate.h"
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    bool verbose = false;
    bool verbosevalues = false;
    int opt = 0;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    char *pvfilename = "rsa.priv";
    //FILE *pvfile;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r");
            /*if (infile == NULL) {
                infile = stdin;
            }*/
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            /*if (outfile == NULL) {
                outfile = stdout;
            }*/
            break;
        case 'n':
            pvfilename = optarg;
            /*if (pvfilename == NULL) {
                pvfilename = "rsa.priv";
            }*/
            break;
        case 'v': verbosevalues = true; break;
        case 'h': verbose = true; break;
        default: verbose = true; break;
        }
    }
    FILE *pvfile = fopen(pvfilename, "r");
    if (verbose) {
        printf("SYNPOSIS\n");
        printf(" Generates an RSA public/private key pair.\n");
        printf(" USAGE\n");
        printf("     ./encrypt [-hv] [-b bits] -i infile -o outfile\n");
        printf(" OPTIONS\n");
        printf("   -h               Display program help and usage.\n");
        printf("   -v               Display verbose program output.\n");
        printf("   -d pvfile       Private key file (default: rsa.pub).\n");
        printf("   -i infile       Input file (default: stdin).\n");
        printf("   -o outfile        Output File (default: stdout).\n");
    }
    mpz_t nvalue, e;
    mpz_inits(nvalue, e, NULL);
    rsa_read_priv(nvalue, e, pvfile);
    if (verbosevalues) {
        gmp_printf("N(%lu bits) = %Zx\n", mpz_size(nvalue), nvalue);
        gmp_printf("E(%lu bits) = %Zx\n", mpz_size(e), e);
    }
    rsa_decrypt_file(infile, outfile, nvalue, e);
    fclose(pvfile);
    fclose(infile);
    fclose(outfile);

    mpz_clears(nvalue, e, NULL);
    return 0;
}
