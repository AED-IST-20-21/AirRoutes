/* Project AirRoutes - AED IST 20/21 - GR032 - António Vidais (96162) & Tiago Leite (96232) */

#ifndef AIRROUTES_VECTORGRAPH_H
#define AIRROUTES_VECTORGRAPH_H

#include "Graph.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>


struct graph *VGRead(FILE *entryfp, struct PBArg *Arg);   /* Read Graph */
int lessVertice(const void *,const void *);   /* Less Vertice criteria for qsort */
struct edge **CreateEdgeV(int size);   /* Create Edge Array */
int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int)); /* Search and mark edges */
int EdgeDelete(struct edge *aux, int vi, int vj);   /* Edge delete criteria for SearchDelete */
int VerticeDelete(struct edge *aux, int vi, int vj);   /* Vertice Delete criteria for SearchDelete */
void VGFree(struct graph *g);   /* Free the graph */
struct graph *graphcpy(struct graph *source);   /* Create a copy of a graph */
void FreeEdgeV(struct edge **data, int size);   /* Free an edge array */
struct edge* ProblemSolver(struct graph*, double*, int);   /* Solver for E1 mode */
void Format(struct edge* );   /* Formatter for edges during reading */

#endif //AIRROUTES_VECTORGRAPH_H
