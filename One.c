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

void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) { /* CLOSED */
	
	struct graph *g;
	double sum;
	
	g = VGRead(entryfp, Arg);                                                              /* Reading graph from file */
	sum = Kruskal(g, NULL, NoBin);                                     /* find the backbone using Kruskal´s Algorithm */
	
	qsort(((struct edge **) g->data)[0], Arg->v - 1,               /* Sorting the backbone using the vertice criteria */
	      sizeof(struct edge), lessVertice);
	
	if ((sum > 0) && (Arg->err == 0)) {                                      /* Print the graph, if there is no error */
		
		fprintf(outputfp, "%d %d %s %d %lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);                       /* Print error message */
	
	GFree(g, FreeEdgeV);                                                                            /* Free the graph */
	return;
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0;
	int *id,*sz,ncpos;
	
	UFinit(Arg->v,id,sz);
	bindata=CreateEdgeV(Arg->e-Arg->v+1);
	G = VGRead(entryfp, Arg);
	
	sum = Kruskal(G, bindata, Bin); /*initial kruskal*/
	emptybin(bindata, ((struct edge **) G->data), G->Arg->v, G->Arg->e); /* Dump the bin onto the graph */
	SearchDelete(G,0,G->Arg->v-1,EdgeDelete); /* Search for the edge to delete in the backbone */
	find(G->Arg,((struct edge **)G->data),id,sz); /* Restore Connectivity */
	ncpos=binsearch(id, G, G->Arg->v);
	
	flag=flagcheck(ncpos,Arg);
	qsort(((struct edge **) G->data)[0], Arg->v - 1, sizeof(struct edge), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,
		  flag);
		EdgePrint(outputfp, G->data, 0, Arg->v - 1);
		if (flag==1) fprintf(outputfp,"%d %d %lf",((struct edge **)G->data)[ncpos]->vi,
				((struct edge **)G->data)[ncpos]->vj,((struct edge **)G->data)[ncpos]->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	GFree(G, FreeEdgeV);
	free(id);
	free(sz);
	
	return;
}


void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {

	return;
	
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {

	return;
	
}
