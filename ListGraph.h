#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "FileOp.h"
#include "ListGraph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

struct graph {
	struct PBArg* Arg;
	struct list** vertice;
};


struct PBArg {
		int v;
		int e;
		int vi;
		int vj;
		char* var;
};

struct list{
	int v;
	double cost;
	struct list *next;
};


struct edge{
	int vi;
	int vj;
	double cost;
};

struct graph *GraphInit();
struct graph* GraphInit(struct PBArg *Arg);
struct graph *LGRead(FILE *entryfp,struct PBArg *Arg);
struct list *NewListElement();
void FreeListV(struct list **LV,int V);
void FreeList(struct list* L);
struct list* CreateListNode();
void AddList(struct list* L);
struct list** CreateListV(int V);

#endif

