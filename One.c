//
// Created by anton on 11/30/2020.
//

#include "One.h"

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
	sum = Kruskal(Arg->v, Arg->e, G->data);
	
	qsort(G->data[0], Arg->v - 1, sizeof(struct edge), lessVertice);
	
	if ((sum > 0) && (Arg->err == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp,G->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);
	
	return;
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *G;
	double sum;
	
	G = VGRead(entryfp, Arg);
	sum = Kruskal(Arg->v, Arg->e, G->data, sum);
	
	qsort(G->data[0], Arg->v - 1, sizeof(struct edge), lessVertice);
	
	if ((flag >= 0) && (Arg->err == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %d %d %lf %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,flag);
		EdgePrint(outputfp,G->data, 0, Arg->v - 1);
		/*if (flag!=-1) fprintf(outputfp, "%d %d %lf",TO IMPLEMENT);*/
		
	} else if (Arg->err==0) fprintf(outputfp, "%d %d %s -1", Arg->v,Arg->e,Arg->var);
	
	return;
}
