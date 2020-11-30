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
	
	for (i=0;i<Arg->e;i++){
		if (fscanf(entryfp,"%d %d %lf",G->data[i]->vi,G->data[i]->vj,G->data[i]->cost)!=3){
			VGFree(G);
			Arg->err=1;
			return NULL;
		}
	}

	return G;
}

int lessVertice(const void *a,const void *b){
	
	if (((struct edge* )a)->vi<((struct edge* )b)->vi) return 0;
	else if (((struct edge* )a)->vi==((struct edge* )b)->vi){
		if (((struct edge* )a)->vj<((struct edge* )b)->vj)return 0;
		else return 1;
	} else return 1;
}