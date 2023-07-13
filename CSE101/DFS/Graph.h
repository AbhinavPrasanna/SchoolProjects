#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#define NIL 0
#define UNDEF -1
#define WHITE "white"
#define GRAY "gray"
#define BLACK "black"

typedef struct GraphObj* Graph;

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA2
* Graph.h
* Graph ADT Header 
*********************************************************************************/

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List s);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
