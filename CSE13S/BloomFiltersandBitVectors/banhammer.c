#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include <inttypes.h>
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "bst.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#define OPTIONS "hst:f:"
#define WORD    "[a-zA-Z0-9_'-]+"

void print_help(void) {
    printf(" Generates an RSA public/private key pair.\n");
    printf(" USAGE\n");
    printf("     ./encrypt [-hv] [-b bits] -i infile -o outfile\n");
    printf(" OPTIONS\n");
    printf("   -h  Prints out the program usage. Refer to the reference program in the resources "
           "repository for what to print. \n");
    printf("   -t size Specifies that the Hash Table will have size entries(the default will be "
           "2^16\n");
    printf("   -f size Specifies that the Bloom Filter will have size entries(the default will be "
           "2^20).\n");
    printf("   -s will enable the printing of statistics to stdout.The statistics to calcuate "
           "are:\n* Average binary search tree size\n* Average binary search tree height\n* "
           "Average branches traversed\n* Hash table load\n* Bloom filter load\n");
}
int main(int argc, char **argv) {
    regex_t re;
    uint64_t lookups = 0;
    char *buff = (char *) calloc(4096, sizeof(char));
    char *buff2 = (char *) calloc(4096, sizeof(char));
    HashTable *hashtable;
    BloomFilter *bloomfilter;
    Node *thoughtcrimes = bst_create();
    Node *rightspeak = bst_create();
    //int tempvar;
    char *word = NULL;
    bool statsverbose = false;
    char *first_invalid;
    Node *node;
    uint32_t sizeofht = 65536;
    uint32_t sizeofbloomfilter = 1048576;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); break;
        case 's': statsverbose = true; break;
        case 't':
            sizeofht = strtoul(optarg, &first_invalid, 10);
            if ((*first_invalid) == '\0') {
                fprintf(stderr, "Invalid HashTable Size\n");
                return -1;
            }
            break;
        case 'f':
            sizeofbloomfilter = strtoul(optarg, &first_invalid, 10);
            if ((*first_invalid) == '\0') {
                fprintf(stderr, "Invalid BloomFilter Size\n");
                return -1;
            }
            break;
        default: print_help(); break;
        }
    }
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }
    FILE *badspeak = fopen("badspeak.txt", "r");
    if (!badspeak) {
        fprintf(
            stderr, "Failed to open badspeak.txt. Please add the file in a working directory.\n");
    }
    FILE *newspeak = fopen("newspeak.txt", "r");
    if (!newspeak) {
        fprintf(
            stderr, "Failed to open newspeak.txt. Please add the file in a working directory.\n");
    }
    hashtable = ht_create(sizeofht);
    bloomfilter = bf_create(sizeofbloomfilter);
    while (fscanf(badspeak, "%s", buff) != EOF) {
        bf_insert(bloomfilter, buff);
        ht_insert(hashtable, buff, NULL);
    }
    while (fscanf(newspeak, "%s %s", buff, buff2) != EOF) {
        bf_insert(bloomfilter, buff);
        ht_insert(hashtable, buff, buff2);
        lookups++;
    }
    while ((word = next_word(stdin, &re)) != NULL) {
        for (int index = 0; word[index]; index++) {
            word[index] = tolower(word[index]);
        }
        if (bf_probe(bloomfilter, word)) {
            node = ht_lookup(hashtable, word);
            lookups++;
            if (node) {
                if (node->newspeak && node->oldspeak) {
                    rightspeak = bst_insert(rightspeak, node->oldspeak, node->newspeak);
                } else if (node->oldspeak) {
                    thoughtcrimes = bst_insert(thoughtcrimes, node->oldspeak, NULL);
                }
            }
        }
    }
    if (statsverbose) {
        fprintf(stdout, "Average binary search tree size %f\n", ht_avg_bst_size(hashtable));
        fprintf(stdout, "Average binary search tree height: %f\n", ht_avg_bst_height(hashtable));
        fprintf(
            stdout, "Average branches traversed %f%%\n", ((double) ht_count(hashtable) / lookups));
        fprintf(stdout, "Hash table load: %f%%\n",
            100 * ((double) ht_count(hashtable) / ht_size(hashtable)));
        fprintf(stdout, "Bloom Filter Load: %f%%\n",
            100 * ((double) bf_count(bloomfilter) / bf_size(bloomfilter)));
    } else {
        uint32_t thoughtcrimesize = bst_size(thoughtcrimes);
        uint32_t rightspeaksize = bst_size(rightspeak);
        if (thoughtcrimesize > 0 && rightspeaksize > 0) {
            fprintf(stdout, "%s", mixspeak_message);
            bst_print(thoughtcrimes);
            bst_print(rightspeak);
        } else if (thoughtcrimesize > 0) {
            fprintf(stdout, "%s", badspeak_message);
            bst_print(thoughtcrimes);
        } else if (rightspeaksize > 0) {
            fprintf(stdout, "%s", goodspeak_message);
            bst_print(rightspeak);
        }
    }
    fclose(badspeak);
    fclose(newspeak);
    bst_delete(&thoughtcrimes);
    bst_delete(&rightspeak);
    ht_delete(&hashtable);
    bf_delete(&bloomfilter);
    clear_words();
    regfree(&re);
    //BloomFilter *bf = bf_create(12);
    //BloomFilter **bloomfilter = (BloomFilter **) calloc(bf_size(bf),sizeof(BloomFilter*));
    //bf_count(bf);
    return 0;
}
