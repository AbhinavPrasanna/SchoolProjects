#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdlib.h>
struct Path {
    uint32_t size;
    Stack *Vertices;
};

Path *path_create(void) {
    Path *path = calloc(1, sizeof(Path));
    if (path != NULL) {
        path->size = 0;
        path->Vertices = stack_create(VERTICES + 1);
    }
    return path;
}

void path_delete(Path **p) {
    if (*p != NULL) {
        stack_delete(&(*p)->Vertices);
        free(*p);
        *p = NULL;
    }
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t top = 0;
    stack_peek(p->Vertices, &top);
    bool returnvalue = false;
    if (stack_push(p->Vertices, v)) {
        if (!(top == v)) {
            p->size = p->size + graph_edge_weight(G, top, v);
        }
        returnvalue = true;
    }
    return returnvalue;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    bool returnvalue = false;
    if (stack_pop(p->Vertices, v)) {
        uint32_t top = 0;
        stack_peek(p->Vertices, &top);
        if (!(top == *v)) {
            p->size -= graph_edge_weight(G, top, *v);
        }
        returnvalue = true;
    }
    return returnvalue;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->Vertices);
}

uint32_t path_length(Path *p) {
    return p->size;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->Vertices, src->Vertices);
    dst->size = src->size;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %d\n", p->size);
    fprintf(outfile, "Path: ");
    stack_print(p->Vertices, outfile, cities);
}
