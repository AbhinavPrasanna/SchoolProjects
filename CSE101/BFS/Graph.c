#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#include "List.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA2
* Graph.c 
* Graph ADT
*********************************************************************************/

typedef struct GraphObj{
    int n;
    int size;
    int recentvertex;
    List* array;
    char** color;
    int* parent;
    int* dist;  
}GraphObj;

Graph newGraph(int n){
    Graph G = malloc(sizeof(GraphObj));
    G->size = 0;
    G->n = n;
    G->recentvertex = NIL;
    G->color = (char**)malloc((n+1)*sizeof(char*)); 
    for(int i = 1; i<n+1;i++){
        G->color[i] = WHITE;
    }
    G->parent = (int*)malloc((n+1)*sizeof(int));
    for(int i = 1; i<=n;i++){
        G->parent[i] = NIL;
    }
    G->array = (List*)malloc((n+1)*sizeof(List));
    for(int y = 1; y<=n;y++){
        G->array[y] = newList();
    }
    G->dist = (int*)malloc((n+1)*sizeof(int));
    for(int d = 1; d<=n;d++){
        G->dist[d] = INF;
    }
    return G;
}

void freeGraph(Graph *pG){
  if(pG!=NULL && *pG!=NULL){
     int index = 1;
     while(index<=getOrder(*pG)){
       clear((*pG)->array[index]);
       freeList(&(((*pG)->array[index])));
       ((*pG)->array[index]) = NULL;
        index++;
     }
     free((*pG)->array);
     free((*pG)->color);
     free((*pG)->parent);
     free((*pG)->dist);
     free((*pG));
     (*pG)->array = NULL;
     (*pG)->color = NULL;
     (*pG)->parent = NULL;
     (*pG)->dist = NULL;
     *pG = NULL;
 }
}

int getOrder(Graph G){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->n;
}

int getSize(Graph G){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->size;
}

int getSource(Graph G){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->recentvertex;
}

int getParent(Graph G, int u){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];    
}

int getDist(Graph G, int u){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->dist[u];
}

void getPath(List L, Graph G, int u){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    if(u == getSource(G)){
        append(L,u);
    }
    else if(G->parent[u] == NIL){
        append(L,NIL);
    }
    else{
        getPath(L,G,G->parent[u]);
        append(L,u);
    }
}

void makeNull(Graph G){
  if(G==NULL){
      fprintf(stderr,"Graph not setup properly");
      exit(EXIT_FAILURE);
  }
  clear(*(G->array));
  G->size = 0;
}

void addEdge(Graph G,int u, int v){
    if(G==NULL){
       fprintf(stderr,"Graph was not initialized!");
       exit(EXIT_FAILURE);
    }
    addArc(G,u,v);
    addArc(G,v,u);
    G->size--;
}
void addArc(Graph G, int u, int v){
    if(G==NULL){
       fprintf(stderr,"Graph was not initialized!");
       exit(EXIT_FAILURE);
    }
    if(length(G->array[u])>0){
        //printf("index %d\n",u);
        for(moveBack(G->array[u]);index(G->array[u])>0;movePrev(G->array[u])){
              if(get(G->array[u])<v){
                   //printf("Insert After.\n");
                   insertAfter(G->array[u],v);
                   G->size++;
                   break;
              }
        }
        if(index(G->array[u])==0){
           if(get(G->array[u])<v){
            //printf("index == 0 v....\n");
            insertAfter(G->array[u],v);
            G->size++;
           }
           else {
            //:printf("index == 0 v....\n");
            //printf("Prepend!\n");
            prepend(G->array[u],v);
            G->size++;
           }
        }
    }
    else{
        //printf("Append!\n");
        append(G->array[u],v);
        G->size++;
    }
}

void BFS(Graph G, int s){
  free(G->color);
  free(G->dist);
  free(G->parent);
  G->color = (char**)malloc((getOrder(G)+1)*sizeof(char*)); 
  G->parent = (int*)malloc((getOrder(G)+1)*sizeof(List));
  G->dist = (int*)malloc((getOrder(G)+1)*sizeof(int));
  int x;
  if(s<1||s>getOrder(G)){
        fprintf(stderr,"Searching outside of bounds.");
        exit(EXIT_FAILURE);
  }
  for(int m = 1; m<=getOrder(G);m++){
       //printf("%d color=WHITE dist=INF parent=NIL\n",m);
       G->color[m] = WHITE;
       G->dist[m] = INF;
       G->parent[m] = NIL;
  }
  //printf("%d color=GRAY dist=0 parent=-1\n",s);
  G->recentvertex = s;
  G->color[s] = GRAY;
  G->dist[s] = 0;
  G->parent[s] = NIL;
  //printf("NEW LIST AND APPEND!\n");
  List queue = newList();
  prepend(queue,s);
  moveFront(queue);
  while(index(queue)>=0){
    x = get(queue);
    //printf("X == %d\n",get(queue));
    if(length(G->array[x])>0){
        //printf("Length is non empty!\n");
        for(moveFront(G->array[x]); index(G->array[x])>=0;moveNext(G->array[x])){
            //printf("FOR!\n");
            //printf("G->color[%d] = %s\n",get(G->array[x]),G->color[get(G->array[x])]);
            if(strcmp(G->color[get(G->array[x])],WHITE)==0){
                G->color[get(G->array[x])] = GRAY;
                //printf("G->color[%d] == GRAY\n",get(G->array[x]));
                G->dist[get(G->array[x])] = G->dist[x] + 1;
                //printf("G->dist[%d] == G->dist[%d] + 1\n",get(G->array[x]),x);
                G->parent[get(G->array[x])] = x;
                //printf("G->parent[%d] == %d\n",get(G->array[x]),x);
                append(queue,get(G->array[x]));
                //printf("append(%d) \n",get(G->array[x]));
             }
         }
    } 
    G->color[x] = BLACK;
    //printf("G->color[%d] = BLACK\n",x);
    moveNext(queue);
    //printf("moveNext!\n");
  }
  freeList(&queue);
}

void printGraph(FILE* out, Graph G){
    for(int i=1;i<=getOrder(G);i++){
         fprintf(out,"%d:",i);
         for(moveFront(G->array[i]);index(G->array[i])>=0;moveNext(G->array[i])){
             fprintf(out,"%d ",get(G->array[i]));
         }
         fprintf(out,"\n");
    }
}

