#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=55;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%2!=0 ) addEdge(G, i, i+5);
      if( i<=10  ) addEdge(G, i, i+10);
   }
   addEdge(G, 11, 40);
   addEdge(G, 20, 50);
   addEdge(G, 30, 40);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      //printf("BFS?\n");
      BFS(G, s);
      //printf("BFS!!!\n");
      max = getDist(G, 5);
      //printf("Max = %d\n",max);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         //printf("d = %d\n",d);
         max = ( max<d ? d : max );
         //printf("Max = %d\n",max);
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   //printf("min = %d\n",min);
   moveFront(E);
   moveNext(E);
   for(i=1; i<=n; i++){
      d = get(E);
      //printf("D = %d\n",d);
      if( d==min ){
         append(C, i);
         //printf("d==min\n");
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
         //printf("d<min\n");
      }
      if( d==max ){
         append(P, i);
         //printf("d==max\n");
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
         //printf("d>max\n");
      }
      moveNext(E);
      //printf("Move Next(E)\n");
   }

   // Print results 
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   return(0);
}
