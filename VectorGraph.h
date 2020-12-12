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
int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int));
int EdgeDelete(struct edge *aux, int vi, int vj);
int VerticeDelete(struct edge *aux, int vi, int vj);
void VGFree(struct graph *g);
struct graph *graphcpy(struct graph *source);
void FreeEdgeV(struct edge **data, int size);
struct edge* ProblemSolver(struct graph*, double*, int);
#endif //AIRROUTES_VECTORGRAPH_H
