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
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    bool verbose = false;
    bool verbosevalues = false;
    int opt = 0;
    //FILE *pbfile = NULL;
    char username[256];
    //char *infilename = NULL;
    //char *outfilename = NULL;
    char *pbfilename = "rsa.pub";
    FILE *infile = stdin;
    FILE *outfile = stdout;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w+"); break;
        case 'n': pbfilename = optarg; break;
        case 'v': verbosevalues = true; break;
        case 'h': verbose = true; break;
        default: verbose = true; break;
        }
    }
    if (verbose) {
        printf("SYNPOSIS\n");
        printf(" Generates an RSA public/private key pair.\n");
        printf(" USAGE\n");
        printf("     ./encrypt [-hv] [-b bits] -i infile -o outfile\n");
        printf(" OPTIONS\n");
        printf("   -h               Display program help and usage.\n");
        printf("   -v               Display verbose program output.\n");
        printf("   -n pbfile       Public key file (default: rsa.pub).\n");
        printf("   -i infile       Input file (default: stdin).\n");
        printf("   -o outfile        Output File (default: stdout).\n");
    }
    mpz_t nvalue, exponent, signature, uservalue;
    FILE *pbfile = fopen(pbfilename, "r");
    mpz_inits(nvalue, exponent, signature, uservalue, NULL);
    rsa_read_pub(nvalue, exponent, signature, username, pbfile);
    mpz_set_str(uservalue, username, 62);
    if (verbosevalues) {
        printf("Username is %s\n", username);
        gmp_printf("Signature(%lu bits) = %Zx\n", mpz_size(signature), signature);
        gmp_printf("N(%lu bits) = %Zx\n", mpz_size(nvalue), nvalue);
        gmp_printf("Exponent(%lu bits) = %Zx\n", mpz_size(exponent), exponent);
    }
    if (!rsa_verify(uservalue, signature, exponent, nvalue)) {
        printf("Error!Exiting Program.....");
        exit(0);
    }
    rsa_encrypt_file(infile, outfile, nvalue, exponent);
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);
    mpz_clears(nvalue, exponent, signature, uservalue, NULL);
    return 0;
}
