//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_GRAPH_H
#define AIRROUTES_GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>
/*
#include "FileOp.h"
#include "VectorGraph.h"
#include "ListGraph.h"
*/

#define DEBUG

struct graph {
	struct PBArg* Arg;
	struct edge **data;
};
struct graph0 {
	struct PBArg* Arg;
	struct list** data;
};

struct PBArg {
	int v;
	int e;
	int vi;
	int vj;
	char var[3];
	bool err;
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

/*Exit Errors*/
void ErrExit(int);

/*PBArg*/
int ArgCheck (struct PBArg *);
struct PBArg *PBinit();

/*Graph*/
struct graph* GraphInit();
/*void GFree(struct graph *, void (*FreeData)(void*, int));*/

/*List Vector*/
/*struct list* AddList(struct list*);
struct list* CreateListV();*/ /*?*/

#endif //AIRROUTES_GRAPH_H
