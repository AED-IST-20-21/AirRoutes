#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "FileOp.h"
#include "VectorGraph.h"
#include "Kruskal.h"

struct graph *VGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph *G;
	int i;
	
	G = GraphInit();                                                                            /*Initialize the graph*/
	
	G->Arg = Arg;
	G->data = CreateEdgeV(Arg->e);
	
	for (i = 0; i < Arg->e; i++) {                                                      /*Reading the graph from file*/
		
		if ((G->data[i] = (struct edge*) malloc(sizeof(struct edge)))==NULL) ErrExit(3);

		if (fscanf(entryfp, "%d %d %lf", &G->data[i]->vi, &G->data[i]->vj, &G->data[i]->cost) !=3) 
		{                  /*Checking for errors during reading*/
			VGFree(G);
			Arg->err = 1;
			return NULL;
		} else if ((G->data[i]->vi < 0) || (G->data[i]->vj < 0) 
				|| (G->data[i]->vi > Arg->v) || (G->data[i]->vj > Arg->v)) 
		{
			VGFree(G);
			Arg->err = 1;
			return NULL;
		}
	}
	return G;
}

struct edge **CreateEdgeV(int size) {
	
	struct edge **aux;
	
	if ((aux = (struct edge **) malloc(size*sizeof(struct edge *))) == NULL) ErrExit(3);
	
	return aux;
}

int SearchDelete(struct graph *g, int start, int end, int (*Delete)(struct edge *, int, int)) {
	int i, cnt = 0;
	
	for (i = start; i < end; i++) {
		
		if ((*Delete)(g->data[i], g->Arg->vi, g->Arg->vj)) {
			
			g->data[i]->cost = -g->data[i]->cost;
			cnt++;
		}
	}
	return cnt;
}

int EdgeDelete(struct edge *aux, int vi, int vj) {
	
	if (((aux->vi == vi) && (aux->vj == vj)) || ((aux->vj == vi) && (aux->vi == vj))) return 1;
	else return 0;
	
}

int VerticeDelete(struct edge *aux, int vi, int vj) {
	
	if ((aux->vi == vi) || (aux->vj == vi)) return 1;
	else return 0;
	
}

void VGFree(struct graph *g){
	
	FreeEdgeV(g->data,g->Arg->e);
	free(g);
	
}
void FreeEdgeV(struct edge **data, int size)
{
	int i;
	
	for (i=0; i<size; i++)
	{
		free(data[i]);
	}
	free(data);
	return;
	
}

struct graph *graphcpy(struct graph *source){
	struct graph *new;
	int i;
	new=GraphInit();
	new->Arg=source->Arg;
	new->data=CreateEdgeV(source->Arg->e);
	for (i=0; i < source->Arg->e; i++) new->data[i]=source->data[i];
	return new;
}

struct edge* ProblemSolver(struct graph* g, double* Sum, int StopMe)
{
	struct edge* backup;
	int NewStop, ncpos, *id, *sz;
	
	if ((id=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(g->Arg->v * sizeof(int)))==NULL) ErrExit(3);
	
	NewStop = CWQU(g->data, g->Arg->v, Sum, id, sz, StopMe);
	
	if (StopMe - NewStop > 1)
	{
		free(id);
		free(sz);
		return NULL;
	}
	
	ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);
	
	if (ncpos ==-1)
	{
		free(id);
		free(sz);
		return NULL;
	}
	
	if ((backup = (struct edge*) malloc(sizeof(struct edge)))==NULL) ErrExit(3);
	
	backup->vi = g->data[ncpos]->vi;
	backup->vj = g->data[ncpos]->vj;
	backup->cost = g->data[ncpos]->cost;
	
	free(id);
	free(sz);
	return backup;
}