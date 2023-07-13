#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "aeisqrnph:"

static Stats stats;

int main(int argc, char *argv[]) {
    int opt;
    bool test_insertion_sort = false;
    bool test_heap_sort = false;
    bool test_shell_sort = false;
    bool test_quick_sort = false;
    bool set_seed = false;
    bool set_size = false;
    bool set_elements = false;
    bool test_info = false;
    int seed = 13371453;
    int size = 100;
    int elements = 100;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            test_insertion_sort = true;
            test_heap_sort = true;
            test_shell_sort = true;
            test_quick_sort = true;
            break;
        case 'e': test_heap_sort = true; break;
        case 'i': test_insertion_sort = true; break;
        case 's': test_shell_sort = true; break;
        case 'q': test_quick_sort = true; break;
        case 'r':
            if (argc >= 3) {
                seed = (int) (atoi(argv[2]));
            }
            set_seed = true;
            break;
        case 'n':
            if (argc >= 3) {
                size = (int) (atoi(argv[2]));
            }
            set_size = true;
            break;
        case 'p':
            if (argc >= 3) {
                elements = (int) (atoi(argv[2]));
            }
            set_elements = true;
            break;
        case 'h': test_info = true; break;
        default: fprintf(stderr, "Bad getopt"); exit(EXIT_FAILURE);
        }
        uint32_t *arr;
        arr = (uint32_t *) calloc(size, sizeof(uint32_t));
        srandom(seed);
        for (int index = 0; index < size; index++) {
            arr[index] = random();
        }

        if (test_heap_sort) {
            heap_sort(&stats, arr, size);
            printf("Heap Sort, %d elements, %lu move, %lu compares\n ", elements, stats.moves,
                stats.compares);
            for (int i = 0; i < elements; i += 1) {
                printf("%13" PRIu32 "", arr[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
            reset(&stats);
        }
        if (test_insertion_sort) {
            insertion_sort(&stats, arr, size);
            printf("Insertion Sort, %d elements, %lu moves, %lu compares\n", elements, stats.moves,
                stats.compares);
            for (int i = 0; i < elements; i += 1) {
                printf("%13" PRIu32 "", arr[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
            reset(&stats);
        }
        if (test_shell_sort) {
            shell_sort(&stats, arr, size);
            printf("Shell Sort, %d elements, %lu moves, %lu compares\n", elements, stats.moves,
                stats.compares);
            for (int i = 0; i < elements; i += 1) {
                printf("%13" PRIu32 "", arr[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
            reset(&stats);
        }
        if (test_quick_sort) {
            quick_sort(&stats, arr, size);
            printf("Quick Sort, %d elements, %lu moves, %lu compares\n", elements, stats.moves,
                stats.compares);
            for (int i = 0; i < elements; i += 1) {
                printf("%13" PRIu32 "", arr[i]);
                if ((i + 1) % 5 == 0) {
                    printf("\n");
                }
            }
            reset(&stats);
        }
        if (test_info) {
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n");
            printf("\n");
            printf("USAGE\n");
            printf("   ./sorting [-haeisqn:p:r] [-n length] [-p elements] [-r seed]\n");
            printf("\n");
            printf("OPTIONS\n");
            printf("  -h            display program help and usage.\n");
            printf("  -a            enable all sorts.\n");
            printf("  -e            enable Heap Sort.\n");
            printf("  -i            enable Insertion Sort.\n");
            printf("  -s            enable Shell Sort.\n");
            printf("  -q            enable Quick Sort.\n");
            printf("  -n length  	specify number of array elements (default: 100).\n");
            printf("  -p elements   specify number of elements to print (default: 100).\n");
            printf("  -r seed       specify random seed (default: 13371453).\n");
        }
    }
    return 0;
}
