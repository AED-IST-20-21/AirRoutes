//
// Created by anton on 11/30/2020.
//

#include "VectorGraph.h"

struct graph *VGRead(FILE *entryfp, struct PBArg *Arg) {
	
	struct graph *G;
	int i;
	
	G = GraphInit();
	
	G->Arg = Arg;
	
	G->data = CreateEdgeV(Arg->v);
	
	for (i = 0; i < Arg->e; i++) {
		if (fscanf(entryfp, "%d %d %lf", &((struct edge **) G->data)[i]->vi, &((struct edge **) G->data)[i]->vj,&((struct edge **) G->data)[i]->cost) != 3) {
			GFree(G);
			Arg->err = 1;
			return NULL;
		}
	}
	
	return G;
}

int lessVertice(const void *a, const void *b) {
	
	if (((struct edge *) a)->vi < ((struct edge *) b)->vi) return 0;
	else if (((struct edge *) a)->vi == ((struct edge *) b)->vi) {
		if (((struct edge *) a)->vj < ((struct edge *) b)->vj)return 0;
		else return 1;
	} else return 1;
}

struct edge **CreateEdgeV(int size) {
	
	struct edge **aux;
	
	if ((aux = malloc(size * sizeof(struct edge))) == NULL) {
		ErrExit(3);
	}
	
	return aux;
}

struct edge *binsearch(int *id,struct graph *g){
	
	int i=0;
	/* TODO
	id[g->Arg->vi]=0;
	id[g->Arg->vj]=0;
	*/
	for (i=g->Arg->v;i<g->Arg->e;i++){
		
		if (id[((struct edge **) g->data)[i]->vi]!=id[((struct edge **) g->data)[i]->vj]) return ((struct edge **)g->data)[i];
		
	}
	return NULL;
}


