#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA2
* FindPath.c 
* FindPath Main Function
*********************************************************************************/

FILE* infile;
FILE* outfile;
int line[255];
int ind = 0;

int main(int argc, char* argv[]){
     if(argc==3){
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
     while(!feof(infile)){
         if(ind==0){
            fscanf(infile,"%d\n",&line[ind]);
            ind++; 
         }
         else{
            fscanf(infile,"%d %d\n",&line[ind],&line[ind+1]);
            ind = ind + 2;
         }
     }
     int size = line[0];
     int i = 1;
     Graph graph = newGraph(size);
     while(line[i]!=0 && line[i+1]!=0){
          addEdge(graph,line[i],line[i+1]);
          i=i+2;
     }
     printGraph(outfile,graph);
     fprintf(outfile,"\n");
     i = i+2;
     int distance;
     while(line[i]!=0 && line[i+1]!=0){
          List path = newList();
          BFS(graph,line[i]);
          distance = getDist(graph,line[i+1]);
          getPath(path,graph,line[i+1]);
          if(distance!=INF){
              fprintf(outfile,"The distance from %d to %d is %d\n",line[i],line[i+1],distance);
              fprintf(outfile,"A shortest %d-%d path is: ",line[i],line[i+1]);
              printList(outfile,path);
              fprintf(outfile,"\n");
          }
          else{
              fprintf(outfile,"The distance from %d to %d is infinity\n",line[i],line[i+1]);
              fprintf(outfile,"No %d-%d path exists",line[i],line[i+1]);
              fprintf(outfile,"\n");
          }
          i=i+2;
          clear(path);
          freeList(&path);
     }
     freeGraph(&graph);
     fclose(infile);
     fclose(outfile);
}

