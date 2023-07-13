#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"
#include"Graph.h"

FILE* infile;
FILE* outfile;
int line[255];

int main(int argc, char* argv[]){
    if(argc == 3){
        infile = fopen(argv[1],"r");
        outfile = fopen(argv[2],"w+");
        if(infile == NULL){
             fprintf(stderr,"Error: failed to open infile.\n");
             return -1;
        }
        if(outfile == NULL){
             fprintf(stderr,"Error opening file to write\n");
             return -1;
        }
    }
    else{
         fprintf(stderr,"Error: enter correct number of arguments.\n");
         return -1;
    } 
    int source, destination, size;
    fscanf(infile,"%d\n",&size);
    Graph graph = newGraph(size);
    List list = newList();
    while(!feof(infile)){
         fscanf(infile,"%d %d\n",&source,&destination);
         if(source == 0 && destination == 0){
              break;
         }
         addArc(graph,source,destination);
    }
    fprintf(outfile,"Adjacency list representation of G:\n");
    printGraph(outfile,graph);
    List list2 = newList();
    
    for(int i=1;i<=size;i++){
         append(list,i);
         append(list2,i);
    }
    DFS(graph,list);
    printList(stdout,list);
    Graph goft = transpose(graph);
    DFS(goft,list);
    printList(stdout,list);
    int counter = 0;
    List list3 = newList();
    for(moveFront(list);index(list)>=0;moveNext(list)){
         if(getParent(goft,get(list))==NIL){
              counter++;
         }
    }
    fprintf(outfile,"G contains %d strongly connected components: \n",counter);
    int counter2 = 1;
    for(moveBack(list);index(list)>=0;movePrev(list)){
         if(getParent(goft,get(list))==NIL){
              prepend(list3,get(list));
              fprintf(outfile,"Component %d: ",counter2);
              printList(outfile,list3);
              clear(list3);
              counter2++;
         }
         else{
              prepend(list3,get(list));
         }
    }
    freeGraph(&graph);
    freeGraph(&goft);
    freeList(&list);
    freeList(&list2);
    freeList(&list3);
    fclose(infile);
    fclose(outfile);
}
