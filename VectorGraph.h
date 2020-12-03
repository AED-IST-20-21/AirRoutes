//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_VECTORGRAPH_H
#define AIRROUTES_VECTORGRAPH_H

#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>


struct graph *VGRead(FILE *entryfp, struct PBArg *Arg);
int lessVertice(const void *,const void *);
struct edge **CreateEdgeV(int size);
void emptybin(struct edge **bin, struct edge **mst, int V, int E);
int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int));
int EdgeDelete(struct edge *aux, int vi, int vj);
int VerticeDelete(struct edge *aux, int vi, int vj);
int flagcheck(int pos, struct PBArg *Arg);
void EdgeSwitch(struct edge **data,int posA,int posB);
#endif //AIRROUTES_VECTORGRAPH_H
