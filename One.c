
#include "One.h"
#include "Kruskal.h"

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
		case 15:
			EOne(entryfp,outputfp,Arg);
			break;
		default:
			Arg->err = 1;
			break;
	}
	
	free(Arg);
}

void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) { /* CLOSED */
	
	struct graph *g;
	/*
	struct edge** bin=NULL;
	*/
	double sum = 0;
	int StopMe;
	
	g = VGRead(entryfp, Arg);	/* Reading graph from file */
	/*
	BinSize = NmbrUnion(g->data, Arg->v, Arg->e);
	bin = CreateEdgeV(Arg->e - BinSize);
	*/
	StopMe = Kruskal(g, &sum);  /* find the backbone using Kruskal's Algorithm */
	/*emptybin(bin, g->data, StopMe, BinSize);
	emptybin(bin, g->data, 12, 3);*/

	 /* Sorting the backbone using the vertice criteria */
	qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);

	if ((sum > 0) && (Arg->err == 0)) {                                      /* Print the graph, if there is no error */
		
		fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, g->data, 0, StopMe);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);                       /* Print error message */
	
	VGFree(g);                                                                                      /* Free the graph */
}

void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	double Sum = 0, NewSum;
	short int flag = 0, V = Arg->v;
	int *id = NULL, *sz = NULL, ncpos, StopMe, NewStop;

	if ((id = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);
	if ((sz = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);	

	g = VGRead(entryfp, Arg);

	/*OptimizeMe*/	
	/*
	SizeBinData = 5; 	
	SizeBinData = Arg->e - SizeBinData;
	sum = 0;
	
	bindata = CreateEdgeV(SizeBinData);
	*/
	StopMe = Kruskal(g, &Sum); /*initial kruskal*/
	/*
	emptybin(bindata, g->data, g->Arg->v, g->Arg->e);*/ /* Dump the bin onto the graph */
		
	UFinit(V, id, sz);

	if (SearchDelete(g, 0, StopMe, EdgeDelete) != 0) {
		NewStop = CWQU(g, &NewSum, id, sz, StopMe); /* Restore Connectivity */
		/*emptybin(bindata, g->data, StopMe, g->Arg->e);*/

		if (StopMe - NewStop > 1) /* Seria necessário mais do  1 aresta */
		{						  /* para repor a conectividade */
			Arg->err = 1;
		} else {
			ncpos = binsearch(g->data, id, sz, StopMe, g->Arg->e);
		}
	}
	

	qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
	
	if (Arg->err == 0) {
		
		fprintf(outputfp, "%d %d %s %d %d %.2lf %d %d\n",
				Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, Sum, StopMe, flag);
		EdgePrint(outputfp, g->data, 0, StopMe);
		if ((ncpos < Arg->e) && (ncpos >= StopMe)) {
			fprintf(outputfp, "%d %d %lf", g->data[ncpos]->vi, g->data[ncpos]->vj, g->data[ncpos]->cost);
		}
	} else fprintf(outputfp, "%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	VGFree(g);
	free(id);
	free(sz);
}


void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) 
{		
	struct graph *g;
	double Sum, NewSum;
	int StopMe, NewStop, V = Arg->v;
	int *id = NULL, *sz = NULL, ncpos;
	fpos_t args, end;

	if ((id = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);
	if ((sz = (int *) malloc(V * sizeof(int)))==NULL) ErrExit(3);	
	
	g = VGRead(entryfp, Arg);

	UFinit(Arg->v, id, sz);

	StopMe = Kruskal(g, &Sum); /*initial kruskal*/

	fgetpos(outputfp, &args);  /* Get */
	fprintf(outputfp, "\n");
	
	fgetpos(stdout, &args);  /* Get */
	fprintf(stdout, "\n");

	qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);

	EdgePrint(outputfp, g->data, 0, StopMe);
	fprintf(outputfp,"\n");

	EdgePrint(stdout, g->data, 0, StopMe);
	fprintf(stdout,"\n");

	if ((ncpos = SearchOverflow(g, Sum, 0, StopMe, EdgeDelete)) != 0) {
		/*	
		EdgeSwitch(g->data, ncpos, g->Arg->e);
		g->Arg->e--;
		*/
		NewStop = Kruskal(g, &NewSum);
		/*
		g->Arg->e++;
		*/
		EdgePrint(outputfp, g->data, 0, NewStop);
		fprintf(outputfp,"\n");

		EdgePrint(stdout, g->data, 0, NewStop);
		fprintf(stdout,"\n");

	} else {
		Arg->err = 1;
	}
	
	fgetpos(outputfp, &end);  /* Get */

	fsetpos(outputfp, &args);  /* Set */

	fgetpos(stdout, &end);  /* Get */

	fsetpos(stdout, &args);  /* Set */

	if (Arg->err == 0){
		fprintf(outputfp, "%d %d %s %d %lf %d %lf\n", 
				Arg->v, Arg->e, Arg->var, StopMe, Sum, NewStop, NewSum);
	
		fprintf(stdout, "%d %d %s %d %lf %d %lf\n", 
				Arg->v, Arg->e, Arg->var, StopMe, Sum, NewStop, NewSum);

	} else {
		fprintf(outputfp, "%d %d %s %d %d -1\n", 
				Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);

		fprintf(stdout, "%d %d %s %d %d -1\n", 
				Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);

	}
		
	fsetpos(outputfp, &end);  /* Set */

	fsetpos(stdout, &end);  /* Set */

	VGFree(g);
	free(id);
	free(sz);
}

void DOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
#if 0	
	struct graph *g;
	struct edge **bindata;
	double sum = 0;
	short int flag = 0,  ncpos = 0;
	int *id = NULL, *sz = NULL,PosSz, count = 0, *RelPos = NULL, i;
	
	g = VGRead(entryfp, Arg);
	bindata = CreateEdgeV(Arg->e - Arg->v + 1);
	
	sum = Kruskal(g, bindata, Bin);
	emptybin(bindata, g->data, g->Arg->v, g->Arg->e);
	
	if ((PosSz = SearchDelete(g, 0, g->Arg->v - 1, VerticeDelete)) != 0) {
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
#endif
}

void EOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
#if 0	
	struct graph *g;
	struct edge **bindata;
	double sum;
	int i,*backup,*id,*sz;
	
	g=VGRead(entryfp,Arg);
	
	bindata=CreateEdgeV(Arg->e-Arg->v+1);
	if ((backup=malloc(Arg->v*sizeof(int)))==NULL) ErrExit(3);
	if ((id=malloc(Arg->v*sizeof(int)))==NULL) ErrExit(3);
	if ((sz=malloc(Arg->v*sizeof(int)))==NULL) ErrExit(3);
	
	for(i=0;i<Arg->v;i++){
		qsort(g->data, g->Arg->e, sizeof(struct edge*), lessCost);
		
		g->data[i]->cost = -g->data[i]->cost;
		g->Arg->vi=g->data[i]->vi;
		g->Arg->vj=g->data[i]->vj;
		
		find(g->Arg,g->data,id,sz);
		backup[i]=binsearch(id,sz,g,g->Arg->e);
		SearchDelete(g,0,Arg->v,EdgeDelete);
	}
	
	sum=Kruskal(g,bindata,Bin);
	emptybin(bindata,g->data,g->Arg->v,g->Arg->e);
	
	
	EOnePrint(outputfp,g,sum,backup);
#endif
}


