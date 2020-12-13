#ifndef AIRROUTES_GRAPH_H
#define AIRROUTES_GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>
/* #define DEBUG This flag should only be defined when debugging the program */

struct graph {   /* Struct to store a graph represented by an edge array */
	struct PBArg* Arg;   /* Problem Arguments */
	struct edge **data;   /* Edge array */
};
struct graph0 {   /* Struct to store a graph represented by an array of Adjacency lists */
	struct PBArg* Arg;   /* Problem Arguments */
	struct list** data;   /* Adjacency list */
};

struct PBArg {   /* Struct that stores the arguments for 1 problem */
	int v;   /* Number of vertices */
	int e;   /* Number of edges */
	int vi;   /* 1st extra vertice */
	int vj;   /* 2nd extra vertice */
	char var[3];   /* string to store mode */
	bool err;   /* Boolean flag to warn about expected errors */
};

struct list{   /* Struct to store an adjacency list */
	int v;   /* Vertice to to whom this list belongs */
	double cost;   /* Cost for the edge coming from the vertice to the first adjacent vertice */
	struct list *next;   /* Next element of the list */
};

struct edge{   /* Struct to store an edge */
	int vi;   /* 1st Vertice */
	int vj;   /* 2nd Vertice */
	double cost;   /* Cost of the edge */
};

void ErrExit(int);   /* Handles unexpected errors */
int ArgCheck (struct PBArg *);   /* Checks if Argument is valid and returns an integer representing the mode */
struct PBArg *PBinit();   /* Initialization of PBArg structure */
struct graph* GraphInit();   /* Initialization of graph structure */

#endif
