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
	/*struct edge *temp;*/
	
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

		/*
		G->data[i]->vi = temp->vi;
		G->data[i]->vj = temp->vj;
		G->data[i]->cost = temp->cost;
		*/
	}
	
	/*free(temp);*/
	return G;
}


/*Edge Vector*/
struct edge **CreateEdgeV(int size) {
	
	struct edge **aux;
	
	if ((aux = (struct edge **) malloc(size*sizeof(struct edge *))) == NULL) ErrExit(3);
	
	return aux;
}

void emptybin(struct edge **bin, struct edge **mst, int offset, int end) {
	
	int j;
	
	for (j = 0; j < end; j++) 
	{
		mst[j+offset-1] = bin[j];
	}
	
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

int SearchOverflow(struct graph *g, double sum, int start, int end, int (*Delete)(struct edge *, int, int)) 
{
	int i, cnt = 0;
	
	for (i = start; i < end; i++) {
		
		if ((*Delete)(g->data[i], g->Arg->vi, g->Arg->vj)) {
			
			g->data[i]->cost = g->data[i]->cost + sum;
			cnt++;
		}
	}
	return cnt;
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
	
	if ((aux->vi = vi) || (aux->vj == vi)) return 1;
	else return 0;
	
}

int flagcheck(int pos, struct PBArg *Arg) {
	
	if (pos < 0) return -1;
	else if ((0 < pos) && (pos < Arg->v)) return 0;
	else return 1;
	
}

void EdgeSwitch(struct edge **data, int posA, int posB) {
	struct edge *temp;
	
	if ((temp = malloc(sizeof(struct edge))) == NULL) ErrExit(3);
	
	temp = data[posA];
	data[posA] = data[posB];
	data[posB] = temp;
	
	free(temp);
	return;
}

void VGFree(struct graph *g){

	int i;
	for (i=0; i<g->Arg->e; i++)
	{
		free(g->data[i]);
	}
	free(g->data);
	free(g);
	
}


