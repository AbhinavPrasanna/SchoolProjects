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
    int* finish;
    int* discover;  
    int* parent;
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
    for(int i = 1; i<n+1;i++){
        G->parent[i] = NIL;
    }
    G->finish = (int*)malloc((n+1)*sizeof(int));
    for(int i = 1; i<=n;i++){
        G->finish[i] = UNDEF;
    }
    G->array = (List*)malloc((n+1)*sizeof(List));
    for(int y = 1; y<=n;y++){
        G->array[y] = newList();
    }
    G->discover = (int*)malloc((n+1)*sizeof(int));
    for(int d = 1; d<=n;d++){
        G->discover[d] = UNDEF;
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
     free((*pG)->discover);
     free((*pG)->finish);
     free((*pG));
     (*pG)->array = NULL;
     (*pG)->color = NULL;
     (*pG)->parent = NULL;
     (*pG)->discover = NULL;
     (*pG)->finish = NULL;
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

int getDiscover(Graph G, int u){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u){
    if(G==NULL){
        fprintf(stderr,"Graph not setup properly");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
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
              else{
                  if(get(G->array[u]) == v) {
                      return;
                  }
              }
        }
        if(index(G->array[u])==0){
           if(get(G->array[u])<v){
            //printf("index == 0 v....\n");
            insertAfter(G->array[u],v);
            G->size++;
           }
           else if(get(G->array[u])==v){
               return;
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

int Visit(Graph G, int x, int time,List s){
    time++;
    //printf("Visit X = %d\n",x);
    G->discover[x] = time;
    //printf("G->discover[%d] = %d\n",x,time);
    G->color[x] = GRAY;
    //printf("G->discover[%d] = GRAY\n",x);
    if(length(G->array[x])>0){
        for(moveFront(G->array[x]);index(G->array[x])>=0;moveNext(G->array[x])){
        //printf("get(G->array[%d]) = %d\n",x,get(G->array[x]));
            if(strcmp(G->color[get(G->array[x])],WHITE)==0){
            //printf("G->color[%d] = WHITE\n",get(G->array[x]));
                G->parent[get(G->array[x])] = x;
                //printf("G->parent[get(G->array[%d])] = %d\n",get(G->array[x]),x);
            //printf("G->parent[%d] = %d",get(G->array[x]),x);
                time = Visit(G, get(G->array[x]),time,s);
            //printf("Visit\n");
            }
        }
    }
    //printf("time = %d\n",time);
    time++;
    G->color[x] = BLACK;
    //printf("G->color[%d] = BLACK\n",x);
    G->finish[x] = time;
    prepend(s,x);
    return time;
    //printf("G->finish[%d] = %d\n",x,time);
}

void DFS(Graph G, List s){
    free(G->color);
    free(G->parent);
    free(G->discover);
    free(G->finish);
    G->parent = (int*)calloc((getOrder(G)+1),sizeof(int)); 
    G->finish = (int*)calloc((getOrder(G)+1),sizeof(int));
    G->discover = (int*)calloc((getOrder(G)+1),sizeof(int));
    G->color = (char**)calloc((getOrder(G)+1),sizeof(char*)); 
    if(G==NULL){
        fprintf(stderr,"Error null graph\n");
        exit(EXIT_FAILURE);
    }
    for(int x = 1; x<=getOrder(G);x++){
        //printf("X = %d\n",x);
        G->color[x] = WHITE;
        G->discover[x] = UNDEF;
        G->finish[x] = UNDEF;
        //printf("Color = White\n");
        G->parent[x] = NIL;
        //printf("Parent = NIL\n");
     }
     int time = 0;
     int counter;
     for(moveFront(s);index(s)>=0;moveNext(s)){
         //printf("get(s) = %d\n",get(s));
         //printf("Color == %s",G->color[1]);
         if(strcmp(G->color[get(s)],WHITE)==0){
             //printf("time = %d\n",time);
             time = Visit(G,get(s),time,s);  
             //printf("time = %d\n",time);
         }
     }
     for(counter = 1;counter<=getOrder(G);counter++){
         //printf("counter = %d\n",counter);
         deleteBack(s);
     }
}


Graph transpose(Graph G){
    if(G==NULL){
        fprintf(stderr,"Error in add edge\n");
        return NULL;
    }
    Graph M = newGraph(getOrder(G));
    for(int i = 1; i<=getOrder(G);i++){
        if(length(G->array[i])>0){
            List list = G->array[i];
            for(moveFront(list);index(list)>=0;moveNext(list)){
                addArc(M,get(list),i);
            }
        }
    }
    return M;
}

Graph copyGraph(Graph G){
    printf("Copy Graph!\n");
    if(G==NULL){
        fprintf(stderr,"Error in null graph.\n");
        return NULL;
    }
    //printf("New Graph!\n");
    Graph graph = newGraph(getOrder(G));
    //printf("N = %d\n",getOrder(G));
    for(int i = 1; i<=getOrder(G);i++){
        //printf("i = %d\n",i);
        if(length(G->array[i])>0){
            for(moveFront(G->array[i]);index(G->array[i])>=0;moveNext(G->array[i])){
                //printf("get(G->array[%d]) = %d\n",i,get(G->array[i]));
                addArc(graph,i,get(G->array[i]));
            }
        }
        //printf("if loop!\n");
    }
    //printf("2 for loops passed!\n");
    return graph;
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

