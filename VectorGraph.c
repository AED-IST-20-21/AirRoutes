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
	
	G = GraphInit();                                                                            /*Initialize the graph*/
	
	G->Arg = Arg;
	G->data = (struct edge **) CreateEdgeV(Arg->v);
	
	for (i = 0; i < Arg->e; i++) {                                                      /*Reading the graph from file*/
		if (fscanf(entryfp, "%d %d %lf", &((struct edge **) G->data)[i]->vi, &((struct edge **) G->data)[i]->vj,
		           &((struct edge **) G->data)[i]->cost) != 3) {                  /*Checking for errors during reading*/
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
	for (i = start; i < g->Arg->e; i++) {
		
		if (id[((struct edge *) g->data)[i].vi] != id[((struct edge **) g->data)[i]->vj])
			return i;
		
	}
	return -1;
}

/*Edge Vector*/
struct edge **CreateEdgeV(int size) {
	
	struct edge **aux;
	
	if ((aux = (struct edge **) malloc(size * sizeof(struct edge))) == NULL) {
		ErrExit(3);
	}
	
	return aux;
}

void emptybin(struct edge *bin, struct edge *mst, int V, int E) {
	
	int i, j;
	
	for (i = V - 1, j = 0; i < E; i++, j++) ((struct edge *) mst)[i] = bin[j];
	
	free(bin);
	return;
}

int *EdgeBreak(struct edge **EdgeV, int size) {
	int *id, i, Family;
	
	id = (int *) malloc(size * sizeof(int));
	
	Family = EdgeV[0]->vi; /*Arbitrário*/
	for (i = 0; i < size; i++) {
		if (EdgeV[i]->cost == -1) {
			id[i] = -1;
			Family = EdgeV[i + 1]->vi;
		} else {
			id[i] = Family;
		}
	}
	return id;
}

int SearchDelete(struct graph *g,int start,int end, int (*Delete)(struct edge *, int, int)) {
	int i, cnt = 0;
	
	for (i = start; i < end; i++) {
		
		if ((*Delete)(((struct edge **) g->data)[i], g->Arg->vi, g->Arg->vj)) {
			
			((struct edge **) g->data)[i]->cost = -((struct edge **) g->data)[i]->cost;
			cnt++;
		}
	}
	return cnt;
}

int EdgeDelete(struct edge *aux, int vi, int vj) {
	
	if (((aux->vi == vi) && (aux->vj == vj)) || ((aux->vj == vi) && (aux->vi == vj))) return 0;
	else return 1;
	
}

int VerticeDelete(struct edge *aux, int vi, int vj) {
	
	if ((aux->vi = vi) || (aux->vj == vi)) return 0;
	else return 1;
	
}

