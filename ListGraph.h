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
		char var[3];
};

struct list{
	int v;
	double cost;
	int lamp;
	struct list *next;
};


struct edge{
	int vi;
	int vj;
	double cost;
};

struct graph* GraphInit();
struct graph *LGRead(FILE *entryfp, struct PBArg *);

struct PBArg *PBinit();

struct list *NewListElement();
void FreeListV(struct list **,int );
void FreeList(struct list* );
struct list* CreateListNode();
struct list* AddList(struct list* );
void PutList(struct list* ,int ,double );
struct list** CreateListV(int );

#endif

