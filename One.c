
#include "One.h"
#include "Kruskal.h"

/***********************************************************************************************************************
 * Control of mode 1, which handles all modes that require the use of edge vector as graph representation
 * @param entryfp Input File
 * @param outputfp Output File
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void VControl(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	switch (ArgCheck(Arg)) {   /* Converts Arguments to an integer and switches it */
		case 11:
			AOne(entryfp, outputfp, Arg);   /*Standard Backbone*/
			break;
		case 12:
			BOne(entryfp, outputfp, Arg);   /* Variational Backbone with 1 edge deleted */
			break;
		case 13:
			COne(entryfp, outputfp, Arg);   /* Non-Variational backbone with 1 edge deleted  */
			break;
		case 14:
			DOne(entryfp, outputfp, Arg);   /* Variational backbone with 1 vertice deleted */
			break;
		case 15:
			EOne(entryfp, outputfp, Arg);   /* backbone and backup for each edge */
			break;
		default:
			Arg->err = 1;   /* if no mode is selected, there is an error */
			break;
	}
	
	free(Arg);   /*Free the allocated memory for the problem arguments */
}

/***********************************************************************************************************************
 * Control of Mode A1, which prints the outputs backbone
 * @param entryfp File to read graph from
 * @param outputfp File to output backbone to
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void AOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	double sum = 0;   /* Total cost of the backbone */
	int StopMe;   /* Position where the backbone stops */
	
	g = VGRead(entryfp, Arg);   /* Read the graph from the input file */
	StopMe = Kruskal(g, &sum);   /* Apply kruskal´s Algorithm to get the backbone of the graph */
	
	
	
	if ((sum > 0) && (Arg->err == 0)) { /* Print backbone if no errors were detected during execution */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice); /* Sort the backbone in vertice order */
		fprintf(outputfp, "%d %d %s %d %.2lf\n", Arg->v, Arg->e, Arg->var, Arg->v - 1, sum);
		EdgePrint(outputfp, g->data, 0, StopMe);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);    /* print error message */
	
	VGFree(g);   /* Free the allocated memory for the graph */
}

/***********************************************************************************************************************
 * Control of mode B1, which outputs the backbone without a predefined edge
 * @param entryfp Input File
 * @param outputfp Output File
 * @param Arg Problem Arguments
 **********************************************************************************************************************/
void BOne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g;
	double Sum = 0, NewSum=0;
	int *id = NULL, *sz = NULL, ncpos, StopMe, NewStop;
	
	g = VGRead(entryfp, Arg);   /* Read the Graph from input file */
	StopMe = Kruskal(g, &Sum);   /* Apply Kruskal´s Algorithm to find the original backbone */
	
	if (SearchDelete(g, 0, StopMe, EdgeDelete) != 0) {   /* If the deleted edge belongs to the backbone */
		/* Apply an incomplete version of Kruskal´s to get an edge that replaces the deleted one */
		if ((id = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((sz = (int *) malloc( Arg->v * sizeof(int))) == NULL) ErrExit(3);
		/* In this version, the algorithm is divided so it can output different information */
		NewStop = CWQU(g, &NewSum, id, sz, StopMe);
		
		if (StopMe - NewStop > 1) {   /* Check if there is one edge replacing the deleted, or if more are necessary */
			(Arg->err = 1);
		} else {
			ncpos = binsearch(g->data, id, sz, NewStop, g->Arg->e);   /* Get the position of that edge */
		}
	}
	
	if (Arg->err == 0) {   /* If there were no errors, output the backbone. Else print error message */
		
		qsort(g->data, StopMe, sizeof(struct edge *), lessVertice);
		fprintf(outputfp,"%d %d %s %d %d %.2lf %d %d\n",Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj, Sum, StopMe);
		EdgePrint(outputfp, g->data, 0, StopMe);
		if ((ncpos < Arg->e) && (ncpos >= StopMe)) {
			fprintf(outputfp,"%d %d %lf", g->data[ncpos]->vi, g->data[ncpos]->vj, g->data[ncpos]->cost);
		}
		
	} else fprintf(outputfp,"%d %d %s %d %d -1", Arg->v, Arg->e, Arg->var, Arg->vi, Arg->vj);
	
	VGFree(g); /* Before exiting, free the graph and auxiliary vectors */
	free(id);
	free(sz);
}

void COne(FILE *entryfp, FILE *outputfp, struct PBArg *Arg) {
	
	struct graph *g, *newg;
	double Sum, NewSum;
	int StopMe, NewStop;
	int *id = NULL, *sz = NULL, *newid = NULL, *newsz = NULL;
	bool flag;
	
	g = VGRead(entryfp, Arg);
	
	if ((id = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
	if ((sz = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
	
	qsort(g->data, g->Arg->e, sizeof(struct edge *), lessCost);
	
	StopMe = EdgeSearch(g, 0, Arg->e);
	NewStop = CWQU(g, &Sum, id, sz, StopMe);
	
	if (NewStop < Arg->v) {
		
		if ((newid = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		if ((newsz = (int *) malloc(Arg->v * sizeof(int))) == NULL) ErrExit(3);
		
		vectorcpy(newid, id);
		vectorcpy(newsz, sz);
		
		newg = graphcpy(g);
		
		StopMe = CWQU(g, &Sum, id, sz, Arg->e);
		
		newg->data[NewStop]->cost = -newg->data[NewStop]->cost;
		EdgeBreak(g->data, Arg->e, newid);
		
		NewStop = CWQU(newg, &NewSum, newid, newsz, Arg->e);
		
		newg->data[NewStop]->cost = -newg->data[NewStop]->cost;
		
	} else flag = 1;
	
	if ((Arg->err == 0) && (flag == 0)) {
		
		fprintf(outputfp, "%d %d %s %d %lf %d %lf\n", Arg->v, Arg->e, Arg->var, StopMe, Sum, NewStop, NewSum);
		EdgePrint(outputfp, g->data, 0, g->Arg->v);
		EdgePrint(outputfp, newg->data, 0, newg->Arg->v);
		
	} else if ((Arg->err == 0) && (flag == 1)) {
		
		fprintf(outputfp, "%d %d %s %d %lf -1\n", Arg->v, Arg->e, Arg->var, StopMe, Sum);
		EdgePrint(outputfp, g->data, 0, g->Arg->v);
		
	} else fprintf(outputfp, "%d %d %s -1\n", Arg->v, Arg->e, Arg->var);
	
	VGFree(g);
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


