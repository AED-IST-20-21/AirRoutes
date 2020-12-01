//
// Created by anton on 11/30/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#include "FileOp.h"
#include "VectorGraph.h"

struct graph *VGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph *G;
	int i;
	
	G = GraphInit();
	
	G->Arg = Arg;
	
	G->data = (struct edge *) CreateEdgeV(Arg->v);
	
	for (i = 0; i < Arg->e; i++) {
		if (fscanf(entryfp, "%d %d %lf", &((struct edge **) G->data)[i]->vi, &((struct edge **) G->data)[i]->vj,
		           &((struct edge **) G->data)[i]->cost) != 3) {
			GFree(G, FreeEdgeV);
			Arg->err = 1;
			return NULL;
		}
	}
	
	return G;
}



int binsearch(int *id, struct graph *g, int start) {
	
	int i = 0;
	/* TODO
	id[g->Arg->vi]=0;
	id[g->Arg->vj]=0;
	*/
	for (i = start; i < g->Arg->e; i++)
	{
		
		if (id[((struct edge *) g->data)[i].vi] != id[((struct edge **) g->data)[i]->vj])
			return i;
		
	}
	return -1;
}

/*Edge Vector*/
struct edge *CreateEdgeV(int size) {
	
	struct edge *aux;
	
	if ((aux = (struct edge *) malloc(size * sizeof(struct edge))) == NULL) {
		ErrExit(3);
	}
	
	return aux;
}

void emptybin(struct edge *bin, struct graph *g) {
	
	int i, j;
	
	for (i = g->Arg->v - 1, j = 0; i < g->Arg->e; i++, j++) ((struct edge *) g->data)[i] = bin[j];
	
	free(bin);
	return;
}

int* EdgeBreak(struct edge** EdgeV, int size)
{
	int *id, i, Family;

	id = (int*) malloc(size * sizeof(int));

	Family = EdgeV[0]->vi; /*Arbitrário*/
	for (i=0; i<size; i++)
	{
		if ( EdgeV[i]->cost==-1 )
		{
			id[i]=-1;
			Family = EdgeV[i+1]->vi;
		} else {
			id[i]= Family ;
		}
	}
	return id;
}

void EdgeDelete(struct edge** EdgeV, int pos)
{
	int i;
	/*
	EdgeV[pos].vi = -1;
	EdgeV[pos].vj = -1;
	*/
	EdgeV[pos]->cost = -1;

	return;
}


