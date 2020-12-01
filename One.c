//
// Created by anton on 11/30/2020.
//

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdlib.h>

#include "One.h"
#include "VectorGraph.h"
#include "Kruskal.h"

void VControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	int AC = 0;
	
	
	switch (AC = ArgCheck(Arg)) {
		case 11:
			AOne(entryfp, outputfp, Arg);
			break;
		
		case 12:
			BOne(entryfp, outputfp, Arg);
			break;
		
		case 13:
			COne(entryfp, outputfp, Arg);
			break;
		
		case 14:
			DOne(entryfp, outputfp, Arg);
			break;
		default:
			Arg->err = 1;
			break;
	}
	
	free(Arg);
	return;
}

void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	double sum;
	
	G = VGRead(entryfp, Arg);
	sum = Kruskal(G, NULL, NoBin);
	
	qsort(((struct edge **) G->data)[0], Arg->v - 1,
	      sizeof(struct edge), lessVertice);
	
	if ((sum > 0) && (Arg->err == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);
	
	GFree(G, FreeEdgeV);
	return;
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge *aux, *bindata;
	double sum = 0;
	short int flag = 0;
	int *id;
	
	
	if ((aux = (struct edge *) malloc(sizeof(struct edge))) == NULL) ErrExit(3);
	bindata=CreateEdgeV(Arg->e-Arg->v+1);
	G = VGRead(entryfp, Arg);
	
	sum = Kruskal(G, bindata, Bin);
	emptybin(bindata,G);
	binsearch(id, G, G->Arg->v);
	
	qsort(((struct edge **) G->data)[0], Arg->v - 1, sizeof(struct edge), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,
		        flag);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		if (flag < 0) fprintf(outputfp, "%d %d %lf\n", aux->vi, aux->vj, aux->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	GFree(G, FreeEdgeV);
	return;
}

void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	double sum;
	
	G = VGRead(entryfp, Arg);
	sum = Kruskal(G, NULL, NoBin);
	
	qsort(((struct edge **) G->data)[0], Arg->v - 1,
	      sizeof(struct edge), lessVertice);
	
	if ((sum > 0) && (Arg->err == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);
	
	GFree(G, FreeEdgeV);
	return;
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge /**aux,*/ *bindata;
	double sum = 0;
	short int flag = 0;
	int *id, count=0, RelPos = G->Arg->v;
	
	
	/*if ((aux = (struct edge *) malloc(sizeof(struct edge))) == NULL) ErrExit(3);*/
	bindata=CreateEdgeV(Arg->e-Arg->v+1);

	G = VGRead(entryfp, Arg);
	
	sum = Kruskal(G, bindata, Bin);
	emptybin(bindata,G);


	do
	{
		RelPos = binsearch(id, G, RelPos);
		count++;	/*Numero de arestas (no bin) que repõem a conectividade*/
	} while (RelPos!=-1);

	qsort(((struct edge **) G->data)[0], Arg->v - 1, sizeof(struct edge), lessVertice);
	/*
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,
		        flag);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		if (flag < 0) fprintf(outputfp, "%d %d %lf\n", aux->vi, aux->vj, aux->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	*/
	GFree(G, FreeEdgeV);
	return;
}
