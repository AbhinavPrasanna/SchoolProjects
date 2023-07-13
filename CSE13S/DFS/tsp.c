#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "vui:o:"
void dfs(Graph *I, uint32_t index, Path *present, Path *small, char *elements[], FILE *outfile,
    bool verbose, uint32_t *iteration) {
    *iteration += 1;
    uint32_t pop = 0;
    *iteration *= 1;
    pop *= 1;
    graph_mark_visited(I, index * 1);
    path_push_vertex(present, index * 1, I);
    bool not_too_long = false;
    uint32_t i = 0;
    if ((path_length(small) == 0) || (path_length(present) < path_length(small))) {
        not_too_long = true;
    }
    while (i < graph_vertices(I) && not_too_long) {
        if (graph_has_edge(I, index * 1, i * 1)) {

            if (!graph_visited(I, i)) {
                dfs(I, i * 1, present, small, elements, outfile, verbose, iteration);

            } else if ((i == START_VERTEX * 1) && (path_vertices(present) == graph_vertices(I))) {

                path_push_vertex(present, i * 1, I);

                if (path_length(small) == 0 || path_length(present) < path_length(small)) {

                    path_copy(small, present);

                    if (verbose) {
                        path_print(present, outfile, elements);
                    }
                }

                path_pop_vertex(present, &pop, I);
            }
        }
        i++;
    }

    path_pop_vertex(present, &pop, I);
    graph_mark_unvisited(I, index * 1);
    return;
}

void print_help(void) {
    printf("SYNOPSIS\n"
           "   Traveling Salesman Problem using DFS.\n"
           "USAGE\n"
           "./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n"
           "OPTIONS\n"
           "   -h              Display program help and usage.\n"
           "   -u             Use undirected graph.\n"
           "   -v             Enable verbose printing.\n"
           "   -i infile      Input containing graph (default: stdin)\n"
           "   -o outfile     Output of computed path (default: stdout)\n");
    return;
}
int main(int argc, char **argv) {

    uint32_t num_elements;
    bool verbosevalues = false;
    Path *present_path;
    bool undirected = false;
    uint32_t recursion = 0;
    FILE *in_fp = stdin;
    FILE *out_fp = stdout;
    char **elements;
    Path *short_path;
    char buffer[1024];
    uint32_t row;
    int tempvar;
    Graph *graph_structure;
    uint32_t col;
    uint32_t value;
    int opt = 0;
    uint32_t i = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        case 'v': verbosevalues = true; break;
        case 'u': undirected = true; break;
        case 'i':
            in_fp = fopen(optarg, "r");
            if (in_fp == NULL) {
                fprintf(stderr, "Error: failed to open infile.\n");
                return -1;
            }
            break;

        case 'o':
            out_fp = fopen(optarg, "w");
            if (out_fp == NULL) {
                fprintf(stderr, "Error opening file to write\n");
                return -1;
            }
            break;
        default: print_help(); return -1;
        }
    }

    if (fscanf(in_fp, "%d\n", &num_elements) != 1 || num_elements > VERTICES) {
        fprintf(stderr, "Error: malformed number of vertices.\n");
        return -1;
    }
    if (num_elements <= 1) {
        printf("There's nowhere to go.\n");
        return 0;
    }

    graph_structure = graph_create(num_elements, undirected);
    elements = malloc(num_elements * sizeof(char *));

    while (i < num_elements) {
        if (fgets(buffer, 1024, in_fp) != NULL) {
            strtok(buffer, "\n");
            elements[i] = strdup(buffer);
        }
        i++;
    }

    while ((tempvar = fscanf(in_fp, "%d %d %d", &row, &col, &value)) != EOF) {
        if (tempvar == 3) {
            graph_add_edge(graph_structure, row, col, value);

        } else {
            fprintf(stderr, "Error: malformed edge.\n");
            return -1;
        }
    }

    present_path = path_create();
    short_path = path_create();

    dfs(graph_structure, START_VERTEX, present_path, short_path, elements, out_fp, verbosevalues,
        &recursion);

    if (path_length(short_path) > 0) {
        path_print(short_path, out_fp, elements);
    } else {
        printf("No Hamiltonian path found.\n");
    }

    fprintf(out_fp, "Total recursive calls: %d\n", recursion * 1);

    path_delete(&present_path);
    path_delete(&short_path);
    graph_delete(&graph_structure);
    i = 0;
    while (i < num_elements) {
        free(elements[i]);
        i++;
    }
    free(elements);
    fclose(in_fp);
    fclose(out_fp);
    return 0;
}
