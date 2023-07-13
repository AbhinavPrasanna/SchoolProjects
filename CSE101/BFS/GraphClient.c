//-----------------------------------------------------------------------------
//
// GraphClient.c
// 
// This is a fancy test client that calculates the Radius and Diameter of 
// the graph defined on lines 41-49, along with its Central and Peripheral 
// vertices.  The definitions of these terms at:
// 
//    http://en.wikipedia.org/wiki/Distance_(graph_theory)
// 
// Place this file in a directory with copies of your List.c, List.h, Graph.c, 
// Graph.h and an appropriate Makefile, then compile and run. The output 
// is contained in the file GraphClientOut.
// 
// This program does not exercise all functions in your Graph ADT, but it 
// does a pretty good job of testing BFS().  If your output differs from 
// the above, you have a logical problem in either your Graph or List ADT.
// 
// Remember you are required to submit a file named GraphTest.c with pa4 that
// exercises your Graph functions.  Do not submit this file.
//
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

/********************************************************************************* 
* Abhinav Prasanna, aprasann
* 2022 Spring CSE101 PA2
* GraphClient.c
* Testing Client to Graph ADT
*********************************************************************************/

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
   for(s=1; s<=n; s++){
      //printf("BFS?\n");
      BFS(G, s);
      //printf("BFS!!!\n");
      max = getDist(G, 1);
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
   for(i=2; i<=n; i++){
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