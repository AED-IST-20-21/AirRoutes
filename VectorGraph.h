//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_VECTORGRAPH_H
#define AIRROUTES_VECTORGRAPH_H

#include "Graph.h"

struct graph *VGRead(FILE *, struct PBArg *);
/*int lessVertice(const void *,const void *);*/
struct edge **CreateEdgeV(int size);
int binsearch(int *,struct graph *, int);
void emptybin(struct edge **bin, struct edge **mst, int V, int E);
int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int));
int EdgeDelete(struct edge *aux, int vi, int vj);
int VerticeDelete(struct edge *aux, int vi, int vj);
int flagcheck(int pos, struct PBArg *Arg);

#endif //AIRROUTES_VECTORGRAPH_H
