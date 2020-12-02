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
int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int));
int EdgeDelete(struct edge *aux, int vi, int vj);
int VerticeDelete(struct edge *aux, int vi, int vj);

#endif //AIRROUTES_VECTORGRAPH_H
