#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "code.h"
#include "node.h"
#include "pq.h"
#include "stack.h"
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define OPTIONS "hvi:o:"

void printhistogram(uint64_t *histogram) {
    int index = 0;
    while (index < ALPHABET) {
        if (histogram[index] != 0) {
            printf("character is %c, amount :%" PRIu64 "\n", index, histogram[index]);
        }
        index++;
    }
}
void printhelp(void) {
    printf("SYNPOSIS\n");
    printf("  A Huffman encode\n");
    printf("  Compress a file using the Huffman coding algorithm\n");
    printf("USAGE\n");
    printf("  ./encode [-h] [-v] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h            Display program help and usage.\n");
    printf("  -i infile     Input data to compress (default:stdin)\n");
    printf("  -o outfile    Output of compressed data (default:stdin)\n");
    printf("  -v            Print compression statistics.\n");
}

int main(int argc, char **argv) {
    int infile = 0;
    int outfile = 1;
    bool verbose = false;
    /*int opt = 0;
    int br;
    int infile = 0;
    int outfile = 1;
    Code table[ALPHABET] = { 0 };
    Node *root;
    int temp = 0;
    Header h;
    int index = 0;
    uint64_t histogram[ALPHABET];
    uint8_t buffer[BLOCK];
    uint16_t unique_symbols = 0;
    bool verbose = false;
    struct stat instatbuf;
    uint32_t dump_index = 0;
    uint8_t dump[MAX_TREE_SIZE];
    while (index < ALPHABET) {
        histogram[index] = 0;
        index++;
    }
    histogram[0] += 1;
    histogram[225] += 1;*/
    Header h;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': printhelp(); return -1;
        case 'i': infile = open(optarg, O_RDONLY); break;
        case 'o': outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC); break;
        case 'v': verbose = true; break;
        default: printhelp(); return -1;
        }
    }
    struct stat statbuf;
    lseek(infile, 0, SEEK_SET);
    fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);
    h.magic = MAGIC;
    h.permissions = statbuf.st_mode;
    h.tree_size = 0;
    h.file_size = 0;
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    /*if (lseek(infile, 0, SEEK_SET) == -1) {
        temp = open("/tmp/encode.temporary", O_CREAT | O_RDWR | O_TRUNC, 0600);
        br = read_bytes(infile, buffer, BLOCK);
        bool check = br > 0;
        while (check) {
            write_bytes(temp, buffer, br);
            br = read_bytes(infile, buffer, BLOCK);
            check = br > 0;
        }
        infile = temp;
    }
    lseek(infile, 0, SEEK_SET);
    fstat(infile, &instatbuf);
    fchmod(outfile, instatbuf.st_mode);
    br = read_bytes(infile, buffer, BLOCK);
    bool check = br > 0;
    while (check) {
        int index = 0;
        while (index < br) {
            histogram[buffer[index]] += 1;
            index++;
        }
        br = read_bytes(infile, buffer, BLOCK);
        check = br > 0;
    }
    index = 0;
    while (index < ALPHABET) {
        if (histogram[index] > 0) {
            unique_symbols += 1;
        }
    }
    index = 0;
    root = build_tree(histogram);
    build_codes(root, table);
    h.magic = MAGIC;
    h.permissions = instatbuf.st_mode;
    h.tree_size = (3 * unique_symbols) - 1;
    h.file_size = instatbuf.st_size;
    write_bytes(outfile, (uint8_t *) &h, sizeof(Header));
    dump_tree(outfile, root);
    write_bytes(outfile, dump, dump_index);
    lseek(infile, 0, SEEK_SET);
    br = read_bytes(infile, buffer, BLOCK);
    check = br > 0;
    while (check) {
        while (index < br) {
            write_code(outfile, &table[buffer[index]]);
            index++;
        }
        br = read_bytes(infile, buffer, BLOCK);
        check = br > 0;
    }
    flush_codes(outfile);
    if (verbose) {
        fprintf(stderr, "Uncompressed file size: %" PRIu64 " bytes\n", instatbuf.st_size);
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(stderr, "Space saving: %.2f%%\n",
            100.0 * (10.0 * ((double) bytes_written / instatbuf.st_size)));
    }

    if (temp) {
        unlink("/tmp/encode.temporary");
    }
    close(infile);
    close(outfile);
    delete_tree(&root);
    return 0;*/
}
