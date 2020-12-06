
#include "One.h"

void VControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	switch (ArgCheck(Arg)) {
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
	sum = Kruskal(g, NULL, NoBin);                                /* find the backbone using Kruskal´s Algorithm */
	
	qsort(g->data, Arg->v - 1, sizeof(struct edge *),
	      lessVertice);  /* Sorting the backbone using the vertice criteria */
	
	if ((sum > 0) && (Arg->err == 0)) {                                      /* Print the graph, if there is no error */
		
		fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);                       /* Print error message */
	
	VGFree(g);                                                                                      /* Free the graph */
	return;
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0;
	int *id = NULL, *sz = NULL, ncpos;
	
	UFinit(Arg->v, id, sz);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	g = VGRead(entryfp, Arg);
	
	sum = Kruskal(g, bindata, Bin); /*initial kruskal*/
	emptybin(bindata, g->data, g->Arg->v, g->Arg->e); /* Dump the bin onto the graph */
	
	if (SearchDelete(g, 0, g->Arg->v - 1, EdgeDelete) != 0) {
		find(g->Arg, g->data, id, sz); /* Restore Connectivity */
		emptybin(bindata, g->data, g->Arg->v, g->Arg->e);
		ncpos = binsearch(id, sz, g, g->Arg->v);
	}
	
	qsort(g->data, Arg->v - 1, sizeof(struct edge *), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %.2lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum, Arg->v - 1,
		        flag);
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		if ((ncpos < Arg->e) && (ncpos >= Arg->v)) {
			fprintf(outputfp, "%d %d %lf", g->data[ncpos]->vi, g->data[ncpos]->vj, g->data[ncpos]->cost);
		}
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	VGFree(g);
	free(id);
	free(sz);
	
	return;
}


void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	struct edge **bindata;
	double sum[2] = {0, 0};
	int *id = NULL, *sz = NULL, ncpos;
	fpos_t args, end;
	
	UFinit(Arg->v, id, sz);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	g = VGRead(entryfp, Arg);
	
	sum[0] = Kruskal(g, bindata, Bin); /*initial kruskal*/
	fgetpos(outputfp, &args);
	fprintf(outputfp, "\n");
	EdgePrint(outputfp, g->data, 0, Arg->v - 1);
	
	if ((ncpos = SearchDelete(g, 0, g->Arg->v - 1, EdgeDelete)) != 0) {
		
		EdgeSwitch(g->data, ncpos, g->Arg->e);
		g->Arg->e--;
		sum[1] = Kruskal(g, bindata, NoBin);
		g->Arg->e++;
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		fgetpos(outputfp, &end);
	}
	
	fsetpos(outputfp, &args);
	if (Arg->err == 0)
		fprintf(outputfp, "%d %d %s %d %lf %d %lf", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum[0],
		        Arg->v - 1, sum[1]);
	else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	fsetpos(outputfp, &end);
	VGFree(g);
	free(id);
	free(sz);
	
	return;
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0, PosSz, ncpos = 0;
	int *id = NULL, *sz = NULL, count = 0, *RelPos = NULL, i;
	
	g = VGRead(entryfp, Arg);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	
	sum = Kruskal(g, bindata, Bin);
	emptybin(bindata, g->data, g->Arg->v, g->Arg->e);
	
	if ((PosSz = (SearchDelete(g, 0, g->Arg->v - 1, VerticeDelete))) != 0) {
		find(g->Arg, g->data, id, sz); /* Restore Connectivity */
		emptybin(bindata, g->data, g->Arg->v, g->Arg->e);
		
		
		if ((RelPos = (int *) malloc((PosSz - 1) * sizeof(int))) == NULL) ErrExit(3);
		RelPos[0] = Arg->v;
		
		do {
			RelPos[count + 1] = binsearch(id, sz, g, RelPos[count]);
			count++;
			/*Numero de arestas (no bin) que repõem a conectividade*/
		} while (count < PosSz);
	}
	
	/* Verify if every element in id[] has same root */
	count = 0;
	PosSz = 0;
	
	for (i = 0; i < Arg->e; i++)  /* Find 1st non error value for root*/
	{
		if (i != RelPos[count]) {
			PosSz = id[i];
			break;
		}
	}
	
	for (i = 0; i < Arg->e; i++) {
		if (i != RelPos[count]) {
			if (id[i] != PosSz) {
				PosSz = -1;
				break;
			}
		} else {
			count++;
		}
	}
	
	if (PosSz == -1) {
		Arg->err = 1;
	}
	
	qsort(g->data, Arg->v - 1, sizeof(struct edge *), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %lf %d %d\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, sum,
		        Arg->v - 1, flag);
		EdgePrint(outputfp, g->data, 0, Arg->v - 1);
		if (flag < 0)
			fprintf(outputfp, "%d %d %lf\n", g->data[ncpos]->vi,
			        g->data[ncpos]->vj, g->data[ncpos]->cost);
		
	} else fprintf(outputfp, "%d %d %s %d %d -1\n", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	free(id);
	free(sz);
	VGFree(g);
	free(RelPos);
	
	return;
}

void EOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	
	
	EOnePrint(outputfp,g,sum,backup)
	return;
}


