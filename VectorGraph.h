//
// Created by anton on 11/30/2020.
//

#ifndef AIRROUTES_VECTORGRAPH_H
#define AIRROUTES_VECTORGRAPH_H

#include "Graph.h"

struct graph *VGRead(FILE *, struct PBArg *);
/*int lessVertice(const void *,const void *);*/
struct edge *CreateEdgeV(int );
int binsearch(int *,struct graph *, int);
void emptybin(struct edge *bin, struct edge*, int, int);

#endif //AIRROUTES_VECTORGRAPH_H
