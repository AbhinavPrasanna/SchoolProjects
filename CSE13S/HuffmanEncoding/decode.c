#include "defines.h"
#include "header.h"
#include "io.h"
#include "huffman.h"
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#define OPTIONS "hvi:o"

void print_help(void) {
    printf("SYNPOSIS\n");
    printf("    A Huffman encode\n");
    printf("    Decompresses a file using the Huffman coding algorithm.\n");
    printf("USUAGE\n");
    printf("    ./decode [-h] [-v] [-i infile] [-o outfile]\n\n");
    printf("OPTIONS\n");
    printf("  -h               Display program help and usage.\n");
    printf("  -i infile        Input data to compress (default: stdin)\n");
    printf("  -o outfile       Output of compressed data (default: stdout)\n");
    printf("  -v               Print compression statistics/\n");
}

int main(int argc, char **argv) {
    uint64_t byteswritten = 0;
    Node *node;
    Node *root_node;
    uint8_t bit;
    struct stat instatbuf;
    uint8_t buffer[BLOCK];
    uint32_t buf_index = 0;
    Header header;
    int opt = 0;
    int outfile = 1;
    int infile = 0;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': print_help(); return -1;
        case 'i':
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                printf("Error opening file\n");
                return -1;
            }
            break;
        case 'o':
            outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);
            if (outfile == -1) {
                printf("Error opening file\n");
                return -1;
            }
            break;
        case 'v': verbose = true; break;
        default: print_help(); return -1;
        }
    }
    read_bytes(infile, (uint8_t *) &header, sizeof(Header));
    if (header.magic != MAGIC) {
        fprintf(stderr, "Error: unable to read header. \n");
        return -1;
    }
    fstat(infile, &instatbuf);
    fchmod(outfile, header.permissions);
    uint8_t dump[header.tree_size];
    read_bytes(infile, dump, header.tree_size);
    root_node = rebuild_tree(header.tree_size, dump);
    node = root_node;
    bool check = (byteswritten < header.file_size && read_bit(infile, &bit));
    while (check) {
        node = bit ? node->right : node->left;
        if (node->left == NULL && node->right == NULL) {
            buf_index++;
            buffer[buf_index] = node->symbol;
            byteswritten++;
            node = root_node;
            if (buf_index == BLOCK) {
                write_bytes(outfile, buffer, BLOCK);
                buf_index = 0;
            }
        }
    }
    write_bytes(outfile, buffer, buf_index);
    if (verbose) {
        fprintf(stderr, "Compressed file size: %" PRIu64 " bytes\n", bytes_read);
        fprintf(stderr, "Decompressed file size: %" PRIu64 " bytes\n", bytes_written);
        fprintf(
            stderr, "Space saving: %.2f%%\n", 100 * (1 - ((double) bytes_read / bytes_written)));
    }
    delete_tree(&root_node);
    close(infile);
    close(outfile);
    return 0;
}
