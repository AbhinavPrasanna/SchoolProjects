Programming Assignment 2 consists of a Graph data structure, List data structure, and a FindPath file that runs the BFS algorithm. Graph has a sourcevertex, size of the edges, size of the Graph itself, color array, parent array, distance array, and a list of the adjacent vertices. We use the color array in relation with BFS, and to help us figure out which vertices have been visited/unvisited. The distance array is modified accordingly to the iteration that we are on, and the parent array shows parent for each vertex.
Files included:
Graph.c - Implementation of the Graph ADT
Graph.h- Functions that are used in the Graph ADT
GraphTest.c - Testing Harness
List.c - Impelmentation fo the List ADT
List.h - Functions that are used in List ADT
Makefile - Rules for compiling the program
FindPath.c - Main function used to run BFS and to find shortest paths
