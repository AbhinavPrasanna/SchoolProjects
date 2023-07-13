#include "graph.h"

#include "vertices.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Graph {
    bool undirected;
    uint32_t matrix[VERTICES][VERTICES];
    bool indexvisited[VERTICES];
    uint32_t vertices;
};

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph));
    uint32_t row = 0;
    uint32_t col = 0;
    if (G != NULL) {
        G->vertices = vertices;
        G->undirected = undirected;
        while (row < VERTICES) {
            G->indexvisited[row] = false;
            while (col < VERTICES) {
                G->matrix[row][col] = 0;
                col++;
            }
            col = 0;
            row++;
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    bool returnstatement = false;
    if (i < G->vertices && j < G->vertices) {
        G->matrix[i][j] = k;
        if (G->undirected == true) {
            G->matrix[j][i] = k;
        }
        returnstatement = true;
    }
    return returnstatement;
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    bool returnstatement = false;
    if (i < G->vertices && j < G->vertices) {
        if (G->matrix[i][j] > 0) {
            returnstatement = true;
        }
    }
    return returnstatement;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    uint32_t value = 0;
    if (i < G->vertices && j < G->vertices) {
        value = G->matrix[i][j];
    }
    return value;
}

bool graph_visited(Graph *G, uint32_t v) {
    bool value = false;
    if (v < G->vertices) {
        value = G->indexvisited[v];
    }
    return value;
}

void graph_mark_visited(Graph *G, uint32_t v) {
    bool value = true;
    if (v < G->vertices) {
        G->indexvisited[v] = value;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    bool value = false;
    if (v < G->vertices) {
        G->indexvisited[v] = value;
    }
}

void graph_print(Graph *G) {
    uint32_t row = 0;
    uint32_t col = 0;
    while (row < G->vertices) {
        while (col < G->vertices) {
            printf("%d", G->matrix[row][col]);
            col++;
        }
        col = 0;
        printf("\n");
        row++;
    }
    printf("\n");
    return;
}
